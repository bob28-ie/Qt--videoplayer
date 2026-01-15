#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QVariant>
#include <QMap>

class Database : public QObject
{
    Q_OBJECT

public:
    // 单例模式的获取实例方法
    static Database* instance();

    // 禁止拷贝和赋值
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    bool initDatabase();
    bool createTables();

    // 用户管理
    bool addUser(const QString &username, const QString &password, const QString &email);
    bool userExists(const QString &username);
    bool validateUser(const QString &username, const QString &password);
    bool updateLastLogin(const QString &username);
    int getUserId(const QString &username);

    // 用户设置
    bool saveUserSetting(const QString &username, const QString &key, const QString &value);
    QString getUserSetting(const QString &username, const QString &key);

    // 播放历史
    bool savePlayHistory(const QString &username, const QString &videoPath,
                         const QString &videoName, qint64 playTime, qint64 lastPosition);
    QList<QMap<QString, QVariant>> getPlayHistory(const QString &username, int limit = 10);

    QSqlDatabase getDatabase() const { return db; }
    bool isOpen() const { return db.isOpen(); }

    // 手动关闭数据库连接
    void closeDatabase();

    // 析构函数改为public
    ~Database();

private:
    explicit Database(QObject *parent = nullptr);

    static Database* m_instance;
    QSqlDatabase db;
    QString dbPath;
};

#endif // DATABASE_H
