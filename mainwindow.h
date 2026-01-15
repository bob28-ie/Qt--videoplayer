#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QNetworkAccessManager>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCurrentUser(const QString &username);

private slots:
    // 本地视频功能
    void onOpenClicked();
    void onPlayClicked();
    void onPauseClicked();
    void onStopClicked();
    void onVolumeChanged(int volume);
    void onPositionChanged(int position);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void handlePlayerError(QMediaPlayer::Error error, const QString &errorString);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    // 网络视频功能
    void onPlayNetworkClicked();

    // 用户功能
    void onLogoutClicked();
    void onUserProfileClicked();
    void onHistoryClicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;

    QNetworkAccessManager *networkManager;

    QString currentUser;
    QString currentVideoPath;
    bool isNetworkStream;

    void setupConnections();
    void savePlayHistory(const QString &videoPath, const QString &videoName);
    void loadUserSettings();
    void saveUserSettings();
    QString formatTime(qint64 milliseconds);
};

#endif // MAINWINDOW_H
