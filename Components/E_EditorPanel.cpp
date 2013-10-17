/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_EditorPanel.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"



namespace E_GUI {

//! [static] initMembers
void E_EditorPanel::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::EditorPanel,E_EditorPanel>();

	using namespace GUI;

	//! [ESMF] Array EditorPanel.getMarkedChildren()
	ES_MFUN(typeObject,const EditorPanel,"getMarkedChildren",0,0,	EScript::Array::create(thisObj->getMarkedChildren()))
	
	//! [ESMF] self EditorPanel.markChild(Component)
	ES_MFUN(typeObject,EditorPanel,"markChild",1,1,					(thisObj->markChild(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] self EditorPanel.markingChanged()
	ES_MFUN(typeObject,EditorPanel,"markingChanged",0,0,			(thisObj->markingChanged(),thisEObj))

	//! [ESMF] self EditorPanel.unmarkAll()
	ES_MFUN(typeObject,EditorPanel,"unmarkAll",0,0,					(thisObj->unmarkAll(),thisEObj))

	//! [ESMF] self EditorPanel.unmarkChild(Component)
	ES_MFUN(typeObject,EditorPanel,"unmarkChild",1,1,				(thisObj->unmarkChild(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	// ----
	
	//! [ESMF] Array EditorPanel.getData() (alias for getMarkedChildren)
	declareConstant(typeObject, "getData" , typeObject->getAttribute("getMarkedChildren").getValue());
	//	declareFunction(typeObject,"setData",esmf_EditorPanel_markChildren); //alias
	
	//! [ESMF] Bool E_EditorPanel.onDataChanged() \note ObjectAttribute
	ES_FUN(typeObject,"onDataChanged",1,1,false)
	EScript::markAttributeAsObjectAttribute(typeObject,"onDataChanged");


}

}
