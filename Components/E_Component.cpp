/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Component.h"

#include <EScript/EScript.h>
#include <GUI/Components/Container.h>
#include <E_Geometry/E_Vec2.h>
#include <E_Geometry/E_Rect.h>
#include <E_Util/E_Utils.h>
#include "../ELibGUI.h"
#include "../Base/E_AbstractShape.h"
#include "../Base/E_Layouters.h"
#include "../Base/E_Properties.h"

using namespace E_Geometry;

using Geometry::Vec2i;

namespace E_GUI {

//! (static)
E_Util::E_ObjectFactory<GUI::Component,E_Component> E_Component::factorySystem;

//! [static] initMembers
void E_Component::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<GUI::Component,E_Component>();

	using namespace GUI;

	//! [ESMF] self Component.activate()
	ES_MFUN(typeObject,Component,"activate",0,0,(thisObj->bringToFront(),thisObj->activate(),thisEObj))

	//! [ESMF] self Component.addProperty(AbstractProperty)
	ES_MFUN(typeObject,Component,"addProperty",1,1,
				(thisObj->addProperty(parameter[0].to<GUI::AbstractProperty*>(rt)),thisEObj))

	//! [ESMF] self Component.addLayouter(AbstractLayouter)
	ES_MFUN(typeObject,Component,"addLayouter",1,1,
				(thisObj->addLayouter(parameter[0].to<AbstractLayouter*>(rt)),thisEObj))

	//! [ESMF] self Component.bringToFront()
	ES_MFUN(typeObject,Component,"bringToFront",0,0,(thisObj->bringToFront(),thisObj->bringToFront(),thisEObj))

	//! [ESMF] self Component.clearProperties()
	ES_MFUN(typeObject,Component,"clearProperties",0,0,(thisObj->clearProperties(),thisEObj))

	//! [ESMF] self Component.clearLayouters()
	ES_MFUN(typeObject,Component,"clearLayouters",0,0,(thisObj->clearLayouters(),thisEObj))

	//! [ESMF] Bool Component.coversAbsPosition( Vec2 )
	ES_MFUN(typeObject,Component,"coversAbsPosition",1,1, thisObj->coversAbsPosition(parameter[0].to<Geometry::Vec2>(rt)))

	//! [ESMF] Bool Component.coversLocalPosition( Vec2 )
	ES_MFUN(typeObject,Component,"coversLocalPosition",1,1, thisObj->coversLocalPosition(parameter[0].to<Geometry::Vec2>(rt)))

	//! [ESMF] E_Rect Component.getAbsRect()
	ES_MFUN(typeObject,Component,"getAbsRect",0,0,EScript::create(thisObj->getAbsRect()))

	//! [ESMF] E_Vec2 Component.getAbsPosition()
	ES_MFUN(typeObject,Component,"getAbsPosition",0,0, EScript::create(thisObj->getAbsPosition()))

	//! [ESMF] component Component.getComponentAtPos( x,y | Vec2)
	ES_MFUN(typeObject,Component,"getComponentAtPos",1,2,EScript::create( (parameter.count()==2 ?
			thisObj->getComponentAtPos(Geometry::Vec2(parameter[0].to<float>(rt),parameter[1].to<float>(rt))):
			thisObj->getComponentAtPos(parameter[0].to<Geometry::Vec2>(rt))
	)))

	//! [ESMF] bool Component.getFlag(int)
	ES_MFUN(typeObject,const Component,"getFlag",1,1,(thisObj->getFlag(parameter[0].to<int32_t>(rt))))

	//! [ESMF] Number Component.getHeight()
	ES_MFUN(typeObject,const Component,"getHeight",0,0,(thisObj->getHeight()))

	//! [ESMF] Array Component.getLayouters()
	ES_MFUNCTION(typeObject,const Component,"getLayouters",0,0,{
		EScript::ERef<EScript::Array> arr = EScript::Array::create();
		auto layouters = thisObj->getLayouters();
		for(auto & layouter:layouters)
			arr->pushBack( E_AbstractLayouter::create(layouter.get()) );
		return arr.detachAndDecrease();
	})

	//! [ESMF] E_Rect Component.getLocalRect()
	ES_MFUN(typeObject,const Component,"getLocalRect",0,0,	EScript::create(thisObj->getLocalRect()))

	//! [ESMF] component Component.getNext()
	ES_MFUN(typeObject,const Component,"getNext",0,0,		EScript::create(thisObj->getNext()))

	//! [ESMF] component Component.getParentComponent()
	ES_MFUN(typeObject,const Component,"getParentComponent",0,0,EScript::create(thisObj->getParent()))

	//! [ESMF] component Component.getPrev()
	ES_MFUN(typeObject,const Component,"getPrev",0,0,		EScript::create(thisObj->getPrev()))

	//! [ESMF] Vec2 Component.getPosition()
	ES_MFUN(typeObject,const Component,"getPosition",0,0,	EScript::create(thisObj->getPosition()))

	//! [ESMF] E_Rect Component.getRect()
	ES_MFUN(typeObject,const Component,"getRect",0,0,		EScript::create(thisObj->getRect()))

	//! [ESMF] Vec2 Component.getSize()
	ES_MFUN(typeObject,const Component,"getSize",0,0,		EScript::create(Geometry::Vec2(thisObj->getWidth(),thisObj->getHeight())))

	//! [ESMF] String Component.getTooltip()
	ES_MFUN(typeObject,const Component,"getTooltip",0,0,	thisObj->getTooltip())

	//! [ESMF] Number Component.getWidth()
	ES_MFUN(typeObject,const Component,"getWidth",0,0,		thisObj->getWidth())

	//! [ESMF] Bool Component.hasTooltip()
	ES_MFUN(typeObject,const Component,"hasTooltip",0,0,	thisObj->hasTooltip())
	
	//! [ESMF] self Component.invalidateLayout()
	ES_MFUN(typeObject,Component,"invalidateLayout",0,0,	(thisObj->invalidateLayout(),thisEObj))

	//! [ESMF] Bool Component.isEnabled()
	ES_MFUN(typeObject,const Component,"isEnabled",0,0,		thisObj->isEnabled())

	//! [ESMF] Bool Component.isDestroyed()
	ES_MFUN(typeObject,const Component,"isDestroyed",0,0,	thisObj->isDestroyed())

	//! [ESMF] Bool Component.isLocked()
	ES_MFUN(typeObject,const Component,"isLocked",0,0,		thisObj->isLocked())

	//! [ESMF] Bool Component.isSelected()
	ES_MFUN(typeObject,const Component,"isSelected",0,0,	thisObj->isSelected())

	//! [ESMF] Bool Component.isVisible()
	ES_MFUN(typeObject,const Component,"isVisible",0,0,		thisObj->isVisible())

	//! [ESMF] self Component.layout()
	ES_MFUN(typeObject,Component,"layout",0,0,				(thisObj->layout(),thisEObj))

	//! [ESMF] self Component.removeExternalLayout()
	ES_MFUN(typeObject,Component,"removeExternalLayout",0,0,(thisObj->removeExternalLayout(),thisEObj))

	//! [ESMF] self Component.removeLayouter(AbstractLayouter)
	ES_MFUN(typeObject,Component,"removeLayouter",1,1,
				(thisObj->removeLayouter(parameter[0].to<AbstractLayouter*>(rt)),thisEObj))

	//! [ESMF] self Component.removeProperty(AbstractProperty)
	ES_MFUN(typeObject,Component,"removeProperty",1,1,
				(thisObj->removeProperty(parameter[0].to<GUI::AbstractProperty*>(rt)),thisEObj))

	//! [ESMF] self Component.removeTooltip()
	ES_MFUN(typeObject,Component,"removeTooltip",0,0,(thisObj->removeTooltip(),thisEObj))

	//! [ESMF] Component Component.setEnabled([bool])
	ES_MFUN(typeObject,Component,"setEnabled",0,1,(thisObj->setEnabled(parameter[0].to<bool>(rt,true)),thisEObj))

	//! [ESMF] Shape Component.setExtLayout( flags , Vec2 pos[, Vec2 size])
	ES_MFUN(typeObject,Component,"setExtLayout",2,3,(
		(parameter.count()==2 ? thisObj->setExtLayout(
									parameter[0].to<uint32_t>(rt),parameter[1].to<Geometry::Vec2>(rt)) :
								thisObj->setExtLayout(
									parameter[0].to<uint32_t>(rt),parameter[1].to<Geometry::Vec2>(rt),
									parameter[2].to<Geometry::Vec2>(rt))),thisEObj))

	//! [ESMF] self Component.setFlag(int[,bool b=true])
	ES_MFUN(typeObject,Component,"setFlag",1,2,		(thisObj->setFlag(parameter[0].to<uint32_t>(rt),parameter[1].to<bool>(rt,true)),thisEObj))

	//! [ESMF] Component Component.setLocked([bool])
	ES_MFUN(typeObject,Component,"setLocked",0,1,	(thisObj->setLocked(parameter[0].to<bool>(rt,true)),thisEObj))

	//! [ESMF] self Component.setTooltip(String)
	ES_MFUN(typeObject,Component,"setTooltip",1,1,	(thisObj->setTooltip(parameter[0].toString()),thisEObj))

	//! [ESMF] self Component.setHeight(number)
	ES_MFUN(typeObject,Component,"setHeight",1,1,	(thisObj->setHeight(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self Component.setRect( Rect )
	ES_MFUN(typeObject,Component,"setRect",1,1,		(thisObj->setRect(parameter[0].to<const Geometry::Rect&>(rt)),thisEObj))

	//! [ESMF] Shape Component.setSize( Vec2 pos[, float x, float y])
	ES_MFUN(typeObject,Component,"setSize",1,2,(
		(parameter.count()==1 ? thisObj->setSize(parameter[0].to<Geometry::Vec2>(rt)) :
								thisObj->setSize(parameter[0].to<float>(rt),parameter[1].to<float>(rt))),thisEObj))

	//! [ESMF] Component Component.setVisible([bool]) // DEPRECEATED
	ES_MFUN(typeObject,Component,"setVisible",0,1,	(thisObj->setEnabled(parameter[0].to<bool>(rt,true)),thisEObj))

	//! [ESMF] self Component.setWidth(number)
	ES_MFUN(typeObject,Component,"setWidth",1,1,	(thisObj->setWidth(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self Component.setPosition( x,y |  Vec2)
	ES_MFUN(typeObject,Component,"setPosition",1,2,( (parameter.count()==2 ?
			thisObj->setPosition(Geometry::Vec2(parameter[0].to<float>(rt),parameter[1].to<float>(rt))):
			thisObj->setPosition(parameter[0].to<Geometry::Vec2>(rt))
			),thisEObj))

	//! [ESMF] self Component.select()
	ES_MFUN(typeObject,Component,"select",0,0,		(thisObj->select(),thisEObj))

	//! [ESMF] self Component.unselect()
	ES_MFUN(typeObject,Component,"unselect",0,0,	(thisObj->unselect(),thisEObj))
}

}
