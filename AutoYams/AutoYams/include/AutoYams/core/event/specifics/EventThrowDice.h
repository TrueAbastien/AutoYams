#pragma once
#include <AutoYams\core\event\EventRedirector.h>

/**
* \class EventThrowDice
* \brief Redirected Event on Dice Detection
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Redirect dice detection from Video Page to Game Page in the main application.
*/
class EventThrowDice : public EventRedirector
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	*
	* Initialize the event redirector with null values.
	*/
	EventThrowDice() : EventRedirector(nullptr, nullptr) { }

protected:
	/**
	* \brief Method disconnecting dice throw
	*
	* Emitter is the Video Page, while receiver is the Game Page.
	*/
	void onSet() override
	{
		disconnect(emitter, SIGNAL(DiceChanged(QList<int>&)), receiver, SLOT(AutomaticDiceThrown(QList<int>&)));
	}
	/**
	* \brief Method connecting dice throw
	*
	* Emitter is the Video Page, while receiver is the Game Page.
	*/
	void onConnect() override
	{
		connect(emitter, SIGNAL(DiceChanged(QList<int>&)), receiver, SLOT(AutomaticDiceThrown(QList<int>&)));
	}
};