#pragma once
#include <QtWidgets/QMainWindow>
#include <AutoYams\core\event\specifics\EventThrowDice.h>
#include "ui_AutoYams.h"

#include "opencv2/videoio.hpp"

class Page;
class VideoCaptureWindow;

class AutoYams : public QMainWindow
{
	Q_OBJECT

public:
	AutoYams(QWidget *parent = Q_NULLPTR);
	~AutoYams();

	Ui::AutoYamsClass ui;
	cv::VideoCapture* video;

	EventThrowDice* event_diceThrown;

private:
	Page* currentPage = nullptr;
	QList<Page*> allPages;

	VideoCaptureWindow* videoWindow;

private slots:
	void setCurrentPage(int pageID);

	void openVideoWindow(int pageID);
};
