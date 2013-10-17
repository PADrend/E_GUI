/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Window.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Window::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Window,E_Window>();

	using namespace GUI;

	//! [ESMF] self Window.close()
	ES_MFUN(typeObject,Window,"close",0,0,				(thisObj->close(),thisEObj))

	//! [ESMF] string Window.getHeader()
	ES_MFUN(typeObject,const Window,"getHeader",0,0,	(EScript::create(thisObj->getHeader())))

	//! [ESMF] string Window.getLogo()
	ES_MFUN(typeObject,const Window,"getLogo",0,0,		(EScript::create(thisObj->getLogo())))

	//! [ESMF] string Window.getTitle()
	ES_MFUN(typeObject,const Window,"getTitle",0,0,		((thisObj->getTitle())))

	//! [ESMF] self Window.minimize( )
	ES_MFUN(typeObject,Window,"minimize",0,0,			(thisObj->minimize(),thisEObj))

	//! [ESMF] self Window.restore( )
	ES_MFUN(typeObject,Window,"restore",0,0,			(thisObj->restore(),thisEObj))

	//! [ESMF] self Window.setLogo( Component|Void )
	ES_MFUNCTION(typeObject,Window,"setLogo",1,1,{
		E_Component * ec=parameter[0].toType<E_Component>();
		thisObj->setLogo(ec==nullptr?nullptr:**ec);
		return  thisEObj;
	})

	//! [ESMF] self Window.setTitle(string)
	ES_MFUN(typeObject,Window,"setTitle",1,1,			(thisObj->setTitle(parameter[0].toString()),thisEObj))
}

}
