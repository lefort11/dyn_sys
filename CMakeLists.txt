cmake_minimum_required(VERSION 3.6)
project(dyn_sys)

set(CMAKE_CXX_STANDARD 11)


FIND_PACKAGE(wxWidgets REQUIRED net gl core base)
IF(wxWidgets_FOUND)
    message("KEK")
    include(${wxWidgets_USE_FILE})
ENDIF()


#FIND_LIBRARY(FREECHARTS_LIBRARY wxcode_osx_cocoau_freechart-3.0 /usr/local/lib REQUIRED)
FIND_LIBRARY(wxMATHPLOT_LIBRARY mathplot /usr/local/lib REQUIRED)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${WXWIDGETS_CXX_FLAGS}" )


#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
set(SOURCE_FILES main.cpp GUI/Window.cpp GUI/Window.h GUI/Window.cpp GUI/Window.h Solver/RungeKuttaMethod.cpp Solver/RungeKuttaMethod.h Solver/CultureEvolutionModel.cpp Solver/CultureEvolutionModel.h GUI/XYChart.cpp GUI/XYChart.h Application.cpp Application.h)

set(wxWidgets_USE_STATIC ON)

add_executable(dyn_sys ${SOURCE_FILES})
target_link_libraries(dyn_sys ${wxWidgets_LIBRARIES} ${wxMATHPLOT_LIBRARY})

set(BUNDLE_NAME dyn_sys.app)
set(BUNDLE_PATH "${CMAKE_SOURCE_DIR}/${BUNDLE_NAME}")
set(BINDIR ${BUNDLE_PATH}/Contents/MacOS)
set(LIBDIR ${BUNDLE_PATH}/Contents/Libraries)
set(RLIBDIR ${BUNDLE_PATH}/Contents/Frameworks)
set(SHAREDIR ${BUNDLE_PATH}/Contents/Resources)
set(PLUGINSDIR ${BUNDLE_PATH}/Contents/PlugIns)
set(IMPORTSDIR ${BINDIR})
set(wxWidgets_USE_LIBS net gl core base)

install(TARGETS dyn_sys
        RUNTIME DESTINATION ${BINDIR}
        LIBRARY DESTINATION ${LIBDIR}
        ARCHIVE DESTINATION ${LIBDIR}
        BUNDLE DESTINATION ${CMAKE_SOURCE_DIR}
        PERMISSIONS WORLD_WRITE WORLD_READ WORLD_EXECUTE)

#file(GLOB_RECURSE WXPLUGINS_ONE
 #       \"\${CMAKE_INSTALL_PREFIX}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")

#install(FILES ${WXPLUGINS_ONE}
#        DESTINATION ${PLUGINSDIR}
#        COMPONENT RUNTIME)


set(APPS ${CMAKE_SOURCE_DIR}/dyn_sys.app)  # paths to executables
set(DIRS ${wxWidgets_LIBRARY_DIRS})   # directories to search for prerequisites
INSTALL(CODE "
    file(GLOB_RECURSE WXPLUGINS
    \"\${CMAKE_INSTALL_PREFIX}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
   include(BundleUtilities)
   fixup_bundle(\"${APPS}\"   \"\"   \"${DIRS}\")
   " COMPONENT Runtime
        PERMISSIONS WORLD_WRITE WORLD_READ_WORLD_EXECUTE)