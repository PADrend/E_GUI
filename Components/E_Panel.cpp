/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Panel.h"

#include <GUI/GUI_Manager.h>
#include <E_Geometry/E_Vec2.h>
#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Panel::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Panel,E_Panel>();
	addFactory<GUI::Panel::NextRow,E_Component>();
	addFactory<GUI::Panel::NextColumn,E_Component>();

	using namespace GUI;

	//! [ESMF] self Panel.disableAutoBreak()
	ES_MFUN(typeObject,Panel,"disableAutoBreak",0,0,		(thisObj->disableAutoBreak(),thisEObj))

	//! [ESMF] self Panel.enableAutoBreak()
	ES_MFUN(typeObject,Panel,"enableAutoBreak",0,0,			(thisObj->enableAutoBreak(),thisEObj))

	//! Container Panel.getContentContainer( )
	ES_MFUN(typeObject,Panel, "getContentContainer",0,0,	EScript::create(thisObj->getContentContainer()))

	//! [ESMF] self Panel.nextColumn(Number)
	ES_MFUN(typeObject,Panel,"nextColumn",0,1,				(thisObj->nextColumn(parameter[0].toInt(0)),thisEObj))

	//! [ESMF] self Panel.nextRow(Number)
	ES_MFUN(typeObject,Panel,"nextRow",0,1,					(thisObj->nextRow(parameter[0].toInt(0)),thisEObj))

	//! [ESMF] self Panel.setMargin(Number)
	ES_MFUN(typeObject,Panel,"setMargin",1,1,				(thisObj->setMargin(parameter[0].to<int32_t>(rt)),thisEObj))

	//! [ESMF] self Panel.setPadding(Number)
	ES_MFUN(typeObject,Panel,"setPadding",1,1,				(thisObj->setPadding(parameter[0].to<int32_t>(rt)),thisEObj))

	//! self Panel.scrollTo( Vec2 pos [,Number duration] )
	ES_MFUN(typeObject,Panel, "scrollTo", 1,2, (parameter.count()>1 ?
			thisObj->scrollTo(parameter[0].to<const Geometry::Vec2&>(rt),parameter[1].to<float>(rt)) :
			thisObj->scrollTo(parameter[0].to<const Geometry::Vec2&>(rt)), thisEObj));

}

}
