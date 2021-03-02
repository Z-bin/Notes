cmake_minimum_required(VERSION 3.5)

project(network)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(QT Core Gui Quick QuickControls2 DBus Xml Concurrent)
find_package(Qt5 REQUIRED ${QT})

get_target_property(QT_QMAKE_EXECUTABLE ${Qt5Core_QMAKE_EXECUTABLE} IMPORTED_LOCATION)
if(NOT QT_QMAKE_EXECUTABLE)
    message(FATAL_ERROR "qmake is not found.")
endif()


execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_QML
    OUTPUT_VARIABLE INSTALL_QMLDIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(INSTALL_QMLDIR)
    message(STATUS "qml directory:" "${INSTALL_QMLDIR}")
else()
    message(FATAL_ERROR "qml directory cannot be detected.")
endif()

set(SOURCES
    networkmanager/appletproxymodel.cpp
    networkmanager/appletproxymodel.h

    networkmanager/networkitemslist.cpp
    networkmanager/networkitemslist.h

    networkmanager/networkmodel.cpp
    networkmanager/networkmodel.h

    networkmanager/networkmodelitem.cpp
    networkmanager/networkmodelitem.h

    networkmanager/networking.cpp
    networkmanager/networking.h

    networkmanager/wirelessitemsettings.cpp
    networkmanager/wirelessitemsettings.h

    networkmanager/technologyproxymodel.cpp
    networkmanager/technologyproxymodel.h

    networkmanager/uiutils.cpp
    networkmanager/uiutils.h
    main.cpp
    )

add_executable(network ${SOURCES})
find_package(KF5NetworkManagerQt REQUIRED)

find_package(KF5ModemManagerQt REQUIRED)

#add_library(networknm SHARED ${SHARE_SOURCES})
#generate_export_header(networknm EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/networkmanager_export.h BASE_NAME NetworkManager)


target_link_directories(network
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
    )

target_link_libraries (network
    Qt5::Core
    Qt5::Quick
    Qt5::Gui
    Qt5::DBus

    KF5::NetworkManagerQt
    KF5::ModemManagerQt
)

