#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "database.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    setWindowTitle("视频播放器 - 注册");
    setFixedSize(450, 350);

    // 连接信号槽
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterWindow::onRegisterClicked);
    connect(ui->btnBack, &QPushButton::clicked, this, &RegisterWindow::onBackClicked);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

bool RegisterWindow::validateInput()
{
    QString username = ui->editUsername->text().trimmed();
    QString password = ui->editPassword->text();
    QString confirmPassword = ui->editConfirmPassword->text();
    QString email = ui->editEmail->text().trimmed();

    if (username.length() < 3 || username.length() > 20) {
        QMessageBox::warning(this, "警告", "用户名长度应在3-20个字符之间！");
        return false;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "警告", "密码长度至少6个字符！");
        return false;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "警告", "两次输入的密码不一致！");
        return false;
    }

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!email.isEmpty() && !emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "警告", "邮箱格式不正确！");
        return false;
    }

    return true;
}

void RegisterWindow::onRegisterClicked()
{
    if (!validateInput()) {
        return;
    }

    QString username = ui->editUsername->text().trimmed();
    QString password = ui->editPassword->text();
    QString email = ui->editEmail->text().trimmed();

    Database* db = Database::instance();

    if (db->userExists(username)) {
        QMessageBox::warning(this, "警告", "用户名已存在！");
        return;
    }

    if (db->addUser(username, password, email)) {
        QMessageBox::information(this, "成功", "注册成功！");
        emit registerSuccess();
        accept();
    } else {
        QMessageBox::warning(this, "错误", "注册失败，请重试！");
    }
}

void RegisterWindow::onBackClicked()
{
    emit backToLogin();
    reject();
}
