/*
 * Copyright (C) 2016 Dhiraj Salian
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef OPENSKYPLANETARIUM_HPP_
#define OPENSKYPLANETARIUM_HPP_

#include "StelModule.hpp"
#include "StelGui.hpp"
#include<QString>
#include <QFont>

class OSPMainDialog;

//! This is used to dynamically load Open Sky Planetarium plugin into stellarium
class OpenSkyPlanetarium :public StelModule
{
	Q_OBJECT
public:

	/**
	*	Class constructor.
	*/
	OpenSkyPlanetarium();
	
	/**
	*	Class destructor.
	*/
	~OpenSkyPlanetarium();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class

	/**
	*	Init Open Sky Planetarium module
	*/
	virtual void init();
	
	/**
	*	This method is used to delete the instance of main Window
	*/
	virtual void deinit();
	virtual void update(double) {;}

	/**
	*	This method is used to reimplement the getCallOrder method
	*/
	virtual double getCallOrder(StelModuleActionName actionName) const;

	/**
	*	This method is used to show the plugin interface
	*/
	virtual bool configureGui(bool show);
private:
	QFont *font;
	OSPMainDialog *mainDialog;
	StelButton* toolbarButton;	
};


#include <QObject>
#include "StelPluginInterface.hpp"

//! This class is used by Qt to manage a plug-in interface
class OpenSkyPlanetariumPluginInterface : public QObject, public StelPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID StelPluginInterface_iid)
	Q_INTERFACES(StelPluginInterface)
public:

	/**
	*	 This method is the one called automatically by the StelModuleMgr just after loading the dynamic library
	*/
	virtual StelModule* getStelModule() const;

	/**
	*	This method is used to pass the information about the OpenSky Planetarium plugin.
	*/
	virtual StelPluginInfo getPluginInfo() const;
};

#endif /*OPENSKYPLANETARIUM_HPP_*/
