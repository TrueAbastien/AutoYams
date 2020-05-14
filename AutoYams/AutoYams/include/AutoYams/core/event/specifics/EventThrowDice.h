#pragma once
#include <AutoYams\core\event\EventRedirector.h>

class EventThrowDice : public EventRedirector
{
	Q_OBJECT

public:
	EventThrowDice() : EventRedirector(nullptr, nullptr) { }

protected:
	void onConnect() override
	{
		disconnect(emitter, SIGNAL(DiceChanged(QList<int>&)), receiver, SLOT(AutomaticDiceThrown(QList<int>&)));
		connect(emitter, SIGNAL(DiceChanged(QList<int>&)), receiver, SLOT(AutomaticDiceThrown(QList<int>&)));
	}
};