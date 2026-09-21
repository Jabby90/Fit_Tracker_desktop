cmake_minimum_required(VERSION 3.19)
project(Fit_Tracker_desktop LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(SQLite3)

qt_standard_project_setup()

qt_add_executable(Fit_Tracker_desktop
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    include/constants.h
    include/tracker_db.h src/tracker_db.cpp
)

target_link_libraries(Fit_Tracker_desktop
    PRIVATE
        Qt::Core
        Qt::Widgets
        SQLite3::SQLite3
)

install(TARGETS Fit_Tracker_desktop
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Fit_Tracker_desktop
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
