/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GUI_MANAGER_H
#define E_GUI_MANAGER_H

#include <GUI/GUI_Manager.h>
#include <EScript/Objects/ExtObject.h>
#include <GUI/Base/Listener.h>
#include <memory>

namespace Util {
namespace UI {
union Event;
class EventContext;
}
}

namespace E_GUI{
class E_GUI_Manager;

/**
 *   [EScript_EventHandler]    ---|> [ActionListener]
 *                             ---|> [DataChangeListener]
 */
class EScript_EventHandler:
			public GUI::ActionListener, public GUI::DataChangeListener,
			public GUI::MouseButtonListener,public GUI::MouseMotionListener {
	public:
		EScript_EventHandler(EScript::Runtime & _rt,E_GUI_Manager & _eManager):rt(_rt),eManager(_eManager){};
		// ---|> ActionListener
		GUI::listenerResult_t handleAction(GUI::Component * component,const Util::StringIdentifier & actionName) override;
		// ---|> DataChangeListener
		void handleDataChange(GUI::Component *,const Util::StringIdentifier & actionName) override;
		// ---|> MouseButtonListener
		GUI::listenerResult_t onMouseButton(GUI::Component * component, const Util::UI::ButtonEvent & buttonEvent) override;
		// ---|> MouseMotionListener
		GUI::listenerResult_t onMouseMove(GUI::Component * component, const Util::UI::MotionEvent & motionEvent) override;

		bool onKeyEvent(GUI::Component * component, const Util::UI::KeyboardEvent & keyEvent);

	private:
		EScript::Runtime & rt;
		E_GUI_Manager & eManager;
};

/**
 *  EScript-Wrapper for GUI::GUI_Manager.
 *
 *    [E_GUI_Manager] ---|> [EScript::ExtObject]
 *      |
 *      ------> [GUI::GUI_Manager]
 */
class E_GUI_Manager : public EScript::ExtObject{
	ES_PROVIDES_TYPE_NAME(GUI_Manager)

	public:
		E_GUI_Manager(Util::UI::EventContext & eventContext, EScript::Runtime & rt,EScript::Type * type=nullptr);

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_GUI_Manager();
		const GUI::GUI_Manager & getGUI_Manager()const	{	return *manager.get();		}
		GUI::GUI_Manager & getGUI_Manager()				{	return *manager.get();		}
		bool handleEvent(const Util::UI::Event & event);
		EScript_EventHandler * getEScriptEventHandler()	{	return &myEventHandler;	}
		
		const GUI::GUI_Manager* operator*()const		{	return manager.get();	}
		GUI::GUI_Manager* operator*()					{	return manager.get();	}

		EScript::Object * clone() const override;

	protected:
		std::unique_ptr<GUI::GUI_Manager> manager;
		EScript_EventHandler myEventHandler;
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_GUI_Manager,		GUI::GUI_Manager*,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_GUI_Manager,		GUI::GUI_Manager&,		***eObj)

#endif // E_GUI_MANAGER_H
