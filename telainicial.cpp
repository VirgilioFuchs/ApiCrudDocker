#include "telainicial.h"
#include "./ui_telainicial.h"
#include "telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>

//Bibliotecas necessárias para o SQLite
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>


TelaInicial::TelaInicial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaInicial)
{
    ui->setupUi(this);
}

TelaInicial::~TelaInicial()
{
    delete ui;
}

void TelaInicial::on_btnLogin_clicked()
{
    QString nome = ui->leUsuario->text();
    QString senha = ui->leSenha->text();

    // Conexão com o Banco de Dados
    QSqlDatabase bd = QSqlDatabase::database();

    if(!bd.open()){
        qDebug() << "Erro ao conectar ao banco de dados!" << bd.lastError().text();
        QMessageBox::critical(this, "Erro de Banco de Dados", "Não foi possível conectar ao banco de dados!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT nome FROM usuarios WHERE nome = :nome AND senha = :senha");
    query.bindValue(":nome", nome);
    query.bindValue(":senha", senha);

    // Verifica as credenciais de login
    if(query.exec() && query.next()) {
        QMessageBox::information(this, "Login realizado!", "Bem vindo ao nosso sistema " + nome + "!");
        close();
    } else {
        QMessageBox::critical(this, "Falha ao logar!", "Usuário ou senha inválidos!");
        ui->leUsuario->clear();
        ui->leSenha->clear();
    }

}

// Abre a Tela Cadastro
void TelaInicial::on_btnCadastrar_clicked()
{
    TelaCadastro telaCadastro(this);
    telaCadastro.exec();
}
