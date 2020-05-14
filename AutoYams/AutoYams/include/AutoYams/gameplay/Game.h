#pragma once
#include <QObject>
#include <AutoYams\gameplay\Dice.h>
#include <AutoYams\gameplay\Player.h>
#include <AutoYams\gameplay\Scoring.h>
#include <AutoYams\core\exception\AdvancedException.h>

class Game : public QObject
{
	Q_OBJECT

private:
	int turn, currentPlayerIndex, currentPlayerThrow;
	QList<Player*> players;
	QList<Dice*> dices;
	Scoring scoreSystem;

public:
	Game(QStringList players);
	~Game();

	void roll();

	Dice* getDice(int index);
	Player* getCurrentPlayer() const;
	int getCurrentThrow() const;
	int getCurrentTurn() const;

	bool Play(QString name);
	bool isEnd() const;
	bool isLastTurn() const;

	void NextThrow();
	void NextPlayer();
	void NextTurn();

	QList<QPair<int, PlayableMove*>> bestCurrentPlayerMoves();
	int currentScoreOf(QString move);

	void setDices(QList<int> dices);
	Player* winningPlayer() const;

signals:
	void thrown();
	void newPlayer(int);
	void newTurn(int);
	void end();

public slots:
	void clickDice(int);
};