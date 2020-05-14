#include <AutoYams\gameplay\Dice.h>

#include <AutoYams\FileDebug.h> //DEBUG

void Dice::roll()
{
	if (selected)
		currentValue = qrand() % 6 + 1;
	//FileDebug::write(QString::number(currentValue)); //DEBUG
}

int Dice::getValue() const
{
	return currentValue;
}

void Dice::setValue(int val)
{
	if (val <= 6 && val >= 1)
		currentValue = val;
}

void Dice::switchSelect()
{
	selected = !selected;
}

bool Dice::isSelected() const
{
	return selected;
}
