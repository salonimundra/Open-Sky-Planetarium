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

#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelLocaleMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelGui.hpp"
#include "StelGuiItems.hpp"

#include "OpenSkyPlanetarium.hpp"
#include "OSPMainDialog.hpp"

#include <QAction>
#include <QString>
#include <QDebug>
#include <stdexcept>

/*************************************************************************
 This method is the one called automatically by the StelModuleMgr just 
 after loading the dynamic library
*************************************************************************/
StelModule* OpenSkyPlanetariumPluginInterface::getStelModule() const
{	
	return new OpenSkyPlanetarium();
}

StelPluginInfo OpenSkyPlanetariumPluginInterface::getPluginInfo() const
{

	qDebug() << "[OpenSkyPlanetarium] __debug__ getplugininfo";
	Q_INIT_RESOURCE(OpenSkyPlanetarium);
	StelPluginInfo info;
	info.id = "OpenSkyPlanetarium";
	info.displayedName = N_("OpenSkyPlanetarium");
	info.authors = "IIT Bombay Interns";
	info.contact = "redcoder265@gmail.com";
	info.description = N_("An open source initiative for Planetarium shows in Open Sky");
	return info;
}

/*************************************************************************
 Constructor
*************************************************************************/
OpenSkyPlanetarium::OpenSkyPlanetarium()
{
	setObjectName("OpenSkyPlanetarium");
	mainDialog = new OSPMainDialog();
}

/*************************************************************************
 Destructor
*************************************************************************/
OpenSkyPlanetarium::~OpenSkyPlanetarium()
{

}

/*************************************************************************
 Reimplementation of the getCallOrder method
*************************************************************************/
double OpenSkyPlanetarium::getCallOrder(StelModuleActionName actionName) const
{
	if (actionName == StelModule::ActionDraw)
		return StelApp::getInstance().getModuleMgr().getModule("LandscapeMgr")->getCallOrder(actionName) + 1.;
	return 0.;
}

/*************************************************************************
Configure Gui
*************************************************************************/
bool OpenSkyPlanetarium::configureGui(bool show)
{
	return false;
}

/*************************************************************************
 Init our module
*************************************************************************/
void OpenSkyPlanetarium::init()
{
    try{

        addAction("actionShow_Main_Dialog", N_("OpenSkyPlanetarium"), N_("Show Open Sky Planetarium Window"), mainDialog, "visible", "Ctrl+Shift+P");

	//Create toolbar button
		StelGui* gui = dynamic_cast<StelGui*>(StelApp::getInstance().getGui());
		if (gui!=NULL)
		{
			toolbarButton =	new StelButton(NULL,
						       QPixmap(":/OpenSkyPlanetarium/bt_osp_on.png"),
						       QPixmap(":/OpenSkyPlanetarium/bt_osp_off.png"),
						       QPixmap(":/graphicGui/glow32x32.png"),
						       "actionShow_Main_Dialog");
			gui->getButtonBar()->addButton(toolbarButton, "065-pluginsGroup");
		}
	}
	catch (std::runtime_error &e)
	{
		qWarning() << "[OpemSkyPlanetarium] init() error: " << e.what();
		return;
	}
}

/*************************************************************************
Deinit our Module
*************************************************************************/
void OpenSkyPlanetarium::deinit()
{
    delete mainDialog;
}


