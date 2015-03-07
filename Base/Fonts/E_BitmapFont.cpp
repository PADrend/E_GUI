/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BitmapFont.h"

#include <EScript/EScript.h>
#include <E_Geometry/E_Rect.h>
#include <E_Geometry/E_Vec2.h>
#include <E_Util/E_FileName.h>
#include <E_Util/Graphics/E_Bitmap.h>
#include "../../Components/E_Image.h"
#include "../../ELibGUI.h"

using namespace EScript;

namespace E_GUI {

Type* E_BitmapFont::typeObject=nullptr;

//!	[static] initMembers
void E_BitmapFont::init(EScript::Namespace & lib) {
	// GUI.BitmapFont  ---|> GUI.AbstractFont  ---|> Object
	typeObject = new EScript::Type(E_AbstractFont::typeObject);
	declareConstant(&lib,getClassName(),typeObject);

	using namespace GUI;
	
	//!	[ESF] BitmapFont new BitmapFont( FileName,Number size,String charMap)
	ES_FUN(typeObject,"createFont",3,3, EScript::create(BitmapFont::createFont(parameter[0].to<Util::FileName>(rt),parameter[1].to<uint32_t>(rt),parameter[2].toString())))
	
	//!	[ESF] BitmapFont new BitmapFont( Image,lineHeight )
	ES_CTOR(typeObject,2,2, EScript::create(new GUI::BitmapFont(parameter[0].to<Image*>(rt)->getImageData(),parameter[1].toInt())))

	//!	[ESMF] self BitmapFont.addGlyph( Number unicode, Number width, Number height, Geometry::Vec2 textureOffset,Geometry::Vec2 screenOffset,Number xAdvance )
	ES_MFUNCTION(typeObject,E_BitmapFont,"addGlyph",6,6,{
		thisObj->get()->addGlyph( 	parameter[0].to<uint32_t>(rt),
									parameter[1].to<uint32_t>(rt),
									parameter[2].to<uint32_t>(rt),
									Geometry::Vec2i( parameter[3].to<Geometry::Vec2>(rt) ),
									Geometry::Vec2i( parameter[4].to<Geometry::Vec2>(rt) ),
									parameter[5].to<uint32_t>(rt));
		return thisEObj;
	})

	//!	[ESMF] self BitmapFont.setKerning( Number unicode1,Number unicode2,Number kerning)
	ES_MFUN(typeObject,BitmapFont,"setKerning",3,3,(thisObj->setKerning(parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt),parameter[2].to<int16_t>(rt)),thisObj))

	//!	[ESMF] Util.Bitmap BitmapFont.getBitmap( )
	ES_MFUN(typeObject,BitmapFont,"getBitmap",0,0,
		EScript::create( thisObj->getBitmap() ))

}

//---

//!	(ctor)
E_BitmapFont::E_BitmapFont(GUI::BitmapFont * font,EScript::Type * type):
   E_AbstractFont(font,type?type:typeObject) {
}

//!	(dtor)
E_BitmapFont::~E_BitmapFont() {
}

}
