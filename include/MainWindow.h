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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDirectoryPath(const QString &path);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void showNextImage();
    void showPreviousImage();
    void openDirectorySelector();

private:
    void loadImages();
    void displayImage();

    QLabel *imageLabel;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QVBoxLayout *layout;

    QStringList imageFiles;
    int currentIndex;
    QString directoryPath; 

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *openDirAction;
};

#endif // MAINWINDOW_H

