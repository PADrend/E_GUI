/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_ABSTRACT_SHAPE_H
#define E_GUI_ABSTRACT_SHAPE_H

#include <GUI/Base/AbstractShape.h>
#include <EScript/Objects/ReferenceObject.h>
#include <Util/References.h>

namespace E_GUI{

/**
 *  EScript-Wrapper for GUI::AbstractShape.
 *
 *   [E_AbstractShape] ---|> [EScript::ReferenceObject] ---|> [EScript::Object]
 */
class E_AbstractShape :  public EScript::ReferenceObject<Util::Reference<GUI::AbstractShape> >{
	ES_PROVIDES_TYPE_NAME(AbstractShape)
	public:
		// ----
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);


		E_AbstractShape(GUI::AbstractShape * c,EScript::Type * type=nullptr);
		virtual ~E_AbstractShape();

};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_AbstractShape,		GUI::AbstractShape*,		(**eObj).get())
ES_CONV_OBJ_TO_EOBJ(GUI::AbstractShape*,		E_GUI::E_AbstractShape,		new E_GUI::E_AbstractShape(obj))

#endif // E_GUI_ABSTRACT_SHAPE_H
