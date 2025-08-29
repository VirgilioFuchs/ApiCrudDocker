#include "telacadastro.h"
#include "ui_telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>

//Bibliotecas necessárias para o SQLite
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

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

    // Verifica se os campos estão preenchidos
    if(nomeCadastro.isEmpty() || senhaCadastro.isEmpty()){
        QMessageBox::warning(this, "Aviso!", "Coloque todas as informações necessárias em seus respectivos lugares!");
        return;
    }

    // Conexão com o Banco de Dados
    QSqlDatabase bd = QSqlDatabase::database();
    if(!bd.open()){
        qDebug() << "Erro ao conectar ao banco de dados!" << bd.lastError().text();
        QMessageBox::critical(this, "Erro de Banco de Dados", "Não foi possível conectar ao banco de dados!");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nome, senha) VALUES (:nome, :senha)");
    query.bindValue(":nome", nomeCadastro);
    query.bindValue(":senha", senhaCadastro);

    // Verificação se o Usuário existe !
    if (!query.exec()){
        qDebug() << "Erro ao salvar no banco:" << query.lastError().text();
        QMessageBox::critical(this, "Erro de banco de dados", "Ocorreu um erro ao cadastrar os dados!");    // Aviso do BD caso de erro
    } else {
        qDebug() << "Enviando as informações ao banco de dados";
        QMessageBox::information(this, "Sucesso", "Usuário salvo com sucesso!");    // Avisa que o cadastro funcionou
        accept();
    }
}

// Volta para a Tela Inicial
void TelaCadastro::on_btnVoltar_clicked()
{
    reject();
}

