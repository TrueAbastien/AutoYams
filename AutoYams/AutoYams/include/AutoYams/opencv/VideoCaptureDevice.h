#pragma once
#include <QObject>
#include <QList>

#include <memory>

#include <DeviceEnumerator\include\DeviceEnumerator.h>

class VideoCaptureDevice : public QObject
{
public:
	VideoCaptureDevice(int id, QString name, QString path = "");

	int getID() const { return ID; }
	QString getName() const { return deviceName; }
	QString getPath() const { return devicePath; }
	QString getAlias() const { return deviceAlias; }

private:
	int ID;
	QString deviceName, devicePath, deviceAlias;

public:
	static void get(QList<std::shared_ptr<VideoCaptureDevice>>&);
};