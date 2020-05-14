#include "AutoYams.h"
#include <QtWidgets/QApplication>

#include <DeviceEnumerator\include\DeviceEnumerator.h> //DEBUG
#include <QFile> //DEBUG
#include <QTextStream>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoYams w;

	/** ----------------------------------------------------------------------------------------- //
	// File Init
	QFile debug("output.txt");
	if (debug.open(QFile::ReadWrite | QFile::Text | QFile::ExistingOnly | QFile::Append))
	{
		QTextStream out(&debug);
		DeviceEnumerator de;

		// Audio Devices
		std::map<int, Device> devices = de.getVideoDevicesMap();

		// Print information about the devices
		for (auto const &device : devices) {
			out << "== VIDEO DEVICE (id:" << device.first << ") ==" << "\n";
			out << "Name: " << device.second.deviceName.data() << "\n";
			out << "Path: " << device.second.devicePath.data() << "\n\n";
		}

		debug.close();
	}
	// ----------------------------------------------------------------------------------------- //**/

	w.show();
	return a.exec();
}
