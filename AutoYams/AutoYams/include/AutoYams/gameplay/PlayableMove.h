#pragma once
#include <functional>
#include <AutoYams\gameplay\Dice.h>
#include <QList>
#include <QString>

/**
* \class PlayableMove
* \brief Game object storing data for a specific move
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Allow us to compute the average amount of points in
* every possible dice disposition and std::sort it afterwards.
*/
class PlayableMove
{
private:
	/**
	* Computed average result of every possible dice set.
	*/
	double averageResult;
	/**
	* Name of the move.
	*/
	QString moveName;
	/**
	* Delegated function to compute the move score.
	*/
	std::function<int(QList<Dice*>)> computeMove;

public:
	/**
	* \brief Default constructor
	* \param name Name of the move
	* \param move Delegated function store and use to compute score
	*
	* Simply copy every given arguments, then run
	* through every possible dice set to compute the average result.
	*/
	PlayableMove(QString name, std::function<int(QList<Dice*>)> move);

	/**
	* \brief Compute the delegated function to compute move
	* \param dices Set of dice to compute the function with
	* \return Result of the computation
	*
	* Broadly used for scoring purpose.
	*/
	int get(QList<Dice*> dices) const;
	/**
	* \brief Get factor from specified result
	* \param result Specific result
	* \return Computed factor
	*
	* Compute factor by dividing the specified result by its average.
	*/
	double factorFrom(int result) const;
	/**
	* \brief Get factor from a set of dice
	* \param dices Specific set of dice
	* \return Computed factor
	*
	* Compute factor by dividing the result of the dice
	* set function computation by its average.
	*/
	double factor(QList<Dice*> dices) const;

	/**
	* \brief Access the move name
	* \return Accessed value
	*
	* Simple getter for the move name.
	*/
	QString getName() const;
};