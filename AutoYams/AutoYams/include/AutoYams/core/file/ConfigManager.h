#pragma once
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

/**
* \class ConfigManager
* \brief Manager of configuration in Video Window
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Manager in configuration to modify main JSON file.
*/
class ConfigManager : public QObject
{
	Q_OBJECT

private:
	/**
	* JSON file to get and post data.
	*/
	QFile file;
	/**
	* Data buffer from main JSON file.
	*/
	QJsonDocument buffer;
	/**
	* Root object containing all data to read from and update in through methods.
	*/
	QJsonObject root;

public:
	/**
	* \brief Default constructor
	*
	* Instantiate propreties and read JSON file data.
	*/
	ConfigManager();
	/**
	* \brief Default deconstructor
	*
	* Close and save JSON file and its new data.
	*/
	~ConfigManager();
	/**
	* \brief Read data from JSON file.
	*
	* Read data and store it in root object.
	*/
	void read();

	/**
	* \brief Get all configs from specified device
	* \param deviceID Device alias created from a specific device name
	* \return List of all configs resulting from the search
	*
	* Get configurations from a specific device alias in root object, not file data.
	*/
	QStringList getConfigs_fromDevice(const QString& deviceID);
	/**
	* \brief Get all existing configs
	* \return List of all configs resulting from the search
	*
	* Get all configurations store and declared in root object.
	*/
	QStringList getConfigs();
	/**
	* \brief Get config name from its surename
	* \param surename Specific config surename
	* \param device Device the surename is issued from
	* \return Name result from the search
	*
	* Get name for a specific configuration surename on a specific device.
	*/
	QString getName_fromConfigSurename(const QString& surename, const QString& device);
	/**
	* \brief Get config path from its name
	* \param name Specific config name
	* \return Path of the specific config
	*
	* Get path from a specific configuration name on any device.
	*/
	QString getPath_fromConfigName(const QString& name);
	/**
	* \brief Get config path from its surename
	* \param surename Specific config surename
	* \param device Device the surename is issued from
	* \return Path of the specific config
	*
	* Get path from a specific configuration surename on a specific device.
	*/
	QString getPath_fromConfigSurename(const QString& surename, const QString& device);
	/**
	* \brief Get default device name
	* \return Result of the search
	*
	* Look for and return the default device from stored data.
	*/
	QString getDefaultDevice();
	/**
	* \brief Verify if specified config path is free
	* \param path Specified path to verify
	* \return Result of the verification
	*
	* Verify if a configuration is already using the specified path.
	*/
	bool isConfigPath_free(const QString& path);
	/**
	* \brief Verify if specified config surename is free on a specific device
	* \param surename Specific config surename
	* \param device Specific device name/alias
	* \return Result of the verification
	*
	* Verify if a configuration surename is already defined for a specific device.
	*/
	bool isConfigSurename_free(const QString& surename, const QString& device);
	/**
	* \brief Verify if specified device is already saved or not
	* \param device Specific device name/alias
	* \return Result of the verification
	*
	* Verify if a device has already been saved in root object.
	*/
	bool isDevice_saved(const QString& device);

public slots:
	/**
	* \brief Save root object in JSON file
	*
	* Take data in root object to store it in JSON file.
	*/
	void save();
	/**
	* \brief Add new device to root object
	* \param device New device name
	*
	* Add new device in root object with specified device name.
	*/
	void addDevice(QString device);
	/**
	* \brief Add and define new config to a specific device
	* \param device Name of the default device
	* \param name Name of the new config
	* \param path Path of the new config
	* \param surename Surename of the new config for specified device
	*
	* Create a new configuration, attributes it to the specified device and save it all in root object.
	*/
	void addConfig(QString device, QString name, QString path, QString surename);
	/**
	* \brief Attach config to a specific device with a specific surename
	* \param device Specified device name
	* \param name Specified config name
	* \param surename Specified config surename
	*
	* Attach a specific configuration to a specified device with a specific surename.
	*/
	void setConfig(QString device, QString name, QString surename);
	/**
	* \brief Change default config of a specific device
	* \param device Specific device to change the default config of
	* \param surename New default config
	*
	* Set the default configuration of a specific device from its surename.
	*/
	void setDefaultConfig(QString device, QString surename);
	/**
	* \brief Change default device of the application
	* \param device New default device name
	*
	* Set the default device loaded on application construction.
	*/
	void setDefaultDevice(QString device);
	/**
	* \brief Remove default config
	*
	* Set default config to 'none' in root object.
	*/
	void removeDefaultConfig();
};