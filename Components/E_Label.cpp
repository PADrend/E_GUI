/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Label.h"

#include "../Base/Fonts/E_AbstractFont.h"
#include "../ELibGUI.h"
#include <EScript/EScript.h>
#include <E_Util/Graphics/E_Color.h>

namespace E_GUI {

//! [static] initMembers
void E_Label::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Label,E_Label>();

	using namespace GUI;

	//! [ESMF] string Label.getText()
	ES_MFUN(typeObject,const Label,"getText",0,0, 	(thisObj->getText()))

	//!	[ESMF] self Label.setColor(E_Color4?)
	ES_MFUN(typeObject,Label,"setColor",1,1,		(thisObj->setColor( parameter[0].to<Util::Color4f>(rt) ),thisEObj))

	//! [ESMF] self Label.setFont(AbstractFont f)
	ES_MFUN(typeObject,Label,"setFont",1,1,			(thisObj->setFont(parameter[0].to<AbstractFont*>(rt)),thisEObj))

	//! [ESMF] self Label.setText(string)
	ES_MFUN(typeObject,Label,"setText",1,1,			(thisObj->setText(parameter[0].toString()),thisEObj))

	//! [ESMF] self Label.setTextStyle(int i)
	ES_MFUN(typeObject,Label,"setTextStyle",1,1,	(thisObj->setTextStyle(parameter[0].to<uint32_t>(rt)),thisEObj))
}

}
