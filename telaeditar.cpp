#include "telaeditar.h"
#include "ui_telaeditar.h"
#include <qmessagebox.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

TelaEditar::TelaEditar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TelaEditar)
    , idAluno(-1)
{
    ui->setupUi(this);
}

void TelaEditar::dadosAlunos(int rmAluno,
                             const QString &nomeAluno,
                             const QDate &dataNascimentoAluno,
                             const QString &sexoAluno,
                             const QString &cpfAluno,
                             const QString &rgAluno,
                             const QString &nomeResponsavel,
                             const QString &telefoneResponsavel)
{
    idAluno = rmAluno;

    ui->leRmAluno->setText(QString::number(rmAluno));
    ui->leNomeAluno->setText(nomeAluno);
    ui->deDataNascimento->setDate(dataNascimentoAluno);
    ui->leCPFAluno->setText(cpfAluno);
    ui->leRGAluno->setText(rgAluno);
    ui->leNomeResponsavel->setText(nomeResponsavel);
    ui->leTelefoneResponsavel->setText(telefoneResponsavel);

    if(sexoAluno == "M") {
        ui->rbMasculino->setChecked(true);
    } else if(sexoAluno == "F") {
        ui->rbFeminino->setChecked(true);
    }
}

TelaEditar::~TelaEditar()
{
    delete ui;
}

void TelaEditar::on_btnAlterarDados_clicked()
{
    QString nomeAluno = ui->leNomeAluno->text();
    QDate dataNascimentoAluno = ui->deDataNascimento->date();
    QString nomeResponsavel = ui->leNomeResponsavel->text();
    QString telefoneResponsavel = ui->leTelefoneResponsavel->text();

    QString sexoAluno;
    if(ui->rbMasculino->isChecked()) sexoAluno = "M";
    else if(ui->rbFeminino->isChecked()) sexoAluno = "F";
    else QMessageBox::critical(this, "Erro!", "Erro ao identificar o sexo do aluno!");

    QSqlQuery query1;
    query1.prepare("UPDATE alunos SET "
                   "nomeAluno = :nomeAluno, "
                   "dataNascimento = :dataNascimentoAluno, "
                   "sexoAluno = :sexoAluno "
                   "WHERE id = :rmAluno");

    query1.bindValue(":nomeAluno", nomeAluno);
    query1.bindValue(":dataNascimentoAluno", dataNascimentoAluno);
    query1.bindValue(":sexoAluno", sexoAluno);
    query1.bindValue(":rmAluno", idAluno);

    if (!query1.exec()) {
        QMessageBox::critical(this, "Erro Sql!", "Erro ao atualizar os dados do aluno!" + query1.lastError().text());
        return;
    }

    QSqlQuery query2;
    query2.prepare("UPDATE responsavel SET "
                   "nomeResponsavel = :nomeResponsavel, "
                   "telefoneResponsavel = :telefoneResponsavel "
                   "WHERE id = (SELECT id_Responsavel FROM alunos WHERE id = :rmAluno)");
    query2.bindValue(":nomeResponsavel", nomeResponsavel);
    query2.bindValue(":telefoneResponsavel", telefoneResponsavel);
    query2.bindValue(":rmAluno", idAluno);

    if (!query2.exec()) {
        QMessageBox::critical(this, "Erro Sql!", "Erro ao atualizar os dados do responsável! " + query2.lastError().text());
        return;
    }

    emit dadosInseridos();
    QMessageBox::information(this, "Sucesso!", "Dados atualizados com sucesso!");
    this->close();
}


void TelaEditar::on_btnVoltar_clicked()
{
    this->close();
}

