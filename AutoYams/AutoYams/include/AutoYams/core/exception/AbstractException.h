#pragma once
#include <QString>
#include <QMessagebox>
#include <QWidget>

/**
* \class AbstractException
* \brief Abstract exception class for further custom exception handling
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Used to be redefined in AdvancedException.h file... no documentation on that though.
*/
class AbstractException
{
protected:
	/**
	* Current error message.
	*/
	QString errorMessage;
	/**
	* \brief Abstract method giving out error title
	* \return Specific error title
	*
	* Return current error title after being specified on declaration.
	*/
	virtual QString entitled() const = 0;

	/**
	* \brief Access current error message
	* \return Current error message
	*
	* Return current error message if defined, otherwise, a default message.
	*/
	QString errorMsg() const
	{
		if (errorMessage.isEmpty())
			return "An error has occured...";
		return errorMessage;
	}
	
public:
	/**
	* \brief Default constructor
	* \param content New error message
	*
	* Specify and set error message in this unhandy abstract constructor.
	*/
	explicit AbstractException(QString content = "")
		: errorMessage(content) { }

	/**
	* \brief Get full error message
	* \return Full error message
	*
	* Access full error message: from specific title to the actual error message.
	*/
	QString get() const
	{
		return entitled() + ": " + errorMsg();
	}
	/**
	* \brief Display error message in warning message box (dialog)
	* \param context Context of the new message box
	*
	* Draw the current message, with specific title and error message, in a message box.
	*/
	void draw(QWidget* context = Q_NULLPTR)
	{
		QMessageBox::warning(context, entitled() + " !", errorMsg());
	}
};