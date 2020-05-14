#include <AutoYams\core\page\advanced\ConfigPage.h>

ConfigPage::ConfigPage(AutoYams* app, VideoCaptureWindow* ref)
	: AdvancedPage(1, app, ref)
{
	connect(wnd->ui.config_addBtn, SIGNAL(pressed()), this, SLOT(addConfig()));
	connect(wnd->ui.config_setBtn, SIGNAL(pressed()), this, SLOT(setConfig()));

	connect(wnd->ui.config_defaultDeviceBtn, SIGNAL(pressed()), this, SLOT(setDefaultDevice()));
	connect(wnd->ui.config_defaultConfigBtn, SIGNAL(pressed()), this, SLOT(setDefaultConfig()));

	connect(wnd->ui.config_addBtn, SIGNAL(pressed()), wnd, SLOT(refreshConfigList()));
	connect(wnd->ui.config_setBtn, SIGNAL(pressed()), wnd, SLOT(refreshConfigList()));
}

void ConfigPage::handle()
{
	//
	updateConfigCB();
}

bool ConfigPage::pressOkButton()
{
	return true;
}

void ConfigPage::updateConfigCB()
{
	wnd->ui.config_pickCB->clear();
	QStringList allConfigs = wnd->configManager->getConfigs();
	for (QString& configName : allConfigs)
		wnd->ui.config_pickCB->addItem(configName);
}

void ConfigPage::addConfig()
{
	QString configName = wnd->ui.config_nameEdit->text();
	if (configName.size() < 3)
		return;

	QString currentDevice = wnd->devices[wnd->currentDeviceIndex]->getAlias();
	if (wnd->configManager->isConfigPath_free(configName)
		&& wnd->configManager->isConfigSurename_free(configName, currentDevice))
	{
		QString configPath = ConfigFile::Create(configName);
		if (!configPath.isEmpty())
		{
			wnd->configManager->addConfig(currentDevice,
				configName, configPath, configName);
			updateConfigCB();
		}
	}
}

void ConfigPage::setConfig()
{
	QString configSurename = wnd->ui.config_nameEdit->text();
	if (configSurename.size() < 3)
		return;

	QString currentDevice = wnd->devices[wnd->currentDeviceIndex]->getAlias();
	if (wnd->configManager->isConfigSurename_free(configSurename, currentDevice))
	{
		wnd->configManager->setConfig(currentDevice,
			wnd->ui.config_pickCB->currentText(), configSurename);
		updateConfigCB();
	}
}

void ConfigPage::setDefaultDevice()
{
	if (wnd->currentDeviceIndex >= 0)
		wnd->configManager->setDefaultDevice(wnd->devices[wnd->currentDeviceIndex]->getAlias());
}

void ConfigPage::setDefaultConfig()
{
	if (wnd->currentDeviceIndex >= 0)
		wnd->configManager->setDefaultConfig(wnd->devices[wnd->currentDeviceIndex]->getAlias(), wnd->ui.configCB->currentText());
}
