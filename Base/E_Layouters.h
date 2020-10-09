/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_AbstractLayouters_H
#define __E_AbstractLayouters_H

#include <EScript/Objects/ReferenceObject.h>
#include <E_Util/E_ObjectFactory.h>
#include <GUI/Base/Layouters/AbstractLayouter.h>
#include <GUI/Base/Layouters/FlowLayouter.h>
#include <Util/References.h>
#include <Util/Factory/WrapperFactory.h>

namespace E_GUI {

/***
 **   E_AbstractLayouter ---|> ReferenceObject
 **     |
 **     ------> GUI::AbstractLayouter
 **/
class E_AbstractLayouter : public EScript::ReferenceObject<Util::Reference<GUI::AbstractLayouter> >{
		ES_PROVIDES_TYPE_NAME(AbstractLayouter)

	//!	@name AbstractLayouter -> E_AbstractLayouter
	//	@{
	private:
		EGUIAPI static E_Util::E_ObjectFactory<GUI::AbstractLayouter, E_AbstractLayouter> factorySystem;
	protected:
		template<class LayouterType, class E_AbstractLayouterType>
		static void addFactory() {
			factorySystem.registerType(LayouterType::getClassId(), Util::PolymorphicWrapperCreator<GUI::AbstractLayouter, LayouterType, E_AbstractLayouterType>());
		}
	public:
		static E_AbstractLayouter * create(GUI::AbstractLayouter * property) {
			if(property == nullptr) {
				return nullptr;
			}
			return factorySystem.create(property->getTypeId(), property);
		}
	//	@}

		// ---
		EGUIAPI static EScript::Type * getTypeObject();
		EGUIAPI static void init(EScript::Namespace & lib);

		E_AbstractLayouter(GUI::AbstractLayouter * p, EScript::Type* type=nullptr) : ReferenceObject_t(p,type?type:getTypeObject()) {}
		virtual ~E_AbstractLayouter()		{}
};

/***
 **   E_FlowLayouter ---|> E_AbstractLayouter ---|> ReferenceObject
 **/
class E_FlowLayouter : public E_AbstractLayouter{
		ES_PROVIDES_TYPE_NAME(FlowLayouter)
	public:
		EGUIAPI static EScript::Type * getTypeObject();

		E_FlowLayouter(GUI::FlowLayouter * p, EScript::Type* type=nullptr) : E_AbstractLayouter(p,type?type:getTypeObject()) {}
		virtual ~E_FlowLayouter()		{}

		const GUI::FlowLayouter * operator*()const	{	return static_cast<const GUI::FlowLayouter*>(ref().get());	}	\
		GUI::FlowLayouter * operator*()				{	return static_cast<GUI::FlowLayouter*>(ref().get());	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_AbstractLayouter,	GUI::AbstractLayouter*,			(**eObj).get())	
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_FlowLayouter,		GUI::FlowLayouter*,				**eObj)	
ES_CONV_OBJ_TO_EOBJ(GUI::AbstractLayouter*,		E_GUI::E_AbstractLayouter,		E_GUI::E_AbstractLayouter::create(obj))	

#endif // __E_AbstractLayouters_H
