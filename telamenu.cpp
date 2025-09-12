#include "telamenu.h"
#include "ui_telamenu.h"
#include "telaadicionar.h"
#include "telaeditar.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>

TelaMenu::TelaMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaMenu)
    , telaLogin(nullptr)
{
    ui->setupUi(this);

    connect(ui->actionLogout, &QAction::triggered,
            this, &TelaMenu::fazerLogout);

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

    exibirDadosAlunos->setHeaderData(0, Qt::Horizontal, "RM");
    exibirDadosAlunos->setHeaderData(1, Qt::Horizontal, "Aluno");
    exibirDadosAlunos->setHeaderData(2, Qt::Horizontal, "Nascimento");
    exibirDadosAlunos->setHeaderData(3, Qt::Horizontal, "Sexo");
    exibirDadosAlunos->setHeaderData(4, Qt::Horizontal, "CPF");
    exibirDadosAlunos->setHeaderData(5, Qt::Horizontal, "RG");
    exibirDadosAlunos->setHeaderData(6, Qt::Horizontal, "Cod Resp.");
    exibirDadosAlunos->setHeaderData(7, Qt::Horizontal, "Responsável");
    exibirDadosAlunos->setHeaderData(8, Qt::Horizontal, "Telefone Resp.");

    ui->tableDados->setModel(exibirDadosAlunos);
    ui->tableDados->resizeColumnsToContents();
    ui->tableDados->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->btnPesquisar->installEventFilter(this);
    ui->btnAdicionar->installEventFilter(this);
    ui->btnEditar->installEventFilter(this);
    ui->btnExcluir->installEventFilter(this);
    ui->btnAtualizar->installEventFilter(this);
}

TelaMenu::~TelaMenu()
{
    delete ui;
}

void TelaMenu::on_btnPesquisar_clicked()
{
    QString pesquisa = ui->leBarraPesquisa->text();

    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString sql = QString(
        "SELECT a.id, a.nomeAluno, a.dataNascimento, a.sexoAluno, "
        "a.rgAluno, a.cpfAluno, r.id, r.nomeResponsavel, r.telefoneResponsavel "
        "FROM alunos a "
        "JOIN responsavel r ON a.id_Responsavel = r.id "
        "WHERE a.nomeAluno LIKE '%%1%' OR r.nomeResponsavel LIKE '%%1%' OR a.cpfAluno LIKE '%%1%' OR a.rgAluno LIKE '%%1%'"
                      ).arg(pesquisa);

    model->setQuery(sql);

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Erro!", "Erro ao Pesquisar!");
        qDebug() << "ERRO: " << model->lastError().text();
        return;
    }

    if (pesquisa.isEmpty()) {
        sql = "SELECT a.id, a.nomeAluno, a.dataNascimento, a.sexoAluno, "
              "a.rgAluno, a.cpfAluno, r.id, r.nomeResponsavel, r.telefoneResponsavel "
              "FROM alunos a "
              "JOIN responsavel r ON a.id_Responsavel = r.id ";
    }

    model->setHeaderData(0, Qt::Horizontal, "RM");
    model->setHeaderData(1, Qt::Horizontal, "Aluno");
    model->setHeaderData(2, Qt::Horizontal, "Nascimento");
    model->setHeaderData(3, Qt::Horizontal, "Sexo");
    model->setHeaderData(4, Qt::Horizontal, "CPF");
    model->setHeaderData(5, Qt::Horizontal, "RG");
    model->setHeaderData(6, Qt::Horizontal, "Cod Resp.");
    model->setHeaderData(7, Qt::Horizontal, "Responsável");
    model->setHeaderData(8, Qt::Horizontal, "Telefone Resp.");

    ui->tableDados->setModel(model);
    ui->tableDados->resizeColumnsToContents();
    ui->tableDados->horizontalHeader()->setStretchLastSection(true);

    ui->leBarraPesquisa->clear();
}


void TelaMenu::on_btnAdicionar_clicked()
{
    TelaAdicionar *telaAdicionar = new TelaAdicionar(this);
    telaAdicionar->setAttribute(Qt::WA_DeleteOnClose);
    telaAdicionar->setWindowFlags(Qt::Window);
    telaAdicionar->setWindowTitle("Cadastro de Aluno");
    telaAdicionar->resize(836,522);
    connect(telaAdicionar, &TelaAdicionar::dadosInseridos,
            this, &TelaMenu::atualizarTabela);
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
    QString cpfAluno = ui->tableDados->model()->index(linhaSelecionada, 4).data().toString();
    QString rgAluno = ui->tableDados->model()->index(linhaSelecionada, 5).data().toString();
    QString nomeResponsavel = ui->tableDados->model()->index(linhaSelecionada, 7).data().toString();
    QString telefoneResponsavel = ui->tableDados->model()->index(linhaSelecionada, 8).data().toString();

    // Dessa maneira evita o fundo da TelaEditar sobrepor a MainWindow e ficar sem fundo!
    TelaEditar *editar = new TelaEditar(this);
    editar->setAttribute(Qt::WA_DeleteOnClose);
    editar->dadosAlunos(rmAluno, nomeAluno, dataNascimentoAluno, sexoAluno, cpfAluno, rgAluno, nomeResponsavel,telefoneResponsavel);
    editar->setWindowFlags(Qt::Window);
    editar->setWindowTitle("Editar dados do Aluno");
    editar->resize(926,643);
    connect(editar, &TelaEditar::dadosInseridos,
            this, &TelaMenu::atualizarTabela);
    editar->show();
}

void TelaMenu::on_btnExcluir_clicked()
{
    QModelIndex index = ui->tableDados->currentIndex();

    if(!index.isValid()){
        QMessageBox::warning(this, "Aviso", "Selecione um registro primeiro!");
        return;
    }

    int linhaSelecionada = index.row();

    int idAluno = ui->tableDados->model()->index(linhaSelecionada, 0).data().toInt();
    int idResponsavel = ui->tableDados->model()->index(linhaSelecionada,6).data().toInt();

    auto resposta = QMessageBox::question(
        this,
        "Confirmação",
        "Tem certeza que deseja excluir este aluno? (Será excluido os dados do responsável também!)",
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::No){
        return;
    }

    QSqlQuery query1, query2;

    query1.prepare("DELETE FROM alunos WHERE id = :rmAluno");
    query1.bindValue(":rmAluno", idAluno);

    if(!query1.exec()) {
        QMessageBox::critical(this, "Erro!", "Erro ao excluir aluno!");
        return;
    }

    query2.prepare("DELETE FROM responsavel WHERE id = :idResponsavel");
    query2.bindValue(":idResponsavel", idResponsavel);

    if(!query2.exec()) {
        QMessageBox::critical(this, "Erro!", "Erro ao excluir o Responsável!");
        return;
    }

    QMessageBox::information(this, "Sucesso!", "Dados do aluno e responsável excluído com sucesso!");

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

    exibirDadosAlunos->setHeaderData(0, Qt::Horizontal, "RM");
    exibirDadosAlunos->setHeaderData(1, Qt::Horizontal, "Aluno");
    exibirDadosAlunos->setHeaderData(2, Qt::Horizontal, "Nascimento");
    exibirDadosAlunos->setHeaderData(3, Qt::Horizontal, "Sexo");
    exibirDadosAlunos->setHeaderData(4, Qt::Horizontal, "CPF");
    exibirDadosAlunos->setHeaderData(5, Qt::Horizontal, "RG");
    exibirDadosAlunos->setHeaderData(6, Qt::Horizontal, "Cod Resp.");
    exibirDadosAlunos->setHeaderData(7, Qt::Horizontal, "Responsável");
    exibirDadosAlunos->setHeaderData(8, Qt::Horizontal, "Telefone Resp.");

    ui->tableDados->setModel(exibirDadosAlunos);
    ui->tableDados->resizeColumnsToContents();
    ui->tableDados->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void TelaMenu::on_btnAtualizar_clicked()
{
    atualizarTabela();
}

void TelaMenu::atualizarTabela()
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

    exibirDadosAlunos->setHeaderData(0, Qt::Horizontal, "RM");
    exibirDadosAlunos->setHeaderData(1, Qt::Horizontal, "Aluno");
    exibirDadosAlunos->setHeaderData(2, Qt::Horizontal, "Nascimento");
    exibirDadosAlunos->setHeaderData(3, Qt::Horizontal, "Sexo");
    exibirDadosAlunos->setHeaderData(4, Qt::Horizontal, "CPF");
    exibirDadosAlunos->setHeaderData(5, Qt::Horizontal, "RG");
    exibirDadosAlunos->setHeaderData(6, Qt::Horizontal, "Cod Resp.");
    exibirDadosAlunos->setHeaderData(7, Qt::Horizontal, "Responsável");
    exibirDadosAlunos->setHeaderData(8, Qt::Horizontal, "Telefone Resp.");

    ui->tableDados->setModel(exibirDadosAlunos);
    ui->tableDados->resizeColumnsToContents();
    ui->tableDados->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qDebug() << "Dados Atualizados na tabela";
    ui->lApresentar->setText("Dados Atualizados na tabela!");
}

bool TelaMenu::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter){
        if (watched == ui->btnPesquisar) {
            ui->lApresentar->setText("Faz a pesquisa por nome do aluno, nome do responsavel, \ncpf do aluno e rg do aluno!");
        } else if (watched == ui->btnAdicionar) {
            ui->lApresentar->setText("Adiciona um aluno e o responsável no sistema!");
        } else if (watched == ui->btnEditar) {
            ui->lApresentar->setText("Edita os dados do aluno e do responsável no sistema!");
        } else if (watched == ui->btnExcluir) {
            ui->lApresentar->setText("Exclui os dados do aluno e do responsável no sistema!");
        } else if (watched == ui->btnAtualizar) {
            ui->lApresentar->setText("Atualiza os dados do aluno e do responsável na tabela!");
        }
    } else if (event->type() == QEvent::Leave) {
        ui->lApresentar->setText("...");
    }
    return QMainWindow::eventFilter(watched, event);
}

void TelaMenu::setTelaLogin(QWidget *login) {
    telaLogin = login;
}

void TelaMenu::fazerLogout()
{
    auto resposta = QMessageBox::question(this,
                                          "Confirmação",
                                          "Deseja realmente sair?",
                                          QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        this->close();
        if (telaLogin) {
            telaLogin->show();
        }
    }
}
