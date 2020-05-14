#pragma once
#include <QMap>

class Score
{
private:
	QMap<QString, int> equivalences;

public:
	bool add(QString key);
	bool add(QStringList keys);
	bool set(QString key, int val);
	int get() const;
	int get(int bonus, int minimum) const;
};