#pragma once
#include <functional>
#include <AutoYams\gameplay\Dice.h>
#include <QList>
#include <QString>

class PlayableMove
{
private:
	double averageResult;
	QString moveName;
	std::function<int(QList<Dice*>)> computeMove;

public:
	PlayableMove(QString name, std::function<int(QList<Dice*>)> move);

	int get(QList<Dice*> dices) const;
	double factorFrom(int result) const;
	double factor(QList<Dice*> dices) const;

	QString getName() const;
};