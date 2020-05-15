#include <AutoYams\core\page\advanced\VideoPage.h>

#include <AutoYams\core\exception\AdvancedException.h>

VideoPage::VideoPage(AutoYams * app, VideoCaptureWindow * ref)
	: AdvancedPage(0, app, ref)
{
	videoDisplay = new VideoOpenCV(wnd->ui.video_displayLabel, app->video);
}

void VideoPage::handle()
{
	changeBrightness(wnd->ui.form_brightnessSlider->value());
	changeContrast(wnd->ui.form_contrastSlider->value());
	changeFramerate(wnd->ui.form_framerateSlider->value());
	changeZoom((double)wnd->ui.form_zoomSlider->value() / 100.0);

	app->event_diceThrown->setEmitter(videoDisplay);
	
	selectDevice(wnd->ui.deviceCB->currentIndex());
}

bool VideoPage::pressOkButton()
{
	return true;
}

void VideoPage::selectDevice(int index)
{
	if (index == 0)
		videoDisplay->turnOff();
}

void VideoPage::selectConfig(int index)
{
}

void VideoPage::changeBrightness(int val)
{
	videoDisplay->setBrightness(val);
}

void VideoPage::changeContrast(int val)
{
	videoDisplay->setContrast(val);
}

void VideoPage::changeFramerate(int val)
{
	videoDisplay->setMaxFPS(val);
}

void VideoPage::changeZoom(double val)
{
	videoDisplay->setZoom(val);
}
