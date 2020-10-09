/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_ABSTRACT_FONT_H
#define E_GUI_ABSTRACT_FONT_H

#include <GUI/Base/Fonts/AbstractFont.h>
#include <EScript/Objects/ReferenceObject.h>
#include <Util/References.h>

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::AbstractFont.
 *
 *   [E_AbstractFont] ---|> [EScript::ReferenceObject] ---|> [EScript::Object]
 */
class E_AbstractFont :  public EScript::ReferenceObject<Util::Reference<GUI::AbstractFont> >{
	ES_PROVIDES_TYPE_NAME(AbstractFont)
	public:
		// ----
		EGUIAPI static EScript::Type* typeObject;
		EGUIAPI static void init(EScript::Namespace & lib);


		EGUIAPI E_AbstractFont(GUI::AbstractFont * c,EScript::Type * type=nullptr);
		EGUIAPI virtual ~E_AbstractFont();
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_AbstractFont,		GUI::AbstractFont*,		(**eObj).get())

#endif // E_GUI_ABSTRACT_FONT_H
