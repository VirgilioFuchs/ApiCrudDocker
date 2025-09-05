#include "telacadastro.h"
#include "ui_telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>

//Bibliotecas necessárias para o MySQL
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <qcryptographichash.h>

TelaCadastro::TelaCadastro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TelaCadastro)
{
    ui->setupUi(this);
}

TelaCadastro::~TelaCadastro()
{
    delete ui;
}

void TelaCadastro::on_btnCadastrar_clicked()
{

    QString nomeCadastro = ui->leCadastroUsuario->text();
    QString senhaCadastro = ui->leCadastroSenha->text();

    if(nomeCadastro.isEmpty() && senhaCadastro.isEmpty()){
        QMessageBox::critical(this, "Erro!", "Preencha todos os campos!");
        return;
    }

    // Verifica se já existe usuário com esse nome
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM usuarios WHERE nome = :nome");
    checkQuery.bindValue(":nome", nomeCadastro);
    checkQuery.exec();
    checkQuery.next();

    if (checkQuery.value(0).toInt() > 0) {
        QMessageBox::critical(this, "Erro!", "Este nome de usuario já está cadastrado!");
        return;
    }

    QByteArray senhaHash = QCryptographicHash::hash(senhaCadastro.toUtf8(), QCryptographicHash::Sha256).toHex();

    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nome, senha) VALUES (:nome, :senha)");
    query.bindValue(":nome", nomeCadastro);
    query.bindValue(":senha", QString(senhaHash));

    if(!query.exec()) {
        qDebug() << "Erro ao inserir: " << query.lastError().text();
    } else {
        qDebug() << "Cadastro realizado com sucesso!";
        close();
        ui->leCadastroUsuario->clear();
        ui->leCadastroSenha->clear();
        QMessageBox::information(this, "Sucesso!", "Cadastro realizado com sucesso!");
    }
}

// Volta para a Tela Inicial
void TelaCadastro::on_btnVoltar_clicked()
{
    reject();
}

