/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ListView.h"

#include <GUI/GUI.h>
#include <E_Geometry/E_Vec2.h>
#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI{

//! [static] initMembers
void E_ListView::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::ListView,E_ListView>();

	using namespace GUI;

	//! self ListView.addMarking( Component )
	ES_MFUN(typeObject,ListView, "addMarking", 1,1,				(thisObj->addMarking(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! self ListView.clearMarkings( )
	ES_MFUN(typeObject,ListView, "clearMarkings", 0,0,			(thisObj->clearMarkings(),thisEObj))

	//! Container ListView.getContentContainer( )
	ES_MFUN(typeObject,ListView, "getContentContainer", 0,0,	EScript::create(thisObj->getContentContainer()))

	//! Array ListView.getMarkings( )
	ES_MFUN(typeObject,const ListView, "getMarkings", 0,0,  	EScript::Array::create(thisObj->getMarkings()))

	//! Number ListView.getEntryHeight( )
	ES_MFUN(typeObject,const ListView, "getEntryHeight", 0,0, 	(thisObj->getEntryHeight()))

	//! self ListView.isMarked( Component )
	ES_MFUN(typeObject,const ListView, "isMarked", 1,1,			(thisObj->isMarked(parameter[0].to<GUI::Component*>(rt))))

	//! self ListView.removeMarking( Component )
	ES_MFUN(typeObject,ListView, "removeMarking", 1,1,			(thisObj->removeMarking(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! self ListView.scrollTo( Vec2 pos [,Number duration=0] )
	ES_MFUN(typeObject,ListView, "scrollTo", 1,2,				(thisObj->scrollTo(parameter[0].to<const Geometry::Vec2&>(rt),parameter[1].toFloat(0)), thisEObj));

	//! self ListView.setEntryHeight(Number )
	ES_MFUN(typeObject,ListView, "setEntryHeight", 1,1, 		(thisObj->setEntryHeight(parameter[0].to<float>(rt)),thisEObj))

	//! self ListView.setMarking( Component )
	ES_MFUN(typeObject,ListView, "setMarking", 1,1,				(thisObj->setMarking(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! self ListView.setMarkings( Array )
	ES_MFUNCTION(typeObject, ListView, "setMarkings", 1,1, {
		EScript::Array * a = parameter[0].to<EScript::Array*>(rt);
		GUI::ListView::markingList_t markings;
		for(const auto & eMarkedComponent : *a) {
			markings.push_back(**EScript::assertType<E_Component>(rt, eMarkedComponent));
		}
		thisObj->setMarkings(markings);
		return thisEObj;
	})
	
	// ----

	//! Array ListView.getData( )
	declareConstant(typeObject, "getData", typeObject->getAttribute("getMarkings").getValue()); // alias

	//! self ListView.setData( Array )
	declareConstant(typeObject, "setData", typeObject->getAttribute("setMarkings").getValue()); // alias

	declareConstant(&lib,"AT_LEAST_ONE_MARKING",(GUI::ListView::AT_LEAST_ONE_MARKING));
	declareConstant(&lib,"AT_MOST_ONE_MARKING",(GUI::ListView::AT_MOST_ONE_MARKING));

}

//---

}
