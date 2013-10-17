/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Tab.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Tab::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	addFactory<GUI::TabbedPanel::Tab,E_Tab>();

	using namespace GUI;

	//! [ESMF] string Tab.getTitle()
	ES_MFUN(typeObject,TabbedPanel::Tab,"getTitle",0,0,(thisObj->getTitle()))

	//! [ESMF] self Tab.setTitle(string)
	ES_MFUN(typeObject,TabbedPanel::Tab,"setTitle",1,1,(thisObj->setTitle(parameter[0].toString()),thisEObj))

}

}
