#pragma once
#include <QObject>

/**
* \class EventRedirector
* \brief Abstract class for event handling
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Allow for redefinition to connect two QObject if both party are specified.
*/
class EventRedirector : public QObject
{
	Q_OBJECT

protected:
	/**
	* Current instance emitter (sending signal).
	*/
	const QObject* emitter;
	/**
	* Current instance receiver (attached to slot).
	*/
	const QObject* receiver;

	/**
	* \brief Abstract method called on party Set
	*
	* Before a party is set, the function will be called (usually to deconnect the previouses parties).
	*/
	virtual void onSet() = 0;
	/**
	* \brief Abstract method called on party Connect
	*
	* After a party is set, the function will be called (usually to connect the new parties).
	*/
	virtual void onConnect() = 0;
	/**
	* \brief Disconnect parties if requiered
	* \return If the parties can and have been disconnected
	*
	* If both parties are existant, not null, call onSet method.
	*/
	bool PrepareConnection()
	{
		if (emitter != nullptr && receiver != nullptr)
		{
			onSet();
			return true;
		}
		return false;
	}
	/**
	* \brief Connect parties if possible
	* \return If the parties can and have been connected
	*
	* If both parties are existant, not null, call onConnect method.
	*/
	bool TriggerConnection()
	{
		if (emitter != nullptr && receiver != nullptr)
		{
			onConnect();
			return true;
		}
		return false;
	}

public:
	/**
	* \brief Default constructor
	* \param _emit Default emitter to be set
	* \param _recv Default receiver to be set
	*
	* Initialize instance by setting both party and connecting them if possible.
	*/
	EventRedirector(const QObject* _emit = nullptr, const QObject* _recv = nullptr)
		: emitter(_emit), receiver(_recv)
	{
		TriggerConnection();
	}

	/**
	* \brief Set current emitter
	* \param _emit New emitter to connect
	*
	* Change emitter while disconnecting previouses parties
	* and connecting the new ones if possible.
	*/
	bool setEmitter(const QObject* _emit)
	{
		PrepareConnection();
		emitter = _emit;
		return TriggerConnection();
	}
	/**
	* \brief Set current receiver
	* \param _emit New receiver to connect
	*
	* Change receiver while disconnecting previouses parties
	* and connecting the new ones if possible.
	*/
	bool setReceiver(const QObject* _recv)
	{
		PrepareConnection();
		receiver = _recv;
		return TriggerConnection();
	}

};