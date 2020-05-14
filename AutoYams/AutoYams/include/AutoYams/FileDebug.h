#pragma once
#include <QFile>

class FileDebug
{
private:
	static FileDebug* instance;
	FileDebug();

public:
	QFile output;

	static FileDebug* write(QString content);
	~FileDebug();
};