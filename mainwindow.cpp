#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QNetworkReply>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>
#include <QTime>
#include <QStandardPaths>
#include <QVideoFrame>
#include <QVideoSink>
#include <QClipboard>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , videoWidget(new QVideoWidget(this))
    , audioOutput(new QAudioOutput(this))
    , networkManager(new QNetworkAccessManager(this))
    , isNetworkStream(false)
{
    ui->setupUi(this);

    setWindowTitle("视频播放器");
    resize(1000, 700);

    // 设置优化的样式表
    setStyleSheet(R"(
        QMainWindow {
            background-color: #2b2b2b;
        }
        QPushButton {
            background-color: #4a4a4a;
            color: white;
            border: 1px solid #5a5a5a;
            border-radius: 5px;
            padding: 8px 15px;
            font-weight: bold;
            font-size: 12px;
        }
        QPushButton:hover {
            background-color: #5a5a5a;
            border-color: #6a6a6a;
        }
        QPushButton:pressed {
            background-color: #3a3a3a;
        }
        QPushButton:disabled {
            background-color: #3a3a3a;
            color: #7a7a7a;
        }
        QSlider::groove:horizontal {
            height: 8px;
            background: #4a4a4a;
            border-radius: 4px;
        }
        QSlider::handle:horizontal {
            background: #0078d7;
            width: 18px;
            height: 18px;
            margin: -5px 0;
            border-radius: 9px;
        }
        QLineEdit {
            background-color: #3a3a3a;
            color: white;
            border: 1px solid #5a5a5a;
            border-radius: 4px;
            padding: 5px;
            font-size: 12px;
        }
        QLabel {
            color: white;
            font-size: 12px;
        }
        QMessageBox {
            background-color: #2b2b2b;
        }
        QMessageBox QLabel {
            color: black;
            font-size: 14px;
        }
        QMessageBox QPushButton {
            min-width: 80px;
            min-height: 30px;
            font-size: 12px;
        }
    )");

    // 初始化视频部件
    videoWidget->setStyleSheet("background-color: black; border: 1px solid #5a5a5a;");
    videoWidget->setMinimumSize(640, 400);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);

    // 创建布局并添加视频部件
    if (!ui->videoContainer->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->videoContainer);
        layout->setContentsMargins(0, 0, 0, 0);
        ui->videoContainer->setLayout(layout);
    }
    ui->videoContainer->layout()->addWidget(videoWidget);

    // 配置播放器
    player->setAudioOutput(audioOutput);
    player->setVideoOutput(videoWidget);

    // 连接信号槽
    setupConnections();

    // 设置默认音量
    audioOutput->setVolume(0.5f);
    ui->sliderVolume->setValue(50);
    ui->labelVolume->setText("音量: 50%");

    // 使用国内可访问的阿里云测试视频URL
    ui->txtNetworkUrl->setText("http://player.alicdn.com/video/aliyunmedia.mp4");

    qDebug() << "主窗口初始化完成，播放器状态：" << player->playbackState();
}

MainWindow::~MainWindow()
{
    saveUserSettings();
    delete ui;
}

void MainWindow::setupConnections()
{
    // 本地视频功能
    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::onOpenClicked);
    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::onPlayClicked);
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::onPauseClicked);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::onStopClicked);

    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    connect(ui->sliderPosition, &QSlider::sliderMoved, this, &MainWindow::onPositionChanged);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateDuration);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::onPlaybackStateChanged);
    connect(player, &QMediaPlayer::errorOccurred, this, &MainWindow::handlePlayerError);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);

    // 网络视频功能
    connect(ui->btnPlayNetwork, &QPushButton::clicked, this, &MainWindow::onPlayNetworkClicked);

    // 用户功能
    connect(ui->btnUserProfile, &QPushButton::clicked, this, &MainWindow::onUserProfileClicked);
    connect(ui->btnHistory, &QPushButton::clicked, this, &MainWindow::onHistoryClicked);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
}

void MainWindow::setCurrentUser(const QString &username)
{
    currentUser = username;
    setWindowTitle("视频播放器 - 欢迎，" + username);
    loadUserSettings();
}

void MainWindow::onOpenClicked()
{
    QStringList videoExtensions = {
        "*.mp4", "*.avi", "*.mkv", "*.mov", "*.wmv",
        "*.flv", "*.mpg", "*.mpeg", "*.webm", "*.3gp", "*.m4v"
    };

    QString filter = QString("视频文件 (%1);;所有文件 (*.*)").arg(videoExtensions.join(" "));

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "打开视频文件",
        QStandardPaths::writableLocation(QStandardPaths::MoviesLocation),
        filter
        );

    if (!fileName.isEmpty()) {
        isNetworkStream = false;
        currentVideoPath = fileName;

        // 停止当前播放
        player->stop();

        // 设置新的源
        QUrl fileUrl = QUrl::fromLocalFile(fileName);
        player->setSource(fileUrl);

        QString shortName = QFileInfo(fileName).fileName();
        setWindowTitle("视频播放器 - " + shortName);

        // 显示消息
        ui->lblNetworkStatus->setText("正在播放本地文件");

        // 开始播放
        player->play();

        if (!currentUser.isEmpty()) {
            savePlayHistory(fileName, shortName);
        }
    }
}

void MainWindow::onPlayClicked()
{
    if (player->source().isEmpty()) {
        QMessageBox::warning(this, "警告", "请先打开视频文件");
    } else {
        player->play();
        ui->lblNetworkStatus->setText("正在播放");
    }
}

void MainWindow::onPauseClicked()
{
    player->pause();
    ui->lblNetworkStatus->setText("已暂停");
}

void MainWindow::onStopClicked()
{
    player->stop();
    ui->sliderPosition->setValue(0);
    ui->labelTime->setText("00:00:00");
    ui->lblNetworkStatus->setText("已停止");
}

void MainWindow::onVolumeChanged(int volume)
{
    float vol = volume / 100.0f;
    audioOutput->setVolume(vol);
    ui->labelVolume->setText(QString("音量: %1%").arg(volume));

    if (!currentUser.isEmpty()) {
        Database* db = Database::instance();
        if (db->initDatabase()) {
            db->saveUserSetting(currentUser, "volume", QString::number(volume));
        }
    }
}

void MainWindow::onPositionChanged(int position)
{
    player->setPosition(position);
}

void MainWindow::updatePosition(qint64 position)
{
    if (!ui->sliderPosition->isSliderDown()) {
        ui->sliderPosition->setValue(position);
    }

    ui->labelTime->setText(formatTime(position));

    // 保存播放位置
    if (!currentUser.isEmpty() && !currentVideoPath.isEmpty() && player->duration() > 0) {
        Database* db = Database::instance();
        if (db->initDatabase()) {
            db->saveUserSetting(currentUser, "last_position_" + QFileInfo(currentVideoPath).fileName(),
                                QString::number(position));
        }
    }
}

void MainWindow::updateDuration(qint64 duration)
{
    ui->sliderPosition->setRange(0, duration);
    ui->labelDuration->setText("/ " + formatTime(duration));
}

void MainWindow::onPlayNetworkClicked()
{
    QString urlText = ui->txtNetworkUrl->text().trimmed();

    if (urlText.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入网络视频URL！");
        return;
    }

    QUrl url(urlText);
    if (!url.isValid()) {
        QMessageBox::warning(this, "警告", "URL格式不正确！");
        return;
    }

    ui->lblNetworkStatus->setText("正在连接...");
    ui->btnPlayNetwork->setEnabled(false);

    // 停止当前播放
    player->stop();

    // 设置为网络流
    isNetworkStream = true;
    currentVideoPath = urlText;

    // 设置网络源
    player->setSource(url);

    QString shortName = QFileInfo(urlText).fileName();
    if (shortName.isEmpty()) {
        shortName = url.host();
    }

    setWindowTitle("视频播放器 - 网络视频: " + shortName);

    // 开始播放
    player->play();

    if (!currentUser.isEmpty()) {
        savePlayHistory(urlText, shortName);
    }

    // 重新启用按钮
    QTimer::singleShot(1000, [this]() {
        ui->btnPlayNetwork->setEnabled(true);
    });
}

void MainWindow::onPlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
    QString stateText;
    switch (state) {
    case QMediaPlayer::PlayingState:
        stateText = "正在播放";
        break;
    case QMediaPlayer::PausedState:
        stateText = "已暂停";
        break;
    case QMediaPlayer::StoppedState:
        stateText = "已停止";
        break;
    }

    ui->lblNetworkStatus->setText(stateText);
}

void MainWindow::handlePlayerError(QMediaPlayer::Error error, const QString &errorString)
{
    QString errorMsg;
    switch (error) {
    case QMediaPlayer::NoError:
        return;
    case QMediaPlayer::ResourceError:
        errorMsg = "资源错误";
        break;
    case QMediaPlayer::FormatError:
        errorMsg = "格式错误";
        break;
    case QMediaPlayer::NetworkError:
        errorMsg = "网络错误";
        break;
    case QMediaPlayer::AccessDeniedError:
        errorMsg = "访问被拒绝";
        break;
    default:
        errorMsg = "未知错误";
        break;
    }

    QString fullError = QString("%1: %2").arg(errorMsg).arg(errorString);
    ui->lblNetworkStatus->setText(fullError);
    ui->btnPlayNetwork->setEnabled(true);

    QMessageBox msgBox;
    msgBox.setWindowTitle("播放错误");
    msgBox.setText(fullError);
    msgBox.setInformativeText("可能原因:\n"
                              "1. URL不正确或视频已失效\n"
                              "2. 网络连接问题\n"
                              "3. 视频格式不支持\n"
                              "4. 网站有防盗链机制");

    msgBox.setDetailedText("国内可用的测试URL:\n"
                           "1. http://player.alicdn.com/video/aliyunmedia.mp4 (阿里云公开视频)\n"
                           "2. http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4 (经典测试视频)\n"
                           "3. https://vjs.zencdn.net/v/oceans.mp4 (海洋测试视频)\n\n"
                           "提示：\n"
                           "• 第一个URL在国内通常可以正常访问\n"
                           "• 如果网络视频无法播放，请先测试本地文件功能是否正常");

    msgBox.setStyleSheet("QLabel{color: black; min-width: 400px;} QTextEdit{color: black;}");

    msgBox.exec();
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "媒体状态改变:" << status;

    switch (status) {
    case QMediaPlayer::LoadingMedia:
        ui->lblNetworkStatus->setText("正在加载...");
        break;
    case QMediaPlayer::LoadedMedia:
        ui->lblNetworkStatus->setText("已加载");
        break;
    case QMediaPlayer::BufferingMedia:
        ui->lblNetworkStatus->setText("正在缓冲...");
        break;
    case QMediaPlayer::BufferedMedia:
        ui->lblNetworkStatus->setText("已缓冲");
        break;
    case QMediaPlayer::InvalidMedia:
        ui->lblNetworkStatus->setText("无效媒体");
        break;
    default:
        break;
    }
}

void MainWindow::onLogoutClicked()
{
    saveUserSettings();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "退出登录",
                                  "确定要退出当前账号吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Database::instance()->closeDatabase();
        this->close();
        qApp->quit();
    }
}

void MainWindow::onUserProfileClicked()
{
    if (currentUser.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("警告");
        msgBox.setText("用户未登录");
        msgBox.setStyleSheet("QLabel{color: black;}");
        msgBox.exec();
        return;
    }

    Database* db = Database::instance();
    if (db->initDatabase()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("用户信息");
        msgBox.setText(QString("当前用户: %1\n\n欢迎使用视频播放器！").arg(currentUser));
        msgBox.setStyleSheet("QLabel{color: black; min-width: 300px;}");
        msgBox.exec();
    }
}

void MainWindow::onHistoryClicked()
{
    if (currentUser.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("警告");
        msgBox.setText("用户未登录");
        msgBox.setStyleSheet("QLabel{color: black;}");
        msgBox.exec();
        return;
    }

    Database* db = Database::instance();
    if (db->initDatabase()) {
        QList<QMap<QString, QVariant>> history = db->getPlayHistory(currentUser, 10);

        QString historyText = "最近播放记录:\n\n";

        if (history.isEmpty()) {
            historyText = "暂无播放记录";
        } else {
            int count = 0;
            for (const auto &record : history) {
                QString videoName = record["video_name"].toString();
                QDateTime playDate = record["play_date"].toDateTime();
                qint64 lastPosition = record["last_position"].toLongLong();

                QString timeStr = formatTime(lastPosition);

                historyText += QString("%1. %2\n   时间: %3  位置: %4\n\n")
                                   .arg(++count)
                                   .arg(videoName)
                                   .arg(playDate.toString("yyyy-MM-dd HH:mm:ss"))
                                   .arg(timeStr);
            }
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("播放历史");
        msgBox.setText(historyText);
        msgBox.setStyleSheet("QLabel{color: black; min-width: 500px;}");

        QPushButton *copyButton = new QPushButton("复制文本", &msgBox);
        msgBox.addButton(copyButton, QMessageBox::ActionRole);
        connect(copyButton, &QPushButton::clicked, [historyText]() {
            QApplication::clipboard()->setText(historyText);
            QMessageBox::information(nullptr, "提示", "已复制到剪贴板");
        });

        msgBox.addButton("确定", QMessageBox::AcceptRole);

        msgBox.exec();
    }
}

void MainWindow::savePlayHistory(const QString &videoPath, const QString &videoName)
{
    Database* db = Database::instance();
    if (db->initDatabase()) {
        db->savePlayHistory(currentUser, videoPath, videoName,
                            player->duration(), player->position());
    }
}

void MainWindow::loadUserSettings()
{
    Database* db = Database::instance();
    if (db->initDatabase()) {
        QString volume = db->getUserSetting(currentUser, "volume");
        if (!volume.isEmpty()) {
            int vol = volume.toInt();
            ui->sliderVolume->setValue(vol);
            audioOutput->setVolume(vol / 100.0f);
            ui->labelVolume->setText(QString("音量: %1%").arg(vol));
        }

        QString defaultUrl = db->getUserSetting(currentUser, "default_network_url");
        if (!defaultUrl.isEmpty()) {
            ui->txtNetworkUrl->setText(defaultUrl);
        }
    }
}

void MainWindow::saveUserSettings()
{
    if (currentUser.isEmpty()) return;

    Database* db = Database::instance();
    if (db->initDatabase()) {
        int volume = ui->sliderVolume->value();
        db->saveUserSetting(currentUser, "volume", QString::number(volume));

        QString url = ui->txtNetworkUrl->text().trimmed();
        if (!url.isEmpty()) {
            db->saveUserSetting(currentUser, "default_network_url", url);
        }
    }
}

QString MainWindow::formatTime(qint64 milliseconds)
{
    int totalSeconds = milliseconds / 1000;
    int seconds = totalSeconds % 60;
    int minutes = (totalSeconds / 60) % 60;
    int hours = totalSeconds / 3600;

    if (hours > 0) {
        return QString("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
    } else {
        return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
    }
}
