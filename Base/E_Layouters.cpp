/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Layouters.h"

#include "../ELibGUI.h"
#include "E_AbstractShape.h"
#include "Fonts/E_AbstractFont.h"

#include <GUI/GUI_Manager.h>
#include <EScript/EScript.h>

#include <Util/Factory/WrapperFactory.h>

#include <iostream>
#include <sstream>

using namespace GUI;
using namespace EScript;

namespace E_GUI {

//! (static)
E_Util::E_ObjectFactory<AbstractLayouter, E_AbstractLayouter> E_AbstractLayouter::factorySystem;

//! (static)
Type * E_AbstractLayouter::getTypeObject(){
	// [E_AbstractLayouter] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}
//! (static)
Type * E_FlowLayouter::getTypeObject(){
	// [E_FlowLayouter] ---|> [E_AbstractLayouter] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_AbstractLayouter::getTypeObject());
	return typeObject;
}

// -----
/**
 * [static]
 */
void E_AbstractLayouter::init(EScript::Namespace & lib) {
	{	// GUI.AbstractLayouter ---|> Object
		Type  * t = E_AbstractLayouter::getTypeObject();

		declareConstant(&lib,E_AbstractLayouter::getClassName(),t);

		addFactory<AbstractLayouter,E_AbstractLayouter>();
	}
	// --------------------------------------------------------------
	{	// GUI.FlowLayouter ---|> GUI.Layouter ---|> Object
		Type  * t = E_FlowLayouter::getTypeObject();

		declareConstant(&lib,E_FlowLayouter::getClassName(),t);

		//! [ESF] new FlowLayouter(margin,padding )
		ES_CTOR(t, 0,0, 									EScript::create(new FlowLayouter))

		//! [ESF] Bool FlowLayouter.disableAutoBreak()
		ES_MFUN(t, FlowLayouter, "disableAutoBreak", 0,0, 	(thisObj->setAutoBreak(false),thisEObj))

		//! [ESF] Bool FlowLayouter.enableAutoBreak()
		ES_MFUN(t, FlowLayouter, "enableAutoBreak", 0,0, 	(thisObj->setAutoBreak(true),thisEObj))

		//! [ESF] Bool FlowLayouter.getAutoBreak()
		ES_MFUN(t, const FlowLayouter, "getAutoBreak", 0,0, thisObj->getAutoBreak())

		//! [ESF] Number FlowLayouter.getMargin()
		ES_MFUN(t, const FlowLayouter, "getMargin", 0,0,	thisObj->getMargin())

		//! [ESF] Number FlowLayouter.getPadding()
		ES_MFUN(t, const FlowLayouter, "getPadding", 0,0, 	thisObj->getPadding())
		
		//! [ESF] self FlowLayouter.setAutoBreak(Bool)
		ES_MFUN(t, FlowLayouter, "setAutoBreak", 1,1, 		(thisObj->setAutoBreak(parameter[0].toBool()),thisEObj))
		
		//! [ESF] self FlowLayouter.setMargin(Number)
		ES_MFUN(t, FlowLayouter, "setMargin", 1,1, 			(thisObj->setMargin(parameter[0].to<int32_t>(rt)),thisEObj))
		
		//! [ESF] self FlowLayouter.setPadding(Number)
		ES_MFUN(t, FlowLayouter, "setPadding", 1,1, 		(thisObj->setPadding(parameter[0].to<int32_t>(rt)),thisEObj))
	
		addFactory<FlowLayouter,E_FlowLayouter>();
	}
	

}

}
