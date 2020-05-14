#include "VideoCaptureWindow.h"

// Pages
#include <AutoYams\core\page\advanced\VideoPage.h>
#include <AutoYams\core\page\advanced\ConfigPage.h>


VideoCaptureWindow::VideoCaptureWindow(AutoYams * wnd)
	: QDialog(nullptr), app(wnd)
{
	ui.setupUi(this);

	configFile = std::make_shared<ConfigFile>();
	configManager = std::make_shared<ConfigManager>();

	connect(ui.pagination, SIGNAL(currentChanged(int)), this, SLOT(setCurrentPage(int)));

	connect(ui.okButton, SIGNAL(pressed()), this, SLOT(pressOkButton()));
	connect(ui.deviceCB, SIGNAL(currentIndexChanged(int)), this, SLOT(selectDevice(int)));
	connect(ui.configCB, SIGNAL(currentIndexChanged(int)), this, SLOT(selectConfig(int)));

	connect(ui.form_brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBrightness(int)));
	connect(ui.form_contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
	connect(ui.form_framerateSlider, SIGNAL(valueChanged(int)), this, SLOT(changeFramerate(int)));
	connect(ui.form_zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(changeZoom(int)));

	allPages.append(new VideoPage(app, this));
	allPages.append(new ConfigPage(app, this));

	//setCurrentPage(0);
	refreshDeviceList();

	this->close();
}

VideoCaptureWindow::~VideoCaptureWindow()
{
	saveConfig();
	configManager->save();
}

void VideoCaptureWindow::display(int pageID)
{
	setCurrentPage(pageID);
	this->open();
}

void VideoCaptureWindow::closeEvent(QCloseEvent * _event)
{
	saveConfig();
	configManager->save();
	QDialog::closeEvent(_event);
}

void VideoCaptureWindow::setCurrentPage(int pageID)
{
	if (pageID < 0 || pageID >= allPages.length())
		currentPage = nullptr;
	else
	{
		currentPage = allPages[pageID];
		currentPage->handle();
		ui.pagination->setCurrentIndex(pageID);
	}
}

void VideoCaptureWindow::refreshDeviceList()
{
	VideoCaptureDevice::get(devices);

	ui.deviceCB->clear();
	ui.deviceCB->addItem("---");
	for (auto& device : devices)
	{
		ui.deviceCB->addItem(device->getName());
		if (!configManager->isDevice_saved(device->getAlias()))
			configManager->addDevice(device->getAlias());
	}

	int index = findDeviceIndex_byAlias(configManager->getDefaultDevice());
	if (index < 0)
		configManager->removeDefaultConfig();
	else ui.deviceCB->setCurrentIndex(index + 1);
}

void VideoCaptureWindow::refreshConfigList()
{
	ui.configCB->clear();
	if (currentDeviceIndex < 0)
		return;

	QStringList configs = configManager->getConfigs_fromDevice(devices[currentDeviceIndex]->getAlias());
	for (QString& config : configs)
		ui.configCB->addItem(config);
}

int VideoCaptureWindow::findDeviceIndex_byAlias(QString device)
{
	for (int ii = 0; ii < devices.size(); ++ii)
		if (devices[ii]->getAlias() == device)
			return ii;
	return -1;
}

void VideoCaptureWindow::pressOkButton()
{
	if (currentPage != nullptr)
	{
		if (currentPage->pressOkButton())
			this->close();
	}
	else this->close();
}

void VideoCaptureWindow::selectDevice(int index)
{
	if (index == 0)
		app->video->release();
	else if (index - 1 < ui.deviceCB->count())
		app->video->open(index - 1);

	currentDeviceIndex = index - 1;

	if (currentPage != nullptr)
		currentPage->selectDevice(index);

	refreshConfigList();
	ui.configCB->setCurrentIndex(0);
}

void VideoCaptureWindow::selectConfig(int index)
{
	saveConfig();
	currentConfigIndex = index;
	if (currentDeviceIndex < 0)
		return;

	loadConfig(configManager->getPath_fromConfigSurename(
		ui.configCB->itemText(index),
		devices[currentDeviceIndex]->getAlias()));
}

void VideoCaptureWindow::saveConfig()
{
	if (configFile != nullptr)
	{
		configFile->set("brightness", QString::number(ui.form_brightnessSlider->value()));
		configFile->set("contrast", QString::number(ui.form_contrastSlider->value()));
		configFile->set("framerate", QString::number(ui.form_framerateSlider->value()));
		configFile->set("zoom", QString::number(ui.form_zoomSlider->value()));
		configFile->writeFile();
	}
}

void VideoCaptureWindow::loadConfig(QString file)
{
	if (configFile != nullptr && file != "---")
	{
		configFile->Load(file);
		configFile->readFile();
		ui.form_brightnessSlider->setValue(configFile->get("brightness").toInt());
		ui.form_contrastSlider->setValue(configFile->get("contrast").toInt());
		ui.form_framerateSlider->setValue(configFile->get("framerate").toInt());
		ui.form_zoomSlider->setValue(configFile->get("zoom").toInt());
	}
}

void VideoCaptureWindow::changeBrightness(int val)
{
	if (currentPage != nullptr)
	{
		currentPage->changeBrightness(val);
		//configFile->set("brightness", QString::number(val));
	}
}

void VideoCaptureWindow::changeContrast(int val)
{
	if (currentPage != nullptr)
	{
		currentPage->changeContrast(val);
		//configFile->set("contrast", QString::number(val));
	}
}

void VideoCaptureWindow::changeFramerate(int val)
{
	if (currentPage != nullptr)
	{
		currentPage->changeFramerate(val);
		//configFile->set("framerate", QString::number(val));
	}
}

void VideoCaptureWindow::changeZoom(int val)
{
	double newVal = (double)val / 100.0;
	if (currentPage != nullptr)
	{
		currentPage->changeZoom(newVal);
		//configFile->set("zoom", QString::number(newVal));
	}
}
