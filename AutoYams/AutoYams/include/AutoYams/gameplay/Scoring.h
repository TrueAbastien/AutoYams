#pragma once
#include <AutoYams\gameplay\Player.h>
#include <AutoYams\gameplay\PlayableMove.h>

/**
* \class Scoring
* \brief Manager used to compute combos from dices to a given player
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Compute each and every moves globally.
*/
class Scoring
{
private:
	/**
	* Every Playable Move (combo) possible in the current game and mapped to its original name.
	*/
	QMap<QString, PlayableMove*> playCombos;

public:
	/**
	* \brief Add a new mapped possible combo/move
	* \param name Name of the new combo
	* \param combo Delegated function meant to compute a list of Dices as a score
	* \return True if the combo has been successfully mapped (ie. is name unique)
	*
	* Used to define every possible moves in Yams such as Brelan, Full, Yams, or many other...
	*/
	bool addCombo(QString name, std::function<int(QList<Dice*>)> combo);
	/**
	* \brief Play a specific combo for a specific player with the current set of dice
	* \param player Specific player
	* \param dices Specific set of dices (5 in total)
	* \param name Name of played combo
	* \return Verify is move is playable or has already been played before
	*
	* Add score to a player for a specific combo depending on his current situation and if possible.
	*/
	bool play(Player* player, QList<Dice*> dices, QString name);
	/**
	* \brief Find and sort every possible move a specified player can play
	* \param player Specific player
	* \param dices List of current dice set
	* \return List resulting of the search with every move and its score/points
	*
	* Run through every possible move to sample the best ones to play for a specific player.
	*/
	QList<QPair<int, PlayableMove*>> sampleBestMoves(Player* player, QList<Dice*> dices);
	/**
	* \brief Sample a specific move without consideration of a specific player
	* \param dices Current set of dice
	* \param name Move name to play
	* \return Score (amount of points) a move would give
	*
	* Process a specific move in order to, for example, display a move current score in a Grid.
	*/
	int sampleMove(QList<Dice*> dices, QString name) const;
};