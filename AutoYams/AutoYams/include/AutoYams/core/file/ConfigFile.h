#pragma once
#include <QFile>
#include <QMap>
#include <QDir>

/**
* \class ConfigFile
* \brief File for configuration
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Configuration file used to change propreties of the current Video Capture output.
*/
class ConfigFile : public QFile
{
public:
	/**
	* \brief Default constructor
	* \param fileName Name of the file to open the config from (aka. data model)
	*
	* Load and read data from a config file for an Image propreties.
	*/
	explicit ConfigFile(QString fileName = "");
	/**
	* \brief Default deconstructor
	*
	* Close file when requiered to free its use.
	*/
	~ConfigFile();

	/**
	* \brief Load specified file
	* \param file Name of the current file to load
	*
	* Change file name and load it again meaning only one instance
	* is required to access the directory data.
	*/
	void Load(QString file);

	/**
	* \brief Read current file data
	* \return Verification on file reading
	*
	* Read file data if possible, then store it in the instance propreties.
	*/
	bool readFile();
	/**
	* \brief Write current file data
	* \return Verification on file writing
	*
	* Write file data, if possible, from stored and modified propreties.
	*/
	bool writeFile();

	/**
	* \brief Change value on specified key
	* \param key Specified key where to change data on
	* \param data New data to set on specified key
	*
	* Change data in Map propreties but doesn't save it in current file.
	*/
	void set(QString key, QString data);
	/**
	* \brief Get String value from specified key.
	* \param key Specified key where to take data from
	* \return Value on specified key
	*
	* Return mapped value on specified key from propreties, not file data.
	*/
	QString& get(QString key);

	/**
	* \brief Access raw data in debug string to display in console
	* \return Debug string resulting from file data read
	*
	* After reading data in configfile, return a raw debug string to display data.
	*/
	QString Debug() const;

	/**
	* \brief Static method to create a specific Config File
	* \param fileName Name of the new file
	* \return Filepath if a new file is created, otherwise, returns an empty string.
	*/
	static QString Create(QString fileName);

private:
	/**
	* Mapped content created on file data.
	*/
	QMap<QString, QString> content;
	/**
	* List of all possible keys (aka. rules).
	*/
	QList<QString> rules;

	/**
	* \brief Setting all rules
	* \param rules List of all new rules
	*
	* Replace every rules by the specified ones.
	*/
	void setRules(QStringList rules);
	/**
	* \brief Add new rules
	* \param rules List of all new rules
	*
	* Add rules in propreties.
	*/
	void addRules(QStringList rules);
};