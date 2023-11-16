#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPointer>

namespace Ui {
class tipDialog;
}

class tipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tipDialog(QWidget *parent = nullptr);
    ~tipDialog();

    void SetTipText(const QString&);
    void SetAutoHide();

private:
    Ui::tipDialog *ui;
    bool m_autoHide = true;
    QPointer<QTimer> m_opacityTimer;
    double m_opacity = 0.0;
private slots:
    void on_closeBtn_clicked();
    void OnOpacityTimeOut();
protected:
    void showEvent(QShowEvent* e) override;
};

#endif // TIPDIALOG_H
