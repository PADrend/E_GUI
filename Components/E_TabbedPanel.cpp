/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_TabbedPanel.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_TabbedPanel::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::TabbedPanel,E_TabbedPanel>();

	using namespace GUI;

	/**
	 * [ESMF] Tab TabbedPanel.addTab(string title,con)
	 * \deprecated
	 */
	ES_MFUN(typeObject,TabbedPanel,"addTab",2,2,
				EScript::create(thisObj->
							createTab(parameter[0].toString(),
							parameter[1].to<Container*>(rt))))
							

	//! [ESMF] Tab TabbedPanel.createTab(string title)
	ES_MFUN(typeObject,TabbedPanel,"createTab",1,1,				EScript::create(thisObj->createTab(parameter[0].toString())))


	//! [ESMF] Number TabbedPanel.getActiveTabIndex()
	ES_MFUN(typeObject,TabbedPanel,"getActiveTabIndex", 0,0, 	(thisObj->getActiveTabIndex()))

	//! [ESMF] self TabbedPanel.setActiveTabIndex(Number)
	ES_MFUN(typeObject,TabbedPanel,"setActiveTabIndex", 1,1, 	(thisObj->setActiveTabIndex(parameter[0].to<int32_t>(rt)),thisEObj))
}

}
