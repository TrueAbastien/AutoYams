#include <AutoYams.h>

#include <VideoCaptureWindow.h>

#include <AutoYams\core\page\main\GamePage.h>
#include <AutoYams\core\page\main\MenuPage.h>

#include <QDesktopServices>


AutoYams::AutoYams(QWidget *parent)
	: QMainWindow(parent)
{
	// Setup AutoYams UI
	ui.setupUi(this);

	// Connect the pagination system to the page changement
	connect(ui.pagination, SIGNAL(currentChanged(int)), this, SLOT(setCurrentPage(int)));

	// Instantiate each and every main Pages
	allPages.append(new MenuPage(this));
	allPages.append(new GamePage(this));

	// Instantiate every Video related elements
	video = new cv::VideoCapture();
	videoWindow = new VideoCaptureWindow(this);

	// Add to both windows an icon and a title
	videoWindow->setWindowTitle("Video Device");
	QIcon icon("Resources/img/icon.png");
	videoWindow->setWindowIcon(icon);
	this->setWindowIcon(icon);

	// Set the default page as Menu
	ui.pagination->setCurrentIndex(0);

	// Connect most menu based action
	connect(ui.actionVideo, &QAction::triggered, [this]() { openVideoWindow(0); });
	connect(ui.actionQuit, &QAction::triggered, [this]() { QCoreApplication::exit(); });
	connect(ui.actionSource, &QAction::triggered, [this]() { QDesktopServices::openUrl(QUrl("https://github.com/TrueAbastien/AutoYams")); });
	connect(ui.actionAbout, &QAction::triggered, [this]() { QMessageBox::about(this, "About AutoYams", "<b>Author:</b> Bastien L.<br><b>Date:</b> 15th May of 2020"); });

	// Declare the Throw Dice event redirector
	event_diceThrown = new EventThrowDice();
}

AutoYams::~AutoYams()
{
}

void AutoYams::setCurrentPage(int pageID)
{
	if (pageID < 0 || pageID >= allPages.length())
	{
		currentPage = nullptr;
	}
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