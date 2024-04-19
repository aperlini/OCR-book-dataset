cmake_minimum_required(VERSION 3.16)

project(gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Tesseract
include_directories(${Tesseract_INCLUDE_DIRS})

# Leptonica
include_directories(${Leptonica_INCLUDE_DIRS})

qt_standard_project_setup()

qt_add_executable(appgui
    main.cpp
)

qt_add_qml_module(appgui
    URI gui
    VERSION 1.0      
    SOURCES
        Models/authormodel.h Models/authormodel.cpp
        Models/bookmodel.h Models/bookmodel.cpp
        Models/apidata.h Models/apidata.cpp         
        Controllers/appcontroller.h Controllers/appcontroller.cpp
        Controllers/apicontroller.h Controllers/apicontroller.cpp
        OCR/imagetreatment.h OCR/imagetreatment.cpp
        OCR/translationthread.h OCR/translationthread.cpp
        Helpers/utils.h Helpers/utils.cpp
        Helpers/selection.h

    QML_FILES
        Main.qml
        UI/HomeScreen/HomeScreen.qml
        UI/HomeScreen/Upload.qml
        UI/ResultScreen/ResultScreen.qml
        UI/ResultScreen/ImageSettings.qml
        UI/ResultScreen/OcrResults.qml
        UI/NetworkScreen/SaveResults.qml
        UI/NetworkScreen/CreateCompleted.qml
        UI/NetworkScreen/RegisterForm.qml
        UI/ResultScreen/TranslationProcess.qml
        UI/Utils/LoadingAnim.qml

    RESOURCES
        UI/assets/images/spinner.gif
        UI/assets/images/spinner1.gif
        UI/assets/images/spinner2.gif
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appgui PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgui
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgui
    PRIVATE Qt6::Quick
    ${OpenCV_LIBS}
    tesseract
    lept
)

include(GNUInstallDirs)
install(TARGETS appgui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
