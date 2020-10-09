/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_COMPONENT_H
#define E_GUI_COMPONENT_H

#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_Utils.h>
#include <E_Util/E_ObjectFactory.h>
#include <GUI/Components/Component.h>
#include <Util/Factory/WrapperFactory.h>

namespace E_GUI {

// This macro allows accessing the referenced Object as if the E_Object was a smart pointer.
#define E_GUI_COMPONENT_ACCESSORS(_specificType)\
	public:	\
		const _specificType * operator*()const			{	return static_cast<const _specificType*>(ref().get());	}	\
		_specificType * operator*()						{	return static_cast<_specificType*>(ref().get());	}

#define E_GUI_PROVIDES_TYPE_OBJ(_eBaseType)\
	public:	\
		static EScript::Type * getTypeObject(){		\
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(_eBaseType::getTypeObject());	\
			return typeObject.get();	\
		} 

/**
 *  EScript-Wrapper for GUI::Component.
 *
 *    [E_Component] ---|> [EScript::Object]
 *      |
 *      ------> [GUI::Component]
 */
class E_Component : public EScript::ExtReferenceObject< GUI::Component::Ref,EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider>{
		ES_PROVIDES_TYPE_NAME(Component)
		E_GUI_COMPONENT_ACCESSORS(GUI::Component)
		E_GUI_PROVIDES_TYPE_OBJ(EScript::Object)

	private:
		EGUIAPI static E_Util::E_ObjectFactory<GUI::Component, E_Component> factorySystem;
	protected:
		template<class ComponentType, class E_ComponentType>
		static void addFactory() {
			factorySystem.registerType(ComponentType::getClassId(), Util::PolymorphicWrapperCreator<GUI::Component, ComponentType, E_ComponentType>());
		}
	public:
		static E_Component * create(GUI::Component * component) {
			if(component == nullptr) {
				return nullptr;
			}
			return factorySystem.create(component->getTypeId(), component);
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EGUIAPI static void init(EScript::Namespace & lib);

		virtual ~E_Component() {}

	protected:
		E_Component(GUI::Component * c,EScript::Type * type=nullptr) : ExtReferenceObject_t(c,type?type:getTypeObject()) {}
};

}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_Component,		GUI::Component*,		**eObj)	
ES_CONV_OBJ_TO_EOBJ(GUI::Component*,		E_GUI::E_Component,		E_GUI::E_Component::create(obj))	

#endif // E_GUI_COMPONENT_H
