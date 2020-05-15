#pragma once
#include <AutoYams\core\page\Page.h>

/**
* \class MenuPage
* \brief Menu page for the main window
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Used to display the first page seen in the application meant to add the player names.
*/
class MenuPage : public Page
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param ref Reference to the main application window
	*
	* Initialise every connection possible meant for the menu to handle.
	*/
	explicit MenuPage(AutoYams* ref = 0);

	/**
	* \brief Method called when page is selected in pagination
	*
	* Called in main Window when the Menu Page is displayed.
	*/
	void handle() override;

private slots:
	/**
	* \brief Event meant for starting the game
	*
	* Start the game if 2 player names or more have been added to the list.
	*/
	void startGame();
	/**
	* \brief Event meant for adding player to the list
	*
	* Take the current name in edit and add it on button push
	* if it is unique and more than 3 characters long.
	*/
	void addPlayer();

signals:
	/**
	* \brief Signal meant to indicate a page changement
	* \param index Index of the new page in the main Window
	*
	* Called when page should be changed to Game Page.
	*/
	void changePage(int index);
};