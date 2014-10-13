/*
	This file is part of the E_GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "ELibGUI.h"

#include <EScript/EScript.h>

#include <GUI/Components/ComponentPropertyIds.h>
#include <GUI/Base/Draw.h>
#include <GUI/Base/Layouters/ExtLayouter.h>
#include <GUI/Style/Style.h>
#include <GUI/Style/Colors.h>

#include <E_Util/Graphics/E_Color.h>
#include "E_GUI_Manager.h"

#include "Base/E_AbstractShape.h"
#include "Base/E_Layouters.h"
#include "Base/E_Properties.h"
#include "Base/E_ImageData.h"
#include "Base/Fonts/E_AbstractFont.h"
#include "Base/Fonts/E_BitmapFont.h"

#include "Components/E_Button.h"
#include "Components/E_Checkbox.h"
#include "Components/E_Connector.h"
#include "Components/E_EditorPanel.h"
#include "Components/E_Icon.h"
#include "Components/E_Image.h"
#include "Components/E_LayoutHelper.h"
#include "Components/E_Label.h"
#include "Components/E_ListView.h"
#include "Components/E_Menu.h"
#include "Components/E_Panel.h"
#include "Components/E_Scrollbar.h"
#include "Components/E_Slider.h"
#include "Components/E_Splitter.h"
#include "Components/E_Tab.h"
#include "Components/E_TabbedPanel.h"
#include "Components/E_Textarea.h"
#include "Components/E_Textfield.h"
#include "Components/E_TreeView.h"
#include "Components/E_Window.h"

using namespace EScript;

namespace E_GUI {

//! (static)
void init(EScript::Namespace * globals) {
	Namespace * lib=new Namespace();
	declareConstant(globals,"GUI",lib);

	E_GUI_Manager::init(*lib);

	E_Component::init(*lib);
	E_Container::init(*lib);

	E_Button::init(*lib);
	E_Checkbox::init(*lib);
	E_Connector::init(*lib);
	E_Icon::init(*lib);
	E_Image::init(*lib);
	E_EditorPanel::init(*lib);
	E_Label::init(*lib);
	E_ListView::init(*lib);
	E_Menu::init(*lib);
	E_NextRow::init(*lib);
	E_NextColumn::init(*lib);
	E_Panel::init(*lib);
	E_Scrollbar::init(*lib);
	E_Slider::init(*lib);
	E_Splitter::init(*lib);
	E_Tab::init(*lib);
	E_TabbedPanel::init(*lib);
	E_Textarea::init(*lib);
	E_Textfield::init(*lib);
	E_TreeView::init(*lib);
	E_TreeViewEntry::init(*lib);
	E_Window::init(*lib);

	E_AbstractFont::init(*lib);
	E_BitmapFont::init(*lib);

	E_AbstractShape::init(*lib);
	E_ImageData::init(*lib);
	E_AbstractLayouter::init(*lib);
	E_Property::init(*lib);

	declareConstant(lib,"EVENT_IGNORED",new EScript::Bool(false));
	declareConstant(lib,"EVENT_HANDLED",new EScript::Bool(true));

	/// Flags
	declareConstant(lib,"AUTO_MAXIMIZE",new EScript::Number(GUI::Component::AUTO_MAXIMIZE));
	declareConstant(lib,"AUTO_MINIMIZE",new EScript::Number(GUI::Component::AUTO_MINIMIZE));
	declareConstant(lib,"BACKGROUND",new EScript::Number(GUI::Component::BACKGROUND));
	declareConstant(lib,"LOWERED_BORDER",new EScript::Number(GUI::Component::LOWERED_BORDER));
	declareConstant(lib,"RAISED_BORDER",new EScript::Number(GUI::Component::RAISED_BORDER));
	declareConstant(lib,"BORDER",new EScript::Number(GUI::Component::BORDER));
	declareConstant(lib,"ALWAYS_ON_TOP",new EScript::Number(GUI::Component::ALWAYS_ON_TOP));
	declareConstant(lib,"LOCKED",new EScript::Number(GUI::Component::LOCKED));
	declareConstant(lib,"USE_SCISSOR",new EScript::Number(GUI::Component::USE_SCISSOR));

	/// ExternalLayout
	declareConstant(lib,"REFERENCE_X_LEFT",new EScript::Number(GUI::ExtLayouter::REFERENCE_X_LEFT));
	declareConstant(lib,"REFERENCE_X_CENTER",new EScript::Number(GUI::ExtLayouter::REFERENCE_X_CENTER));
	declareConstant(lib,"REFERENCE_X_RIGHT",new EScript::Number(GUI::ExtLayouter::REFERENCE_X_RIGHT));
	declareConstant(lib,"REFERENCE_Y_TOP",new EScript::Number(GUI::ExtLayouter::REFERENCE_Y_TOP));
	declareConstant(lib,"REFERENCE_Y_CENTER",new EScript::Number(GUI::ExtLayouter::REFERENCE_Y_CENTER));
	declareConstant(lib,"REFERENCE_Y_BOTTOM",new EScript::Number(GUI::ExtLayouter::REFERENCE_Y_BOTTOM));
	declareConstant(lib,"ALIGN_X_RIGHT",new EScript::Number(GUI::ExtLayouter::ALIGN_X_RIGHT));
	declareConstant(lib,"ALIGN_X_CENTER",new EScript::Number(GUI::ExtLayouter::ALIGN_X_CENTER));
	declareConstant(lib,"ALIGN_X_LEFT",new EScript::Number(GUI::ExtLayouter::ALIGN_X_LEFT));
	declareConstant(lib,"ALIGN_Y_TOP",new EScript::Number(GUI::ExtLayouter::ALIGN_Y_TOP));
	declareConstant(lib,"ALIGN_Y_CENTER",new EScript::Number(GUI::ExtLayouter::ALIGN_Y_CENTER));
	declareConstant(lib,"ALIGN_Y_BOTTOM",new EScript::Number(GUI::ExtLayouter::ALIGN_Y_BOTTOM));
	declareConstant(lib,"POS_X_ABS",new EScript::Number(GUI::ExtLayouter::POS_X_ABS));
	declareConstant(lib,"POS_X_REL",new EScript::Number(GUI::ExtLayouter::POS_X_REL));
	declareConstant(lib,"POS_Y_ABS",new EScript::Number(GUI::ExtLayouter::POS_Y_ABS));
	declareConstant(lib,"POS_Y_REL",new EScript::Number(GUI::ExtLayouter::POS_Y_REL));
	declareConstant(lib,"WIDTH_REL",new EScript::Number(GUI::ExtLayouter::WIDTH_REL));
	declareConstant(lib,"HEIGHT_REL",new EScript::Number(GUI::ExtLayouter::HEIGHT_REL));
	declareConstant(lib,"WIDTH_ABS",new EScript::Number(GUI::ExtLayouter::WIDTH_ABS));
	declareConstant(lib,"HEIGHT_ABS",new EScript::Number(GUI::ExtLayouter::HEIGHT_ABS));
	declareConstant(lib,"WIDTH_CHILDREN_REL",new EScript::Number(GUI::ExtLayouter::WIDTH_CHILDREN_REL));
	declareConstant(lib,"HEIGHT_CHILDREN_REL",new EScript::Number(GUI::ExtLayouter::HEIGHT_CHILDREN_REL));
	declareConstant(lib,"WIDTH_CHILDREN_ABS",new EScript::Number(GUI::ExtLayouter::WIDTH_CHILDREN_ABS));
	declareConstant(lib,"HEIGHT_CHILDREN_ABS",new EScript::Number(GUI::ExtLayouter::HEIGHT_CHILDREN_ABS));
	declareConstant(lib,"WIDTH_FILL_REL",new EScript::Number(GUI::ExtLayouter::WIDTH_FILL_REL));
	declareConstant(lib,"HEIGHT_FILL_REL",new EScript::Number(GUI::ExtLayouter::HEIGHT_FILL_REL));
	declareConstant(lib,"WIDTH_FILL_ABS",new EScript::Number(GUI::ExtLayouter::WIDTH_FILL_ABS));
	declareConstant(lib,"HEIGHT_FILL_ABS",new EScript::Number(GUI::ExtLayouter::HEIGHT_FILL_ABS));

	/// Button
	declareConstant(lib,"FLAT_BUTTON",new EScript::Number(GUI::Button::FLAT_BUTTON));
	/// Menu
	declareConstant(lib,"ONE_TIME_MENU",new EScript::Number(GUI::Menu::ONE_TIME_MENU));
	/// Panel
	declareConstant(lib,"AUTO_LAYOUT",new EScript::Number(GUI::Panel::AUTO_LAYOUT));
	/// Slider
	declareConstant(lib,"SHOW_VALUE",new EScript::Number(GUI::Slider::SHOW_VALUE));
	declareConstant(lib,"SLIDER_BUTTONS",new EScript::Number(GUI::Slider::SLIDER_BUTTONS));
	/// TreeView::TreeViewEntry
	declareConstant(lib,"COLLAPSED_ENTRY",new EScript::Number(GUI::TreeView::TreeViewEntry::COLLAPSED_ENTRY));
	/// Window
	declareConstant(lib,"NO_CLOSE_BUTTON",new EScript::Number(GUI::Window::NO_CLOSE_BUTTON));
	declareConstant(lib,"NO_MINIMIZE_BUTTON",new EScript::Number(GUI::Window::NO_MINIMIZE_BUTTON));
	declareConstant(lib,"NO_RESIZE_PANEL",new EScript::Number(GUI::Window::NO_RESIZE_PANEL));
	declareConstant(lib,"HIDDEN_WINDOW",new EScript::Number(GUI::Window::HIDDEN_WINDOW));
	declareConstant(lib,"ONE_TIME_WINDOW",new EScript::Number(GUI::Window::ONE_TIME_WINDOW));

	/// TextStyles
	declareConstant(lib,"TEXT_ALIGN_LEFT",Number::create(GUI::Draw::TEXT_ALIGN_LEFT));
	declareConstant(lib,"TEXT_ALIGN_RIGHT",Number::create(GUI::Draw::TEXT_ALIGN_RIGHT));
	declareConstant(lib,"TEXT_ALIGN_CENTER",Number::create(GUI::Draw::TEXT_ALIGN_CENTER));
	declareConstant(lib,"TEXT_ALIGN_MIDDLE",Number::create(GUI::Draw::TEXT_ALIGN_MIDDLE));
//	declareConstant(lib,"TEXT_HIGHLIGHT",Number::create(GUI::Draw::TEXT_HIGHLIGHT));

	/// Property Ids
	declareConstant(lib,"PROPERTY_BUTTON_ENABLED_COLOR",new EScript::Number(GUI::PROPERTY_BUTTON_ENABLED_COLOR));
	declareConstant(lib,"PROPERTY_BUTTON_SHAPE",new EScript::Number(GUI::PROPERTY_BUTTON_SHAPE));
	declareConstant(lib,"PROPERTY_BUTTON_HOVERED_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_BUTTON_HOVERED_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_CHECKBOX_LABEL_INDENTATION",new EScript::Number(GUI::PROPERTY_CHECKBOX_LABEL_INDENTATION));
	declareConstant(lib,"PROPERTY_CHECKBOX_SHAPE",new EScript::Number(GUI::PROPERTY_CHECKBOX_SHAPE));
	declareConstant(lib,"PROPERTY_CHECKBOX_MARKER_SHAPE",new EScript::Number(GUI::PROPERTY_CHECKBOX_MARKER_SHAPE));
	declareConstant(lib,"PROPERTY_COMPONENT_BACKGROUND_SHAPE",new EScript::Number(GUI::PROPERTY_COMPONENT_BACKGROUND_SHAPE));
	declareConstant(lib,"PROPERTY_COMPONENT_ADDITIONAL_BACKGROUND_SHAPE",new EScript::Number(GUI::PROPERTY_COMPONENT_ADDITIONAL_BACKGROUND_SHAPE));
	declareConstant(lib,"PROPERTY_COMPONENT_BORDER_SHAPE",new EScript::Number(GUI::PROPERTY_COMPONENT_BORDER_SHAPE));
	declareConstant(lib,"PROPERTY_COMPONENT_RAISED_BORDER_SHAPE",new EScript::Number(GUI::PROPERTY_COMPONENT_RAISED_BORDER_SHAPE));
	declareConstant(lib,"PROPERTY_COMPONENT_LOWERED_BORDER_SHAPE",new EScript::Number(GUI::PROPERTY_COMPONENT_LOWERED_BORDER_SHAPE));
	declareConstant(lib,"PROPERTY_CONNECTOR_LINE_SHAPE",new EScript::Number(GUI::PROPERTY_CONNECTOR_LINE_SHAPE));
	declareConstant(lib,"PROPERTY_DEFAULT_FONT",new EScript::Number(GUI::PROPERTY_DEFAULT_FONT));
	declareConstant(lib,"PROPERTY_ICON_COLOR",new EScript::Number(GUI::PROPERTY_ICON_COLOR));
	declareConstant(lib,"PROPERTY_LISTVIEW_SHAPE",new EScript::Number(GUI::PROPERTY_LISTVIEW_SHAPE));
	declareConstant(lib,"PROPERTY_LISTVIEW_DEFAULT_ENTRY_HEIGHT",new EScript::Number(GUI::PROPERTY_LISTVIEW_DEFAULT_ENTRY_HEIGHT));
	declareConstant(lib,"PROPERTY_LISTVIEW_MARKED_ENTRY_SHAPE",new EScript::Number(GUI::PROPERTY_LISTVIEW_MARKED_ENTRY_SHAPE));
	declareConstant(lib,"PROPERTY_MENU_SHAPE",new EScript::Number(GUI::PROPERTY_MENU_SHAPE));
	declareConstant(lib,"PROPERTY_MENU_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_MENU_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_KEY_REPEAT_DELAY_1",new EScript::Number(GUI::PROPERTY_KEY_REPEAT_DELAY_1));
	declareConstant(lib,"PROPERTY_KEY_REPEAT_DELAY_2",new EScript::Number(GUI::PROPERTY_KEY_REPEAT_DELAY_2));
	declareConstant(lib,"PROPERTY_SELECTION_RECT_SHAPE",new EScript::Number(GUI::PROPERTY_SELECTION_RECT_SHAPE));
	declareConstant(lib,"PROPERTY_SLIDER_BAR_SHAPE",new EScript::Number(GUI::PROPERTY_SLIDER_BAR_SHAPE));
	declareConstant(lib,"PROPERTY_SLIDER_BUTTON_SIZE",new EScript::Number(GUI::PROPERTY_SLIDER_BUTTON_SIZE));
	declareConstant(lib,"PROPERTY_SLIDER_MARKER_SHAPE",new EScript::Number(GUI::PROPERTY_SLIDER_MARKER_SHAPE));
	declareConstant(lib,"PROPERTY_SLIDER_ZERO_BAR_SHAPE",new EScript::Number(GUI::PROPERTY_SLIDER_ZERO_BAR_SHAPE));
	declareConstant(lib,"PROPERTY_SPLITTER_SHAPE",new EScript::Number(GUI::PROPERTY_SPLITTER_SHAPE));
	declareConstant(lib,"PROPERTY_TAB_HEADER_ACTIVE_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_TAB_HEADER_ACTIVE_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_TAB_HEADER_HEIGHT",new EScript::Number(GUI::PROPERTY_TAB_HEADER_HEIGHT));
	declareConstant(lib,"PROPERTY_TAB_HEADER_PASSIVE_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_TAB_HEADER_PASSIVE_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_TAB_HEADER_SHAPE",new EScript::Number(GUI::PROPERTY_TAB_HEADER_SHAPE));
	declareConstant(lib,"PROPERTY_TAB_BODY_SHAPE",new EScript::Number(GUI::PROPERTY_TAB_BODY_SHAPE));
	declareConstant(lib,"PROPERTY_TOOLTIP_FONT",new EScript::Number(GUI::PROPERTY_TOOLTIP_FONT));
	declareConstant(lib,"PROPERTY_TOOLTIP_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_TOOLTIP_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_TEXTFIELD_INDENTATION",new EScript::Number(GUI::PROPERTY_TEXTFIELD_INDENTATION));
	declareConstant(lib,"PROPERTY_TEXTFIELD_SHAPE",new EScript::Number(GUI::PROPERTY_TEXTFIELD_SHAPE));
	declareConstant(lib,"PROPERTY_TEXTFIELD_CLEAR_BUTTON_SIZE",new EScript::Number(GUI::PROPERTY_TEXTFIELD_CLEAR_BUTTON_SIZE));
	declareConstant(lib,"PROPERTY_TEXTFIELD_CLEAR_TEXT_SHAPE",new EScript::Number(GUI::PROPERTY_TEXTFIELD_CLEAR_TEXT_SHAPE));
	declareConstant(lib,"PROPERTY_TEXTFIELD_TEXT_SELECTION_SHAPE",new EScript::Number(GUI::PROPERTY_TEXTFIELD_TEXT_SELECTION_SHAPE));
	declareConstant(lib,"PROPERTY_TEXTFIELD_CURSOR_SHAPE",new EScript::Number(GUI::PROPERTY_TEXTFIELD_CURSOR_SHAPE));
	declareConstant(lib,"PROPERTY_TEXTFIELD_OPTIONS_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_TEXTFIELD_OPTIONS_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_TEXTFIELD_TEXT_COLOR",new EScript::Number(GUI::PROPERTY_TEXTFIELD_TEXT_COLOR));
	declareConstant(lib,"PROPERTY_TREEVIEW_SUBROUP_SHAPE",new EScript::Number(GUI::PROPERTY_TREEVIEW_SUBROUP_SHAPE));
	declareConstant(lib,"PROPERTY_TREEVIEW_ENTRY_SELECTION_SHAPE",new EScript::Number(GUI::PROPERTY_TREEVIEW_ENTRY_SELECTION_SHAPE));
	declareConstant(lib,"PROPERTY_TREEVIEW_ENTRY_MARKING_SHAPE",new EScript::Number(GUI::PROPERTY_TREEVIEW_ENTRY_MARKING_SHAPE));
	declareConstant(lib,"PROPERTY_TREEVIEW_ACTIVE_INDENTATION_SHAPE",new EScript::Number(GUI::PROPERTY_TREEVIEW_ACTIVE_INDENTATION_SHAPE));
	declareConstant(lib,"PROPERTY_TREEVIEW_PASSIVE_INDENTATION_SHAPE",new EScript::Number(GUI::PROPERTY_TREEVIEW_PASSIVE_INDENTATION_SHAPE));
	declareConstant(lib,"PROPERTY_WINDOW_ACTIVE_SHAPE",new EScript::Number(GUI::PROPERTY_WINDOW_ACTIVE_SHAPE));
	declareConstant(lib,"PROPERTY_WINDOW_BORDER_SIZE",new EScript::Number(GUI::PROPERTY_WINDOW_BORDER_SIZE));
	declareConstant(lib,"PROPERTY_WINDOW_BUTTON_SHAPE",new EScript::Number(GUI::PROPERTY_WINDOW_BUTTON_SHAPE));
	declareConstant(lib,"PROPERTY_WINDOW_PASSIVE_SHAPE",new EScript::Number(GUI::PROPERTY_WINDOW_PASSIVE_SHAPE));
	declareConstant(lib,"PROPERTY_WINDOW_RESIZER_SHAPE",new EScript::Number(GUI::PROPERTY_WINDOW_RESIZER_SHAPE));
	declareConstant(lib,"PROPERTY_WINDOW_TITLE_COLOR",new EScript::Number(GUI::PROPERTY_WINDOW_TITLE_COLOR));
	declareConstant(lib,"PROPERTY_WINDOW_TITLE_FONT",new EScript::Number(GUI::PROPERTY_WINDOW_TITLE_FONT));
	declareConstant(lib,"PROPERTY_WINDOW_TITLEBAR_HEIGHT",new EScript::Number(GUI::PROPERTY_WINDOW_TITLEBAR_HEIGHT));

	/// Shapes
	declareConstant(lib,"NULL_SHAPE",new E_AbstractShape( GUI::NullShape::instance()));
	declareConstant(lib,"BUTTON_SHAPE_NORMAL",new E_AbstractShape( GUI::Style::getButtonShape()));
	declareConstant(lib,"BUTTON_SHAPE_TOP_LEFT",new E_AbstractShape( GUI::Style::createButtonShape(3,0,0,0)));
	declareConstant(lib,"BUTTON_SHAPE_TOP",new E_AbstractShape( GUI::Style::createButtonShape(3,3,0,0)));
	declareConstant(lib,"BUTTON_SHAPE_TOP_RIGHT",new E_AbstractShape( GUI::Style::createButtonShape(0,3,0,0)));
	declareConstant(lib,"BUTTON_SHAPE_RIGHT",new E_AbstractShape( GUI::Style::createButtonShape(0,3,0,3)));
	declareConstant(lib,"BUTTON_SHAPE_BOTTOM_RIGHT",new E_AbstractShape( GUI::Style::createButtonShape(0,0,0,3)));
	declareConstant(lib,"BUTTON_SHAPE_BOTTOM",new E_AbstractShape( GUI::Style::createButtonShape(0,0,3,3)));
	declareConstant(lib,"BUTTON_SHAPE_BOTTOM_LEFT",new E_AbstractShape( GUI::Style::createButtonShape(0,0,3,0)));
	declareConstant(lib,"BUTTON_SHAPE_LEFT",new E_AbstractShape( GUI::Style::createButtonShape(3,0,3,0)));
	declareConstant(lib,"BUTTON_SHAPE_MIDDLE",new E_AbstractShape( GUI::Style::createButtonShape(0,0,0,0)));

	/// Colors
	declareConstant(lib,"ACTIVE_COLOR_1",EScript::create( GUI::Colors::ACTIVE_COLOR_1));
	declareConstant(lib,"ACTIVE_COLOR_2",EScript::create( GUI::Colors::ACTIVE_COLOR_2));
	declareConstant(lib,"ACTIVE_COLOR_3",EScript::create( GUI::Colors::ACTIVE_COLOR_3));
	declareConstant(lib,"ACTIVE_COLOR_4",EScript::create( GUI::Colors::ACTIVE_COLOR_4));
	declareConstant(lib,"PASSIVE_COLOR_1",EScript::create( GUI::Colors::PASSIVE_COLOR_1));
	declareConstant(lib,"PASSIVE_COLOR_2",EScript::create( GUI::Colors::PASSIVE_COLOR_2));
	declareConstant(lib,"PASSIVE_COLOR_3",EScript::create( GUI::Colors::PASSIVE_COLOR_3));
	declareConstant(lib,"PASSIVE_COLOR_4",EScript::create( GUI::Colors::PASSIVE_COLOR_4));
    
    /// MouseCursors
    declareConstant(lib, "PROPERTY_MOUSECURSOR_DEFAULT", EScript::String::create(GUI::PROPERTY_MOUSECURSOR_DEFAULT));
    declareConstant(lib, "PROPERTY_MOUSECURSOR_COMPONENTS", EScript::String::create(GUI::PROPERTY_MOUSECURSOR_COMPONENTS));
    declareConstant(lib, "PROPERTY_MOUSECURSOR_TEXTFIELD", EScript::String::create(GUI::PROPERTY_MOUSECURSOR_TEXTFIELD));
    declareConstant(lib, "PROPERTY_MOUSECURSOR_RESIZEDIAGONAL", EScript::String::create(GUI::PROPERTY_MOUSECURSOR_RESIZEDIAGONAL));
}

}
