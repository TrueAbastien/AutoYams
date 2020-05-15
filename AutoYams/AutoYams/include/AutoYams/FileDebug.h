#pragma once
#include <QFile>

/**
* \class FileDebug
* \brief Singleton console file system for debugging purpose
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Append 'output.txt' file in local files with any written content.
*/
class FileDebug
{
private:
	/**
	* Singleton unique & static instance of the class.
	*/
	static FileDebug* instance;
	/**
	* \brief Default constructor
	*
	* Empty the output file to write anew.
	*/
	FileDebug();

public:
	/**
	* Output file in which to write content ('output.txt').
	*/
	QFile output;

	/**
	* \brief Static method write content in file
	* \param content New content to append
	* \return Singleton instance for easier access
	*
	* Write specified content in the output file as a new line.
	*/
	static FileDebug* write(QString content);
	/**
	* \brief Default deconstructor
	*
	* Close output file and free its memory.
	*/
	~FileDebug();
};