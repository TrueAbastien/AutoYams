#pragma once
#include <QObject>
#include <AutoYams\gameplay\Dice.h>
#include <AutoYams\gameplay\Player.h>
#include <AutoYams\gameplay\Scoring.h>
#include <AutoYams\core\exception\AdvancedException.h>

/**
* \class Game
* \brief Main game object
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Link every game objects to the game page.
*/
class Game : public QObject
{
	Q_OBJECT

private:
	/**
	* Current turn counter.
	*/
	int turn;
	/**
	* Current player index in player list.
	*/
	int currentPlayerIndex;
	/**
	* Current throw counter for current player.
	*/
	int currentPlayerThrow;
	/**
	* List of all players currently in game.
	*/
	QList<Player*> players;
	/**
	* List of all 5 dices.
	*/
	QList<Dice*> dices;
	/**
	* Instance of scoring system used to compute player moves.
	*/
	Scoring scoreSystem;

public:
	/**
	* \brief Default constructor
	* \param players List of all player names
	*
	* Instantiate all Dices then Players according to the specified names,
	* then specify each possible moves to the Scoring system instance.
	*/
	Game(QStringList players);
	/**
	* \brief Default deconstructor
	*
	* Free memory space from every Dice & Player.
	*/
	~Game();

	/**
	* \brief Roll every dices in members.
	*
	* Every selected dices will be rolled for a new dice value.
	*/
	void roll();

	/**
	* \brief Access dice at a specified index
	* \param index Specific index
	* \return Accessed dice pointer
	*
	* Get dice from members at a specific index,
	* allowing us to read its current value.
	*/
	Dice* getDice(int index);
	/**
	* \brief Access currently playing player
	* \return Accessed player pointer
	*
	* Return the current player from members as the one currently playing.
	*/
	Player* getCurrentPlayer() const;
	/**
	* \brief Access counter value of the current throw
	* \return Accessed counter value
	*
	* Get current throw, that's about it.
	*/
	int getCurrentThrow() const;
	/**
	* \brief Access current turn value
	* \return Accessed turn value
	*
	* Get current turn, that's all.
	*/
	int getCurrentTurn() const;

	/**
	* \brief Play move with currently specified name if possible
	* \param name Name of the current move to play
	* \return Verification result of the move is playable or not
	*
	* Play specific move from name to the current player while updating its score accordingly.
	*/
	bool Play(QString name);
	/**
	* \brief Verify if the game reached its end
	* \return Result of the verification
	*
	* If more than 10 turns (included) have been played, the game should end.
	*/
	bool isEnd() const;
	/**
	* \brief Verify if the current player reached its last throw
	* \return Result of the verification
	*
	* Return true if it is the player 3rd throw (or more).
	* There's actually nothing turn related there.
	*/
	bool isLastTurn() const;

	/**
	* \brief Increment next throw for the current player if possible.
	*
	* Change next throw if possible and requiered, cannot exceed 3 though.
	*/
	void NextThrow();
	/**
	* \brief Increment current player index to change to the next player.
	*
	* Change to the following player and, if the index reached the end of the list,
	* come back the first index and call Next Turn method.
	* Reset dices values too.
	*/
	void NextPlayer();
	/**
	* \brief Increment turn counter if possible.
	*
	* Increase by one the turn counter if below 10.
	*/
	void NextTurn();

	/**
	* \brief Obtain every possible moves correctly ordered.
	* \return Resulting of the search: a list of every moves and its value (so it doesn't need to be computed again).
	*
	* For every possible moves, compute the current value on it's average possible result of any dice combination as a factor,
	* then sort the list by the computed factor to return it correctly ordered.
	*/
	QList<QPair<int, PlayableMove*>> bestCurrentPlayerMoves();
	/**
	* \brief Compute the current score of a specified move name
	* \param move Specific move name
	* \return Result of the computation
	*
	* Compute the current score of a specific move then return its value/score.
	*/
	int currentScoreOf(QString move);

	/**
	* \brief Change dices values to the specified data
	* \param dices Specific data of new dices values
	*
	* Change every value when dices have been changed (ie. thrown).
	*/
	void setDices(QList<int> dices);
	/**
	* \brief Search for the currently winning player
	* \return Result of the search
	*
	* Used to declare the winning player at the end of the game.
	*/
	Player* winningPlayer() const;

signals:
	/**
	* \brief Signal sent when a new throw occured
	*
	* Currently useless, was meant for a multiplayer implementation as a callback.
	*/
	void thrown();
	/**
	* \brief Signal sent when a new player has been chosen
	* \param index Index of the new player in propreties list
	*
	* Currently useless, was meant for a multiplayer implementation as a callback.
	*/
	void newPlayer(int index);
	/**
	* \brief Signal sent when a new turn started
	* \param val Value of the new turn counter
	*
	* Currently useless, was meant for a multiplayer implementation as a callback.
	*/
	void newTurn(int val);
	/**
	* \brief Signal sent when the game should end
	*
	* Currently useless, was meant for a multiplayer implementation as a callback.
	*/
	void end();

public slots:
	/**
	* \brief Processing selection on a dice when clicked
	* \param index Index of the clicked dice
	*
	* Currently useless, was meant for the user to select and unselect a dice on Manual Input methods.
	*/
	void clickDice(int index);
};