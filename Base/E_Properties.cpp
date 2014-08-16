/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Properties.h"

#include "../ELibGUI.h"
#include "E_AbstractShape.h"
#include "Fonts/E_AbstractFont.h"

#include <E_Util/Graphics/E_Color.h>
#include <EScript/EScript.h>

#include <Util/Factory/WrapperFactory.h>

#include <iostream>
#include <sstream>

using namespace GUI;
using namespace EScript;

namespace E_GUI {

//! (static)
E_Util::E_ObjectFactory<AbstractProperty, E_Property> E_Property::factorySystem;

//! (static)
Type * E_Property::getTypeObject(){
	// [E_Property] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}
//! (static)
Type * E_ColorProperty::getTypeObject(){
	// [E_ColorProperty] ---|> [E_Property] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_Property::getTypeObject());
	return typeObject;
}
//! (static)
Type * E_FontProperty::getTypeObject(){
	// [E_FontProperty] ---|> [E_Property] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_Property::getTypeObject());
	return typeObject;
}
//! (static)
Type * E_ShapeProperty::getTypeObject(){
	// [E_ShapeProperty] ---|> [E_Property] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_Property::getTypeObject());
	return typeObject;
}
//! (static)
Type * E_UseShapeProperty::getTypeObject(){
	// [E_UseShapeProperty] ---|> [E_Property] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_Property::getTypeObject());
	return typeObject;
}

// -----
/**
 * [static]
 */
void E_Property::init(EScript::Namespace & lib) {
	{	// GUI.AbstractProperty ---|> Object
		Type  * t = E_Property::getTypeObject();

		declareConstant(&lib,E_Property::getClassName(),t);

		addFactory<AbstractProperty,E_Property>();
	}
	{	// GUI.ColorProperty ---|> GUI.Property ---|> Object
		Type  * t = E_ColorProperty::getTypeObject();

		declareConstant(&lib,E_ColorProperty::getClassName(),t);

		//! [ESF] new ColorProperty(Number id,Util.Color4(ub|f) )
		ES_CTOR(t, 2,2, (EScript::create(new ColorProperty(parameter[0].toInt(),parameter[1].to<Util::Color4ub>(rt)))))

		addFactory<ColorProperty,E_ColorProperty>();
	}
	{	// GUI.FontProperty ---|> GUI.Property ---|> Object
		Type  * t = E_FontProperty::getTypeObject();

		declareConstant(&lib,E_FontProperty::getClassName(),t);

		//! [ESF] new FontProperty(Number id,AbstractFont) )
		ES_CTOR(t, 2,2, EScript::create(new FontProperty(parameter[0].toInt(), parameter[1].to<AbstractFont*>(rt))))
		addFactory<FontProperty,E_FontProperty>();
	}
	{	// GUI.ShapeProperty ---|> GUI.AbstractProperty ---|> Object
		Type  * t = E_ShapeProperty::getTypeObject();

		declareConstant(&lib,E_ShapeProperty::getClassName(),t);

		//! [ESF] new ShapeProperty(Number id,Shape)
		ES_CTOR(t, 2,2, EScript::create(new ShapeProperty(parameter[0].toInt(), parameter[1].to<AbstractShape*>(rt))))

		//! [ESF] Shape ShapeProperty.getShape()
		ES_MFUN(t, const ShapeProperty, "getShape", 0, 0, EScript::create(thisObj->getShape()))

		//! [ESF] self ShapeProperty.setShape(Shape)
		ES_MFUN(t, ShapeProperty, "setShape", 1, 1, (thisObj->setShape(parameter[0].to<AbstractShape*>(rt)), thisEObj))

		addFactory<ShapeProperty,E_ShapeProperty>();
	}
	{	// GUI.UseShapeProperty ---|> GUI.AbstractProperty ---|> Object
		Type * t = E_UseShapeProperty::getTypeObject();

		declareConstant(&lib,E_UseShapeProperty::getClassName(),t);

		//! [ESF] new ColorProperty(Number id1,Number id2)
		ES_CTOR(t, 2,2, EScript::create(new UseShapeProperty(parameter[0].toInt(),parameter[1].toInt())))

		addFactory<UseShapeProperty,E_UseShapeProperty>();
	}
}

}
