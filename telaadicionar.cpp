#include "telaadicionar.h"
#include "ui_telaadicionar.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>

//Blibliotecas para MySQL
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

TelaAdicionar::TelaAdicionar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TelaAdicionar)
    , respostaSexo(-1)      // Inicializa sem nenhuma resposta
{
    ui->setupUi(this);

    // Grupo com os radio buttons adicionado do campo sexo
    grupoSexoAluno = new QButtonGroup(this);
    grupoSexoAluno->addButton(ui->rbMasculino, 1);
    grupoSexoAluno->addButton(ui->rbFeminino, 2);

    // Atualiza o valor caso o radio button seja alterado
    connect(grupoSexoAluno, SIGNAL(idClicked(int)),
            this, SLOT(respostaSelecionadaSexo(int)));
}

TelaAdicionar::~TelaAdicionar()
{
    delete ui;
}

void TelaAdicionar::on_btnAdicionarFoto_clicked()
{

}


void TelaAdicionar::on_btnCadastrar_clicked()
{
    QString nomeAluno = ui->leNomeAluno->text();
    QDate dataNascimento = ui->dateNascimento->date();
    QString dataFormatada = dataNascimento.toString("yyyy-MM--dd");
    QString rgAluno = ui->leRG->text();
    QString cpfAluno = ui->leCPF->text();
    QString nomeResponsavel = ui->leNomeResponsavel->text();
    QString telefoneResponsavel = ui->leContato->text();

    if (nomeAluno.isEmpty() || rgAluno.isEmpty()
        || cpfAluno.isEmpty() || nomeResponsavel.isEmpty() || telefoneResponsavel.isEmpty()){
        QMessageBox::critical(this, "Erro!", "Preencha todos os campos!");
        return;
    }

    QAbstractButton *selecionado = grupoSexoAluno->checkedButton();

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM alunos WHERE rgAluno = :rgAluno AND cpfAluno = :cpfAluno");
    checkQuery.bindValue(":rgAluno", rgAluno);
    checkQuery.bindValue(":cpfAluno", cpfAluno);
    checkQuery.exec();
    checkQuery.next();

    if (checkQuery.next()){
        if (checkQuery.value(0).toInt() > 0){
            QMessageBox::critical(this, "Erro!", "CPF e RG inválido");
            return;
        }
    }

    // Armazena a resposta do radioButtton
    QString sexoAluno;

    switch (respostaSexo) {
    case 1:
        sexoAluno = "M";
        break;
    case 2:
        sexoAluno = "F";
        break;
    default:
        QMessageBox::critical(this, "Erro!", "Selecione se o seu filho(a) e sexo masculino ou feminino!");
        return;
        break;
    }

    QSqlQuery query2;
    query2.prepare("INSERT INTO responsavel (nomeResponsavel, telefoneResponsavel)"
                   "VALUES (:nomeResponsavel, :telefoneResponsavel)");
    query2.bindValue(":nomeResponsavel", nomeResponsavel);
    query2.bindValue(":telefoneResponsavel", telefoneResponsavel);

    if(!query2.exec()){
        QMessageBox::critical(this, "Erro!", "Erro ao cadastrar o responsável no sistema!");
        qDebug() << "Erro ao inserir o responsável" << query2.lastError().text();
        return;
    }

    int idResponsavel = query2.lastInsertId().toInt();

    QSqlQuery query1;
    query1.prepare("INSERT INTO alunos(nomeAluno, dataNascimento, sexoAluno, rgAluno, cpfAluno, id_Responsavel) "
                  "VALUES (:nomeAluno, :dataNascimento, :sexoAluno, :rgAluno, :cpfAluno, :id_Responsavel)");
    query1.bindValue(":nomeAluno", nomeAluno);
    query1.bindValue(":dataNascimento", dataNascimento);
    query1.bindValue(":sexoAluno", sexoAluno);
    query1.bindValue(":rgAluno", rgAluno);
    query1.bindValue(":cpfAluno", cpfAluno);
    query1.bindValue(":id_Responsavel", idResponsavel);

    if(!query1.exec()){
        QMessageBox::critical(this, "Erro!", "Erro ao cadastrar o aluno no sistema!");
        qDebug() << "Erro ao inserir dados da tabela" << query1.lastError().text();
        return;
    }

    QMessageBox::information(this, "Sucesso!", "Dados do aluno cadastrado com sucesso!");
    close();

}

void TelaAdicionar::respostaSelecionadaSexo(int id)
{
    respostaSexo = id;
    QAbstractButton *button = grupoSexoAluno->button(id);
    qDebug() << "Foi selecionado o botão:" << button->text();
}

void TelaAdicionar::on_btnFechar_clicked()
{
    close();
}

