/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_WINDOW_H
#define E_GUI_WINDOW_H

#include <GUI/Components/Window.h>
#include "E_Container.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::Window.
 *
 *   [E_Window] ---|> [E_Container] ---|> [E_Component] ---|> [EScript::Object]
 *                                          |
 *                                           ------> [GUI::Component]
 */
class E_Window : public E_Container{
		ES_PROVIDES_TYPE_NAME(Window)
		E_GUI_PROVIDES_TYPE_OBJ(E_Container)
		E_GUI_COMPONENT_ACCESSORS(GUI::Window)
		
	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_Window(GUI::Window * c,EScript::Type * type=nullptr) : E_Container(c,type?type:getTypeObject()) {}
	public:
		static void init(EScript::Namespace & lib);

		virtual ~E_Window() {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Window,		GUI::Window*,		**eObj)	

#endif // E_GUI_WINDOW_H
