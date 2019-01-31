cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
project (anna)

# find version
if (NOT anna_VERSION)
    file (READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION anna_VERSION)
    string (STRIP ${anna_VERSION} anna_VERSION)

    include (GetGitRevisionDescription)
    get_git_head_revision(GIT_REFSPEC GIT_SHA1)

    if (NOT "${GIT_SHA1}" STREQUAL "GITDIR-NOTFOUND")
        # shorten SHA
        string (SUBSTRING "${GIT_SHA1}" 0 10 GIT_HASH)
        set (anna_VERSION "${anna_VERSION}-${GIT_HASH}-git")
    endif ()
endif ()

set (CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -Wall -Wextra -Wpedantic")
set (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_VISIBILITY_PRESET hidden)
set (CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_subdirectory (src)

message (STATUS "anna-${anna_VERSION} build summary:")
message (STATUS " * install prefix: ${CMAKE_INSTALL_PREFIX}")
message (STATUS " * build type: ${CMAKE_BUILD_TYPE}")

