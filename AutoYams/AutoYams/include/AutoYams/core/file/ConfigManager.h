#pragma once
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

class ConfigManager : public QObject
{
	Q_OBJECT

private:
	QFile file;
	QJsonDocument buffer;
	QJsonObject root;

public:
	ConfigManager();
	~ConfigManager();
	void read();

	// GETTERS
	QStringList getConfigs_fromDevice(const QString& deviceID);
	QStringList getConfigs();
	QString getName_fromConfigSurename(const QString& surename, const QString& device);
	QString getPath_fromConfigName(const QString& name);
	QString getPath_fromConfigSurename(const QString& surename, const QString& device);
	QString getDefaultDevice();
	bool isConfigPath_free(const QString& path);
	bool isConfigSurename_free(const QString& surename, const QString& device);
	bool isDevice_saved(const QString& device);

public slots:
	void save();
	void addDevice(QString device);
	void addConfig(QString device, QString name, QString path, QString surename);
	void setConfig(QString device, QString name, QString surename);
	void setDefaultConfig(QString device, QString surename);
	void setDefaultDevice(QString device);
	void removeDefaultConfig();
};