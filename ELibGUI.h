/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef ELIBGUI_H
#define ELIBGUI_H

namespace EScript {
class Namespace;
}
namespace GUI {
class Component;
}

namespace E_GUI {
class E_Component;

//LIB_EXPORT
void init(EScript::Namespace * globals);

}

#endif // ELIBGUI_H
