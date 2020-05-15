#include <AutoYams\FileDebug.h>
#include <QTextStream>

FileDebug* FileDebug::instance = nullptr;

FileDebug::FileDebug()
	: output("output.txt")
{
	output.open(QFile::WriteOnly | QFile::Text | QFile::Append);
	output.resize(0);
}

FileDebug * FileDebug::write(QString content)
{
	if (instance == nullptr)
		instance = new FileDebug();
	QTextStream out(&instance->output);
	out << content << "\n";
	return instance;
}

FileDebug::~FileDebug()
{
	output.close();
}
