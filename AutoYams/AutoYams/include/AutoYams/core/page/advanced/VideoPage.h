#pragma once
#include <AutoYams\core\page\AdvancedPage.h>
#include <AutoYams\opencv\graphic\VideoOpenCV.h>

/**
* \class VideoPage
* \brief Advanced video page
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Page used in Video Window to display video capture & algorithm output.
*/
class VideoPage : public AdvancedPage
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
	VideoPage(AutoYams* app, VideoCaptureWindow* ref);

	/**
	* \brief Method called when page is selected in pagination
	*
	* Called in Video Window when the Video Page is selected in the top-left pagination.
	*/
	virtual void handle() override;

	/**
	* \brief Method called when 'OK' button is pressed
	* \return If need to be closed, should return True
	*
	* Called in Video Window when the 'OK' button is pressed in Video Page.
	*/
	virtual bool pressOkButton() override;

	/**
	* \brief Method called when a new device is selected
	* \param index Index of newly selected device in original Combobox
	*
	* Called in Video Window when a new device is selected in the center-right Device Combobox on Video Page.
	*/
	virtual void selectDevice(int index) override;
	/**
	* \brief Method called when a new config is selected
	* \param index Index of newly selected config in original Combobox
	*
	* Called in Video Window when a new config is selected in the center-right Config Combobox on Video Page.
	*/
	virtual void selectConfig(int index) override;

	/**
	* \brief Method called when brightness is changed
	* \param value Value of the new brightness from original Slider
	*
	* Called in Video Window when brightness is modified through center-right Brightness Slider in Video Page.
	*/
	virtual void changeBrightness(int value) override;
	/**
	* \brief Method called when contrast is changed
	* \param value Value of the new contrast from original Slider
	*
	* Called in Video Window when contrast is modified through center-right Contrast Slider in Video Page.
	*/
	virtual void changeContrast(int value) override;
	/**
	* \brief Method called when framerate is changed
	* \param value Value of the new framerate from original Slider
	*
	* Called in Video Window when framerate is modified through center-right Framerate Slider in Video Page.
	*/
	virtual void changeFramerate(int value) override;
	/**
	* \brief Method called when zoom/scale is changed
	* \param value Value of the new zoom/scale from original Slider
	*
	* Called in Video Window when zoom/scale is modified through center-right Zoom/scale Slider in Video Page.
	*/
	virtual void changeZoom(double value) override;

private:
	/**
	* Video display of OpenCV video capture object in main application.
	*/
	VideoOpenCV* videoDisplay;
};