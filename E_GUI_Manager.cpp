/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_GUI_Manager.h"

#include <EScript/EScript.h>
#include <GUI/GUI.h>
#include <GUI/Components/ListView.h>
#include <GUI/Style/StdShapes.h>
#include "ELibGUI.h"
#include "Components/E_Image.h"
#include "Components/E_Container.h"
#include "Components/E_Textarea.h"
#include "Base/E_AbstractShape.h"
#include "Base/E_ImageData.h"
#include "Base/E_Properties.h"
#include "Base/Fonts/E_AbstractFont.h"
#include <Util/Macros.h>
#include <Util/Graphics/Bitmap.h>
#include <E_Util/Graphics/E_Bitmap.h>
#include <E_Geometry/E_Rect.h>
#include <E_Geometry/E_Vec2.h>
#include <E_Util/Graphics/E_Color.h>
#include <E_Util/UI/E_Event.h>
#include <E_Util/UI/E_EventContext.h>
#include <E_Util/UI/E_Window.h>
#include <Util/UI/Event.h>

namespace E_GUI {

EScript::Type* E_GUI_Manager::typeObject=nullptr;

// ----------------------------------------------------------------------

//! [static] initMembers
void E_GUI_Manager::init(EScript::Namespace & lib) {
	// GUI.GUI_Manager ---|> Object
	typeObject = new EScript::Type(ExtObject::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	using namespace GUI;

	//! [ESF] GUI_Manager new GUI.GUI_Manager(EventContext)
	ES_CONSTRUCTOR(typeObject, 1, 1, {
		Util::UI::EventContext & eventContext = **EScript::assertType<E_Util::E_UI::E_EventContext>(rt, parameter[0]);
		return new E_GUI_Manager(eventContext, rt);
	})

	//! [ESMF] void GUI_Manager.enableMouseButtonListener(Component)
	ES_MFUNCTION(typeObject,E_GUI_Manager,"enableMouseButtonListener",1,1,{
		parameter[0].to<GUI::Component*>(rt)->addMouseButtonListener(thisObj->getEScriptEventHandler());
		return thisEObj;
	})

	//! [ESMF] void GUI_Manager.addKeyListener(Component)
	ES_MFUNCTION(typeObject,E_GUI_Manager,"addKeyListener",1,1,{
		parameter[0].to<GUI::Component*>(rt)->addKeyListener(thisObj->getEScriptEventHandler());
		return thisEObj;
	})

	//! [ESMF] self GUI_Manager.closeAllMenus()
	ES_MFUN(typeObject,GUI_Manager,"closeAllMenus",0,0,(thisObj->closeAllMenus(),thisEObj))

	//! [ESMF] GUI_Manager.createButton( [w,h[,text[,flags]]] )
	ES_MFUNCTION(typeObject,GUI_Manager,"createButton",0,4,{
		GUI::Button * b = thisObj->createButton(parameter[2].toString("Button"),parameter[3].to<uint32_t>(rt,0));
		if(parameter.count()>1)
			b->setRect(Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)));
		return EScript::create(b);
	})

	//! [ESMF] GUI_Manager.createContainer(w,h[,flags])
	ES_MFUNCTION(typeObject,GUI_Manager,"createContainer",2,3,{
		return EScript::create(thisObj->createContainer(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
			parameter[2].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createCheckbox( [text,[checked,[flags]]])
	ES_MFUN(typeObject,GUI_Manager,"createCheckbox",0,3,
				EScript::create(thisObj->createCheckbox(parameter[0].toString(),parameter[1].to<bool>(rt),parameter[2].to<uint32_t>(rt) )))

	declareConstant(typeObject,"createCheckBox",typeObject->getAttribute("createCheckbox").getValue()); //! \deprecated

	//! [ESMF] GUI_Manager.createConnector( [flags] )
	ES_MFUN(typeObject,GUI_Manager,"createConnector",0,1,EScript::create(
			thisObj->createConnector(parameter[0].to<uint32_t>(rt,0) )))

	//! [ESMF] GUI_Manager.createEditorPanel( [flags] )
	ES_MFUNCTION(typeObject,GUI_Manager,"createEditorPanel",0,1,{
		return EScript::create(thisObj->createEditorPanel(parameter[0].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createIcon( Image|ImageData,Rect imageRect,[,flags] )
	ES_MFUNCTION(typeObject,GUI_Manager,"createIcon",2,3,{
		E_Image * eImg = parameter[0].toType<E_Image>();
		GUI::ImageData * imageData = (eImg==nullptr) ? parameter[0].to<GUI::ImageData*>(rt) : (**eImg)->getImageData();
		const Geometry::Rect & imageRect = parameter[1].to<const Geometry::Rect>(rt);

		return EScript::create(thisObj->createIcon(Geometry::Vec2(0,0),imageData,imageRect,parameter[2].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createImage( (w,h[,flags]) | Bitmap )
	ES_MFUNCTION(typeObject,GUI_Manager,"createImage",1,3,{
		if(parameter.count() > 1) {
			return EScript::create(thisObj->createImage(Geometry::Rect(0,
																	   0,
																	   parameter[0].to<float>(rt),
																	   parameter[1].to<float>(rt)), 
														parameter[2].to<uint32_t>(rt, 0)));
		}
		return EScript::create(thisObj->createImage(parameter[0].to<Util::Bitmap &>(rt), 
													parameter[1].to<uint32_t>(rt)));
	})

	//! [ESMF] GUI_Manager.createHSplitter([flags])
	ES_MFUN(typeObject,GUI_Manager,"createHSplitter",0,1,
				EScript::create(thisObj->createHSplitter(parameter[0].to<uint32_t>(rt,0))))

	//! [ESMF] GUI_Manager.createLabel(w,h,text,[flags] | "text"[,flags] )
	ES_MFUNCTION(typeObject,GUI_Manager,"createLabel",0,4,{
		if(parameter.count()<3){
			return EScript::create(thisObj->createLabel(parameter[0].toString(""), parameter[1].to<uint32_t>(rt,0)));
		}
		return EScript::create(thisObj->createLabel(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
			parameter[2].toString("Text..."),parameter[3].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createListView( [flags] )
	ES_MFUN(typeObject,GUI_Manager,"createListView",0,1,
				EScript::create(thisObj->createListView(parameter[0].to<uint32_t>(rt,0))))

	//! [ESMF] GUI_Manager.createMenu( [flags] )
	ES_MFUN(typeObject,GUI_Manager,"createMenu",0,1,
				EScript::create(thisObj->createMenu(parameter[0].to<uint32_t>(rt,0))))
	
	//! [ESMF] GUI_Manager.createNextColumn( [flags] )
	ES_MFUN(typeObject,GUI_Manager,"createNextRow",0,1,
				EScript::create(thisObj->createNextRow(parameter[0].toFloat(0))))
	
	//! [ESMF] GUI_Manager.createNextColumn( [flags] )
	ES_MFUN(typeObject,GUI_Manager,"createNextColumn",0,1,
				EScript::create(thisObj->createNextColumn(parameter[0].toFloat(0))))

	//! [ESMF] GUI_Manager.createPanel( [w,h,[,flags]] | [flags] )
	ES_MFUNCTION(typeObject,GUI_Manager,"createPanel",0,3,{
		if(parameter.count()<2){
			return EScript::create(thisObj->createPanel(parameter.count()>0?parameter[0].to<uint32_t>(rt):0));
		}
		return EScript::create(thisObj->createPanel(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
			parameter[2].to<uint32_t>(rt)));
	})

	//! [ESMF] GUI_Manager.createSlider(w,h,min,max,[steps,[flags]])
	ES_MFUNCTION(typeObject,GUI_Manager,"createSlider",4,6,{
		float min=parameter[2].toDouble();
		float max=parameter[3].toDouble();
		int steps=parameter[4].toInt(parameter[0].to<uint32_t>(rt));

		return EScript::create(thisObj->createSlider(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
			min,max,steps,"",parameter[5].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createTab(title,clientArea)
	ES_MFUN(typeObject,GUI_Manager,"createTab",2,2,
					EScript::create( new TabbedPanel::Tab(*thisObj,parameter[0].toString(),parameter[1].to<Container*>(rt))))

	//! [ESMF] GUI_Manager.createTabbedPanel([w,h,[flags]])
	ES_MFUNCTION(typeObject,GUI_Manager,"createTabbedPanel",0,3,{
		return EScript::create(thisObj->createTabbedPanel(
			Geometry::Rect(0,0,parameter[0].toFloat(10),parameter[1].toFloat(10)),
				parameter[2].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createTextarea([text[,flags]])
	ES_MFUN(typeObject,GUI_Manager,"createTextarea",0,2,
					EScript::create(thisObj->createTextarea(parameter[0].toString(""),parameter[1].toInt(0))))

	//! [ESMF] GUI_Manager.createTextfield(w,h,[text[,flags]])
	ES_MFUNCTION(typeObject,GUI_Manager,"createTextfield",2,4,{
		return EScript::create(thisObj->createTextfield(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
			parameter[2].toString(""),parameter[3].to<uint32_t>(rt,0)));
	})

	declareConstant(typeObject,"createTextField",typeObject->getAttribute("createTextfield").getValue()); //! \deprecated

	//! [ESMF] GUI_Manager.createTreeView(w,h,[flags])
	ES_MFUNCTION(typeObject,GUI_Manager,"createTreeView",2,3,{
		return EScript::create(thisObj->createTreeView(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
				parameter[2].to<uint32_t>(rt,0)));
	})

	//! [ESMF] TreeViewEntry GUI_Manager.createTreeViewEntry(Component)
	ES_MFUNCTION(typeObject,GUI_Manager,"createTreeViewEntry",1,1,{
		Component * c=parameter[0].to<GUI::Component*>(rt);
		return EScript::create(thisObj->createTreeViewEntry(c));
	})

	//! [ESMF] GUI_Manager.createWindow(w,h,[text,[flags]])
	ES_MFUNCTION(typeObject,GUI_Manager,"createWindow",2,4,{
		return EScript::create(thisObj->createWindow(
			Geometry::Rect(0,0,parameter[0].to<float>(rt),parameter[1].to<float>(rt)),
			parameter[2].toString("Title"),parameter[3].to<uint32_t>(rt,0)));
	})

	//! [ESMF] GUI_Manager.createVSplitter([flags])
	ES_MFUN(typeObject,GUI_Manager,"createVSplitter",0,1,
			EScript::create(thisObj->createVSplitter(parameter[0].to<uint32_t>(rt,0))))

	//! [ESMF] GUI_Manager.createHSplitter([flags])
	ES_MFUN(typeObject,GUI_Manager,"createHSplitter",0,1,
			EScript::create(thisObj->createHSplitter(parameter[0].to<uint32_t>(rt,0))))

	//! [ESMF] GUI_Manager.disableLazyRendering( )
	ES_MFUN(typeObject,GUI_Manager,"disableLazyRendering",0,0,(thisObj->disableLazyRendering(),thisEObj))
			
	//! [ESMF] serl GUI_Manager.display()
	ES_MFUN(typeObject,GUI_Manager,"display",0,0,(thisObj->display(),thisEObj))

	//! [ESMF] GUI_Manager.enableLazyRendering( )
	ES_MFUN(typeObject,GUI_Manager,"enableLazyRendering",0,0,(thisObj->enableLazyRendering(),thisEObj))

	//! [ESMF] Component GUI_Manager.getComponentAtPos(Geometry.Vec2 pos)
	ES_MFUN(typeObject,GUI_Manager,"getComponentAtPos",1,1,EScript::create(
				thisObj->getComponentAtPos(parameter[0].to<const Geometry::Vec2&>(rt))))
	
	//! [ESMF] Number GUI_Manager.getDebugMode()
	ES_MFUN(typeObject,GUI_Manager,"getDebugMode",0,0,thisObj->getDebugMode())

	//! [ESMF] Rect GUI_Manager.getScreenRect()
	ES_MFUN(typeObject,GUI_Manager,"getScreenRect",0,0,EScript::create(thisObj->getScreenRect()))

	//! [ESMF] AbstractFont GUI_Manager.getDefaultFont(Number id)
	//! \todo change the resulting type into the actual type
	ES_MFUN(typeObject,GUI_Manager,"getDefaultFont",1,1,
				new E_AbstractFont(thisObj->getDefaultFont(parameter[0].toUInt())))

	//! [ESMF] int GUI_Manager.handleEvent(Event)
	ES_MFUN(typeObject,GUI_Manager,"handleEvent",1,1,
				thisObj->handleEvent(parameter[0].toType<E_Util::E_UI::E_Event>()->getEvent()))

	//! [ESMF] void GUI_Manager.setWindow(Window)
	ES_MFUN(typeObject,GUI_Manager, "setWindow", 1, 1, 
		(thisObj->setWindow((**EScript::assertType<E_Util::E_UI::E_Window>(rt, parameter[0])).get()), thisEObj))

	//! [ESMF] Bool GUI_Manager.isCurrentlyEnabled(Component * c)
	ES_MFUN(typeObject,GUI_Manager,"isCurrentlyEnabled",1,1,
				thisObj->isCurrentlyEnabled(parameter[0].to<GUI::Component*>(rt)))

	//! [ESMF] Bool GUI_Manager.isLazyRenderingEnabled( )
	ES_MFUN(typeObject,GUI_Manager,"isLazyRenderingEnabled",0,0,
				thisObj->isLazyRenderingEnabled())
	
	//! [ESMF] GUI_Manager.loadImage(  filename[,flags]  )
	ES_MFUNCTION(typeObject,GUI_Manager,"loadImage",1,2,{
		return EScript::create(
				thisObj->createImage(Util::FileName(parameter[0].toString()),parameter[1].to<uint32_t>(rt))
		);
	})

	//! [ESMF] self GUI_Manager.markForRemoval(Component * c)
	ES_MFUN(typeObject,GUI_Manager,"markForRemoval",1,1,
				(thisObj->markForRemoval(parameter[0].to<GUI::Component*>(rt)),thisEObj))


	//! [ESMF] GUI_Manager.registerWindow(Component * c)
	ES_MFUN(typeObject,GUI_Manager,"registerWindow",1,1,
				(thisObj->registerWindow(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! [ESMF] GUI_Manager.setActiveComponent(Component * c)
	ES_MFUNCTION(typeObject,GUI_Manager,"setActiveComponent",1,1,{
		Component* c=parameter[0].to<GUI::Component*>(rt);
		if(c)
			thisObj->setActiveComponent(c);
		return nullptr;
	})
	
	//! [ESMF] self GUI_Manager.setDebugMode(Number level)
	ES_MFUN(typeObject,GUI_Manager,"setDebugMode",1,1,
				(thisObj->setDebugMode(static_cast<uint8_t>(parameter[0].toUInt())),thisEObj))

	//! [ESMF] self GUI_Manager.setDefaultColor(Number id,Color4)
	ES_MFUN(typeObject,GUI_Manager,"setDefaultColor",2,2,
				(thisObj->setDefaultColor(parameter[0].toUInt(),
												parameter[1].to<Util::Color4ub>(rt)),thisEObj))

	//! [ESMF] self GUI_Manager.setDefaultFont(Number id,AbstractFont)
	ES_MFUN(typeObject,GUI_Manager,"setDefaultFont",2,2,
				(thisObj->setDefaultFont(parameter[0].toUInt(),
												parameter[1].to<AbstractFont*>(rt)),thisEObj))

	//! [ESMF] self GUI_Manager.setDefaultShape(Number id,AbstractShape)
	ES_MFUN(typeObject,GUI_Manager,"setDefaultShape",2,2,
				(thisObj->setDefaultShape(parameter[0].toUInt(),parameter[1].to<AbstractShape*>(rt)),thisEObj))
    
    ES_MFUN(typeObject,GUI_Manager, "registerMouseCursor", 4, 4,
                 (thisObj->registerMouseCursor(parameter[0].toString(), parameter[1].to<Util::Reference<Util::Bitmap>>(rt), parameter[2].to<uint32_t>(rt), parameter[3].to<uint32_t>(rt)),thisEObj))
    
	//! [ESMF] self GUI_Manager.setGlobalValue(Number id,Number)
	ES_MFUN(typeObject,GUI_Manager,"setGlobalValue",2,2,
				(thisObj->setGlobalValue(parameter[0].toUInt(),
												parameter[1].to<float>(rt)),thisEObj))

	//! [ESMF] GUI_Manager.unregisterWindow(Component * c)
	ES_MFUN(typeObject,GUI_Manager,"unregisterWindow",1,1,
				(thisObj->unregisterWindow(parameter[0].to<GUI::Component*>(rt)),thisEObj))

	//! self GUI_Manager.unselectAll()
	ES_MFUN(typeObject,GUI_Manager,"unselectAll",0,0, (thisObj->unselectAll(),thisEObj))


	//! [ESMF] (internal) Component GUI_Manager._createPanelNextRow( spacing )
	ES_MFUN(typeObject,GUI_Manager,"_createPanelNextRow",1,1,
			EScript::create( new Panel::NextRow(*thisObj,parameter[0].to<float>(rt))))

	//! [ESMF] (internal)  Component GUI_Manager._createPanelNextColumn( spacing )
	ES_MFUN(typeObject,GUI_Manager,"_createPanelNextColumn",1,1,
			EScript::create( new Panel::NextColumn(*thisObj,parameter[0].to<float>(rt))))

	// ---------------------------------------------------------------------------------------
	// some quick'n dirty helper functions - use at your own risk

	//! [ESMF] Shape GUI_Manager._createGridShape( Color4?  _majorColor,Color4? _minorColor,float _hDistance,float _vDistance,int _hNumMinors,int _vNumMinors )
	ES_FUN(typeObject,"_createGridShape",6,6,
			new E_AbstractShape( new GridShape( parameter[0].to<Util::Color4ub>(rt),
												parameter[1].to<Util::Color4ub>(rt),
												parameter[2].to<float>(rt),parameter[3].to<float>(rt),parameter[4].to<uint32_t>(rt),parameter[5].to<uint32_t>(rt)	)))


	//! [ESMF]  Shape GUI_Manager._createRectShape( Color4?  bgColor,Color4? lineColor,bool blend)
	ES_FUN(typeObject,"_createRectShape",3,3,
			new E_AbstractShape( new RectShape( parameter[0].to<Util::Color4ub>(rt),
												parameter[1].to<Util::Color4ub>(rt),
												parameter[2].to<bool>(rt))))

	//! [ESMF]  Shape GUI_Manager._createRect3dShape( Color4?  bgColor1,Color4? bgColor2,bool blend[,bool invert=false])
	ES_FUN(typeObject,"_createRect3dShape",3,4,
			new E_AbstractShape( new Rect3dShape( parameter[0].to<Util::Color4ub>(rt),
												parameter[1].to<Util::Color4ub>(rt),
												parameter[2].to<bool>(rt),parameter[3].to<bool>(rt,false))))

	//! [ESMF]  Shape GUI_Manager._createShadowedRectShape( Color4?  _bgColor,Color4? _lineColor,bool blend)
	ES_FUN(typeObject,"_createShadowedRectShape",3,3,
			new E_AbstractShape( new ShadowedRectShape( parameter[0].to<Util::Color4ub>(rt),
												parameter[1].to<Util::Color4ub>(rt),
												parameter[2].to<bool>(rt))))


	//! [ESMF]  Shape GUI_Manager.Rounded3dRectShape( Color4?  _bgColor,Color4? _lineColor,bool blend,float _roundnessTL=2,float _roundnessTR=2,float _roundnessBL=2,float _roundnessBR=2)
	ES_FUN(typeObject,"_createRounded3dRectShape",3,7,
			new E_AbstractShape( new Rounded3dRectShape( parameter[0].to<Util::Color4ub>(rt),
												parameter[1].to<Util::Color4ub>(rt),
												parameter[2].to<bool>(rt),
												parameter[3].toFloat(2),parameter[4].toFloat(2),parameter[5].toFloat(2),parameter[6].toFloat(2))))

	//! [ESMF]  Shape GUI_Manager._createSmoothConnectorShape( Color4?  c, number lineWidth)
	ES_FUN(typeObject,"_createSmoothConnectorShape",2,2,
			new E_AbstractShape( new SmoothConnectorShape( parameter[0].to<Util::Color4ub>(rt),parameter[1].to<float>(rt))))


	//! [ESMF]  Shape GUI_Manager._createStraightLineShape( Color4?  c, number lineWidth)
	ES_FUN(typeObject,"_createStraightLineShape",2,2,
			new E_AbstractShape( new StraightLineShape( parameter[0].to<Util::Color4ub>(rt),parameter[1].to<float>(rt))))

	//! [ESMF] Shape GUI_Manager.getNullShape()
	ES_FUN(typeObject,"getNullShape",0,0,
			new E_AbstractShape( NullShape::instance()))

}

// -------------------------------------------------------------------------

//! ---|> ActionListener
GUI::listenerResult_t EScript_EventHandler::handleAction(GUI::Component * component,const Util::StringIdentifier & actionName) {
	EScript::ObjRef obj = EScript::create(component);
	if (obj.isNull() ) {
		std::cout << "No E_Component: "<<component<<"\n";
		WARN(" ");
		return GUI::LISTENER_EVENT_NOT_CONSUMED;
	}
	EScript::Object * handler = nullptr;
	
	if(actionName == GUI::TreeView::TreeViewEntry::ACTION_TreeViewEntry_collapse){
		static const EScript::StringId ID_handler("onClose");
		handler = obj->getAttribute(ID_handler).getValue();
	}else if(actionName == GUI::TreeView::TreeViewEntry::ACTION_TreeViewEntry_open){
		static const EScript::StringId ID_handler("onOpen");
		handler = obj->getAttribute(ID_handler).getValue();
	}else if(actionName == GUI::Window::ACTION_onWindowClosed){
		static const EScript::StringId ID_handler("onWindowClosed");
		handler = obj->getAttribute(ID_handler).getValue();
	}else{
		static const EScript::StringId ID_onClick("onClick");
		handler = obj->getAttribute(ID_onClick).getValue();
	}
	
	if(handler==nullptr)
		return GUI::LISTENER_EVENT_NOT_CONSUMED;


//std::cout << "actionName:"<< actionName.toString()<<"\n";

	EScript::ObjRef resultObj = rt.executeFunction(handler, obj, EScript::ParameterValues());
	return GUI::LISTENER_EVENT_CONSUMED;
}

//! ---|> DataChangeListener
void EScript_EventHandler::handleDataChange(GUI::Component * component,const Util::StringIdentifier & /*actionName*/) {
	EScript::ObjRef obj = EScript::create(component);
	if (obj.isNull()) {
		WARN(" ");
		return;
	}

	static const EScript::StringId ID_getData("getData");
	static const EScript::StringId ID_onDataChanged("onDataChanged");
	if ( obj->getAttribute(ID_onDataChanged).isNull() )
		return;

	EScript::ObjRef data;
	if ( !obj->getAttribute(ID_getData).isNull() ){
		data = callMemberFunction(rt,obj,ID_getData,EScript::ParameterValues());
	}

	if(data.isNull())
		data = EScript::create(nullptr);

	EScript::ObjRef resultObj = callMemberFunction(rt,obj,ID_onDataChanged,EScript::ParameterValues(data));
}

//! ---|> MouseButtonListener
GUI::listenerResult_t EScript_EventHandler::onMouseButton(GUI::Component * component, const Util::UI::ButtonEvent & buttonEvent){
	static const EScript::StringId ID_onMouseButton("onMouseButton");

	Util::UI::Event event;
	event.type = buttonEvent.type;
	event.button = buttonEvent;
	if(component == nullptr){// global handler?
		const bool handlerExists = !eManager.getAttribute(ID_onMouseButton).isNull();
		if(handlerExists){
			EScript::ObjRef resultObj = callMemberFunction(rt,&eManager,ID_onMouseButton,EScript::ParameterValues(new E_Util::E_UI::E_Event(event)));
			if(resultObj.toBool())
				return GUI::LISTENER_EVENT_CONSUMED;
		}
	}else{ // object handler
		EScript::ObjRef obj = EScript::create(component);
		if (obj.isNull()) {
			WARN(" ");
			return GUI::LISTENER_EVENT_NOT_CONSUMED;
		}

		const bool handlerExists = !obj->getAttribute(ID_onMouseButton).isNull();

		if (handlerExists){
			EScript::ObjRef resultObj = callMemberFunction(rt,obj,ID_onMouseButton,EScript::ParameterValues(new E_Util::E_UI::E_Event(event)));
			if(resultObj.toBool())
				return GUI::LISTENER_EVENT_CONSUMED;
		}
	}
	return GUI::LISTENER_EVENT_NOT_CONSUMED;
}

//! ---|> MouseMotionListener
GUI::listenerResult_t EScript_EventHandler::onMouseMove(GUI::Component * /*component*/, const Util::UI::MotionEvent & motionEvent) {
	static Geometry::Vec2i lastMousePos;
	const Geometry::Vec2i currentMousePos(motionEvent.x, motionEvent.y);
	lastMousePos = currentMousePos;

	Util::UI::Event event;
	event.type = motionEvent.type;
	event.motion = motionEvent;
	
	// global mouse motion listener 'gui.onMouseMove(evt)'
	static const EScript::StringId ID_onMouseMove("onMouseMove");
	EScript::ObjPtr mouseMotionHandler = eManager.getAttribute(ID_onMouseMove).getValue();
	if(mouseMotionHandler.toBool()){
		EScript::ObjRef resultObj = callMemberFunction(rt,&eManager,ID_onMouseMove,EScript::ParameterValues(new E_Util::E_UI::E_Event(event)));
		if(resultObj.toBool())
			return GUI::LISTENER_EVENT_CONSUMED;
	}

	return GUI::LISTENER_EVENT_NOT_CONSUMED;
}

//! ---|> KeyListener
bool EScript_EventHandler::onKeyEvent(GUI::Component * component, const Util::UI::KeyboardEvent & keyEvent){
	EScript::ObjRef obj=EScript::create(component);
	if (obj.isNull()) {
		WARN(" ");
		return false;
	}

	static const EScript::StringId ID_onKeyEvent("onKeyEvent");
	const bool handlerExists = !obj->getAttribute(ID_onKeyEvent).isNull();

	if (handlerExists){
		Util::UI::Event event;
		event.type = keyEvent.type;
		event.keyboard = keyEvent;
		EScript::ObjRef resultObj = callMemberFunction(rt,obj,ID_onKeyEvent,EScript::ParameterValues(new E_Util::E_UI::E_Event(event)));
		return resultObj.toBool() ? true : false;
	}
	return false;
}

// --------------------------------------------------------------------------

//! (ctor)
E_GUI_Manager::E_GUI_Manager(Util::UI::EventContext & eventContext, EScript::Runtime & rt,EScript::Type * type):
		ExtObject(type?type:typeObject),manager(new GUI::GUI_Manager(eventContext)),myEventHandler(rt,*this) {
	manager->registerActionListener(&myEventHandler);
	manager->registerDataChangeListener(&myEventHandler);
	manager->addMouseMotionListener(&myEventHandler);
	manager->addMouseButtonListener(&myEventHandler);

	_initAttributes(rt);
}

//! (dtor)
E_GUI_Manager::~E_GUI_Manager() {
	// FIXME: See ticket #316.
	//delete manager;
}

//! ---|> Object
EScript::Object * E_GUI_Manager::clone()const {
	WARN("Unclonable!");
	return nullptr;
}

bool E_GUI_Manager::handleEvent(const Util::UI::Event & event) {
	return manager->handleEvent(event);
}

}
