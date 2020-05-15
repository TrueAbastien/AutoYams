#pragma once
#include <QtWidgets/QMainWindow>
#include <AutoYams\core\event\specifics\EventThrowDice.h>
#include "ui_AutoYams.h"

#include "opencv2/videoio.hpp"

class Page;
class VideoCaptureWindow;

/**
* \class AutoYams
* \brief Application window for main instance
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Main application window, contains alot but doesn't do much.
*/
class AutoYams : public QMainWindow
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param parent Parent widget (usually null)
	*
	* Mostly: connect events, create pages, instantiate propreties & much more...
	*/
	AutoYams(QWidget *parent = Q_NULLPTR);
	/**
	* \brief Default deconstructor
	*
	* Free pointers if required (who cares for the main app ?).
	*/
	~AutoYams();

	/**
	* Current main application UI setup.
	*/
	Ui::AutoYamsClass ui;
	/**
	* Video Capture object from OpenCV to handle video wherever in the application.
	*/
	cv::VideoCapture* video;

	/**
	* Redirector of the following event:
	* whenever 5 new dices are detected, the event is triggered.
	*/
	EventThrowDice* event_diceThrown;

private:
	/**
	* Current selected page.
	*/
	Page* currentPage = nullptr;
	/**
	* List of all main pages.
	*/
	QList<Page*> allPages;

	/**
	* Unique instance of Video Window in application.
	*/
	VideoCaptureWindow* videoWindow;

private slots:
	/**
	* \brief Change current page from id
	* \param pageID New ID for page change
	*
	* Change page on pagination change of index/focus.
	*/
	void setCurrentPage(int pageID);

	/**
	* \brief Open video window when required
	* \param pageID ID on which page to open the window
	*
	* Open and change page of Video Window instance.
	*/
	void openVideoWindow(int pageID);
};
