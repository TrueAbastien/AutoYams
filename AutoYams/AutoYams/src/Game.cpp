#include <AutoYams\gameplay\Game.h>
#include <QTime>

Game::Game(QStringList _players)
	: turn(0), currentPlayerIndex(0), currentPlayerThrow(0)
{
	// Create Players and Dices
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
	foreach(QString name, _players)
		players.push_back(new Player(name));
	for (int ii = 0; ii < 5; ++ii)
		dices.push_back(new Dice());

	// First Score Methods
	scoreSystem.addCombo("Total1", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			if (dice->getValue() == 1)
				result += 1;
		return result;
	});
	scoreSystem.addCombo("Total2", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			if (dice->getValue() == 2)
				result += 2;
		return result;
	});
	scoreSystem.addCombo("Total3", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			if (dice->getValue() == 3)
				result += 3;
		return result;
	});
	scoreSystem.addCombo("Total4", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			if (dice->getValue() == 4)
				result += 4;
		return result;
	});
	scoreSystem.addCombo("Total5", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			if (dice->getValue() == 5)
				result += 5;
		return result;
	});
	scoreSystem.addCombo("Total6", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			if (dice->getValue() == 6)
				result += 6;
		return result;
	});

	// Second Score Methods
	scoreSystem.addCombo("Brelan", [](QList<Dice*> d) -> int {
		int result = 0, count;
		for (int ii = 1; ii <= 6; ++ii)
		{
			count = 0;
			foreach(Dice* dice, d)
			{
				if (dice->getValue() == ii)
					count++;
			}
			if (count >= 3)
			{
				foreach(Dice* dice, d)
					result += dice->getValue();
				return result;
			}
		}
		return 0;
	});
	scoreSystem.addCombo("Carre", [](QList<Dice*> d) -> int {
		int result = 0, count;
		for (int ii = 1; ii <= 6; ++ii)
		{
			count = 0;
			foreach(Dice* dice, d)
			{
				if (dice->getValue() == ii)
					count++;
			}
			if (count >= 4)
			{
				foreach(Dice* dice, d)
					result += dice->getValue();
				return result;
			}
		}
		return 0;
	});
	scoreSystem.addCombo("Full", [](QList<Dice*> d) -> int {
		int result = 0, count1, count2;
		for (int ii = 1; ii < 6; ++ii)
		{
			for (int jj = ii + 1; jj <= 6; ++jj)
			{
				count1 = 0; count2 = 0;
				foreach(Dice* dice, d)
				{
					if (dice->getValue() == ii) count1++;
					if (dice->getValue() == jj) count2++;
				}
				if (count1 + count2 == 5 &&
					(count1 == 3 || count2 == 3))
					return 25;
			}
		}
		return 0;
	});
	scoreSystem.addCombo("PetiteSuite", [](QList<Dice*> d) -> int {
		int counts[] = { 0,0,0,0,0,0 }, count = 0;
		foreach(Dice* dice, d)
			counts[dice->getValue() - 1]++;
		for (int c : counts)
		{
			if (c > 0)
			{
				if (++count >= 4)
					return 30;
			}
			else count = 0;
		}
		return 0;
	});
	scoreSystem.addCombo("GrandeSuite", [](QList<Dice*> d) -> int {
		int counts[] = { 0,0,0,0,0,0 }, count = 0;
		foreach(Dice* dice, d)
			counts[dice->getValue() - 1]++;
		for (int c : counts)
		{
			if (c > 0)
			{
				if (++count >= 5)
					return 40;
			}
			else count = 0;
		}
		return 0;
	});
	scoreSystem.addCombo("Yams", [](QList<Dice*> d) -> int {
		int result = 0, count;
		for (int ii = 1; ii <= 6; ++ii)
		{
			count = 0;
			foreach(Dice* dice, d)
			{
				if (dice->getValue() == ii)
					count++;
			}
			if (count >= 5)
				return 50;
		}
		return 0;
	});
	scoreSystem.addCombo("Chance", [](QList<Dice*> d) -> int {
		int result = 0;
		foreach(Dice* dice, d)
			result += dice->getValue();
		return result;
	});

	//auto res = bestCurrentPlayerMoves(); //DEBUG
}


Game::~Game()
{
	for (auto& d : dices)
		delete d;
	for (auto& p : players)
		delete p;
}

Dice* Game::getDice(int index)
{
	if (index >= 5) index = 4;
	else if (index < 0) index = 0;
	return dices[index];
}

Player* Game::getCurrentPlayer() const
{
	return players[currentPlayerIndex];
}

int Game::getCurrentThrow() const
{
	return currentPlayerThrow;
}

int Game::getCurrentTurn() const
{
	return turn;
}

bool Game::Play(QString name)
{
	return scoreSystem.play(players[currentPlayerIndex], dices, name);
}

bool Game::isEnd() const
{
	return turn >= 10;
	//return turn >= 2;
}

void Game::NextThrow()
{
	if (isEnd()) return;
	if (currentPlayerThrow < 3)
	{
		currentPlayerThrow++;
		emit thrown();
	}
	//throw GameException("You cannot throw again !");
}

void Game::NextPlayer()
{
	if (isEnd()) return;
	foreach(Dice* d, dices)
		if (!d->isSelected())
			d->switchSelect();
	currentPlayerThrow = 0;
	if (++currentPlayerIndex >= players.length())
		NextTurn();
	emit newPlayer(currentPlayerIndex);
}

void Game::NextTurn()
{
	if (!isEnd())
	{
		turn++;
		currentPlayerIndex = 0;
		emit newTurn(turn);
	}

	if (isEnd())
		emit end();
}

QList<QPair<int, PlayableMove*>> Game::bestCurrentPlayerMoves()
{
	return scoreSystem.sampleBestMoves(getCurrentPlayer(), dices);
}

int Game::currentScoreOf(QString move)
{
	return scoreSystem.sampleMove(dices, move);
}

void Game::setDices(QList<int> _dices)
{
	if (_dices.size() == dices.size())
		for (int ii = 0; ii < 5; ++ii)
			dices[ii]->setValue(_dices[ii]);
	else throw GameException("There's not enough dices !");
}

Player * Game::winningPlayer() const
{
	Player* savedPlayer = nullptr;
	int maxScore = 0;
	for (Player* player : players)
		if (player->getScore() > maxScore)
		{
			maxScore = player->getScore();
			savedPlayer = player;
		}
	return savedPlayer;
}

bool Game::isLastTurn() const
{
	return currentPlayerThrow >= 3;
}

void Game::clickDice(int index)
{
	getDice(index)->switchSelect();
}

void Game::roll()
{
	for (Dice* d : dices)
		d->roll();
}
