/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_AbstractShape.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

using namespace EScript;

namespace E_GUI {

Type* E_AbstractShape::typeObject=nullptr;

//! [static] initMembers
void E_AbstractShape::init(EScript::Namespace & lib) {
	// GUI.AbstractShape  ---|> Object
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
}

//---

//! (ctor)
E_AbstractShape::E_AbstractShape(GUI::AbstractShape * font,EScript::Type * type):
   EScript::ReferenceObject<Util::Reference<GUI::AbstractShape> >(font,type?type:typeObject) {
}

//! (dtor)
E_AbstractShape::~E_AbstractShape() {
}

}
