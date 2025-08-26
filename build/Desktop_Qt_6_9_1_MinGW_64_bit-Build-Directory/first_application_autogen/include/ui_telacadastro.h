/********************************************************************************
** Form generated from reading UI file 'telacadastro.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TELACADASTRO_H
#define UI_TELACADASTRO_H

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

class Ui_TelaCadastro
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLineEdit *leCadastroUsuario;
    QLineEdit *leCadastroSenha;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnCadastrar;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnVoltar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TelaCadastro)
    {
        if (TelaCadastro->objectName().isEmpty())
            TelaCadastro->setObjectName("TelaCadastro");
        TelaCadastro->resize(426, 600);
        centralwidget = new QWidget(TelaCadastro);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(100, 70, 201, 351));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(8, 8, 8, 8);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer);

        leCadastroUsuario = new QLineEdit(widget);
        leCadastroUsuario->setObjectName("leCadastroUsuario");
        leCadastroUsuario->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(leCadastroUsuario);

        leCadastroSenha = new QLineEdit(widget);
        leCadastroSenha->setObjectName("leCadastroSenha");
        leCadastroSenha->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(leCadastroSenha);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        btnCadastrar = new QPushButton(widget);
        btnCadastrar->setObjectName("btnCadastrar");

        verticalLayout->addWidget(btnCadastrar);

        verticalSpacer_3 = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer_3);

        btnVoltar = new QPushButton(widget);
        btnVoltar->setObjectName("btnVoltar");

        verticalLayout->addWidget(btnVoltar);

        TelaCadastro->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TelaCadastro);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 426, 25));
        TelaCadastro->setMenuBar(menubar);
        statusbar = new QStatusBar(TelaCadastro);
        statusbar->setObjectName("statusbar");
        TelaCadastro->setStatusBar(statusbar);

        retranslateUi(TelaCadastro);

        QMetaObject::connectSlotsByName(TelaCadastro);
    } // setupUi

    void retranslateUi(QMainWindow *TelaCadastro)
    {
        TelaCadastro->setWindowTitle(QCoreApplication::translate("TelaCadastro", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("TelaCadastro", "<h2>Cadastrar</h2>", nullptr));
        leCadastroUsuario->setPlaceholderText(QCoreApplication::translate("TelaCadastro", "Nome de usu\303\241rio", nullptr));
        leCadastroSenha->setPlaceholderText(QCoreApplication::translate("TelaCadastro", "Senha de usu\303\241rio", nullptr));
        btnCadastrar->setText(QCoreApplication::translate("TelaCadastro", "Cadastrar", nullptr));
        btnVoltar->setText(QCoreApplication::translate("TelaCadastro", "Voltar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TelaCadastro: public Ui_TelaCadastro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TELACADASTRO_H
