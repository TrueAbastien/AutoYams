#pragma once
#include <AutoYams.h>

/**
* \class Page
* \brief Abstract page for any current window pagination
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/05/15 $
*
* Representation of any page and its content.
*/
class Page : public QObject
{
	Q_OBJECT

public:
	/**
	* \brief Default constructor
	* \param id ID number of the current page
	* \param ref Reference of the main page to access for further connection
	*
	* Initialize instance by copying the arguments as propreties.
	*/
	Page(int id, AutoYams* ref = 0) : app(ref), ID(id) { }

	/**
	* \brief Abstract method called on page selection
	*
	* Called whenever a page is selected or gran focus on a window display.
	*/
	virtual void handle() = 0;

protected:
	/**
	* Reference of the current main application window.
	*/
	AutoYams* app;
	/**
	* Page default ID in his window.
	*/
	int ID;
};