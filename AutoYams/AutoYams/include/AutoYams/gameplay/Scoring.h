#pragma once
#include <AutoYams\gameplay\Player.h>
#include <AutoYams\gameplay\PlayableMove.h>

class Scoring
{
private:
	QMap<QString, PlayableMove*> playCombos;

public:
	bool addCombo(QString name, std::function<int(QList<Dice*>)> combo);
	bool play(Player* player, QList<Dice*> dices, QString name);
	QList<QPair<int, PlayableMove*>> sampleBestMoves(Player* player, QList<Dice*> dices);
	int sampleMove(QList<Dice*> dices, QString name) const;
};