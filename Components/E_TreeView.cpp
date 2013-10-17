/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_TreeView.h"

#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI {

//! [static] initMembers
void E_TreeView::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::TreeView,E_TreeView>();

	using namespace GUI;

	//! [ESMF] Array TreeView.getMarkedComponents()
	ES_MFUN(typeObject,TreeView,"getMarkedComponents",0,0,			EScript::Array::create(thisObj->getMarkedComponents()))

	//! [ESMF] TreeViewEntry TreeView.getRootEntry()
	ES_MFUN(typeObject,const TreeView,"getRootEntry",0,0,			EScript::create(thisObj->getRootEntry()))

	//! [ESMF] self TreeView.markComponent(Component)
	ES_MFUN(typeObject,TreeView,"markComponent",1,1,				(thisObj->markComponent(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] self TreeView.markEntry(TreeViewEntry)
	ES_MFUN(typeObject,TreeView,"markEntry",1,1,					(thisObj->markEntry(parameter[0].to<TreeView::TreeViewEntry*>(rt)),thisEObj))

	//! [ESMF] self TreeView.unmarkAll()
	ES_MFUN(typeObject,TreeView,"unmarkAll",0,0,					(thisObj->unmarkAll(),thisEObj))

	//! [ESMF] self TreeView.unmarkComponent(Component)
	ES_MFUN(typeObject,TreeView,"unmarkComponent",1,1,				(thisObj->unmarkComponent(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] self TreeView.unmarkEntry(TreeViewEntry)
	ES_MFUN(typeObject,TreeView,"unmarkEntry",1,1,					(thisObj->unmarkEntry(parameter[0].to<TreeView::TreeViewEntry*>(rt)),thisEObj))

	// ----
	
	declareConstant(typeObject,"getData",typeObject->getAttribute("getMarkedComponents").getValue()); //alias

	
	//! [ESMF] Bool TreeView.onDataChanged() \note ObjectAttribute
	ES_FUN(typeObject,"onDataChanged",1,1,false)
	EScript::markAttributeAsObjectAttribute(typeObject,"onDataChanged");
}

//---

// -----------------------------------------------------------------------------------------------
// E_TreeViewEntry

//! [static] initMembers
void E_TreeViewEntry::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::TreeView::TreeViewEntry,E_TreeViewEntry>();

	using namespace GUI;

	//! [ESMF] TreeViewEntry|void TreeView.getFirstSubentry()
	ES_MFUN(typeObject,const TreeView::TreeViewEntry,"getFirstSubentry",0,0,	EScript::create(thisObj->getFirstSubentry()))

	//! [ESMF] bool TreeViewEntry.isCollapsed()
	ES_MFUN(typeObject,const TreeView::TreeViewEntry,"isCollapsed",0,0,			(thisObj->isCollapsed()))

	//! [ESMF] bool TreeViewEntry.isMarked()
	ES_MFUN(typeObject,const TreeView::TreeViewEntry,"isMarked",0,0,			(thisObj->isMarked()))

	//! [ESMF] self TreeViewEntry.collapse()
	ES_MFUN(typeObject,TreeView::TreeViewEntry,"collapse",0,0,					(thisObj->collapse(),thisEObj))

	//! [ESMF] self TreeViewEntry.open()
	ES_MFUN(typeObject,TreeView::TreeViewEntry,"open",0,0,						(thisObj->open(),thisEObj))

	//! [ESMF] self TreeViewEntry.setComponent(Component)
	ES_MFUN(typeObject,TreeView::TreeViewEntry,"setComponent",1,1,				(thisObj->setComponent(parameter[0].to<GUI::Component*>(rt)),thisEObj))

}

}
