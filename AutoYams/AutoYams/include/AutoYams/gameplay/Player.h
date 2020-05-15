#pragma once
#include <AutoYams\gameplay\Score.h>

/**
* \class Player
* \brief Player game object used as a representation of every user
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Only used to store data, almost no computation is done here.
*/
class Player
{
public:
	/**
	* Structure ScoreData.
	* Contains every total score related data to display in grid.
	*/
	struct ScoreData
	{
		int firstScore = 0, firstTotal = 0,
			secondScore = 0, lastTotal = 0;
		bool bonusEligeable = false;
	};

private:
	/**
	* Name of the player.
	*/
	QString name;
	/**
	* First set of score: basic moveset (sums).
	*/
	Score firstScore;
	/**
	* Second set of score: special moveset.
	*/
	Score secondScore;

public:
	/**
	* \brief Default constructor
	* \param name Name of the current player
	*
	* Initialise he player name and every other propreties.
	*/
	Player(QString name);
	/**
	* \brief Access the player current name
	* \return Accessed value for the current name
	*
	* Simple getter for the player current name.
	*/
	QString getName() const;
	/**
	* \brief Access the player total score
	* \return Accessed value for the current total score
	*
	* Compute score by adding the bonus when requiered
	* for the first score and simply adding the second.
	*/
	int getScore() const;

	/**
	* \brief Add points to the first score
	* \param name Name of the specific move to play
	* \param amount Points to set for the move
	* \return Verification of score setting
	*
	* Set score of a specific move and return the result on first Score set.
	*/
	bool addFirstScore(QString name, int amount);
	/**
	* \brief Add points to the second score
	* \param name Name of the specific move to play
	* \param amount Points to set for the move
	* \return Verification of score setting
	*
	* Set score of a specific move and return the result on second Score set.
	*/
	bool addSecondScore(QString name, int amount);
	/**
	* \brief Verify is a specified move has ever been played
	* \param name Name of the specific move
	* \return Result of the verification
	*
	* Search through first and second Score for the move name to check
	* if it already has been played (if the amount of points is positive).
	*/
	bool hasPlayed(QString name);

	/**
	* Current score data.
	*/
	ScoreData score;
	/**
	* \brief Process current score data.
	*
	* Compute every totals and store them in the current score data.
	*/
	void processScoreData();
};