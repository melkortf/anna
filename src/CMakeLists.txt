find_package (Qt5 5.6 REQUIRED COMPONENTS Core DBus Network)
find_package (Cutelyst2Qt5 REQUIRED)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (anna_HEADERS
    anna.h
    daemon.h
)

set (anna_SOURCES
    anna.cpp
    daemon.cpp
)

qt5_add_dbus_interface (anna_SOURCES dbus/org.morgoth.Daemon.xml daemoninterface)

add_library (anna SHARED
    ${anna_HEADERS}
    ${anna_SOURCES}
)

target_link_libraries (anna
    Cutelyst::Core
    Qt5::Core
    Qt5::DBus
    Qt5::Network
)

target_include_directories (anna
    PUBLIC
        ${Cutelyst2Qt5_INCLUDE_DIR}
)
