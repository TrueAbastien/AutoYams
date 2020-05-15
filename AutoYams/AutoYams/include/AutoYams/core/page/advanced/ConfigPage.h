#pragma once
#include <AutoYams\core\page\AdvancedPage.h>

/**
* \class ConfigPage
* \brief Advanced configuration page
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Page used in Video Window to handle any configuration related action.
*/
class ConfigPage : public AdvancedPage
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param app Reference of the current application window
	* \param ref Reference of the current Video Window of Application
	*
	* Specifiy required data to build reference for the page connection
	* to UI & window event elements (slots & signals).
	*/
	ConfigPage(AutoYams* app, VideoCaptureWindow* ref);

	/**
	* \brief Method called when page is selected in pagination
	*
	* Called in Video Window when the Config Page is selected in the top-left pagination.
	*/
	virtual void handle() override;

	/**
	* \brief Method called when 'OK' button is pressed
	* \return If need to be closed, should return True
	*
	* Called in Video Window when the 'OK' button is pressed in Config Page.
	*/
	virtual bool pressOkButton() override;

	/**
	* \brief Method called when a new device is selected
	* \param index Index of newly selected device in original Combobox
	*
	* Called in Video Window when a new device is selected in the center-right Device Combobox on Config Page.
	*/
	virtual void selectDevice(int index) override { }
	/**
	* \brief Method called when a new config is selected
	* \param index Index of newly selected config in original Combobox
	*
	* Called in Video Window when a new config is selected in the center-right Config Combobox on Config Page.
	*/
	virtual void selectConfig(int index) override { }

	/**
	* \brief Method called when brightness is changed
	* \param value Value of the new brightness from original Slider
	*
	* Called in Video Window when brightness is modified through center-right Brightness Slider in Config Page.
	*/
	virtual void changeBrightness(int value) override { }
	/**
	* \brief Method called when contrast is changed
	* \param value Value of the new contrast from original Slider
	*
	* Called in Video Window when contrast is modified through center-right Contrast Slider in Config Page.
	*/
	virtual void changeContrast(int value) override { }
	/**
	* \brief Method called when framerate is changed
	* \param value Value of the new framerate from original Slider
	*
	* Called in Video Window when framerate is modified through center-right Framerate Slider in Config Page.
	*/
	virtual void changeFramerate(int value) override { }
	/**
	* \brief Method called when zoom/scale is changed
	* \param value Value of the new zoom/scale from original Slider
	*
	* Called in Video Window when zoom/scale is modified through center-right Zoom/scale Slider in Config Page.
	*/
	virtual void changeZoom(double value) override { }

private slots:
	/**
	* \brief Update list of all existing configs
	*
	* Search in manager the list of all declared configurations and display them in a Combobox.
	*/
	void updateConfigCB();
	/**
	* \brief Add and declare a new config in manager
	*
	* Search for the current file name displayed in the page Edit,
	* create a new file of this name if nothing is found,
	* then declare it in manager and attach it with its name as surename on the current device.
	*/
	void addConfig();
	/**
	* \brief Attach specific config to current Device
	*
	* Take the Edit text as surename, verify if the current device already got a configuration under the same surename,
	* if not, attach the configuration in page Combobox to the device even if it DOES already exist under another surename.
	*/
	void setConfig();
	/**
	* \brief Change default device to current device
	*
	* Change and store current device in root object of the manager so, every time the application is started,
	* the default device will be started and ready to use.
	*/
	void setDefaultDevice();
	/**
	* \brief Change default config of the current device
	*
	* Change and store current configuration of the current device in root object of the manager so,
	* every time current device is selected, its default configuration will start with him.
	*/
	void setDefaultConfig();
};