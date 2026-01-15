#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class RegisterWindow;
}
QT_END_NAMESPACE

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

signals:
    void registerSuccess();
    void backToLogin();

private slots:
    void onRegisterClicked();
    void onBackClicked();

private:
    Ui::RegisterWindow *ui;
    bool validateInput();
};

#endif // REGISTERWINDOW_H
