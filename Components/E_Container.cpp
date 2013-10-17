/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Container.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Container::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Container,E_Container>();

	using namespace GUI;

	//! [ESMF] self Container.add(Component)
	ES_MFUN(typeObject,Container,"add",1,1,						(thisObj->addContent(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] self Container.clear()
	ES_MFUN(typeObject,Container,"clear",0,0,					(thisObj->clearContents(),thisEObj))

	//! [ESMF] self Container.destroyContents()
	ES_MFUN(typeObject,Container,"destroyContents",0,0,			(thisObj->destroyContents(),thisEObj))

	//! [ESMF] Array Container.getContents()
	ES_MFUN(typeObject,Container,"getContents",0,0, 			EScript::Array::create(thisObj->getContents()))

	//! [ESMF] Component Container.getFirstChild()
	ES_MFUN(typeObject,const Container,"getFirstChild", 0,0,	EScript::create(thisObj->getFirstChild()))

	//! [ESMF] Component Container.getLastChild()
	ES_MFUN(typeObject,const Container,"getLastChild", 0,0,		EScript::create(thisObj->getLastChild()))

	//! [ESMF] selft Container.insertAfter(Component c,Component after)
	ES_MFUN(typeObject,Container,"insertAfter", 2,2,(thisObj->insertAfter(
			parameter[0].to<GUI::Component*>(rt),
			parameter[1].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] selft Container.insertBefore(Component c,Component after)
	ES_MFUN(typeObject,Container,"insertBefore", 2,2,(thisObj->insertBefore(
			parameter[0].to<GUI::Component*>(rt),
			parameter[1].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] number Container.numChildren()
	ES_MFUN(typeObject,const Container,"numChildren", 0,0,		static_cast<uint32_t>(thisObj->getContentsCount()))

	//! [ESMF] self Container.remove(Component)
	ES_MFUN(typeObject,Container,"remove",1,1,					(thisObj->removeContent(parameter[0].to<GUI::Component*>(rt)),thisEObj))

}

}
