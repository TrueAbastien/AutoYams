#pragma once
#include <AutoYams.h>

class Page : public QObject
{
	Q_OBJECT

public:
	Page(int id, AutoYams* ref = 0) : app(ref), ID(id) { }

	virtual void handle() = 0;

protected:
	AutoYams* app;
	int ID;
};