#include "telainicial.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Define a senha do banco de dados através da variável ambiente
    const char* senha = std::getenv("DB_PASSWORD");

    // verificação se foi criada a variável ambiente
    if(!senha){
        qDebug() << "Definir variável ambiente DB_PASSWORD";
        return -1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("logintestebd");
    db.setUserName("root");
    db.setPassword(senha);

    if (!db.open()) {
        qDebug() << "Erro ao conectar ao MySQL:" << db.lastError().text();
        return -1;
    } else {
        qDebug() << "Conexão estabelecida com sucesso!";
    }

    TelaInicial w;
    w.show();
    return a.exec();
}
