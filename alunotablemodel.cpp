#include "alunotablemodel.h"
#include <QJsonObject>

AlunoTableModel::AlunoTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

void AlunoTableModel::setDataFromJson(const QJsonArray &array) {
    beginResetModel();
    alunos.clear();

    for (const auto &val : array) {
        QJsonObject obj = val.toObject();
        alunos.append({
            obj["idAluno"].toInt(),
            obj["nomeAluno"].toString(),
            obj["dataNascimento"].toString(),
            obj["sexoAluno"].toString(),
            obj["rgAluno"].toString(),
            obj["cpfAluno"].toString(),
            obj["idResponsavel"].toInt(),
            obj["nomeResponsavel"].toString(),
            obj["telefoneResponsavel"].toString()
        });
    }
    endResetModel();
}

int AlunoTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return alunos.size();
}

int AlunoTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 9;
}

QVariant AlunoTableModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || role != Qt::DisplayRole) return QVariant();

    const Aluno &a = alunos[index.row()];

    switch (index.column()) {
    case 0: return a.idAluno;
    case 1: return a.nomeAluno;
    case 2: return a.dataNascimento;
    case 3: return a.sexoAluno;
    case 4: return a.rgAluno;
    case 5: return a.cpfAluno;
    case 6: return a.idResponsavel;
    case 7: return a.nomeResponsavel;
    case 8: return a.telefoneResponsavel;
    }
    return QVariant();
}

QVariant AlunoTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "RM Aluno";
        case 1: return "Nome Aluno";
        case 2: return "Nascimento";
        case 3: return "Sexo Aluno";
        case 4: return "RG Aluno";
        case 5: return "CPF Aluno";
        case 6: return "ID Resp.";
        case 7: return "Nome Resp.";
        case 8: return "Telefone Resp.";
        }
    }
    return QVariant();
}
