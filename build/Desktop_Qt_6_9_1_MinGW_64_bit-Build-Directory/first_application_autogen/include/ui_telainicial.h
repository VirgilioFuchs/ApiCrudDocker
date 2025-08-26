/********************************************************************************
** Form generated from reading UI file 'telainicial.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TELAINICIAL_H
#define UI_TELAINICIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TelaInicial
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *leUsuario;
    QLineEdit *leSenha;
    QSpacerItem *verticalSpacer;
    QPushButton *btnLogin;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnCadastrar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TelaInicial)
    {
        if (TelaInicial->objectName().isEmpty())
            TelaInicial->setObjectName("TelaInicial");
        TelaInicial->resize(471, 600);
        centralwidget = new QWidget(TelaInicial);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(130, 40, 201, 391));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(8, 0, 8, 8);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        leUsuario = new QLineEdit(widget);
        leUsuario->setObjectName("leUsuario");
        leUsuario->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(leUsuario);

        leSenha = new QLineEdit(widget);
        leSenha->setObjectName("leSenha");
        leSenha->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(leSenha);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer);

        btnLogin = new QPushButton(widget);
        btnLogin->setObjectName("btnLogin");

        verticalLayout->addWidget(btnLogin);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer_3);

        btnCadastrar = new QPushButton(widget);
        btnCadastrar->setObjectName("btnCadastrar");

        verticalLayout->addWidget(btnCadastrar);

        TelaInicial->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TelaInicial);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 471, 25));
        TelaInicial->setMenuBar(menubar);
        statusbar = new QStatusBar(TelaInicial);
        statusbar->setObjectName("statusbar");
        TelaInicial->setStatusBar(statusbar);

        retranslateUi(TelaInicial);

        QMetaObject::connectSlotsByName(TelaInicial);
    } // setupUi

    void retranslateUi(QMainWindow *TelaInicial)
    {
        TelaInicial->setWindowTitle(QCoreApplication::translate("TelaInicial", "TelaInicial", nullptr));
        label->setText(QCoreApplication::translate("TelaInicial", "<html><head/><body><h2 style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:700;\">Login</span></h2></body></html>", nullptr));
        leUsuario->setPlaceholderText(QCoreApplication::translate("TelaInicial", "Usuario", nullptr));
        leSenha->setPlaceholderText(QCoreApplication::translate("TelaInicial", "Senha", nullptr));
        btnLogin->setText(QCoreApplication::translate("TelaInicial", "Login", nullptr));
        btnCadastrar->setText(QCoreApplication::translate("TelaInicial", "Cadastro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TelaInicial: public Ui_TelaInicial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TELAINICIAL_H
