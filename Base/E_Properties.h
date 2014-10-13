/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_Properties_H
#define __E_Properties_H

#include <EScript/Objects/ReferenceObject.h>
#include <E_Util/E_ObjectFactory.h>
#include <GUI/Base/Properties.h>
#include <Util/References.h>
#include <Util/Factory/WrapperFactory.h>

namespace E_GUI {

/***
 **   E_Property ---|> ReferenceObject
 **     |
 **     ------> GUI::DisplayProperty
 **/
class E_Property : public EScript::ReferenceObject<Util::Reference<GUI::DisplayProperty> >{
		ES_PROVIDES_TYPE_NAME(DisplayProperty)

	//!	@name DisplayProperty -> E_Property
	//	@{
	private:
		static E_Util::E_ObjectFactory<GUI::DisplayProperty, E_Property> factorySystem;
	protected:
		template<class PropertyType, class E_PropertyType>
		static void addFactory() {
			factorySystem.registerType(PropertyType::getClassId(), Util::PolymorphicWrapperCreator<GUI::DisplayProperty, PropertyType, E_PropertyType>());
		}
	public:
		static E_Property * create(GUI::DisplayProperty * property) {
			if(property == nullptr) {
				return nullptr;
			}
			return factorySystem.create(property->getTypeId(), property);
		}
	//	@}

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_Property(GUI::DisplayProperty * p, EScript::Type* type=nullptr) : ReferenceObject_t(p,type?type:getTypeObject()) {}
		virtual ~E_Property()	{}
};

/***
 **   E_ColorProperty ---|> E_Property ---|> ReferenceObject
 **/
class E_ColorProperty : public E_Property{
		ES_PROVIDES_TYPE_NAME(ColorProperty)
	public:
		static EScript::Type * getTypeObject();

		E_ColorProperty(GUI::ColorProperty * p, EScript::Type* type=nullptr) : E_Property(p,type?type:getTypeObject()) {}
		virtual ~E_ColorProperty()	{}
	
		const GUI::ColorProperty * operator*()const		{	return static_cast<const GUI::ColorProperty*>(ref().get());	}
		GUI::ColorProperty * operator*()				{	return static_cast<GUI::ColorProperty*>(ref().get());	}
};


/***
 **   E_FontProperty ---|> E_Property ---|> ReferenceObject
 **/
class E_FontProperty : public E_Property{
		ES_PROVIDES_TYPE_NAME(FontProperty)
	public:
		static EScript::Type * getTypeObject();

		E_FontProperty(GUI::FontProperty * p, EScript::Type* type=nullptr) : E_Property(p,type?type:getTypeObject()) {}
		virtual ~E_FontProperty()	{}

		const GUI::FontProperty * operator*()const	{	return static_cast<const GUI::FontProperty*>(ref().get());	}
		GUI::FontProperty * operator*()				{	return static_cast<GUI::FontProperty*>(ref().get());	}
};

/***
 **   E_ShapeProperty ---|> E_Property ---|> ReferenceObject
 **/
class E_ShapeProperty : public E_Property{
		ES_PROVIDES_TYPE_NAME(ShapeProperty)
	public:
		static EScript::Type * getTypeObject();

		E_ShapeProperty(GUI::ShapeProperty * p, EScript::Type* type=nullptr) : E_Property(p,type?type:getTypeObject()) {}
		virtual ~E_ShapeProperty()	{}

		const GUI::ShapeProperty * operator*()const		{	return static_cast<const GUI::ShapeProperty*>(ref().get());	}
		GUI::ShapeProperty * operator*()				{	return static_cast<GUI::ShapeProperty*>(ref().get());	}
};

/***
 **   E_UseShapeProperty ---|> E_Property ---|> ReferenceObject
 **/
class E_UseShapeProperty : public E_Property{
		ES_PROVIDES_TYPE_NAME(UseShapeProperty)
	public:
		static EScript::Type * getTypeObject();

		E_UseShapeProperty(GUI::UseShapeProperty * p, EScript::Type* type=nullptr) : E_Property(p,type?type:getTypeObject()) {}
		virtual ~E_UseShapeProperty()	{}

		const GUI::UseShapeProperty * operator*()const	{	return static_cast<const GUI::UseShapeProperty*>(ref().get());	}
		GUI::UseShapeProperty * operator*()				{	return static_cast<GUI::UseShapeProperty*>(ref().get());	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Property,			GUI::DisplayProperty*,		(**eObj).get())
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_ColorProperty,		GUI::ColorProperty*,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_FontProperty,		GUI::FontProperty*,			**eObj)
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_ShapeProperty,		GUI::ShapeProperty*,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_UseShapeProperty,	GUI::UseShapeProperty*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(GUI::DisplayProperty*,		E_GUI::E_Property,			E_GUI::E_Property::create(obj))

#endif // __E_Properties_H
