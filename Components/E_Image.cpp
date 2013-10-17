/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Image.h"

#include <E_Util/Graphics/E_Bitmap.h>
#include <E_Util/Graphics/E_PixelAccessor.h>
#include <EScript/EScript.h>
#include <Util/Graphics/PixelAccessor.h>
#include "../Base/E_ImageData.h"
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Image::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<GUI::Image,E_Image>();
	
	using namespace GUI;

	//! [ESMF] PixelAccessor|Void Image.createPixelAccessor()
	ES_MFUNCTION(typeObject,Image,"createPixelAccessor",0,0,{
		Util::Reference<Util::PixelAccessor> acc = thisObj->createPixelAccessor( );
		if(acc!=nullptr)
			return EScript::create(acc);
		else
			return EScript::create(nullptr);
	})

	//! [ESMF] self Image.dataChanged()
	ES_MFUN(typeObject,Image,"dataChanged",0,0,				(thisObj->dataChanged(),thisEObj))

	//! [ESMF] E_Rect Component.getImageData()
	ES_MFUN(typeObject,const Image,"getImageData",0,0,		EScript::create(thisObj->getImageData()))

	//!	[ESMF] Number Image.getImageHeight()
	ES_MFUN(typeObject,const Image,"getImageHeight", 0, 0, (thisObj->getBitmap()->getHeight()))

	//!	[ESMF] Number Image.getImageWidth()
	ES_MFUN(typeObject,const Image,"getImageWidth", 0, 0, 	(thisObj->getBitmap()->getWidth()))

	//! [ESMF] self Image.updateData(_Bitmap )
	ES_MFUN(typeObject,Image,"updateData",1,1,				(thisObj->updateData(parameter[0].to<Util::Bitmap*>(rt)),thisEObj))
	
}

}
