#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#ifdef Q_OS_LINUX
# include <X11/XKBlib.h>
#endif

class Tray:public QObject
{
    Q_OBJECT
    QTimer *timer;
    bool isLocked();
    QSystemTrayIcon *trayIcon;

    //if this is put in isLocked(), it will be created many times.
    //Then it says "Maximum number of clients reached" and crashes.
    //Therefore I put this here so that it is created only once.
    Display *d;
    QMenu *menu;
    QAction *actQuit;
    QIcon iconOn,iconOff;
    bool oldState,newState;

public:
    Tray(QWidget *parent=0);
private slots:
    void updateIcon();
};

#endif // MAINWINDOW_H
