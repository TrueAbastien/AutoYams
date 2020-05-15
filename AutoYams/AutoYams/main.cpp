#include "AutoYams.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoYams w;
	w.show();
	return a.exec();
}
