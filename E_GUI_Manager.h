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

#include <EScript/Objects/ExtObject.h>
#include <memory>

namespace GUI {
class GUI_Manager;
}
namespace Util {
namespace UI {
union Event;
class EventContext;
}
}

namespace E_GUI{
struct E_GUI_Manager_EventHandler;

/**
 *  EScript-Wrapper for GUI::GUI_Manager.
 *
 *    [E_GUI_Manager] ---|> [EScript::ExtObject]
 *      |
 *      ------> [GUI::GUI_Manager]
 */
class E_GUI_Manager : public EScript::ExtObject {
	ES_PROVIDES_TYPE_NAME(GUI_Manager)

	public:
		static E_GUI_Manager* getEObj(GUI::GUI_Manager*);
		
		E_GUI_Manager(Util::UI::EventContext * eventContext, EScript::Runtime & rt,EScript::Type * type=nullptr);

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_GUI_Manager();
		const GUI::GUI_Manager & getGUI_Manager()const	{	return *manager.get();		}
		GUI::GUI_Manager & getGUI_Manager()				{	return *manager.get();		}
		bool handleEvent(const Util::UI::Event & event);
		E_GUI_Manager_EventHandler * getEventHandler();
		
		const GUI::GUI_Manager* operator*()const		{	return manager.get();	}
		GUI::GUI_Manager* operator*()					{	return manager.get();	}

		EScript::Object * clone() const override;

	private:
		std::unique_ptr<GUI::GUI_Manager> manager;
		std::unique_ptr<E_GUI_Manager_EventHandler> eventHandler;
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_GUI_Manager,		GUI::GUI_Manager*,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_GUI::E_GUI_Manager,		GUI::GUI_Manager&,		***eObj)
ES_CONV_OBJ_TO_EOBJ(GUI::GUI_Manager*,			E_GUI::E_GUI_Manager,	E_GUI::E_GUI_Manager::getEObj(obj))

#endif // E_GUI_MANAGER_H
