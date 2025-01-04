# Project type and name
TEMPLATE = app
TARGET = cpp-gallery-browser

# Include source and header files
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    include/MainWindow.h

# Add include paths for headers
INCLUDEPATH += include

DISTFILES += styles/styles.qss

# Define the Qt modules to use
QT += core gui widgets

# Set C++ standard
CONFIG += c++17

# Directory where the images are located 
DEFINES += IMAGE_DIR=\"/path/to/your/images\"

# Output paths for builds
DESTDIR = build/bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
