#include <QSettings>
#include <QKeyEvent>
#include "mainwindow.h"

#ifdef Q_OS_WIN
# include <windows.h>
#endif
#ifdef Q_OS_LINUX
# include <X11/XKBlib.h>
#endif

Tray::Tray(QWidget *parent)
    :QObject(parent)
{
    iconOn=QIcon(":/capslock_on.png");
    iconOff=QIcon(":/capslock_off.png");
#ifdef Q_OS_LINUX
    d = XOpenDisplay((char*)0);
#endif
    timer=new QTimer;
    timer->start(1);
    trayIcon=new QSystemTrayIcon;
    if(isLocked()){
        trayIcon->setIcon(iconOn);
        oldState=true;
    }
    else{
        trayIcon->setIcon(iconOff);
        oldState=false;
    }
    trayIcon->setToolTip(tr("capslock-status"));
    menu=new QMenu;
    actQuit=menu->addAction(tr("Exit"));
    trayIcon->setContextMenu(menu);
    trayIcon->show();
    connect(timer,&QTimer::timeout,
            this,&Tray::updateIcon);
    connect(actQuit,&QAction::triggered,
            qApp,&QApplication::quit);

}
void Tray::updateIcon()
{
    newState=isLocked();
    if(newState!=oldState){
        if(newState){
            trayIcon->setIcon(iconOn);
        }
        else{
            trayIcon->setIcon(iconOff);
        }
    }
    oldState=newState;
}

bool Tray::isLocked()
{
#ifdef Q_OS_WIN
    if(GetKeyState(VK_CAPITAL) == 1)
        return true;
    else
        return false;
#endif
#ifdef Q_OS_LINUX
    bool caps_state;
    unsigned n;
    XkbGetIndicatorState(d, XkbUseCoreKbd, &n);
    caps_state = (n & 0x01) == 1;
    return caps_state;
#endif
}
