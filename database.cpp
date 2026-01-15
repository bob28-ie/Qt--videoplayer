#include "database.h"
#include <QSqlRecord>
#include <QSqlDriver>
#include <QFileInfo>

Database* Database::m_instance = nullptr;

Database* Database::instance()
{
    if (!m_instance) {
        m_instance = new Database();
    }
    return m_instance;
}

Database::Database(QObject *parent) : QObject(parent)
{
    QString dataDir = QDir::currentPath() + "/data";
    QDir dir(dataDir);
    if (!dir.exists()) {
        qDebug() << "创建数据目录:" << dataDir;
        if (!dir.mkpath(".")) {
            qDebug() << "创建数据目录失败:" << dataDir;
        }
    }
    dbPath = dataDir + "/videoplayer.db";
    qDebug() << "数据库路径:" << dbPath;
}

Database::~Database()
{
    closeDatabase();
    m_instance = nullptr;
}

bool Database::initDatabase()
{
    if (db.isOpen()) {
        return true;
    }

    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "可用的数据库驱动:";
    for (const QString &driver : drivers) {
        qDebug() << "  - " << driver;
    }

    if (!drivers.contains("QSQLITE")) {
        qDebug() << "错误: 系统不支持SQLite驱动!";
        return false;
    }

    if (QSqlDatabase::contains("videoplayer_connection")) {
        QSqlDatabase::removeDatabase("videoplayer_connection");
    }

    db = QSqlDatabase::addDatabase("QSQLITE", "videoplayer_connection");

    if (!db.isValid()) {
        qDebug() << "数据库对象无效，驱动可能未正确加载";
        return false;
    }

    db.setDatabaseName(dbPath);
    qDebug() << "尝试打开数据库:" << dbPath;

    if (!db.open()) {
        qDebug() << "数据库打开失败:" << db.lastError().text();
        qDebug() << "数据库错误:" << db.lastError().databaseText();
        qDebug() << "驱动错误:" << db.lastError().driverText();
        return false;
    }

    qDebug() << "数据库打开成功";
    return createTables();
}

void Database::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::createTables()
{
    QSqlQuery query(db);

    QString userTable =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username VARCHAR(50) UNIQUE NOT NULL, "
        "password VARCHAR(100) NOT NULL, "
        "email VARCHAR(100), "
        "register_time DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "last_login DATETIME, "
        "is_admin BOOLEAN DEFAULT 0"
        ")";

    if (!query.exec(userTable)) {
        qDebug() << "创建用户表失败:" << query.lastError().text();
        return false;
    }

    QString settingsTable =
        "CREATE TABLE IF NOT EXISTS user_settings ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER, "
        "setting_key VARCHAR(50), "
        "setting_value TEXT, "
        "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE"
        ")";

    if (!query.exec(settingsTable)) {
        qDebug() << "创建设置表失败:" << query.lastError().text();
        return false;
    }

    QString historyTable =
        "CREATE TABLE IF NOT EXISTS play_history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER, "
        "video_path TEXT, "
        "video_name TEXT, "
        "play_time INTEGER, "
        "last_position INTEGER, "
        "play_date DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE"
        ")";

    if (!query.exec(historyTable)) {
        qDebug() << "创建历史表失败:" << query.lastError().text();
        return false;
    }

    query.prepare("SELECT COUNT(*) FROM users WHERE username = 'admin'");
    if (query.exec() && query.next() && query.value(0).toInt() == 0) {
        query.prepare("INSERT INTO users (username, password, email, is_admin) "
                      "VALUES (:username, :password, :email, :is_admin)");
        query.bindValue(":username", "admin");
        query.bindValue(":password", "123456");
        query.bindValue(":email", "admin@example.com");
        query.bindValue(":is_admin", 1);
        if (!query.exec()) {
            qDebug() << "创建默认管理员账户失败:" << query.lastError().text();
        } else {
            qDebug() << "创建默认管理员账户成功";
        }
    }

    return true;
}

bool Database::addUser(const QString &username, const QString &password, const QString &email)
{
    if (!isOpen() && !initDatabase()) {
        qDebug() << "数据库未打开，无法添加用户";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password, email) "
                  "VALUES (:username, :password, :email)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "添加用户失败:" << query.lastError().text();
        return false;
    }
    qDebug() << "添加用户成功:" << username;
    return true;
}

bool Database::userExists(const QString &username)
{
    if (!isOpen() && !initDatabase()) {
        qDebug() << "数据库未打开，无法检查用户是否存在";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool Database::validateUser(const QString &username, const QString &password)
{
    if (!isOpen() && !initDatabase()) {
        qDebug() << "数据库未打开，无法验证用户";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        QString storedPassword = query.value(0).toString();
        return storedPassword == password;
    }
    return false;
}

bool Database::updateLastLogin(const QString &username)
{
    if (!isOpen() && !initDatabase()) {
        qDebug() << "数据库未打开，无法更新登录时间";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET last_login = CURRENT_TIMESTAMP "
                  "WHERE username = :username");
    query.bindValue(":username", username);
    return query.exec();
}

int Database::getUserId(const QString &username)
{
    if (!isOpen() && !initDatabase()) {
        qDebug() << "数据库未打开，无法获取用户ID";
        return -1;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool Database::saveUserSetting(const QString &username, const QString &key, const QString &value)
{
    int userId = getUserId(username);
    if (userId == -1) return false;

    if (!isOpen() && !initDatabase()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM user_settings "
                  "WHERE user_id = :user_id AND setting_key = :key");
    query.bindValue(":user_id", userId);
    query.bindValue(":key", key);

    if (query.exec() && query.next() && query.value(0).toInt() > 0) {
        query.prepare("UPDATE user_settings SET setting_value = :value "
                      "WHERE user_id = :user_id AND setting_key = :key");
    } else {
        query.prepare("INSERT INTO user_settings (user_id, setting_key, setting_value) "
                      "VALUES (:user_id, :key, :value)");
    }

    query.bindValue(":user_id", userId);
    query.bindValue(":key", key);
    query.bindValue(":value", value);

    return query.exec();
}

QString Database::getUserSetting(const QString &username, const QString &key)
{
    if (!isOpen() && !initDatabase()) {
        return QString();
    }

    QSqlQuery query(db);
    query.prepare("SELECT us.setting_value FROM users u "
                  "JOIN user_settings us ON u.id = us.user_id "
                  "WHERE u.username = :username AND us.setting_key = :key");
    query.bindValue(":username", username);
    query.bindValue(":key", key);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return QString();
}

bool Database::savePlayHistory(const QString &username, const QString &videoPath,
                               const QString &videoName, qint64 playTime, qint64 lastPosition)
{
    int userId = getUserId(username);
    if (userId == -1) return false;

    if (!isOpen() && !initDatabase()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO play_history (user_id, video_path, video_name, play_time, last_position) "
                  "VALUES (:user_id, :video_path, :video_name, :play_time, :last_position)");
    query.bindValue(":user_id", userId);
    query.bindValue(":video_path", videoPath);
    query.bindValue(":video_name", videoName);
    query.bindValue(":play_time", playTime);
    query.bindValue(":last_position", lastPosition);

    if (!query.exec()) {
        qDebug() << "保存播放历史失败:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<QMap<QString, QVariant>> Database::getPlayHistory(const QString &username, int limit)
{
    QList<QMap<QString, QVariant>> historyList;
    int userId = getUserId(username);
    if (userId == -1) return historyList;

    if (!isOpen() && !initDatabase()) {
        return historyList;
    }

    QSqlQuery query(db);
    query.prepare("SELECT video_name, video_path, play_time, last_position, play_date "
                  "FROM play_history "
                  "WHERE user_id = :user_id "
                  "ORDER BY play_date DESC "
                  "LIMIT :limit");
    query.bindValue(":user_id", userId);
    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> record;
            record["video_name"] = query.value("video_name");
            record["video_path"] = query.value("video_path");
            record["play_time"] = query.value("play_time");
            record["last_position"] = query.value("last_position");
            record["play_date"] = query.value("play_date");
            historyList.append(record);
        }
    } else {
        qDebug() << "查询播放历史失败:" << query.lastError().text();
    }

    return historyList;
}
