#
# This file is part of the E_GUI library.
# Copyright (C) 2009-2013 Benjamin Eikel <benjamin@eikel.org>
# Copyright (C) 2014-2019 Sascha Brandt <sascha@brandt.graphics>
#
# This library is subject to the terms of the Mozilla Public License, v. 2.0.
# You should have received a copy of the MPL along with this library; see the 
# file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.1.0)
project(E_GUI VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up install directories
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKECONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/E_GUI)

add_library(E_GUI
	Base/E_AbstractShape.cpp
	Base/E_ImageData.cpp
	Base/E_Layouters.cpp
	Base/E_Properties.cpp
	Base/Fonts/E_AbstractFont.cpp
	Base/Fonts/E_BitmapFont.cpp
	Components/E_Button.cpp
	Components/E_Checkbox.cpp
	Components/E_Component.cpp
	Components/E_Container.cpp
	Components/E_Connector.cpp
	Components/E_EditorPanel.cpp
	Components/E_Icon.cpp
	Components/E_Image.cpp
	Components/E_Label.cpp
	Components/E_LayoutHelper.cpp
	Components/E_ListView.cpp
	Components/E_Menu.cpp
	Components/E_Panel.cpp
	Components/E_Scrollbar.cpp
	Components/E_Slider.cpp
	Components/E_Splitter.cpp
	Components/E_TabbedPanel.cpp
	Components/E_Tab.cpp
	Components/E_Textarea.cpp
	Components/E_Textfield.cpp
	Components/E_TreeView.cpp
	Components/E_Window.cpp
	E_GUI_Manager.cpp
	ELibGUI.cpp
)

# Dependency to EScript
if(NOT TARGET EScript)
	find_package(EScript 0.6.7 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC EScript)

# Dependency to Geometry
if(NOT TARGET Geometry)
	find_package(Geometry 0.3.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC Geometry)

# Dependency to GUI
if(NOT TARGET GUI)
	find_package(GUI 0.3.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC GUI)

# Dependency to E_Geometry
if(NOT TARGET E_Geometry)
	find_package(E_Geometry 0.3.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC E_Geometry)

# Dependency to E_Util
if(NOT TARGET E_Util)
	find_package(E_Util 0.3.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC E_Util)

# Dependency to Util
if(NOT TARGET Util)
	find_package(Util 0.3.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC Util)

# Dependency to E_Rendering
if(NOT TARGET E_Rendering)
	find_package(E_Rendering 0.2.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC E_Rendering)

# Dependency to Util
if(NOT TARGET Rendering)
	find_package(Rendering 0.2.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_GUI LINK_PUBLIC Rendering)

# Set version of library
set_target_properties(E_GUI PROPERTIES VERSION ${E_GUI_VERSION}
                                       SOVERSION ${E_GUI_VERSION_MAJOR})

# Install the header files
file(GLOB E_GUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Base/Fonts/*.h")
install(FILES ${E_GUI_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_GUI/Base/Fonts COMPONENT headers)
file(GLOB E_GUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Base/*.h")
install(FILES ${E_GUI_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_GUI/Base COMPONENT headers)
file(GLOB E_GUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Components/*.h")
install(FILES ${E_GUI_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_GUI/Components COMPONENT headers)
file(GLOB E_GUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${E_GUI_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_GUI COMPONENT headers)

# Install the library
install(TARGETS E_GUI EXPORT LibraryExport
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtimelibraries
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtimelibraries
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT developmentlibraries
)

# Set include directories for users of this library
target_include_directories(E_GUI
                           INTERFACE
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
                           "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

# Library export
install(EXPORT LibraryExport DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} FILE E_GUITargets.cmake COMPONENT developmentlibraries)

# Create the configuration files
include(CMakePackageConfigHelpers)
configure_package_config_file(E_GUIConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/E_GUIConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR}
                              PATH_VARS CMAKE_INSTALL_CMAKECONFIGDIR
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/E_GUIConfigVersion.cmake
                                 VERSION ${E_GUI_VERSION}
                                 COMPATIBILITY SameMajorVersion)

# Install the configuration files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/E_GUIConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/E_GUIConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} COMPONENT developmentlibraries)

# Packaging
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "libgui${E_GUI_VERSION_MAJOR}-escript")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "E_GUI library")
set(CPACK_PACKAGE_VENDOR "Benjamin Eikel; Claudius Jaehn; Ralf Petring; Sascha Brandt")
set(CPACK_PACKAGE_CONTACT "Benjamin Eikel <benjamin@eikel.org>")
set(CPACK_PACKAGE_VERSION_MAJOR ${E_GUI_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${E_GUI_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${E_GUI_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "libE_GUI")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES ON)

include(CPack)
