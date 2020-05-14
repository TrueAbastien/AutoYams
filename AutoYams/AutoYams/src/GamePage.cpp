#include <AutoYams\core\page\main\GamePage.h>
#include <QFile>

#include <AutoYams\FileDebug.h> // DEBUG

GamePage::GamePage(AutoYams* ref)
	: Page(1, ref)
{
	// Save Current Row Count
	scoreTableRowCount = app->ui.game_scoreTable->rowCount();

	// Setup Dice File Cache
	for (int ii = 0; ii <= 6; ++ii)
	{
		QImage img("Resources/img/dices/00" + QString::number(ii) + ".png");
		dicePictures.insert(ii, QPixmap::fromImage(img));
	}
	diceIcons.insert(0, app->ui.game_dice_1);
	diceIcons.insert(1, app->ui.game_dice_2);
	diceIcons.insert(2, app->ui.game_dice_3);
	diceIcons.insert(3, app->ui.game_dice_4);
	diceIcons.insert(4, app->ui.game_dice_5);

	// Setup Move Index onto Grid
	moveGridIndex.insert("Total1", 1);
	moveGridIndex.insert("Total2", 2);
	moveGridIndex.insert("Total3", 3);
	moveGridIndex.insert("Total4", 4);
	moveGridIndex.insert("Total5", 5);
	moveGridIndex.insert("Total6", 6);
	// --- //
	moveGridIndex.insert("Brelan", 11);
	moveGridIndex.insert("Carre", 12);
	moveGridIndex.insert("Full", 13);
	moveGridIndex.insert("PetiteSuite", 14);
	moveGridIndex.insert("GrandeSuite", 15);
	moveGridIndex.insert("Yams", 16);
	moveGridIndex.insert("Chance", 17);

	// Setup Input Method
	inputMethodGroup = new QActionGroup(app);
	inputMethodGroup->addAction(app->ui.actionAuto);
	inputMethodGroup->addAction(app->ui.actionSemi);
	inputMethodGroup->addAction(app->ui.actionManual);
	connect(app->ui.actionAuto, &QAction::toggled, [this]() { if (app->ui.actionAuto->isChecked()) changeInputMethod(PlayMethod::AUTO); });
	connect(app->ui.actionSemi, &QAction::toggled, [this]() { if (app->ui.actionSemi->isChecked()) changeInputMethod(PlayMethod::SEMI); });
	connect(app->ui.actionManual, &QAction::toggled, [this]() { if (app->ui.actionManual->isChecked()) changeInputMethod(PlayMethod::MANUAL); });
	app->ui.actionAuto->setChecked(true);

	// Connect Restart
	connect(app->ui.actionRestart, &QAction::triggered, [this]()
	{
		reset();
		app->ui.pagination->setCurrentIndex(0);
	});
}

int GamePage::addRow(unsigned int amount)
{
	int res = app->ui.game_scoreTable->columnCount();
	app->ui.game_scoreTable->setColumnCount(amount + res);
	
	for (int row = 0; row < scoreTableRowCount; ++row)
	{
		QTableWidgetItem* original = app->ui.game_scoreTable->item(row, 0);
		for (int col = 0; col < amount; ++col)
		{
			app->ui.game_scoreTable->setItem(row, res + col, original->clone());
			app->ui.game_scoreTable->item(row, res + col)->setText("");
		}
	}

	return res;
}

void GamePage::resetDices()
{
	const int width = diceIcons[0]->width(), height = diceIcons[0]->height();
	for (int ii = 0; ii < 5; ++ii)
		diceIcons[ii]->setPixmap(dicePictures[0].scaled(width, height, Qt::KeepAspectRatio));
}

void GamePage::handle()
{
	// Add Players
	const int size = app->ui.menu_playerList->count();
	for (int ii = 0; ii < size; ++ii)
		addPlayer(app->ui.menu_playerList->item(ii)->text());

	// Setup Game
	game = new Game(playerIndex.keys());
	resetDices();

	connect(app->ui.game_nextThrow, SIGNAL(pressed()), this, SLOT(playerThrow()));
	connect(app->ui.game_nextPlayer, SIGNAL(pressed()), this, SLOT(playerAccept()));
	connect(game, SIGNAL(end()), this, SLOT(endGame()));
	app->event_diceThrown->setReceiver(this);
	
	// First Draw
	GraphicLabelUpdate(game->getCurrentTurn() + 1, game->getCurrentPlayer()->getName(), 0);
}

bool GamePage::setContent(int row, QString player, QString content)
{
	QTableWidgetItem* field = app->ui.game_scoreTable->item(row, playerIndex.value(player));
	if (field == nullptr)
		return false;

	field->setText(content);
	return true;
}

void GamePage::reset()
{
	app->ui.game_scoreTable->setColumnCount(1);
	playerIndex.clear();
}

void GamePage::addPlayer(QString name)
{
	int col = addRow();
	playerIndex.insert(name, col);
	setContent(0, name, name);
}

void GamePage::playerThrow()
{
	if (game->isEnd()) return;

	if (inputMethod == PlayMethod::MANUAL)
	{
		if (!game->isLastTurn())
		{
			game->roll();
			GraphicThrowUpdate();
		}
		game->NextThrow();
	}

	if (inputMethod == PlayMethod::SEMI && semi_hasBeenThrown)
	{
		game->NextThrow();
		GraphicThrowUpdate();
		changeSemiToggle(false);
	}
}

void GamePage::playerAccept()
{
	if (game->isEnd()) return;

	if (game->Play(app->ui.game_moveCB->currentText()))
	{
		GraphicPickUpdate(app->ui.game_moveCB->currentText());
		game->NextPlayer();
		GraphicLabelUpdate(game->getCurrentTurn() + 1, game->getCurrentPlayer()->getName(), 0);
		changeSemiToggle(false);
	}
}

void GamePage::endGame()
{
	Player* winner = game->winningPlayer();
	if (QMessageBox::information(app, "Game Over", winner->getName() + " won with " + QString::number(winner->getScore()) + " points !",
		QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel) == QMessageBox::StandardButton::Ok)
	{
		reset();
		app->ui.pagination->setCurrentIndex(0);
	}
}

void GamePage::changeInputMethod(PlayMethod method)
{
	inputMethod = method;
	app->ui.game_nextThrow->setEnabled(method != PlayMethod::AUTO);
	changeSemiToggle(false);
}

void GamePage::changeSemiToggle(bool state)
{
	if (inputMethod == PlayMethod::SEMI)
	{
		semi_hasBeenThrown = state;
		app->ui.game_nextThrow->setEnabled(state);
	}
}

void GamePage::AutomaticDiceThrown(QList<int>& dices)
{
	if ((semi_hasBeenThrown && inputMethod == PlayMethod::SEMI)
		|| game->isEnd())
		return;

	if (inputMethod != PlayMethod::MANUAL)
	{
		if (!game->isLastTurn())
		{
			game->setDices(dices);
			GraphicThrowUpdate();
		}

		if (inputMethod == PlayMethod::AUTO)
			game->NextThrow();
		else changeSemiToggle(true);
	}
}

void GamePage::GraphicThrowUpdate()
{
	// Update Dices
	const int width = diceIcons[0]->width(), height = diceIcons[0]->height();
	for (int ii = 0; ii < 5; ++ii)
		diceIcons[ii]->setPixmap(dicePictures[game->getDice(ii)->getValue()].scaled(width, height, Qt::KeepAspectRatio));

	// Update 3 Best Moves
	app->ui.game_bestMoves->clear();
	auto bestMoves = game->bestCurrentPlayerMoves();
	for (int ii = 0; ii < 3; ++ii)
		app->ui.game_bestMoves->addItem(bestMoves[ii].second->getName() + " (" + QString::number(bestMoves[ii].first) + ")");

	// Update All Possible Moves
	app->ui.game_moveCB->clear();
	foreach(auto& ele, bestMoves)
		app->ui.game_moveCB->addItem(ele.second->getName());

	// Update Label(s)
	GraphicLabelUpdate(game->getCurrentTurn() + 1, game->getCurrentPlayer()->getName(), game->getCurrentThrow() + 1);
}

void GamePage::GraphicPickUpdate(QString move)
{
	// Update Move onto Grid
	setContent(moveGridIndex[move], game->getCurrentPlayer()->getName(), QString::number(game->currentScoreOf(move)));
	
	// Update Totals onto Grid
	game->getCurrentPlayer()->processScoreData();
	GraphicTotalUpdate(game->getCurrentPlayer()->getName(), game->getCurrentPlayer()->score);

	// Update Label(s)
	GraphicLabelUpdate(game->getCurrentTurn() + 1, game->getCurrentPlayer()->getName(), game->getCurrentThrow() + 1);

	// Update Dices
	resetDices();

	// Clear Moves
	app->ui.game_bestMoves->clear();
	app->ui.game_moveCB->clear();
}

void GamePage::GraphicLabelUpdate(int turn, QString player, int nThrow)
{
	app->ui.game_currentPlayer->setText("Player: " + player);
	app->ui.game_currentTurn->setText("Turn: " + QString::number(turn));
	app->ui.game_currentThrow->setText("Throw: " + QString::number(nThrow));
}

void GamePage::GraphicTotalUpdate(QString name, Player::ScoreData data)
{
	setContent(7, name, QString::number(data.firstScore));
	setContent(8, name, data.bonusEligeable ? "X" : "");
	setContent(9, name, QString::number(data.firstTotal));
	setContent(18, name, QString::number(data.secondScore));
	setContent(19, name, QString::number(data.lastTotal));
}
