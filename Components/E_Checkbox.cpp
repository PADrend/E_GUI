/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Checkbox.h"

#include <GUI/GUI_Manager.h>
#include <EScript/Basics.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Checkbox::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Checkbox,E_Checkbox>();

	using namespace GUI;

	//! [ESMF] string Checkbox.getText()
	ES_MFUN(typeObject,const Checkbox,"getText",0,0,thisObj->getText())

	//! [ESMF] bool Checkbox.isChecked()
	ES_MFUN(typeObject,const Checkbox,"isChecked",0,0,thisObj->isChecked())

	//! [ESMF] self Checkbox.setChecked(bool)
	ES_MFUN(typeObject,Checkbox,"setChecked",1,1,
					(thisObj->setChecked(parameter[0].to<bool>(rt)),thisEObj))

	//! [ESMF] selfCheckbox.setText(string)
	ES_MFUN(typeObject,Checkbox,"setText",1,1,
					(thisObj->setText(parameter[0].toString()),thisEObj))

	// --------

	//! [ESMF] bool Checkbox.getData() (alias for isChecked)
	EScript::copyAttributeAsAlias(typeObject,"isChecked", "getData");
	
	//! [ESMF] self Checkbox.setData(bool) (alias for setChecked)
	EScript::copyAttributeAsAlias(typeObject,"setChecked", "setData");
	
	//! [ESMF] Bool Checkbox.onDataChanged() \note ObjectAttribute
	ES_FUN(typeObject,"onDataChanged",1,1,false)
	EScript::markAttributeAsObjectAttribute(typeObject,"onDataChanged");
}

}
