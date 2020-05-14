#include <AutoYams\gameplay\Score.h>

bool Score::add(QString key)
{
	if (equivalences.contains(key))
		return false;
	equivalences.insert(key, -1);
	return true;
}

bool Score::add(QStringList keys)
{
	bool res = true;
	foreach(QString key, keys)
		if (!add(key))
			res = false;
	return res;
}

bool Score::set(QString key, int val)
{
	if (!equivalences.contains(key))
		return false;
	else if (equivalences[key] >= 0)
		return false;
	equivalences[key] = val;
	return true;
}

int Score::get() const
{
	int result = 0;
	foreach(int val, equivalences.values())
		if (val > 0)
			result += val;
	return result;
}

int Score::get(int bonus, int minimum) const
{
	int res = get();
	return res + (res > minimum ? bonus : 0);
}
