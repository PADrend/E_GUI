/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_BITMAP_FONT_H
#define E_GUI_BITMAP_FONT_H

#include <GUI/Base/Fonts/BitmapFont.h>
#include "E_AbstractFont.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::BitmapFont.
 *
 *   [E_BitmapFont] ---|> [E_AbstractFont] ---|> [EScript::ReferenceObject] ---|> [EScript::Object]
 */
class E_BitmapFont :  public E_AbstractFont {
	ES_PROVIDES_TYPE_NAME(BitmapFont)
	public:
		// ----
		EGUIAPI static EScript::Type* typeObject;
		EGUIAPI static void init(EScript::Namespace & lib);

		EGUIAPI E_BitmapFont(GUI::BitmapFont * c,EScript::Type * type=nullptr);
		EGUIAPI virtual ~E_BitmapFont();

		GUI::BitmapFont * get() const {
			return dynamic_cast<GUI::BitmapFont *>(E_AbstractFont::ref().get());
		}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_BitmapFont,						GUI::BitmapFont*,		eObj->get())
ES_CONV_OBJ_TO_EOBJ(GUI::BitmapFont*,							E_GUI::E_BitmapFont,	new E_GUI::E_BitmapFont(obj))
ES_CONV_OBJ_TO_EOBJ(Util::Reference<GUI::BitmapFont>,			E_GUI::E_BitmapFont,	new E_GUI::E_BitmapFont(obj.get()))

#endif // E_GUI_BITMAP_FONT_H
