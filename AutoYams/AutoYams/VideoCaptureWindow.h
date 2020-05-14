#pragma once
#include <QDialog>
#include <AutoYams.h>
#include "ui_VideoCapture.h"

#include <AutoYams\opencv\VideoCaptureDevice.h>
#include <AutoYams\core\file\ConfigFile.h>
#include <AutoYams\core\file\ConfigManager.h>

class AdvancedPage;

class VideoCaptureWindow : public QDialog
{
	Q_OBJECT

public:
	explicit VideoCaptureWindow(AutoYams* wnd);
	~VideoCaptureWindow();

	Ui::VideoCapture ui;

	QList<std::shared_ptr<VideoCaptureDevice>> devices;
	std::shared_ptr<ConfigFile> configFile;
	std::shared_ptr<ConfigManager> configManager;
	int currentDeviceIndex, currentConfigIndex;

	void display(int pageID);

	void closeEvent(QCloseEvent* event) override;

private:
	AutoYams* app;

	AdvancedPage* currentPage = nullptr;
	QList<AdvancedPage*> allPages;

	int findDeviceIndex_byAlias(QString device);

private slots:
	void setCurrentPage(int);
	
	void pressOkButton();

	void selectDevice(int);
	void selectConfig(int);

	void saveConfig();
	void loadConfig(QString);

	void changeBrightness(int);
	void changeContrast(int);
	void changeFramerate(int);
	void changeZoom(int);

public slots:
	void refreshDeviceList();
	void refreshConfigList();
};