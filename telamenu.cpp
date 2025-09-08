#include "telamenu.h"
#include "ui_telamenu.h"
#include "telaadicionar.h"
#include "telaeditar.h"
#include <QDate>
#include <QMessageBox>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QSqlError>

TelaMenu::TelaMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaMenu)
{
    ui->setupUi(this);

    QSqlQueryModel *exibirDadosAlunos = new QSqlQueryModel(this);
    exibirDadosAlunos->setQuery(
        "SELECT a.id, a.nomeAluno, a.dataNascimento, a.sexoAluno, a.cpfAluno, a.rgAluno, "
        "r.id AS id, r.nomeResponsavel, r.telefoneResponsavel "
        "FROM alunos a "
        "JOIN responsavel r ON a.id_Responsavel = r.id"
        );

    if (exibirDadosAlunos->lastError().isValid()) {
        qDebug() << "Erro SQL:" << exibirDadosAlunos->lastError().text();
    }

    ui->tableDados->setModel(exibirDadosAlunos);
    ui->tableDados->resizeColumnsToContents();
    ui->tableDados->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

TelaMenu::~TelaMenu()
{
    delete ui;
}

void TelaMenu::on_btnPesquisar_clicked()
{

}


void TelaMenu::on_btnAdicionar_clicked()
{
    TelaAdicionar *telaAdicionar = new TelaAdicionar(this);
    telaAdicionar->setAttribute(Qt::WA_DeleteOnClose);
    telaAdicionar->setWindowFlags(Qt::Window);
    telaAdicionar->setWindowTitle("Cadastro de Aluno");
    telaAdicionar->resize(836,522);
    telaAdicionar->show();
}


void TelaMenu::on_btnEditar_clicked()
{
    QModelIndex index = ui->tableDados->currentIndex();
    if(!index.isValid()){
        QMessageBox::warning(this, "Aviso", "Selecione um registro primeiro");
        return;
    }

    int linhaSelecionada = index.row();

    int rmAluno = ui->tableDados->model()->index(linhaSelecionada, 0).data().toInt();
    QString nomeAluno = ui->tableDados->model()->index(linhaSelecionada, 1).data().toString();
    QVariant dataNascVar = ui->tableDados->model()->index(linhaSelecionada, 2).data();
    QDate dataNascimentoAluno = dataNascVar.toDate();
    QString sexoAluno = ui->tableDados->model()->index(linhaSelecionada, 3).data().toString();
    QString rgAluno = ui->tableDados->model()->index(linhaSelecionada, 4).data().toString();
    QString cpfAluno = ui->tableDados->model()->index(linhaSelecionada, 5).data().toString();
    QString nomeResponsavel = ui->tableDados->model()->index(linhaSelecionada, 7).data().toString();
    QString telefoneResponsavel = ui->tableDados->model()->index(linhaSelecionada, 8).data().toString();

    TelaEditar *editar = new TelaEditar(this);
    editar->setAttribute(Qt::WA_DeleteOnClose);
    editar->dadosAlunos(rmAluno, nomeAluno, dataNascimentoAluno, sexoAluno, rgAluno, cpfAluno, nomeResponsavel,telefoneResponsavel);
    editar->show();
}


void TelaMenu::on_btnExcluir_clicked()
{

}


void TelaMenu::on_btnAtualizar_clicked()
{
    QSqlQueryModel *exibirDadosAlunos = new QSqlQueryModel(this);
    exibirDadosAlunos->setQuery(
        "SELECT a.id, a.nomeAluno, a.dataNascimento, a.sexoAluno, a.cpfAluno, a.rgAluno, "
        "r.id AS id, r.nomeResponsavel, r.telefoneResponsavel "
        "FROM alunos a "
        "JOIN responsavel r ON a.id_Responsavel = r.id"
        );

    if (exibirDadosAlunos->lastError().isValid()) {
        qDebug() << "Erro SQL:" << exibirDadosAlunos->lastError().text();
    }

    ui->tableDados->setModel(exibirDadosAlunos);
    ui->tableDados->resizeColumnsToContents();
    ui->tableDados->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qDebug() << "Dados Atualizados na tabela";
    ui->lApresentar->setText("Dados Atualizados na tabela!");
}

