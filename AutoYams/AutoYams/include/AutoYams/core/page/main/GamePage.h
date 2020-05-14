#pragma once
#include <QMap>
#include <QPixmap>
#include <QList>
#include <QActionGroup>
#include <AutoYams\core\page\Page.h>
#include <AutoYams\gameplay\Game.h>

class GamePage : public Page
{
	Q_OBJECT
public:
	enum PlayMethod { AUTO, SEMI, MANUAL };

public:
	explicit GamePage(AutoYams* ref = 0);

	void handle() override;

	bool setContent(int row, QString player, QString content);
	void reset();

private:
	PlayMethod inputMethod = PlayMethod::AUTO;

	int scoreTableRowCount;
	QMap<QString, int> moveGridIndex, playerIndex;

	Game* game = nullptr;
	QMap<int, QPixmap> dicePictures;
	QMap<int, QLabel*> diceIcons;

	QActionGroup* inputMethodGroup;
	bool semi_hasBeenThrown;

	int addRow(unsigned int amount = 1);

private slots:
	void addPlayer(QString);
	void resetDices();

	void playerThrow();
	void playerAccept();
	void endGame();

	void changeInputMethod(PlayMethod);
	void changeSemiToggle(bool);

public slots:
	void AutomaticDiceThrown(QList<int>&);
	void GraphicThrowUpdate();
	void GraphicPickUpdate(QString);
	void GraphicLabelUpdate(int, QString, int);
	void GraphicTotalUpdate(QString, Player::ScoreData);
};
