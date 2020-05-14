#pragma once
#include <QString>
#include <QMessagebox>
#include <QWidget>

class AbstractException
{
protected:
	QString errorMessage;
	virtual QString entitled() const = 0;

	QString errorMsg() const
	{
		if (errorMessage.isEmpty())
			return "An error has occured...";
		return errorMessage;
	}
	
public:
	explicit AbstractException(QString content = "")
		: errorMessage(content) { }

	QString get() const
	{
		return entitled() + ": " + errorMsg();
	}
	void draw(QWidget* context = Q_NULLPTR)
	{
		QMessageBox::warning(context, entitled() + " !", errorMsg());
	}
};