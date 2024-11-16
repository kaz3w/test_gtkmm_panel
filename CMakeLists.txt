cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# set the project name and version
project(panel VERSION 1.0)

include(GNUInstallDirs)

option(WARNINGS "Switch on extra warnings" OFF)
option(WERROR "Turn warnings into errors" OFF)
option(BUILD_TESTS "Build test cases" OFF)

if (BUILD_TESTS)
  enable_testing()
endif(BUILD_TESTS)

find_package(Git)
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always HEAD
    OUTPUT_VARIABLE GIT_REPO_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  execute_process(COMMAND ${GIT_EXECUTABLE} log -n 1 --pretty=%cd --date=format:%Y-%m-%d ${GIT_REPO_VERSION}
    OUTPUT_VARIABLE GIT_REPO_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  set(GIT_REPO_VERSION "${PROJECT_VERSION}")
endif()

if(WARNINGS)
  set(WARNINGS_CXX_FLAGS ${WARNINGS_CXX_FLAGS}
    -Wall -Wextra
    -pedantic -Wno-c++0x-compat -Wnon-virtual-dtor
    -Wcast-qual -Winit-self -Wno-unused-parameter
    # -Wconversion -Wshadow -Weffc++
    )
endif()

if(WERROR)
  set(WARNINGS_CXX_FLAGS ${WARNINGS_CXX_FLAGS}
    -Werror)
endif()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

find_package(PkgConfig REQUIRED)
find_package(Threads)
pkg_search_module(GTKMM REQUIRED gtkmm-3.0)
pkg_search_module(SIGCPP REQUIRED sigc++-2.0)
pkg_search_module(GTK3 REQUIRED gtk+-3.0)
pkg_search_module(GLIB2 REQUIRED glib-2.0)
pkg_search_module(PANGO REQUIRED pango)
pkg_search_module(X11 REQUIRED x11)

# Copy data files over to build/
file(GLOB PANAL_DATA icon/*.png)
file(
  COPY ${PANAL_DATA}
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

file(GLOB PANAL_SOURCES src/*.cpp)

add_executable(panel ${PANAL_SOURCES})

include_directories(SYSTEM
  ${GTKMM_INCLUDE_DIRS}
  ${SIGCPP_INCLUDE_DIRS}
  ${X11_INCLUDE_DIRS})

set_property(TARGET panel PROPERTY COMPILE_OPTIONS
  ${GTKMM_CFLAGS_OTHER}
  ${SIGCPP_CFLAGS_OTHER}
  ${X11_CFLAGS_OTHER}
  ${WARNINGS_CXX_FLAGS}
  )
  
target_link_libraries(panel
  ${CMAKE_THREAD_LIBS_INIT}
  ${GTKMM_LIBRARIES}
  ${SIGCPP_LIBRARIES}
  ${X11_LIBRARIES})

install(TARGETS panel
  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})

# configure_file(
#   ${CMAKE_CURRENT_SOURCE_DIR}/panel.sh.in
#   ${CMAKE_BINARY_DIR}/panel.sh)

install(FILES
  ${CMAKE_BINARY_DIR}/panel.sh
  RENAME panel
  PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  PATTERN "*~" EXCLUDE)

install(FILES
  panel.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

install(FILES
  panel.svg
  DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/panel.1
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

# EOF #
