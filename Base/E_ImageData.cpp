/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ImageData.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_Util/Graphics/E_Bitmap.h>
#include <E_Util/Graphics/E_PixelAccessor.h>

#include <Util/Graphics/PixelAccessor.h>

namespace E_GUI{

//! (static)
EScript::Type * E_ImageData::getTypeObject() {
	// E_ImageData ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_ImageData::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_ImageData::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace GUI;
	
	//! [ESF] new ImageData(Util::Bitmap)
	ES_CTOR(typeObject,1,1,									EScript::create(new GUI::ImageData(parameter[0].to<Util::Bitmap*>(rt) )))

	//! [ESMF] RESULT ImageData.createPixelAccessor()
	ES_MFUN(typeObject,ImageData,"createPixelAccessor",0,0,	EScript::create(thisObj->createPixelAccessor()))

	//! [ESMF] self ImageData.dataChanged()
	ES_MFUN(typeObject,ImageData,"dataChanged",0,0,			(thisObj->dataChanged(),thisEObj))

	//! [ESMF] RESULT ImageData.getBitmap()
	ES_MFUN(typeObject,ImageData,"getBitmap",0,0,			EScript::create(thisObj->getBitmap()))

	//! [ESMF] self ImageData.removeGLData()
	ES_MFUN(typeObject,ImageData,"removeGLData",0,0,		(thisObj->removeGLData(),thisEObj))

	//! [ESMF] self ImageData.updateData(Util::Bitmap)
	ES_MFUN(typeObject,ImageData,"updateData",1,1,			(thisObj->updateData(parameter[0].to<Util::Bitmap*>(rt)),thisEObj))

}
}
