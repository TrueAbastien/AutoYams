#include "AutoYams.h"
#include <QtWidgets/QApplication>

/**
* \mainpage Auto Yams Development 
*
* \section About the application...
*
* This application is a student project which is still laking and somehow unfinished.
* The application manual can be found on the original Github page.
* The main window of the current application can be found through the class below:
*
* \see AutoYams
*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoYams w;
	w.show();
	return a.exec();
}
