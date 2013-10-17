/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Connector.h"

#include <EScript/EScript.h>
#include <EScript/Utils/DeprecatedMacros.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_Connector::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Connector,E_Connector>();

	using namespace GUI;

	//! [ESF] (static) Array GUI.findConnectors( container,endpoint )
	ES_FUNCTION2(&lib,"findConnectors",2,2,{
		EScript::Array * a = EScript::Array::create();
		std::list<GUI::Connector *> connectors;
		GUI::Connector::findConnectors(	parameter[0].to<Container*>(rt),
										parameter[1].to<Component*>(rt),connectors);

		for(const auto & connector : connectors) 
			a->pushBack(EScript::create(connector));
		return a;
	})
	
	//! [ESMF] Component Connector.getFirstComponent()
	ES_MFUN(typeObject,Connector,"getFirstComponent",0,0,	EScript::create(thisObj->getFirstComponent()))


	//! [ESMF] Number Connector.getLength()
	ES_MFUN(typeObject,const Connector,"getLength",0,0,		thisObj->getLength())


	//! [ESMF] Component Connector.getSecondComponent()
	ES_MFUN(typeObject,Connector,"getSecondComponent",0,0,	EScript::create(thisObj->getSecondComponent()))

	//! [ESMF] self Connector.setFirstComponent(Component|nullptr)
	ES_MFUN(typeObject,Connector,"setFirstComponent",1,1,(
			thisObj->setFirstComponent(
				parameter[0].toType<E_Component>() == nullptr ?
								nullptr :
								(**parameter[0].toType<E_Component>())),thisEObj))

	//! [ESMF] self Connector.setSecondComponent(Component|nullptr)
	ES_MFUN(typeObject,Connector,"setSecondComponent",1,1,(
			thisObj->setSecondComponent(
				parameter[0].toType<E_Component>() == nullptr ?
								nullptr :
								(**parameter[0].toType<E_Component>())),thisEObj))

}

}
