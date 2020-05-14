#pragma once
#include <QObject>

class EventRedirector : public QObject
{
	Q_OBJECT

protected:
	const QObject* emitter, *receiver;

	virtual void onConnect() = 0;
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
	EventRedirector(const QObject* _emit = nullptr, const QObject* _recv = nullptr)
		: emitter(_emit), receiver(_recv)
	{
		TriggerConnection();
	}

	bool setEmitter(const QObject* _emit)
	{
		emitter = _emit;
		return TriggerConnection();
	}
	bool setReceiver(const QObject* _recv)
	{
		receiver = _recv;
		return TriggerConnection();
	}

};