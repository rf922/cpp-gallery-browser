#
# File : cpp-gallery-browser.pro
#







# Project type and name
TEMPLATE = app
TARGET = cpp-gallery-browser

# Include source and header files
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/DirectorySelector.cpp

HEADERS += \
    include/MainWindow.h \
    include/DIrectorySelector.h

# Add include paths for headers
INCLUDEPATH += include

DISTFILES += styles/styles.qss

RESOURCES += styles/styles.qrc \
             resources/icons/icons.qrc


# Define the Qt modules to use
QT += core gui widgets

# Set C++ standard
CONFIG += c++17



# Output paths for builds
DESTDIR = build/bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
