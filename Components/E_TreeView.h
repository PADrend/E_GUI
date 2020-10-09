/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_TREEVIEW_H
#define E_GUI_TREEVIEW_H

#include <GUI/Components/TreeView.h>
#include "E_Container.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::TreeView.
 *
 *   [E_TreeView] ---|> [E_Container] ---|> [E_Component] ---|> [EScript::Object]
 *                                            |
 *                                             ------> [GUI::Component]
 */
class E_TreeView : public E_Container{
		ES_PROVIDES_TYPE_NAME(TreeView)
		E_GUI_PROVIDES_TYPE_OBJ(E_Container)
		E_GUI_COMPONENT_ACCESSORS(GUI::TreeView)	
	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_TreeView(GUI::TreeView * c,EScript::Type * type=nullptr) : E_Container(c,type?type:getTypeObject()) {}
	public:
		EGUIAPI static void init(EScript::Namespace & lib);

		virtual ~E_TreeView() {}
};

/*! E_TreeViewEntry ---|> E_Container */
class E_TreeViewEntry : public E_Container{
		ES_PROVIDES_TYPE_NAME(TreeViewEntry)
		E_GUI_PROVIDES_TYPE_OBJ(E_Container)
		E_GUI_COMPONENT_ACCESSORS(GUI::TreeView::TreeViewEntry)	
	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_TreeViewEntry(GUI::TreeView::TreeViewEntry * c,EScript::Type * type=nullptr) : E_Container(c,type?type:getTypeObject()) {}
	public:
		EGUIAPI static void init(EScript::Namespace & lib);

		virtual ~E_TreeViewEntry() {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_TreeView,			GUI::TreeView*,					**eObj)	
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_TreeViewEntry,		GUI::TreeView::TreeViewEntry*,	**eObj)	

#endif // E_GUI_TREEVIEW_H
