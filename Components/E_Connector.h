/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_CONNECTOR_H
#define E_GUI_CONNECTOR_H

#include <GUI/Components/Connector.h>
#include "E_Container.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::Connector.
 *
 *   [E_Connector] ---|> [E_Container] ---|> [E_Component] ---|> [EScript::Object]
 *                                        |
 *                                         ------> [GUI::Component]
 */
class E_Connector : public E_Container{
		ES_PROVIDES_TYPE_NAME(Connector)
		E_GUI_COMPONENT_ACCESSORS(GUI::Connector)
		E_GUI_PROVIDES_TYPE_OBJ(E_Container)
		
	protected:
		E_Connector(GUI::Connector * c,EScript::Type * type=nullptr) : E_Container(c,type?type:getTypeObject()) {}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	public:
		EGUIAPI static void init(EScript::Namespace & lib);

		virtual ~E_Connector() {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Connector,		GUI::Connector*,		**eObj)	

#endif // E_GUI_CONNECTOR_H
