#include <AutoYams\gameplay\PlayableMove.h>

PlayableMove::PlayableMove(QString name, std::function<int(QList<Dice*>)> move)
	: moveName(name), averageResult(0), computeMove(move)
{
	QList<Dice*> __dices;
	for (int ii = 0; ii < 5; ++ii)
		__dices.append(new Dice());

	for (int d1 = 1; d1 <= 6; ++d1)
		for (int d2 = d1; d2 <= 6; ++d2)
			for (int d3 = d2; d3 <= 6; ++d3)
				for (int d4 = d3; d4 <= 6; ++d4)
					for (int d5 = d4; d5 <= 6; ++d5)
					{
						__dices[0]->setValue(d1);
						__dices[1]->setValue(d2);
						__dices[2]->setValue(d3);
						__dices[3]->setValue(d4);
						__dices[4]->setValue(d5);

						averageResult += move(__dices);
					}

	averageResult /= 3'891;
	for (int jj = 0; jj < 5; ++jj)
		delete __dices[jj];
}

int PlayableMove::get(QList<Dice*> dices) const
{
	return computeMove(dices);
}

double PlayableMove::factorFrom(int result) const
{
	return (double)(result) / averageResult;
}

double PlayableMove::factor(QList<Dice*> dices) const
{
	return factorFrom(computeMove(dices));
}

QString PlayableMove::getName() const
{
	return moveName;
}
