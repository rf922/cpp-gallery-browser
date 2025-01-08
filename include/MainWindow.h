/*
 * File : MainWindow.h
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDir>
#include <QKeyEvent>
#include <QPixmap>
#include <QMenuBar> 
#include <QMenu>   
#include <QAction>
#include <QHBoxLayout>
#include <QStringList>

#include "DirectorySelector.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDirectoryPath(const QString &path);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            toggleFullScreen();
        }
    }


private slots:
    void showNextImage();
    void showPreviousImage();
    void openDirectorySelector();
    void toggleNavigationButtons(bool visible);
    void toggleFullScreen();

private:
    void loadImages();
    void displayImage();
    QString getNextSubdirectory();

    QString parentDirectory;
    

    QLabel *imageLabel;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QVBoxLayout *layout;

    QStringList imageFiles;
    int currentIndex;
    QString directoryPath; 

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QAction *openDirAction;
    QAction *toggleButtonsAction;
    QAction *toggleFullScreenAction;
    DirectorySelector *directorySelector;
};

#endif // MAINWINDOW_H

