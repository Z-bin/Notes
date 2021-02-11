project(myporject)
cmake_minimum_required(VERSION 3.19)

add_definitions(-DTRANSLATION_DOMAIN=\"kcm_myproject\")

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.74")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMMarkAsTest)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)
include(KDEClangFormat)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Test Sensors)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    Config
    DBusAddons
    Declarative
    GlobalAccel
    I18n
    IconThemes
    KCMUtils
    Plasma
    XmlGui
)

set(kcm_myproject_SRCS
    kcm.cpp
)

add_library(kcm_myproject MODULE ${kcm_myproject_SRCS})
target_link_libraries(kcm_myproject
    KF5::QuickAddons
    KF5::I18n
)

kcoreaddons_desktop_to_json(kcm_myproject "kcm_myproject.desktop" SERVICE_TYPES kcmodule.desktop)

#this desktop file is installed only for retrocompatibility with sycoca
install(FILES kcm_myproject.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

install(TARGETS kcm_myproject DESTINATION ${KDE_INSTALL_PLUGINDIR}/kcms)

kpackage_install_package(package kcm_myproject kcms)
