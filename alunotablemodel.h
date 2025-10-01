#ifndef ALUNOTABLEMODEL_H
#define ALUNOTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QJsonArray>
#include <QString>

struct Aluno {
    int idAluno;
    QString nomeAluno;
    QString dataNascimento;
    QString sexoAluno;
    QString rgAluno;
    QString cpfAluno;
    int idResponsavel;
    QString nomeResponsavel;
    QString telefoneResponsavel;
};


class AlunoTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AlunoTableModel(QObject *parent = nullptr);

    void setDataFromJson(const QJsonArray &array);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const ;

private:
    QList<Aluno> alunos;
};

#endif // ALUNOTABLEMODEL_H
