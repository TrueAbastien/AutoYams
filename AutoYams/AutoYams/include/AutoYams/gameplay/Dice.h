#pragma once
#include <QGlobal.h>

class Dice
{
private:
	int currentValue = 0;
	bool selected = true;

public:
	void roll();
	int getValue() const;
	void setValue(int val);
	void switchSelect();
	bool isSelected() const;
};