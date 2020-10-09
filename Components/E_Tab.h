/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_TAB_H
#define E_GUI_TAB_H

#include <GUI/Components/Tab.h>
#include "E_Container.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::TabbedPanel.
 *
 *   [E_Tab] ---|> [E_Container] ---|> [E_Component] ---|> [EScript::Object]
 *                                        |
 *                                         ------> [GUI::Component]
 */
class E_Tab : public E_Container{
		ES_PROVIDES_TYPE_NAME(Tab)
		E_GUI_PROVIDES_TYPE_OBJ(E_Container)
		E_GUI_COMPONENT_ACCESSORS(GUI::TabbedPanel::Tab)
		
	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_Tab(GUI::TabbedPanel::Tab * c,EScript::Type * type=nullptr) : E_Container(c,type?type:getTypeObject()) {}
	public:
		EGUIAPI static void init(EScript::Namespace & lib);

		virtual ~E_Tab() {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Tab,		GUI::TabbedPanel::Tab*,		**eObj)	

#endif // E_GUI_TAB_H
