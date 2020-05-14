#pragma once
#include <AutoYams\core\page\AdvancedPage.h>

class ConfigPage : public AdvancedPage
{
	Q_OBJECT

public:
	ConfigPage(AutoYams* app, VideoCaptureWindow* ref);

	virtual void handle() override;

	virtual bool pressOkButton() override;

	virtual void selectDevice(int) override { }
	virtual void selectConfig(int) override { }

	virtual void changeBrightness(int) override { }
	virtual void changeContrast(int) override { }
	virtual void changeFramerate(int) override { }
	virtual void changeZoom(double) override { }

private slots:
	void updateConfigCB();
	void addConfig();
	void setConfig();
	void setDefaultDevice();
	void setDefaultConfig();
};