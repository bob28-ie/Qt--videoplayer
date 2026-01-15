/********************************************************************************
** Form generated from reading UI file 'registerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *editUsername;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *editPassword;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *editConfirmPassword;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *editEmail;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnRegister;
    QPushButton *btnBack;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(450, 350);
        centralwidget = new QWidget(RegisterWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(label);

        editUsername = new QLineEdit(centralwidget);
        editUsername->setObjectName("editUsername");
        editUsername->setMinimumSize(QSize(250, 30));

        horizontalLayout->addWidget(editUsername);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(80, 30));

        horizontalLayout_2->addWidget(label_2);

        editPassword = new QLineEdit(centralwidget);
        editPassword->setObjectName("editPassword");
        editPassword->setEchoMode(QLineEdit::Password);
        editPassword->setMinimumSize(QSize(250, 30));

        horizontalLayout_2->addWidget(editPassword);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(label_3);

        editConfirmPassword = new QLineEdit(centralwidget);
        editConfirmPassword->setObjectName("editConfirmPassword");
        editConfirmPassword->setEchoMode(QLineEdit::Password);
        editConfirmPassword->setMinimumSize(QSize(250, 30));

        horizontalLayout_3->addWidget(editConfirmPassword);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(80, 30));

        horizontalLayout_4->addWidget(label_4);

        editEmail = new QLineEdit(centralwidget);
        editEmail->setObjectName("editEmail");
        editEmail->setMinimumSize(QSize(250, 30));

        horizontalLayout_4->addWidget(editEmail);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btnRegister = new QPushButton(centralwidget);
        btnRegister->setObjectName("btnRegister");
        btnRegister->setMinimumSize(QSize(100, 35));

        horizontalLayout_5->addWidget(btnRegister);

        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setMinimumSize(QSize(100, 35));

        horizontalLayout_5->addWidget(btnBack);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QDialog *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "\350\247\206\351\242\221\346\222\255\346\224\276\345\231\250 - \346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("RegisterWindow", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterWindow", "\345\257\206\347\240\201:", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterWindow", "\347\241\256\350\256\244\345\257\206\347\240\201:", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterWindow", "\351\202\256\347\256\261:", nullptr));
        btnRegister->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214", nullptr));
        btnBack->setText(QCoreApplication::translate("RegisterWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
