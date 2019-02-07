find_package (Qt5 5.6 REQUIRED COMPONENTS Core DBus Network)
find_package (Cutelyst2Qt5 REQUIRED)
find_package (morgoth REQUIRED)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (anna_HEADERS
    anna.h
    daemon.h
    servers.h
)

set (anna_SOURCES
    anna.cpp
    daemon.cpp
    servers.cpp
)

set (servercoordinator_IFACE_XML dbus/org.morgoth.ServerCoordinator.xml)
set_source_files_properties (${servercoordinator_IFACE_XML} PROPERTIES INCLUDE "servercoordinator.h")
qt5_add_dbus_interface (anna_SOURCES ${servercoordinator_IFACE_XML} servercoordinatorinterface)

set (serverstatus_IFACE_XML dbus/org.morgoth.ServerStatus.xml)
set_source_files_properties (${serverstatus_IFACE_XML} PROPERTIES INCLUDE "playerinfo.h")
qt5_add_dbus_interface (anna_SOURCES ${serverstatus_IFACE_XML} serverstatusinterface)

qt5_add_dbus_interface (anna_SOURCES dbus/org.morgoth.Daemon.xml daemoninterface)
qt5_add_dbus_interface (anna_SOURCES dbus/org.morgoth.ServerManager.xml servermanagerinterface)
qt5_add_dbus_interface (anna_SOURCES dbus/org.morgoth.Server.xml serverinterface)

add_library (anna SHARED
    ${anna_HEADERS}
    ${anna_SOURCES}
)

target_link_libraries (anna
    Cutelyst::Core
    Cutelyst::CSRFProtection
    Qt5::Core
    Qt5::DBus
    Qt5::Network
    morgoth::morgoth
)

target_include_directories (anna
    PUBLIC
        ${Cutelyst2Qt5_INCLUDE_DIR}
)
