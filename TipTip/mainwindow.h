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

    int m_coutTip = 0;
    int m_remainingTime = 0;

    QPointer<QButtonGroup> m_tipTypeGroup;
    QPointer<QButtonGroup> m_tipTimesGroup;
    QPointer<QTimer> m_tickTimer;
    QPointer<QTimer> m_showTimer;
    QPointer<QTimer> m_remainingTimer;
    QPointer<QSystemTrayIcon> m_sysTray;
    QPointer<tipDialog> m_tipDialog;
    QPointer<QMenu> m_pSysTrayMenu;
private:
    void UpdateCountTip();

private slots:
    void on_okBtn_toggled(bool);
    void OnTimeOut();
    void OnMoveTimeOut();
    void OnSysMenuToggled(QAction*);
    void OnSysTrayToggled(QSystemTrayIcon::ActivationReason reason);
    void OnUpdateremainingTime();
    void on_blackScreenCheckBox_toggled(bool);

protected:
    void closeEvent(QCloseEvent* e) override;
};

#endif // MAINWINDOW_H
