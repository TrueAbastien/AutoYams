#include <AutoYams/core/file/ConfigFile.h>

#include <QTextStream>
#include <sstream>

#include <AutoYams\core\exception\AdvancedException.h>


ConfigFile::ConfigFile(QString fileName)
{
	// Load file if possible
	if (!fileName.isEmpty())
	{
		Load(fileName);
	}

	// Define default rules
	setRules({ "brightness","contrast","framerate","zoom" });
}

ConfigFile::~ConfigFile()
{
	this->close();
}

void ConfigFile::Load(QString file)
{
	// Close if already opened
	if (this->isOpen())
		this->close();

	// Open New file
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
	// Verify if opened
	if (!isOpen())
		return false;

	// Read every line to get data
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
	// Verify is opened
	if (!isOpen())
		return false;

	// Write data
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
	// Verify if the file exists
	QFile newConfig("Resources/config/" + fileName + ".config");
	newConfig.open(QFile::ExistingOnly);
	if (newConfig.isOpen())
	{
		newConfig.close();
		return "";
	}

	// Create new file
	newConfig.open(QFile::ReadWrite | QFile::Text);
	newConfig.close();

	// Set the file basic content
	ConfigFile file(fileName);
	file.set("brightness", "0");
	file.set("contrast", "1");
	file.set("framerate", "30");
	file.set("zoom", "100");
	file.writeFile();

	return fileName;
}
