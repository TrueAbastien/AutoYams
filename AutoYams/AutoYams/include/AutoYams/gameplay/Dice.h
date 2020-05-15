#pragma once
#include <QGlobal.h>

/**
* \class Dice
* \brief Dice game object
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Store dice data and allow it to be changed or accessed.
*/
class Dice
{
private:
	/**
	* Current stored value of the dice displayed number.
	*/
	int currentValue = 0;
	/**
	* Switch verifying if the dice is selected or not and if it should be affected by roll(s).
	*/
	bool selected = true;

public:
	/**
	* \brief Roll current dice value
	*
	* Randomly change current dice value if selected.
	*/
	void roll();
	/**
	* \brief Access current dice value
	* \return Current dice value
	*
	* Its just a getter... nothing fancy.
	*/
	int getValue() const;
	/**
	* \brief Change current dice value
	* \param val New dice value
	*
	* Overwrite current dice value for automatic dice detection.
	*/
	void setValue(int val);
	/**
	* \brief Change dice selection
	*
	* Switch dice selection boolean to selected or unselected.
	*/
	void switchSelect();
	/**
	* \brief Verify if dice is selected
	* \return Result of the verification
	*
	* Access and return selection boolean in propreties.
	*/
	bool isSelected() const;
};