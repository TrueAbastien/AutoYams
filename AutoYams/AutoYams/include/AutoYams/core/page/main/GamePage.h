#pragma once
#include <QMap>
#include <QPixmap>
#include <QList>
#include <QActionGroup>
#include <AutoYams\core\page\Page.h>
#include <AutoYams\gameplay\Game.h>

/**
* \class GamePage
* \brief Game page for the main window
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Contains most game related elements, 
* it is the core of the every Yams related objects.
*/
class GamePage : public Page
{
	Q_OBJECT

public:
	/**
	* Enum PlayMethod.
	* Define which input method is the game currently using.
	*/
	enum PlayMethod { AUTO, SEMI, MANUAL };

public:
	/**
	* \brief Default constructor
	* \param ref Reference to the main application window
	*
	* Initialize every connection and every propreties of the game.
	*/
	explicit GamePage(AutoYams* ref = 0);

	/**
	* \brief Method called when page is selected in pagination
	*
	* Called in main Window when the Menu Page is displayed.
	*/
	void handle() override;

	/**
	* \brief Change grid content depending on arguments
	* \param row Row index to change the data from
	* \param player Name of the player (ie. the current column index)
	* \param content The new content of the found cell
	* \return Verification that the cell do exists
	*
	* Used to set the score content of any player at a specific row.
	*/
	bool setContent(int row, QString player, QString content);
	/**
	* \brief Reset most game and graphic propreties
	*
	* Reset the grid, the game current propreties and the overall score for each and every player.
	* This is meant to be called on the Game Page handling or on restart.
	*/
	void reset();

private:
	/**
	* Current input method for dice throwing.
	*/
	PlayMethod inputMethod = PlayMethod::AUTO;

	/**
	* Amount of row in the current grid (a game constant).
	*/
	int scoreTableRowCount;
	/**
	* Map of every move and the row their score should be displayed in.
	*/
	QMap<QString, int> moveGridIndex;
	/**
	* Map of every player and the column they are attached to.
	*/
	QMap<QString, int> playerIndex;

	/**
	* Game object instance.
	*/
	Game* game = nullptr;
	/**
	* Pictures of every possible dice value (7 in total).
	*/
	QMap<int, QPixmap> dicePictures;
	/**
	* Map of every dice index and their label display.
	*/
	QMap<int, QLabel*> diceIcons;

	/**
	* Action group meant for handling the change in input method (ToggleGroup).
	*/
	QActionGroup* inputMethodGroup;
	/**
	* Oddly specific switch in semi-automatic input methods to store
	* if the dices have already been thrown or not.
	*/
	bool semi_hasBeenThrown;

	/**
	* \brief Add a new amount of row to the grid
	* \param amount Amount of row to add
	*
	* Add a new row to the grid while copying every cell style.
	*/
	int addRow(unsigned int amount = 1);

private slots:
	/**
	* \brief Add player to the grid
	* \param name Name of the new player
	*
	* Create a new row then change its player name.
	*/
	void addPlayer(QString name);
	/**
	* \brief Reset each dice display to their default pixmap
	*
	* Reset each and every dice on player changement.
	*/
	void resetDices();

	/**
	* \brief Roll every dices and/or start next throw
	*
	* React differently depending on input method
	* but still require the user to push the Next Throw button.
	*/
	void playerThrow();
	/**
	* \brief Accept the current dice combination and skip turn
	*
	* Update score for the current player depending on the picked move
	* then change to the next player in line for his first turn.
	*/
	void playerAccept();
	/**
	* \brief End game and display winner
	*
	* Display a message box at the 10th turn allowing a user to return on the Menu
	* or stay on the Game Page to check the scores.
	*/
	void endGame();

	/**
	* \brief Change the current input method
	* \param inputMethod New input method for the user
	*
	* Switch the current input method in the action group.
	*/
	void changeInputMethod(PlayMethod inputMethod);
	/**
	* \brief Specific method when changed to Semi-Automatic
	* \param state If the current Play Method is on Semi-Automatic
	*
	* Change state of the Next Throw button and change the switch in propreties.
	*/
	void changeSemiToggle(bool state);

public slots:
	/**
	* \brief Automatically change the Game dices values depending on current input method
	* \params dices List of all dices values (should always be 5 elements long)
	*
	* Whenever a dice combination is detected and is sent from the Video Page and its VideoOpenCV object,
	* this function will trigger (if allowed to) to display and change the value of the current dice set.
	* In Automatic mode, it will also count as a new throw.
	*/
	void AutomaticDiceThrown(QList<int>& dices);
	/**
	* \brief Update every graphic elements related to a new throw
	*
	* Whenever the dices are thrown, each dice display and the bottom labels values will be updated.
	*/
	void GraphicThrowUpdate();
	/**
	* \brief Update every graphic elements related to a new pick
	* \param move Picked move name
	*
	* Whenever a move is selected and accepted, the points gained will be displayed in the grid
	* and the both totals and bottom labels will be so too.
	*/
	void GraphicPickUpdate(QString move);
	/**
	* \brief Update every bottom labels with the specified values
	* \param turn Counter of the current game turn
	* \param player Name of the player currently playing
	* \param nThrow Value from counter of the current player throw
	*
	* Each of the 3 bottom labels will be updated by each of the previous arguments.
	*/
	void GraphicLabelUpdate(int turn, QString player, int nThrow);
	/**
	* \brief Update every totals for a specified player
	* \param player Specific player
	* \param data Score data of the current player at the end of his turn
	*
	* Every possible totals, for the current player, will be updated in the grid.
	*/
	void GraphicTotalUpdate(QString player, Player::ScoreData data);
};
