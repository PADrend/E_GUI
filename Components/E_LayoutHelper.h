/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_LAYOUTHELPERS_H
#define E_GUI_LAYOUTHELPERS_H

#include <GUI/Components/LayoutHelper.h>
#include "E_Component.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::E_GUI.
 *
 *   [E_NextRow] ---|> [E_Component] ---|> [EScript::Object]
 *                              |
 *                              ------> [GUI::Component]
 */
class E_NextRow : public E_Component{
		ES_PROVIDES_TYPE_NAME(NextRow)
		E_GUI_PROVIDES_TYPE_OBJ(E_Component)
		E_GUI_COMPONENT_ACCESSORS(GUI::NextRow)
				
	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_NextRow(GUI::NextRow * c,EScript::Type * type=nullptr) : E_Component(c,type?type:getTypeObject()) {}
	public:
		EGUIAPI static void init(EScript::Namespace & lib);

		virtual ~E_NextRow(){}
};

/**
 *  EScript-Wrapper for GUI::E_GUI.
 *
 *   [E_NextColumn] ---|> [E_Component] ---|> [EScript::Object]
 *                              |
 *                              ------> [GUI::Component]
 */
class E_NextColumn : public E_Component{
		ES_PROVIDES_TYPE_NAME(NextColumn)
		E_GUI_PROVIDES_TYPE_OBJ(E_Component)
		E_GUI_COMPONENT_ACCESSORS(GUI::NextColumn)	
		
	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_NextColumn(GUI::NextColumn * c,EScript::Type * type=nullptr) : E_Component(c,type?type:getTypeObject()) {}
	public:
		static void init(EScript::Namespace & lib);

		virtual ~E_NextColumn(){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_NextColumn,	GUI::NextColumn*,		**eObj)	
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_NextRow,		GUI::NextRow*,			**eObj)	

#endif // E_GUI_LAYOUTHELPERS_H
