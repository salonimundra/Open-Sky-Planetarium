# This is the cmake config file for the OpenSkyPlanetarium
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
SET(OPENSKYPLANETARIUM_VERSION "0.1.0")
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

SET(STELLARIUM_SOURCE_DIR $ENV{STELROOT})

INCLUDE_DIRECTORIES(
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/gui
	${STELLARIUM_SOURCE_DIR}/src
	${STELLARIUM_SOURCE_DIR}/src/core
	${STELLARIUM_SOURCE_DIR}/src/core/modules
	${STELLARIUM_SOURCE_DIR}/src/core/planetsephems
	${STELLARIUM_SOURCE_DIR}/src/core/external
	${STELLARIUM_SOURCE_DIR}/src/core/external/qtcompress
	${STELLARIUM_SOURCE_DIR}/src/core/external/glues_stel/source/
	${STELLARIUM_SOURCE_DIR}/src/core/external/glues_stel/source/libtess
	${STELLARIUM_SOURCE_DIR}/src/gui
	${STELLARIUM_SOURCE_DIR}/src/scripting
	${INTL_INCLUDE_DIR}
	${CMAKE_BINARY_DIR}/src
	${ZLIB_INCLUDE_DIR}
)

ADD_SUBDIRECTORY( src )

SET(QT_LINK_PARAMETERS Qt5::Core Qt5::Gui Qt5::OpenGL)

SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/.stellarium)

install(FILES builds/unix/src/libOpenSkyPlanetarium.so DESTINATION modules/OpenSkyPlanetarium/)
