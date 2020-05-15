#pragma once
#include <QObject>
#include <QList>

#include <memory>

#include <DeviceEnumerator\include\DeviceEnumerator.h>

/**
* \class VideoCaptureDevice
* \brief Capture device data object
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Contains every information requiered for the each device to be recognized from others.
*/
class VideoCaptureDevice : public QObject
{
public:
	/**
	* \brief Default constructor
	* \param id Default ID for the current device
	* \param name Default name for the current device
	* \param path Default path for the current device
	*
	* Simply initialize every data from its arguments
	* and create the device alias from its name.
	*/
	VideoCaptureDevice(int id, QString name, QString path = "");

	/**
	* \brief Access the device ID
	* \return Accessed ID of the instance
	*
	* Getter for the device ID.
	*/
	int getID() const { return ID; }
	/**
	* \brief Access the device name
	* \return Accessed name of the instance
	*
	* Getter for the device name.
	*/
	QString getName() const { return deviceName; }
	/**
	* \brief Access the device path
	* \return Accessed path of the instance
	*
	* Getter for the device path.
	*/
	QString getPath() const { return devicePath; }
	/**
	* \brief Access the device alias
	* \return Accessed alias of the instance
	*
	* Getter for the device alias.
	*/
	QString getAlias() const { return deviceAlias; }

private:
	/**
	* Device current ID.
	*/
	int ID;
	/**
	* Device current name.
	*/
	QString deviceName;
	/**
	* Device current path.
	*/
	QString devicePath;
	/**
	* Device current alias.
	*/
	QString deviceAlias;

public:
	/**
	* \brief Static method getting and initalizing every devices connected
	* \param devices List of all device (used as output)
	*
	* Will find and fill the specified Devices list with every Video Cpature Devices
	* currently connected on your computer.
	*/
	static void get(QList<std::shared_ptr<VideoCaptureDevice>>& devices);
};