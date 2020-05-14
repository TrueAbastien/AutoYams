#pragma once
#include <QFile>
#include <QMap>
#include <QDir>

class ConfigFile : public QFile
{
public:
	explicit ConfigFile(QString fileName = "");
	~ConfigFile();

	void Load(QString file);

	bool readFile();
	bool writeFile();

	void set(QString key, QString data);
	QString& get(QString key);

	QString Debug() const;

	static QString Create(QString fileName);

private:
	QMap<QString, QString> content;
	QList<QString> rules;

	void setRules(QStringList rules);
	void addRules(QStringList rules);
};