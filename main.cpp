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

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("logintestebd");
    db.setUserName("root");
    db.setPassword("Anglopp.g12");

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
