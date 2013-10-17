/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Slider.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Slider::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Slider,E_Slider>();

	using namespace GUI;

	//! [ESMF] number Slider.getValue()
	ES_MFUN(typeObject,Slider,"getValue",0,0,	(thisObj->getValue()))

	//! [ESMF] self Slider.setRange(number left,number right,number steps)
	ES_MFUN(typeObject,Slider,"setRange",3,3,	(thisObj->setRange(parameter[0].to<float>(rt),parameter[1].to<float>(rt),parameter[2].to<uint32_t>(rt)),thisEObj))
							
	//! [ESMF] self Slider.setValue(number)
	ES_MFUN(typeObject,Slider,"setValue",1,1,	(thisObj->setValue(parameter[0].to<float>(rt)),thisEObj))

	// ----

	//! [ESMF] number Slider.getData() (alias for getValue)
	declareConstant(typeObject, "getData",		typeObject->getAttribute("getValue").getValue());
	
	//! [ESMF] self Slider.setData(number) (alias for setValue)
	declareConstant(typeObject, "setData",		typeObject->getAttribute("setValue").getValue());
	
	
	//! [ESMF] Bool Slider.onDataChanged() \note ObjectAttribute
	ES_FUN(typeObject,"onDataChanged",1,1,false)
	EScript::markAttributeAsObjectAttribute(typeObject,"onDataChanged");
}

}
