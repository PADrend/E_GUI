/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef _E_GUI_E_ImageData_H_
#define _E_GUI_E_ImageData_H_

#include <EScript/Objects/ReferenceObject.h>
#include <GUI/Base/ImageData.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_GUI{

/*!	EScript wrapper class for GUI::ImageData.

		E_ImageData ---|> EScript::ReferenceObject<Util::Reference<GUI::ImageData> >
			|
			--------------> GUI::ImageData		*/
class E_ImageData : public EScript::ReferenceObject<Util::Reference<GUI::ImageData> > {
		ES_PROVIDES_TYPE_NAME(ImageData)
	public:
		EGUIAPI static EScript::Type * getTypeObject();
		EGUIAPI static void init(EScript::Namespace & lib);

		E_ImageData(const Util::Reference<GUI::ImageData> & _obj) :
				ReferenceObject_t(_obj, E_ImageData::getTypeObject()) {}
		virtual ~E_ImageData() {}

		GUI::ImageData * operator*()			{	return ref().get();	}
		const GUI::ImageData * operator*()const	{	return ref().get();	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_GUI::E_ImageData,		GUI::ImageData*,		**eObj)	
ES_CONV_OBJ_TO_EOBJ(GUI::ImageData*,		E_GUI::E_ImageData,		new E_GUI::E_ImageData(obj))	

#endif // _E_GUI_E_ImageData_H_
