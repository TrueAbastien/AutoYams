#pragma once
#include <AutoYams\core\page\Page.h>
#include <VideoCaptureWindow.h>

/**
* \class AdvancedPage
* \brief Abstract paging class to handle Video Window pagination
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Used and redefined for Video & Config page in the current application Video Capture Window.
*/
class AdvancedPage : public Page
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param id Current page number (id)
	* \param app Reference of the current application window
	* \param ref Reference of the current Video Window of Application
	*
	* Specifiy required data to build reference for the page connection
	* to UI & window event elements (slots & signals).
	*/
	AdvancedPage(int id, AutoYams* app, VideoCaptureWindow* ref)
		: Page(id, app), wnd(ref)
	{ }

	/**
	* \brief Abstract method called when 'OK' button is pressed
	* \return If need to be closed, should return True
	*
	* Called in Video Window when the 'OK' button is pressed in Current Page.
	*/
	virtual bool pressOkButton() = 0;

	/**
	* \brief Abstract method called when a new device is selected
	* \param index Index of newly selected device in original Combobox
	*
	* Called in Video Window when a new device is selected in the center-right Device Combobox.
	*/
	virtual void selectDevice(int index) = 0;
	/**
	* \brief Abstract method called when a new config is selected
	* \param index Index of newly selected config in original Combobox
	*
	* Called in Video Window when a new config is selected in the center-right Config Combobox.
	*/
	virtual void selectConfig(int index) = 0;

	/**
	* \brief Abstract method called when brightness is changed
	* \param value Value of the new brightness from original Slider
	*
	* Called in Video Window when brightness is modified through center-right Brightness Slider.
	*/
	virtual void changeBrightness(int value) = 0;
	/**
	* \brief Abstract method called when contrast is changed
	* \param value Value of the new constrast from original Slider
	*
	* Called in Video Window when contrast is modified through center-right Constrast Slider.
	*/
	virtual void changeContrast(int value) = 0;
	/**
	* \brief Abstract method called when framerate is changed
	* \param value Value of the new framerate from original Slider
	*
	* Called in Video Window when framerate is modified through center-right Framerate Slider.
	*/
	virtual void changeFramerate(int value) = 0;
	/**
	* \brief Abstract method called when zoom/scale is changed
	* \param value Value of the new zoom/scale from original Slider
	*
	* Called in Video Window when zoom/scale is modified through center-right Zoom/scale Slider.
	*/
	virtual void changeZoom(double value) = 0;

protected:
	/**
	* Reference of the current Video Window in current application.
	*/
	VideoCaptureWindow* wnd;
};