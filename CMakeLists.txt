cmake_minimum_required(VERSION 3.16)

project(CyberGuardian VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Quick3D)

qt_standard_project_setup()

qt_add_executable(appCyberGuardian
    main.cpp
)

qt_add_qml_module(appCyberGuardian
    URI CyberGuardian
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES images/skybox/desert.png images/skybox/grass.png images/skybox/water.png
        RESOURCES images/skybox/desert.jpg
        RESOURCES shaders/floor_material.frag
        SOURCES skytexture.h skytexture.cpp
        SOURCES QMLData.h
        SOURCES macros.h
        RESOURCES shaders/ground_material.frag
        RESOURCES shaders/ground_material.vert
        RESOURCES images/testHM.jpg
        RESOURCES images/earth.png
        SOURCES noise/qnoise.h noise/qnoise.cpp
        SOURCES noiseprovider.h noiseprovider.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCyberGuardian PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCyberGuardian
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCyberGuardian
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Quick3D
)

include(GNUInstallDirs)
install(TARGETS appCyberGuardian
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
