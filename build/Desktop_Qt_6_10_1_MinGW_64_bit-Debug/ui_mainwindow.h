/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainVerticalLayout;
    QWidget *videoAndProgressContainer;
    QVBoxLayout *videoProgressLayout;
    QWidget *videoContainer;
    QVBoxLayout *videoContainerLayout;
    QHBoxLayout *progressLayout;
    QLabel *labelTime;
    QSlider *sliderPosition;
    QLabel *labelDuration;
    QHBoxLayout *mainControlsLayout;
    QPushButton *btnOpen;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnUserProfile;
    QPushButton *btnHistory;
    QPushButton *btnLogout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *networkControlsLayout;
    QLineEdit *txtNetworkUrl;
    QPushButton *btnPlayNetwork;
    QLabel *lblNetworkStatus;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *volumeControlsLayout;
    QLabel *labelVolume;
    QSlider *sliderVolume;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainVerticalLayout = new QVBoxLayout(centralwidget);
        mainVerticalLayout->setObjectName("mainVerticalLayout");
        videoAndProgressContainer = new QWidget(centralwidget);
        videoAndProgressContainer->setObjectName("videoAndProgressContainer");
        videoProgressLayout = new QVBoxLayout(videoAndProgressContainer);
        videoProgressLayout->setObjectName("videoProgressLayout");
        videoContainer = new QWidget(videoAndProgressContainer);
        videoContainer->setObjectName("videoContainer");
        videoContainer->setMinimumSize(QSize(640, 400));
        videoContainerLayout = new QVBoxLayout(videoContainer);
        videoContainerLayout->setObjectName("videoContainerLayout");

        videoProgressLayout->addWidget(videoContainer);

        progressLayout = new QHBoxLayout();
        progressLayout->setObjectName("progressLayout");
        labelTime = new QLabel(videoAndProgressContainer);
        labelTime->setObjectName("labelTime");
        labelTime->setMinimumSize(QSize(70, 25));
        labelTime->setAlignment(Qt::AlignCenter);

        progressLayout->addWidget(labelTime);

        sliderPosition = new QSlider(videoAndProgressContainer);
        sliderPosition->setObjectName("sliderPosition");
        sliderPosition->setOrientation(Qt::Horizontal);
        sliderPosition->setMinimumSize(QSize(200, 20));

        progressLayout->addWidget(sliderPosition);

        labelDuration = new QLabel(videoAndProgressContainer);
        labelDuration->setObjectName("labelDuration");
        labelDuration->setMinimumSize(QSize(80, 25));

        progressLayout->addWidget(labelDuration);


        videoProgressLayout->addLayout(progressLayout);


        mainVerticalLayout->addWidget(videoAndProgressContainer);

        mainControlsLayout = new QHBoxLayout();
        mainControlsLayout->setObjectName("mainControlsLayout");
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName("btnOpen");
        btnOpen->setMinimumSize(QSize(80, 35));

        mainControlsLayout->addWidget(btnOpen);

        btnPlay = new QPushButton(centralwidget);
        btnPlay->setObjectName("btnPlay");
        btnPlay->setMinimumSize(QSize(80, 35));

        mainControlsLayout->addWidget(btnPlay);

        btnPause = new QPushButton(centralwidget);
        btnPause->setObjectName("btnPause");
        btnPause->setMinimumSize(QSize(80, 35));

        mainControlsLayout->addWidget(btnPause);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");
        btnStop->setMinimumSize(QSize(80, 35));

        mainControlsLayout->addWidget(btnStop);

        btnUserProfile = new QPushButton(centralwidget);
        btnUserProfile->setObjectName("btnUserProfile");
        btnUserProfile->setMinimumSize(QSize(90, 35));

        mainControlsLayout->addWidget(btnUserProfile);

        btnHistory = new QPushButton(centralwidget);
        btnHistory->setObjectName("btnHistory");
        btnHistory->setMinimumSize(QSize(90, 35));

        mainControlsLayout->addWidget(btnHistory);

        btnLogout = new QPushButton(centralwidget);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setMinimumSize(QSize(90, 35));

        mainControlsLayout->addWidget(btnLogout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        mainControlsLayout->addItem(horizontalSpacer);


        mainVerticalLayout->addLayout(mainControlsLayout);

        networkControlsLayout = new QHBoxLayout();
        networkControlsLayout->setObjectName("networkControlsLayout");
        txtNetworkUrl = new QLineEdit(centralwidget);
        txtNetworkUrl->setObjectName("txtNetworkUrl");
        txtNetworkUrl->setMinimumSize(QSize(400, 35));

        networkControlsLayout->addWidget(txtNetworkUrl);

        btnPlayNetwork = new QPushButton(centralwidget);
        btnPlayNetwork->setObjectName("btnPlayNetwork");
        btnPlayNetwork->setMinimumSize(QSize(120, 35));

        networkControlsLayout->addWidget(btnPlayNetwork);

        lblNetworkStatus = new QLabel(centralwidget);
        lblNetworkStatus->setObjectName("lblNetworkStatus");
        lblNetworkStatus->setMinimumSize(QSize(100, 25));

        networkControlsLayout->addWidget(lblNetworkStatus);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        networkControlsLayout->addItem(horizontalSpacer_2);


        mainVerticalLayout->addLayout(networkControlsLayout);

        volumeControlsLayout = new QHBoxLayout();
        volumeControlsLayout->setObjectName("volumeControlsLayout");
        labelVolume = new QLabel(centralwidget);
        labelVolume->setObjectName("labelVolume");
        labelVolume->setMinimumSize(QSize(70, 25));

        volumeControlsLayout->addWidget(labelVolume);

        sliderVolume = new QSlider(centralwidget);
        sliderVolume->setObjectName("sliderVolume");
        sliderVolume->setMinimum(0);
        sliderVolume->setMaximum(100);
        sliderVolume->setValue(50);
        sliderVolume->setOrientation(Qt::Horizontal);
        sliderVolume->setMinimumSize(QSize(200, 20));

        volumeControlsLayout->addWidget(sliderVolume);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        volumeControlsLayout->addItem(horizontalSpacer_3);


        mainVerticalLayout->addLayout(volumeControlsLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\247\206\351\242\221\346\222\255\346\224\276\345\231\250", nullptr));
        labelTime->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        labelDuration->setText(QCoreApplication::translate("MainWindow", "/ 00:00:00", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        btnPlay->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
        btnPause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        btnUserProfile->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        btnHistory->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\345\216\206\345\217\262", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        txtNetworkUrl->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\347\275\221\347\273\234\350\247\206\351\242\221URL (http://, rtsp://, rtmp://)", nullptr));
        btnPlayNetwork->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\347\275\221\347\273\234\350\247\206\351\242\221", nullptr));
        lblNetworkStatus->setText(QCoreApplication::translate("MainWindow", "\345\260\261\347\273\252", nullptr));
        labelVolume->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217: 50%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
