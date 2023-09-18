#include <QMessageBox>
#include <QScreen>
#include <QAction>

#include "mainwindow.h"
#include "ui_mainwindow.h"

enum ESysTray
{
    displayWind,
    exitWind

};

enum ECloseType
{
    minuType,
    closeType

};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),m_closeType(minuType)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/res/tip.png"));
    m_tipTypeGroup = new QButtonGroup(this);
    m_tipTypeGroup->addButton(ui->cusRadioBtn);
    m_tipTypeGroup->addButton(ui->sysRadioBtn);
    m_tipTimesGroup = new QButtonGroup(this);
    m_tipTimesGroup->addButton(ui->onceRadioBtn);
    m_tipTimesGroup->addButton(ui->loopRadioBtn);
    m_tickTimer = new QTimer(this);
    connect(m_tickTimer, &QTimer::timeout, this, &MainWindow::OnTimeOut);
    m_sysTray = new QSystemTrayIcon(this);
    m_sysTray->setIcon(QIcon(":/img/res/tip.png"));
    m_showTimer = new QTimer(this);
    connect(m_showTimer, &QTimer::timeout, this, &MainWindow::OnMoveTimeOut);
//    connect(m_tipTimesGroup, QOverload<QAbstractButton* , bool>::of(&QButtonGroup::buttonToggled),
//          [=](QAbstractButton *button, bool checked){
//    });
    m_pSysTrayMenu = new QMenu(this);
   // QAction *pActShowMainWnd = new QAction(QStringLiteral("aa"), this);
    QAction *pActShowMainWnd = new QAction(QStringLiteral("show"),this);
    pActShowMainWnd->setData(QVariant::fromValue((int)displayWind));
    m_pSysTrayMenu->addAction(pActShowMainWnd);
    QAction *pActExit = new QAction(QStringLiteral("exit"),this);
    pActExit->setData(QVariant::fromValue((int)exitWind));
    m_pSysTrayMenu->addAction(pActExit);

    connect(m_sysTray, &QSystemTrayIcon::activated, this, &MainWindow::OnSysTrayToggled);
    connect(m_pSysTrayMenu, &QMenu::triggered, this , &MainWindow::OnSysMenuToggled);

    m_sysTray->setContextMenu(m_pSysTrayMenu);
    m_sysTray->show();
}

MainWindow::~MainWindow()
{
    if(m_tipDialog)
        m_tipDialog->close();
    m_sysTray->hide();
    delete ui;
}

void MainWindow::on_okBtn_clicked()
{

    m_tickTimer->stop();
    int interval = ui->hBox->value() * 3600 + ui->mBox->value() * 60 + ui->sBox->value();
    interval = interval * 1000;
    if(interval <= 0)
    {
        QMessageBox::warning(this,"tip", "the interval must be geater than 1s");
        return;
    }

    if(ui->onceRadioBtn->isChecked())
    {
        QTimer::singleShot(interval, this, &MainWindow::OnTimeOut);

    }
    else
    {
        m_tickTimer->setInterval(interval );
        m_tickTimer->start();

    }
    hide();
    m_sysTray->showMessage("tip"," i'm here", QSystemTrayIcon::NoIcon, 1000);

}

void MainWindow::OnTimeOut()
{
    if(ui->cusRadioBtn->isChecked())
    {
        if(m_tipDialog == nullptr)
        {
            m_tipDialog = new tipDialog(this);
        }
        m_tipDialog->SetTipText(ui->lineEdit->text());
        QRect rct = this->screen()->availableGeometry();
        m_moveHeight = 0;
        m_tipDialog->move(rct.width() -m_tipDialog->width(), rct.height() - m_moveHeight);
        m_tipDialog->show();
        m_showTimer->start(10);
    }
    else
    {
        m_sysTray->showMessage("tip",ui->lineEdit->text());

    }

}

void MainWindow::OnMoveTimeOut()
{

    if(m_tipDialog)
    {
        m_moveHeight ++;
        QRect rct = this->screen()->availableGeometry();
        m_tipDialog->move(m_tipDialog->pos().x(),  rct.height() - m_moveHeight);
        if(m_moveHeight >= m_tipDialog->height())
        {
            m_moveHeight = 0;
            m_showTimer->stop();
            m_tipDialog->SetAutoHide();
        }
    }
}
void MainWindow::OnSysMenuToggled(QAction* act)
{
    if(act)
    {
        int id =act->data().toInt();
        switch (id) {
        case displayWind:
            show();
            showNormal();
            break;
        case exitWind:
            m_closeType = closeType;
            close();
            break;
        default:
            break;
        }

    }

}
void MainWindow::OnSysTrayToggled(QSystemTrayIcon::ActivationReason reason)
{

    if (reason == QSystemTrayIcon::DoubleClick
            || reason == QSystemTrayIcon::Trigger)
        {
              show();
              showNormal();
        }
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    if(m_closeType == minuType)
    {
        hide();
        m_sysTray->showMessage("tip","i'm here", QSystemTrayIcon::NoIcon, 1000);
        e->ignore();
    }
    else
    {

        e->accept();

    }

}
