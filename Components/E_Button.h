/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_BUTTON_H
#define E_GUI_BUTTON_H

#include <GUI/Components/Button.h>
#include "E_Container.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::Button.
 *
 *   [E_Button] ---|> [E_Container] ---|> [E_Component] ---|> [EScript::Object]
 *										|
 *										 ------> [GUI::Component]
 */
class E_Button : public E_Container{
		ES_PROVIDES_TYPE_NAME(Button)
		E_GUI_COMPONENT_ACCESSORS(GUI::Button)
		E_GUI_PROVIDES_TYPE_OBJ(E_Container)
		
	protected:
		E_Button(GUI::Button * c,EScript::Type * type=nullptr) : E_Container(c,type?type:getTypeObject()) {}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	public:
		static void init(EScript::Namespace & lib);

		virtual ~E_Button() {}

};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Button,		GUI::Button*,		**eObj)	

#endif // E_GUI_BUTTON_H
