/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_LayoutHelper.h"

#include <GUI/GUI_Manager.h>
#include <E_Geometry/E_Vec2.h>
#include <EScript/EScript.h>
#include "../ELibGUI.h"

namespace E_GUI{
using namespace EScript;

//! [static] initMembers
void E_NextRow::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::NextRow,E_NextRow>();
}
// -------------------------------------------------------------------

//! [static] initMembers
void E_NextColumn::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::NextColumn,E_NextColumn>();
}
//---


}
