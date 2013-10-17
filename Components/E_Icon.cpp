/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Icon.h"

#include <GUI/Components/Image.h>
#include <E_Geometry/E_Rect.h>
#include <EScript/EScript.h>
#include "../Base/E_ImageData.h"
#include "../ELibGUI.h"

using namespace EScript;

namespace E_GUI {

//! [static] initMembers
void E_Icon::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Icon,E_Icon>();

	using namespace GUI;

	//! [ESMF] E_Rect Component.getImageData()
	ES_MFUN(typeObject,const Icon,"getImageData",0,0,	EScript::create(thisObj->getImageData()))

	//! [ESMF] E_Rect Component.getImageRect()
	ES_MFUN(typeObject,const Icon,"getImageRect",0,0,	EScript::create(thisObj->getImageRect()))

	//! [ESMF] self Component.setImageData(ImageData)
	ES_MFUN(typeObject,Icon,"setImageData",1,1,					(thisObj->setImageData(parameter[0].to<GUI::ImageData*>(rt)),thisEObj))

	//! [ESMF] self Component.setImageRect(Util.Rect)
	ES_MFUN(typeObject,Icon,"setImageRect",1,1,					(thisObj->setImageRect(parameter[0].to<const Geometry::Rect&>(rt)),thisEObj))
}

}
