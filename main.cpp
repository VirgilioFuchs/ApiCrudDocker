#include "telainicial.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

// Inicia o Banco de Dados ao Logar
bool iniciarBD()
{
    QSqlDatabase bd = QSqlDatabase::addDatabase("QSQLITE");
    bd.setDatabaseName(QDir::currentPath() + "/login.db");

    if(!bd.open()) {
        QMessageBox::critical(nullptr, "Erro de Banco de Dados", "Não foi possível conectar ao banco de dados!");
        qDebug() << "Erro: " << bd.lastError().text();
        return false;
    }

    qDebug() << "Banco de dados conectado com sucesso!";

    QSqlQuery query;

    // Cria a tabela se não existir
    bool sucesso = query.exec("CREATE TABLE IF NOT EXISTS usuarios ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "nome TEXT UNIQUE NOT NULL,"
                              "senha TEXT NOT NULL"
                              ")");

    if (sucesso) {
        qDebug() << "Tabela 'usuarios' criada com sucesso!";
    } else {
        qDebug() << "Erro ao criar a tabela 'usuarios':" << query.lastError().text();
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!iniciarBD()){
        return -1; //Se falhar, o banco de dados não abre
    }

    TelaInicial w;
    w.show();
    return a.exec();
}
