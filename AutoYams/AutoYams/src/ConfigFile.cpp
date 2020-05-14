#include <AutoYams/core/file/ConfigFile.h>

#include <QTextStream>
#include <sstream>


ConfigFile::ConfigFile(QString fileName)
{
	if (!fileName.isEmpty())
		Load(fileName);

	setRules({ "brightness","contrast","framerate","zoom" });
}

ConfigFile::~ConfigFile()
{
	this->close();
}

void ConfigFile::Load(QString file)
{
	if (this->isOpen())
		this->close();

	this->setFileName("Resources/config/" + file + ".config");
	this->open(QFile::ReadWrite | QFile::Text | QFile::ExistingOnly);
}

void ConfigFile::setRules(QStringList _rules)
{
	rules.clear();
	addRules(_rules);
}

void ConfigFile::addRules(QStringList _rules)
{
	for (QString& rule : _rules)
		rules.append(rule);
}

bool ConfigFile::readFile()
{
	if (!isOpen())
		return false;

	std::string line, value;
	QString processedValue;
	QTextStream in(this);
	while (!in.atEnd())
	{
		line = in.readLine().toStdString();

		for (QString rule : rules)
		{
			if (line.find(rule.toStdString() + "=") == 0)
			{
				if (line.size() == rule.size() + 1)
				{
					value = "";
				}
				else
				{
					std::stringstream ss(line.c_str() + rule.length() + 1);
					ss >> value;
				}
				this->set(rule, QString(value.c_str()));
			}
		}
	}

	return true;
}

bool ConfigFile::writeFile()
{
	if (!isOpen())
		return false;

	this->resize(0);
	QString processedValue;
	QTextStream out(this);
	for (QString rule : rules)
		out << rule << "=" << content[rule] << '\n';

	return true;
}

void ConfigFile::set(QString key, QString data)
{
	this->content[key] = data;
}

QString& ConfigFile::get(QString key)
{
	return this->content[key];
}

QString ConfigFile::Debug() const
{
	QString res = "";
	foreach(QString key, content.keys())
		res += key + "->" + content[key] + " - ";
	return res;
}

QString ConfigFile::Create(QString fileName)
{
	QFile newConfig("Resources/config/" + fileName + ".config");
	newConfig.open(QFile::ExistingOnly);
	if (newConfig.isOpen())
	{
		newConfig.close();
		return "";
	}

	newConfig.open(QFile::ReadWrite | QFile::Text);
	newConfig.close();

	ConfigFile file(fileName);
	file.set("brightness", "0");
	file.set("contrast", "1");
	file.set("framerate", "30");
	file.set("zoom", "100");
	file.writeFile();

	return fileName;
}
