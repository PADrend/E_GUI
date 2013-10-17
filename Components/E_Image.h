/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_IMAGE_H
#define E_GUI_IMAGE_H

#include <GUI/Components/Image.h>
#include "E_Component.h"

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::Image.
 *
 *   [E_Image]  ---|> [E_Component] ---|> [EScript::Object]
 *                       |
 *                        ------> [GUI::Component]
 */
class E_Image : public E_Component{
		ES_PROVIDES_TYPE_NAME(Image)
		E_GUI_PROVIDES_TYPE_OBJ(E_Component)
		E_GUI_COMPONENT_ACCESSORS(GUI::Image)

	protected:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		E_Image(GUI::Image * c,EScript::Type * type=nullptr) : E_Component(c,type?type:getTypeObject()) {}
	public:
		static void init(EScript::Namespace & lib);

		virtual ~E_Image() {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Image,		GUI::Image*,		**eObj)	

#endif // E_GUI_IMAGE_H
