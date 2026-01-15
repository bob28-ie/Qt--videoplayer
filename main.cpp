#include "loginwindow.h"
#include "mainwindow.h"
#include "registerwindow.h"
#include "database.h"
#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("视频播放器");
    a.setOrganizationName("MyCompany");
    a.setApplicationVersion("1.0.0");

    // 检查数据库驱动
    qDebug() << "=== 检查数据库驱动 ===";
    QStringList drivers = QSqlDatabase::drivers();

    if (drivers.isEmpty()) {
        qDebug() << "未找到任何数据库驱动!";
    } else {
        qDebug() << "可用的数据库驱动:";
        for (const QString &driver : drivers) {
            qDebug() << "  - " << driver;
        }
    }

    // 检查SQLite驱动
    if (!drivers.contains("QSQLITE")) {
        QString errorMsg = "未找到SQLite数据库驱动！\n\n"
                           "请执行以下步骤修复：\n"
                           "1. 确保Qt安装时选择了SQL模块\n"
                           "2. 检查sqldrivers目录：\n"
                           "   Windows: Qt安装目录/plugins/sqldrivers/\n"
                           "   Linux: /usr/lib/qt/plugins/sqldrivers/\n"
                           "   macOS: Qt安装目录/plugins/sqldrivers/\n\n"
                           "当前程序目录：" + QDir::currentPath();

        qDebug() << errorMsg;

        // 检查当前目录是否有sqldrivers文件夹
        QDir pluginsDir(QDir::currentPath() + "/sqldrivers");
        if (pluginsDir.exists()) {
            qDebug() << "找到本地sqldrivers目录:" << pluginsDir.absolutePath();
        }

        QMessageBox::critical(nullptr, "数据库驱动错误", errorMsg);
        return -1;
    } else {
        qDebug() << "SQLite驱动可用";
    }

    // 防止多开
    QSharedMemory sharedMemory("VideoPlayerApp");
    if (!sharedMemory.create(1)) {
        QMessageBox::warning(nullptr, "警告", "程序已经在运行！");
        return 0;
    }

    // 初始化数据库单例
    qDebug() << "初始化数据库单例...";
    Database* db = Database::instance();
    if (!db->initDatabase()) {
        QMessageBox::critical(nullptr, "数据库错误",
                              "数据库初始化失败！\n"
                              "程序将继续运行，但某些功能可能不可用。");
        // 不退出程序，继续运行
    } else {
        qDebug() << "数据库初始化成功";
    }

    bool shouldExit = false;
    int result = 0;

    while (!shouldExit) {
        LoginWindow loginWindow;

        // 连接登录成功信号
        QObject::connect(&loginWindow, &LoginWindow::loginSuccess,
                         [&](const QString &username) {
                             MainWindow *mainWindow = new MainWindow();
                             mainWindow->setCurrentUser(username);
                             mainWindow->show();
                             loginWindow.accept();
                         });

        // 连接注册请求信号
        QObject::connect(&loginWindow, &LoginWindow::registerRequested, [&]() {
            RegisterWindow regWindow(&loginWindow);
            regWindow.setModal(true);

            QObject::connect(&regWindow, &RegisterWindow::registerSuccess, [&]() {
                regWindow.accept();
            });

            QObject::connect(&regWindow, &RegisterWindow::backToLogin, [&]() {
                regWindow.reject();
            });

            if (regWindow.exec() == QDialog::Accepted) {
                QMessageBox::information(&loginWindow, "提示", "注册成功，请登录！");
            }
        });

        // 连接退出信号
        QObject::connect(&loginWindow, &LoginWindow::exitApplication, [&]() {
            loginWindow.reject();
            shouldExit = true;
        });

        if (loginWindow.exec() == QDialog::Accepted) {
            // 主窗口创建后，进入事件循环
            result = QApplication::exec();
            shouldExit = true;
        } else {
            shouldExit = true;
        }
    }

    return result;
}
