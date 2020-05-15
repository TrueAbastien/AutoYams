#include <AutoYams\core\file\ConfigManager.h>
#include <QJsonArray>

#include <AutoYams\core\exception\AdvancedException.h>

ConfigManager::ConfigManager()
{
	// Open file
	file.setFileName("Resources/config/config.json");
	file.open(QFile::ReadWrite | QFile::Text | QFile::ExistingOnly);

	// Read JSON content
	this->read();
}

ConfigManager::~ConfigManager()
{
	this->save();
	file.close();
}

void ConfigManager::read()
{
	// Read and throw errors
	QJsonParseError error;
	buffer = QJsonDocument::fromJson(file.readAll(), &error);

	// Select root object of buffer
	root = buffer.object();
	file.close();
}

QStringList ConfigManager::getConfigs_fromDevice(const QString & deviceID)
{
	QStringList resultBuffer; QString defaultConfig;
	QJsonArray allDevices = root["device"].toObject()["all"].toArray();
	for (auto& device : allDevices)
		if (device.toObject()["name"].toString() == deviceID)
		{
			for (auto& config : device.toObject()["configs"].toArray())
				resultBuffer.append(config.toObject()["surename"].toString());
			defaultConfig = device.toObject()["default"].toString();

			resultBuffer.removeAll(defaultConfig);
			resultBuffer.push_front(defaultConfig);
			break;
		}
	return resultBuffer;
}

QStringList ConfigManager::getConfigs()
{
	QStringList result;
	QJsonArray allConfigs = root["config"].toObject()["all"].toArray();
	for (auto& config : allConfigs)
		result.append(config.toObject()["name"].toString());
	return result;
}

QString ConfigManager::getName_fromConfigSurename(const QString & surename, const QString& deviceName)
{
	QJsonArray allDevices = root["device"].toObject()["all"].toArray();
	for (auto& device : allDevices)
		if (device.toObject()["name"].toString() == deviceName)
		{
			QJsonArray deviceConfigs = device.toObject()["configs"].toArray();
			for (auto& config : deviceConfigs)
				if (config.toObject()["surename"].toString() == surename)
					return config.toObject()["name"].toString();
		}
	return "";
}

QString ConfigManager::getPath_fromConfigName(const QString & name)
{
	QJsonArray allConfigs = root["config"].toObject()["all"].toArray();
	for (auto& config : allConfigs)
		if (config.toObject()["name"].toString() == name)
			return config.toObject()["path"].toString();
	return "";
}

QString ConfigManager::getPath_fromConfigSurename(const QString & surename, const QString& deviceName)
{
	return getPath_fromConfigName(getName_fromConfigSurename(surename, deviceName));
}

QString ConfigManager::getDefaultDevice()
{
	return root["device"].toObject()["default"].toString();
}

bool ConfigManager::isConfigPath_free(const QString & path)
{
	QJsonArray allConfigs = root["config"].toObject()["all"].toArray();
	for (auto& config : allConfigs)
		if (config.toObject()["path"].toString() == path)
			return false;
	return true;
}

bool ConfigManager::isConfigSurename_free(const QString & surename, const QString & deviceName)
{
	QJsonArray allDevices = root["device"].toObject()["all"].toArray();
	for (auto& device : allDevices)
		if (device.toObject()["name"].toString() == deviceName)
		{
			QJsonArray specificConfigs = device.toObject()["configs"].toArray();
			for (auto& config : specificConfigs)
				if (config.toObject()["surename"].toString() == deviceName)
					return false;
			return true;
		}
	return true;
}

bool ConfigManager::isDevice_saved(const QString & deviceName)
{
	QJsonArray allDevices = root["device"].toObject()["all"].toArray();
	for (auto& device : allDevices)
		if (device.toObject()["name"].toString() == deviceName)
			return true;
	return false;
}

void ConfigManager::addDevice(QString device)
{
	QJsonObject defaultObject
	{
		{ "name", "default" },
		{ "surename", "default" }
	};
	QJsonArray devices = root["device"].toObject()["all"].toArray(),
		defaultConfigs{ defaultObject };
	devices.append({
		{
			{ "name", device },
			{ "default", "default" },
			{ "configs", defaultConfigs }
		}
	});
	QJsonObject deviceConfig = root["device"].toObject();
	deviceConfig.find("all").value() = devices;
	root.find("device").value() = deviceConfig;
}

void ConfigManager::addConfig(QString device, QString name, QString path, QString surename)
{
	QJsonArray configs = root["config"].toObject()["all"].toArray();
	configs.append({
		{
			{ "name", name },
			{ "path", path }
		}
	});
	QJsonObject newConfig = root["config"].toObject();
	newConfig.find("all").value() = configs;
	root.find("config").value() = newConfig;

	this->setConfig(device, name, surename);
}

void ConfigManager::setConfig(QString deviceName, QString name, QString surename)
{
	QJsonArray deviceConfigs, allDevices = root["device"].toObject()["all"].toArray();
	for (auto& device : allDevices)
		if (device.toObject()["name"].toString() == deviceName)
		{
			deviceConfigs = device.toObject()["configs"].toArray();
			deviceConfigs.append({
				{
					{ "name", name },
					{ "surename",  surename }
				}
			});

			QJsonObject currentDevice = device.toObject();
			currentDevice.find("configs").value() = deviceConfigs;
			device = currentDevice;

			QJsonObject newDevice = root["device"].toObject();
			newDevice.find("all").value() = allDevices;
			root.find("device").value() = newDevice;

			return;
		}
}

void ConfigManager::setDefaultConfig(QString deviceName, QString surename)
{
	QJsonArray allDevices = root["device"].toObject()["all"].toArray();
	for (auto& device : allDevices)
		if (device.toObject()["name"].toString() == deviceName)
		{
			QJsonObject currentDevice = device.toObject();
			currentDevice.find("default").value() = surename;
			device = currentDevice;

			QJsonObject newDevice = root["device"].toObject();
			newDevice.find("all").value() = allDevices;
			root.find("device").value() = newDevice;

			return;
		}
}

void ConfigManager::setDefaultDevice(QString device)
{
	QJsonObject newDevice = root["device"].toObject();
	newDevice.find("default").value() = device;
	root.find("device").value() = newDevice;
}

void ConfigManager::removeDefaultConfig()
{
	setDefaultDevice("none");
}

void ConfigManager::save()
{
	// Open file for modification
	file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);

	// Write the content
	buffer.setObject(root);
	file.write(buffer.toJson());

	// Close the opened file
	file.close();
}