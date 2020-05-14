#pragma once
#include <AutoYams\core\page\Page.h>
#include <VideoCaptureWindow.h>

class AdvancedPage : public Page
{
	Q_OBJECT

public:
	AdvancedPage(int id, AutoYams* app, VideoCaptureWindow* ref)
		: Page(id, app), wnd(ref)
	{ }

	virtual bool pressOkButton() = 0;

	virtual void selectDevice(int) = 0;
	virtual void selectConfig(int) = 0;

	virtual void changeBrightness(int) = 0;
	virtual void changeContrast(int) = 0;
	virtual void changeFramerate(int) = 0;
	virtual void changeZoom(double) = 0;

protected:
	VideoCaptureWindow* wnd;
};