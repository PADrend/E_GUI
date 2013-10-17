/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Menu.h"

#include <EScript/EScript.h>
#include <E_Geometry/E_Vec2.h>
#include "../ELibGUI.h"


namespace E_GUI {

//! [static] initMembers
void E_Menu::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Menu,E_Menu>();

	using namespace GUI;

	//! [ESMF] self Menu.open(Vec2 pos)
	ES_MFUN(typeObject,Menu,"open",1,1,		(thisObj->open(parameter[0].to<const Geometry::Vec2&>(rt)),thisEObj))

	//! [ESMF] self Menu.close()
	ES_MFUN(typeObject,Menu,"close",0,0,	(thisObj->close(),thisEObj))
}

}
