# cpp-gallery-browser
A C++ QT application for viewing and navigating through images !

# cpp-gallery-browser

## Overview
`cpp-gallery-browser` is a C++ Qt-based application for seamlessly browsing images within a directory structure. It allows users to navigate through subdirectories of images and view them with ease. The application ensures smooth navigation, cycling through images and directories with user-friendly features like navigation buttons and fullscreen mode.

---

## Features

- **Parent Directory Selection**: Start by selecting a parent directory containing image subdirectories.
- **Subdirectory Navigation**: Choose a subdirectory to browse images from the list of available subdirectories.
- **Image Browsing**: Navigate through the images in the selected subdirectory.
  - Cycle through images when the end of the list is reached.
  - Optionally move to the next subdirectory when reaching the last image.
- **Restart Option**: Restart browsing from the top directory if no more subdirectories are available.
- **Responsive Interface**:
  - Fullscreen mode for immersive viewing.
  - Keyboard shortcuts for navigation.
- **Supported Formats**: Handles common image formats like PNG, JPEG, and JPG.
- **Customizable Styles**: The application supports QSS-based styling for a modern and sleek interface.

---

## Installation

### Prerequisites
- **Qt Framework**: Ensure that the Qt development environment is installed (Qt 5.15 or later recommended).
- **C++ Compiler**: A C++17 compatible compiler (e.g., GCC or Clang).

### Build Instructions

To use the command line to build and run:
1. Generate the Makefile using `qmake`:
   ```bash
   qmake cpp-gallery-browser.pro
   ```
2. Build the application using `make`:
   ```bash
   make
   ```
3. Run the application:
   ```bash
   ./build/bin/cpp-gallery-browser
   ```
---

## Usage

### Starting the Application
1. To Run compile and execute the compiled binary.
2. On startup, you will be prompted to select a **parent directory** containing subdirectories with images.

### Navigating Images
- **Select a Subdirectory**: Pick a subdirectory from the list to browse its images.
- **Navigate Through Images**:
  - Use the **Next** and **Previous** buttons to move between images.
  - Keyboard shortcuts:
    - `Right Arrow` / `Down Arrow` / `N`: Next image
    - `Left Arrow` / `Up Arrow` / `P`: Previous image
    - `Alt`: Toggle fullscreen
  - When reaching the last image:
    - Choose to cycle back to the start of the subdirectory.
    - Move to the next subdirectory if available.

### Fullscreen Mode
- Double-click on the image or press `Alt` to toggle fullscreen mode.

---

## Project Structure
```
cpp-gallery-browser/
├── include/                  # Header files
│   ├── MainWindow.h
│   └── DirectorySelector.h
├── src/                      # Source files
│   ├── main.cpp
│   ├── MainWindow.cpp
│   └── DirectorySelector.cpp
├── styles/                   # Stylesheets and resources
│   ├── styles.qss
│   └── icons/                # Icons for the application
├── cpp-gallery-browser.pro   # Qt project configuration file
└── README.md                 # Project documentation
```

---

## Development Notes

### Adding Features
- **Additional File Formats**: Extend the `filters` list in `MainWindow::loadImages` to support more formats.
- **Advanced Sorting**: Customize the sorting logic in `DirectorySelector::customSort`.

### Debugging
- Use `qDebug()` statements in the code for logging runtime events (already implemented in key areas).
- Ensure the `styles.qss` file is in the correct location for styling to apply.

---

## Contributions
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch for your feature/bugfix.
3. Submit a pull request with a clear description of changes.

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.


## Screenshots

<div align="center">
  <img src="https://github.com/user-attachments/assets/9aed6cdc-7fde-4711-9534-ce32554515b5" alt="application-directory-select-dialog" />
  <img src="https://github.com/user-attachments/assets/c225d8f3-32f1-42e0-8b85-7ddc3b40163b" alt="application-img-view-dialog" />
  <img src="https://github.com/user-attachments/assets/0baa6fa3-03a7-4af9-a9b7-9137735c1dc7" alt="next" />
</div>
