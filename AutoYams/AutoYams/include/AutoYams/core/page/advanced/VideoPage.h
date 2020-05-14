#pragma once
#include <AutoYams\core\page\AdvancedPage.h>
#include <AutoYams\opencv\graphic\VideoOpenCV.h>

class VideoPage : public AdvancedPage
{
	Q_OBJECT

public:
	VideoPage(AutoYams* app, VideoCaptureWindow* ref);

	virtual void handle() override;

	virtual bool pressOkButton() override;

	virtual void selectDevice(int) override;
	virtual void selectConfig(int) override;

	virtual void changeBrightness(int) override;
	virtual void changeContrast(int) override;
	virtual void changeFramerate(int) override;
	virtual void changeZoom(double) override;

private:
	VideoOpenCV* videoDisplay;
};