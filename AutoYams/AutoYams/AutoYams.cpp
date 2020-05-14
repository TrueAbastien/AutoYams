#include <AutoYams.h>

#include <VideoCaptureWindow.h>

#include <AutoYams\core\page\main\GamePage.h>
#include <AutoYams\core\page\main\MenuPage.h>

#include <QDesktopServices>


AutoYams::AutoYams(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pagination, SIGNAL(currentChanged(int)), this, SLOT(setCurrentPage(int)));

	allPages.append(new MenuPage(this));
	allPages.append(new GamePage(this));

	video = new cv::VideoCapture();
	videoWindow = new VideoCaptureWindow(this);

	videoWindow->setWindowTitle("Video Device");
	QIcon icon("Resources/img/icon.png");
	videoWindow->setWindowIcon(icon);
	this->setWindowIcon(icon);

	ui.pagination->setCurrentIndex(0);

	connect(ui.actionVideo, &QAction::triggered, [this]() { openVideoWindow(0); });
	connect(ui.actionQuit, &QAction::triggered, [this]() { QCoreApplication::exit(); });
	//connect(ui.actionAbout, &QAction::triggered, [this]() { QDesktopServices::openUrl(QUrl("")); });
	connect(ui.actionAbout, &QAction::triggered, [this]() { QMessageBox::about(this, "About AutoYams", "<b>Author:</b> Bastien L.<br><b>Date:</b> 15th May of 2020"); });

	event_diceThrown = new EventThrowDice();
}

AutoYams::~AutoYams()
{
}

void AutoYams::setCurrentPage(int pageID)
{
	if (pageID < 0 || pageID >= allPages.length())
		currentPage = nullptr;
	else
	{
		currentPage = allPages[pageID];
		currentPage->handle();
	}
}

void AutoYams::openVideoWindow(int pageID)
{
	videoWindow->display(pageID);
}