INCLUDE_DIRECTORIES(.)

LINK_DIRECTORIES(${BUILD_DIR}/src)

SET(OpenSkyPlanetarium_SRCS
     OpenSkyPlanetarium.hpp
     OpenSkyPlanetarium.cpp
     LaserDev.hpp
     LaserDev.cpp
     Calibrate.hpp
     Calibrate.cpp
     SerialCom.hpp
     SerialCom.cpp
     gui/OSPMainDialog.hpp
     gui/OSPMainDialog.cpp
)

SET(OpenSkyPlanetarium_UIS
     gui/OSPMainDialog.ui
)

SET(OpenSkyPlanetarium_RES
     ../OpenSkyPlanetarium.qrc
)
QT5_ADD_RESOURCES(OpenSkyPlanetarium_RES_CXX ${OpenSkyPlanetarium_RES})

# Wrapping UI
QT5_WRAP_UI(OpenSkyPlanetarium_UIS_H ${OpenSkyPlanetarium_UIS})


# Library Properties
ADD_LIBRARY(OpenSkyPlanetarium-static MODULE
${OpenSkyPlanetarium_SRCS} ${OpenSkyPlanetarium_RES_CXX}
${OpenSkyPlanetarium_UIS_H})
QT5_USE_MODULES(OpenSkyPlanetarium-static Core Gui Widgets Multimedia)
SET_TARGET_PROPERTIES(OpenSkyPlanetarium-static PROPERTIES OUTPUT_NAME
"OpenSkyPlanetarium" AUTOMOC TRUE COMPILE_FLAGS "-DQT_OSP")
TARGET_LINK_LIBRARIES(OpenSkyPlanetarium-static ${extLinkerOption})

