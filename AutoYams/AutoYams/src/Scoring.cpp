#include <AutoYams\gameplay\Scoring.h>
#include <algorithm>

bool Scoring::addCombo(QString name, std::function<int(QList<Dice*>)> combo)
{
	if (playCombos.contains(name))
		return false;
	playCombos.insert(name, new PlayableMove(name, combo));
	return true;
}

bool Scoring::play(Player * player, QList<Dice*> dices, QString name)
{
	if (playCombos.contains(name))
	{
		int res = playCombos[name]->get(dices);
		if (!player->addFirstScore(name, res))
			if (!player->addSecondScore(name, res))
				return false;
	}
	else return false;
	return true;
}

QList<QPair<int, PlayableMove*>> Scoring::sampleBestMoves(Player* player, QList<Dice*> dices)
{
	QList<QPair<int, PlayableMove*>> res;
	foreach(QString key, playCombos.keys())
		if (!player->hasPlayed(key))
			res.append({ playCombos[key]->get(dices), playCombos[key] });
	std::sort(res.begin(), res.end(), [](QPair<int, PlayableMove*> a, QPair<int, PlayableMove*> b)
	{
		return a.second->factorFrom(a.first) > b.second->factorFrom(b.first);
	});
	return res;
}

int Scoring::sampleMove(QList<Dice*> dices, QString name) const
{
	if (playCombos.contains(name))
		return playCombos[name]->get(dices);
	return -1;
}
