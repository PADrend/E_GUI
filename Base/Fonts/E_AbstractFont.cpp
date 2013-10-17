/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_AbstractFont.h"

#include <EScript/EScript.h>

using namespace EScript;

namespace E_GUI {

Type* E_AbstractFont::typeObject=nullptr;

//! [static] initMembers
void E_AbstractFont::init(EScript::Namespace & lib) {
	// GUI.AbstractFont  ---|> Object
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
}

//---

/*!	(ctor)	*/
E_AbstractFont::E_AbstractFont(GUI::AbstractFont * font,EScript::Type * type):
   EScript::ReferenceObject<Util::Reference<GUI::AbstractFont> >(font,type?type:typeObject) {
}

/*!	(dtor)	*/
E_AbstractFont::~E_AbstractFont() {
}

}
