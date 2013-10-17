/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Textarea.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Textarea::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Textarea,E_Textarea>();
	
	using namespace GUI;

	//! [ESMF] string Textarea.getText()
	ES_MFUN(typeObject,Textarea,"getText",0,0,	thisObj->getText())

	//! [ESMF] self Textarea.setText(string)
	ES_MFUN(typeObject,Textarea,"setText",1,1,	(thisObj->setText(parameter[0]->toString()),thisEObj))
//
	// ---------
	
	//! [ESMF] string Textarea.getData() (alias for getText)
	declareConstant(typeObject, "getData", 		typeObject->getAttribute("getText").getValue());
	
	//! [ESMF] self Textarea.setData(string) (alias for setText)
	declareConstant(typeObject, "setData",		typeObject->getAttribute("setText").getValue());
	
	
	//! [ESMF] Bool Textarea.onDataChanged() \note ObjectAttribute
	ES_FUN(typeObject,"onDataChanged",1,1,false)
	EScript::markAttributeAsObjectAttribute(typeObject,"onDataChanged");
}

}
