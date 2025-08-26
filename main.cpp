#include "telainicial.h"
#include <QDebug>
#include <QApplication>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelaInicial w;

    qDebug() << "Drivers Disponíveis" << QSqlDatabase::drivers();

    w.show();
    return a.exec();
}
