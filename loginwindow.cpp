#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "database.h"
#include <QMessageBox>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    setWindowTitle("视频播放器 - 登录");
    setFixedSize(400, 300);

    // 连接信号槽
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
    connect(ui->btnExit, &QPushButton::clicked, this, &LoginWindow::onExitClicked);

    // 回车键登录
    connect(ui->editPassword, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginClicked()
{
    QString username = ui->editUsername->text().trimmed();
    QString password = ui->editPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入用户名和密码！");
        return;
    }

    Database* db = Database::instance();
    if (db->validateUser(username, password)) {
        db->updateLastLogin(username);
        emit loginSuccess(username);
        accept();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
    }
}

void LoginWindow::onRegisterClicked()
{
    emit registerRequested();
}

void LoginWindow::onExitClicked()
{
    emit exitApplication();
}
