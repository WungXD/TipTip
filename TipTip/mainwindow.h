#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <qpointer.h>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

#include "tipdialog.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int m_moveHeight = 0;
    int m_closeType;

    QPointer<QButtonGroup> m_tipTypeGroup;
    QPointer<QButtonGroup> m_tipTimesGroup;
    QPointer<QTimer> m_tickTimer;
    QPointer<QTimer> m_showTimer;
    QPointer<QSystemTrayIcon> m_sysTray;
    QPointer<tipDialog> m_tipDialog;
    QPointer<QMenu> m_pSysTrayMenu;
private slots:
    void on_okBtn_clicked();
    void OnTimeOut();
    void OnMoveTimeOut();
    void OnSysMenuToggled(QAction*);
    void OnSysTrayToggled(QSystemTrayIcon::ActivationReason reason);
protected:
    void closeEvent(QCloseEvent* e) override;
};

#endif // MAINWINDOW_H
