/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Button.h"

#include "../Base/Fonts/E_AbstractFont.h"
#include "../ELibGUI.h"
#include <EScript/Basics.h>
#include <E_Util/Graphics/E_Color.h>

namespace E_GUI {

//! [static] initMembers
void E_Button::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Button,E_Button>();

	using namespace GUI;

	//! [ESMF] string Button.getText()
	ES_MFUN(typeObject,const Button,"getText",0,0,		thisObj->getText())

	//! [ESMF] bool Button.isSwitchedOn()
	ES_MFUN(typeObject,const Button,"isSwitchedOn",0,0,	thisObj->isSwitchedOn())

	//!	[ESMF] self Button.setColor(Util.Color4)
	ES_MFUN(typeObject,Button,"setColor",1,1,			(thisObj->setColor(parameter[0].to<Util::Color4ub>(rt)),thisEObj))

	//! [ESMF] self Button.setFont(AbstractFont f)
	ES_MFUN(typeObject,Button,"setFont",1,1,			(thisObj->setFont(parameter[0].to<AbstractFont*>(rt)),thisEObj))

	//! [ESMF] self Button.setSwitch(bool)
	ES_MFUN(typeObject,Button,"setSwitch",1,1,			(thisObj->setSwitch(parameter[0].to<bool>(rt)),thisEObj))

	//! [ESMF] self Button.setText(string)
	ES_MFUN(typeObject,Button,"setText",1,1,			(thisObj->setText(parameter[0].toString()),thisEObj))

	//! [ESMF] self Button.setTextStyle(int i)
	ES_MFUN(typeObject,Button,"setTextStyle",1,1,		(thisObj->setTextStyle(parameter[0].to<int32_t>(rt)),thisEObj))

	//! [ESMF] Bool Button.onClick() \note ObjectAttribute
	ES_FUN(typeObject,"onClick",0,0,(std::cout << "!", (true)))
	EScript::markAttributeAsObjectAttribute(typeObject,"onClick");

}

}
