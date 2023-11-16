#include "tipdialog.h"
#include "ui_tipdialog.h"

tipDialog::tipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tipDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    m_opacityTimer = new QTimer(this);
    connect(m_opacityTimer, &QTimer::timeout, this , &tipDialog::OnOpacityTimeOut);

}

tipDialog::~tipDialog()
{

    delete ui;
}

 void tipDialog::SetTipText(const QString& text)
 {
    ui->label->setText(text);
 }

void tipDialog::on_closeBtn_clicked()
{
    hide();
}

void tipDialog::showEvent(QShowEvent* e)
{
    QWidget::showEvent(e);

}

void tipDialog::OnOpacityTimeOut()
{
    m_opacity -= 0.010;
    setWindowOpacity(m_opacity);
    if(m_opacity <= 0.00)
    {
        m_opacityTimer->stop();
        hide();
    }
}

 void tipDialog::SetAutoHide()
 {
     m_opacity = 1.0;
     m_opacityTimer->start(100);

 }
