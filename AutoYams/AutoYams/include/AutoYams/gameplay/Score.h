#pragma once
#include <QMap>

/**
* \class Score
* \brief Score container object for a player
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Contain every score points for every possible moves.
*/
class Score
{
private:
	/**
	* Map of every possible move name and its current score.
	* The default amount of point is -1 while the minimal played value is 0.
	*/
	QMap<QString, int> equivalences;

public:
	/**
	* \brief Add a new move to the mapped combos
	* \param key Name of the new move
	* \return Verify if the new move has been mapped
	*
	* Add a single move to the equivalences if possible.
	*/
	bool add(QString key);
	/**
	* \brief Add multiples new moves to the mapped combos
	* \param keys Name of the new moves
	* \return Verify if every new moves have been mapped
	*
	* Add multiple move to the equivalences when possible.
	*/
	bool add(QStringList keys);
	/**
	* \brief Change value of a specified move when unplayed
	* \param key Name of the specific move
	* \param val New score for this specific move
	* \return Verify if the move exist and could have been changed
	*
	* Change the value of a specific move, in the mapped member, when possible.
	*/
	bool set(QString key, int val);
	/**
	* \brief Compute the full score
	* \return Result of the computation
	*
	* Compute the sum of every played move (above 0).
	*/
	int get() const;
	/**
	* \brief Compute the full score with an added constant bonus
	* \param bonus Constant bonus to add
	* \param minimum Minimum total score requiered to be rewarded with the bonus
	* \return Result of the computation
	*
	* Compute the sum of every played move (above 0)
	* and apply bonus if the sum is above the specified minimum.
	*/
	int get(int bonus, int minimum) const;
};