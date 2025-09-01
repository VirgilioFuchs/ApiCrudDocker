#include "telainicial.h"
#include "database.h"
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

    qInfo() << "Iniciando verificação de drivers SQL...";
    qInfo() << "Drivers disponíveis:" << QSqlDatabase::drivers();
    qInfo() << "Verificação concluída.";

    // Tenta conectar ao banco de dados ao iniciar a aplicação
    if (!Database::instance()->conectar()) {
        QMessageBox::critical(nullptr, "Erro Crítico", "Não foi possível conectar ao banco de dados.\nA aplicação será encerrada.");
        return -1; // Encerra com código de erro
    }

    TelaInicial w;
    w.show();
    return a.exec();
}
