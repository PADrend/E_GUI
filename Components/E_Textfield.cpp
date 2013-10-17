/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Textfield.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Textfield::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Textfield,E_Textfield>();

	using namespace GUI;

	//! [ESMF] self Textfield.addOption(option)
	ES_MFUN(typeObject,Textfield,"addOption",1,1,			(thisObj->addOption(parameter[0].toString()),thisEObj))

	//! [ESMF] self Textfield.addOptions(Array options)
	ES_MFUNCTION(typeObject,Textfield,"addOptions",1,1,{
		GUI::Textfield * t=thisObj;
		for(auto & value : *parameter[0].to<EScript::Array*>(rt)){
			if(!value.isNull())
				t->addOption(value.toString());
		}
		return thisEObj;
	})

	//! [ESMF] self Textfield.clearOptions()
	ES_MFUN(typeObject,Textfield,"clearOptions",0,0,		(thisObj->clearOptions(),thisEObj))

	//! [ESMF] number Textfield.countOptions()
	ES_MFUN(typeObject,const Textfield,"countOptions",0,0,	(thisObj->countOptions()))

	//! [ESMF] number Textfield.getCurrentOptionIndex()
	ES_MFUN(typeObject,const Textfield,"getCurrentOptionIndex",0,0,(thisObj->getCurrentOptionIndex()))

	//! [ESMF] string Textfield.getOption(nr)
	ES_MFUN(typeObject,Textfield,"getOption",1,1,			(thisObj->getOption(parameter[1].to<int32_t>(rt))))
	
	//! [ESMF] string Textfield.getText()
	ES_MFUN(typeObject,const Textfield,"getText",0,0,		(thisObj->getText()))

	//! [ESMF] bool Textfield.hasOptions()
	ES_MFUN(typeObject,const Textfield,"hasOptions",0,0,	(thisObj->hasOptions()))

	//! [ESMF] self Textfield.setCurrentOptionIndex(number)
	ES_MFUN(typeObject,Textfield,"setCurrentOptionIndex",1,1,
					(thisObj->setCurrentOptionIndex(parameter[0].to<int32_t>(rt)),thisEObj))

	//! [ESMF] self Textfield.setText(string)
	ES_MFUN(typeObject,Textfield,"setText",1,1,				(thisObj->setText(parameter[0].toString()),thisEObj))

	// ---------
	
	//! [ESMF] string Textfield.getData() (alias for getText)
	declareConstant(typeObject, "getData", typeObject->getAttribute("getText").getValue());
	
	//! [ESMF] self Textfield.setData(string) (alias for setText)
	declareConstant(typeObject, "setData", typeObject->getAttribute("setText").getValue());
	
	
	//! [ESMF] Bool Textfield.onDataChanged() \note ObjectAttribute
	ES_FUN(typeObject,"onDataChanged",1,1,false)
	EScript::markAttributeAsObjectAttribute(typeObject,"onDataChanged");
}

}
