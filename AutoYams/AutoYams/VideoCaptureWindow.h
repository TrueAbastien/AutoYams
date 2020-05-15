#pragma once
#include <QDialog>
#include <AutoYams.h>
#include "ui_VideoCapture.h"

#include <AutoYams\opencv\VideoCaptureDevice.h>
#include <AutoYams\core\file\ConfigFile.h>
#include <AutoYams\core\file\ConfigManager.h>

class AdvancedPage;

/**
* \class VideoCaptureWindow
* \brief Video Window dialog for Capture customization and verification
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Allow any user to customize the brightness, contrast, framerate and video scale
* to allow a better recognition of dices through your webcam / video capturing device.
*/
class VideoCaptureWindow : public QDialog
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param wnd Main application window reference
	*
	* Initialize all propreties of the current window, its connections
	* to the config management of any devices.
	*/
	explicit VideoCaptureWindow(AutoYams* wnd);
	/**
	* \brief Default deconstructor
	*
	* Free any pointer remaining variable in propreties while saving any filed data.
	*/
	~VideoCaptureWindow();

	/**
	* UI setup for the Video Cpature window.
	*/
	Ui::VideoCapture ui;

	/**
	* List of all video capturing devices connected to your computer.
	*/
	QList<std::shared_ptr<VideoCaptureDevice>> devices;
	/**
	* Configuration file loader in which to write and read data from for config cutomization.
	*/
	std::shared_ptr<ConfigFile> configFile;
	/**
	* Object containing JSON file to allow us to store and manage every config and devices ever used or created.
	*/
	std::shared_ptr<ConfigManager> configManager;
	/**
	* Current stored device index in device list.
	*/
	int currentDeviceIndex;
	/**
	* Current stored config index for the current device.
	*/
	int currentConfigIndex;

	/**
	* \brief Method displaying Advanced Page at specified index
	* \param pageID Specific index
	*
	* Switch pagination to either Video or Config Page depending on the specified index.
	*/
	void display(int pageID);

	/**
	* \brief Override close event method of the current dialog
	* \param event Event responsible for calling the Window Close Event
	*
	* Update close event to automatically save every config customization related data.
	*/
	void closeEvent(QCloseEvent* event) override;

private:
	/**
	* Reference to the main application window.
	*/
	AutoYams* app;

	/**
	* Currently selected page reference.
	*/
	AdvancedPage* currentPage = nullptr;
	/**
	* List of all pages in current window: Video & Config Page.
	*/
	QList<AdvancedPage*> allPages;

	/**
	* \brief Function finding the deivce index in Devices list
	* \param device Specific device alias
	*
	* Find device index in propreties through its alias.
	*/
	int findDeviceIndex_byAlias(QString device);

private slots:
	/**
	* \brief Change current page in pagination
	* \param index Index of the new page
	*
	* When page is changed in pagination, the stored page its ID is related
	* and attached to will be displayed and trigger its handling.
	*/
	void setCurrentPage(int index);
	
	/**
	* \brief Trigger an event when the 'OK' button is pressed in the window
	*
	* Call the current Advanced Page pressOkButton event if possible,
	* then close the window if the result is True.
	*/
	void pressOkButton();

	/**
	* \brief Select a new device in the devices already stored
	* \param index Index of the new device to select
	*
	* When a new device is selected from the device Combobox, this method
	* will change the current capture video device and load its default configuration
	* then will call the current Advanced Page 'selectDevice' method.
	*/
	void selectDevice(int index);
	/**
	* \brief Select a new config for the device currently selected
	* \param index Index of the new config to select
	*
	* When a new configuratio is selected from the configuration Combobox,
	* this method will change the current configuration and apply it to your current image output
	* then will call the current Advanced Page 'selectConfig' method.
	*/
	void selectConfig(int index);

	/**
	* \brief Save current config data
	*
	* Will save the data of the current device configuration to its specific file path.
	*/
	void saveConfig();
	/**
	* \brief Load a new config and aplly its data
	* \param path Path of the new config to load
	*
	* Will load a new configuration in the Config File object after saving the previous configuration data.
	*/
	void loadConfig(QString path);

	/**
	* \brief Change brightness in current window image settings
	* \param value Value of the newly changed brightness
	*
	* Will change the brightness of the image output,
	* store its value, then call the corresponding method in the current Advanced Page.
	*/
	void changeBrightness(int value);
	/**
	* \brief Change contrast in current window image settings
	* \param value Value of the newly changed contrast
	*
	* Will change the contrast of the image output,
	* store its value, then call the corresponding method in the current Advanced Page.
	*/
	void changeContrast(int value);
	/**
	* \brief Change framerate in current window image settings
	* \param value Value of the newly changed framerate
	*
	* Will change the current max framerate of the video object,
	* store its value, then call the corresponding method in the current Advanced Page.
	*/
	void changeFramerate(int value);
	/**
	* \brief Change zoom/scale in current window image settings
	* \param value Value of the newly changed zoom/scale
	*
	* Will change the zoom/scale of the image output,
	* store its value, then call the corresponding method in the current Advanced Page.
	*/
	void changeZoom(int value);

public slots:
	/**
	* \brief Refresh list of all devices currently connected
	*
	* Find every connected video capturing device and display them in the device Combobox.
	*/
	void refreshDeviceList();
	/**
	* \brief Refresh list of all configs attached to the current device
	*
	* Search and display every configuration attached to the currently
	* selected device using the Config Manager to do so.
	*/
	void refreshConfigList();
};