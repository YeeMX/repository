cmake_minimum_required(VERSION 3.5)

project(BankQueueSystem LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        utils.h
        utils.cpp
        queue.cpp
        queue.h
        customer.cpp
        customer.h
        businesswindow.cpp
        businesswindow.h
        function.cpp
        function.h
        mymainwindow.cpp
        mymainwindow.h
        mymainwindow.ui
        vipwindow.cpp
        vipwindow.h
        vipwindow.ui
        welcomewindow.cpp
        welcomewindow.h
        welcomewindow.ui
        evaluatewindow.cpp
        evaluatewindow.h
        evaluatewindow.ui
        winsthread.cpp
        winsthread.h
        vipthread.cpp
        vipthread.h
        countdownthread.cpp
        countdownthread.h
        main.cpp
        textfinder.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BankQueueSystem
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(BankQueueSystem SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(BankQueueSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BankQueueSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

