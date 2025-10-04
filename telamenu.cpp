#include "telamenu.h"
#include "ui_telamenu.h"
#include "telaadicionar.h"
#include "telaeditar.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QModelIndex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QUrlQuery>


TelaMenu::TelaMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaMenu)
    , telaLogin(nullptr)
    , conexao(new QNetworkAccessManager(this))
    , modelo(new AlunoTableModel(this))
{
    ui->setupUi(this);
    ui->tableDados->setModel(modelo);

    connect(ui->actionLogout, &QAction::triggered,
            this, &TelaMenu::fazerLogout);

    ui->btnPesquisar->installEventFilter(this);
    ui->btnAdicionar->installEventFilter(this);
    ui->btnEditar->installEventFilter(this);
    ui->btnExcluir->installEventFilter(this);
    ui->btnAtualizar->installEventFilter(this);

    QMessageBox::information(this, "Bem-vindo!",
                             "Olá, seja bem-vindo ao sistema de cadastro de alunos!");
}

TelaMenu::~TelaMenu()
{
    delete ui;
}

// Passa o Token da Tela login para o Menu
void TelaMenu::setTelaLogin(TelaInicial *login) {
    telaLogin = login;
    if (telaLogin) {
        jwtToken = telaLogin->getJwtToken();
    }
    carregarAlunos();
}

void TelaMenu::onListarReply(QNetworkReply *resposta) {
    if (resposta->error()) {
        QMessageBox::critical(this, "Erro", "Erro ao buscar os dados do aluno!");
        qDebug() << "Erro da pesquisa:" << resposta->errorString();
        resposta->deleteLater();
        return;
    }

    QByteArray respostaData = resposta->readAll();
    QJsonDocument docJson = QJsonDocument::fromJson(respostaData);

    if (!docJson.isArray()) {
        QMessageBox::critical(this, "Erro", "Resposta inesperada do servidor!");
        resposta->deleteLater();
        return;
    }

    QJsonArray array = docJson.array();
    modelo->setDataFromJson(array);

    ui->lApresentar->setText("Todos os dados estão listados na tabela!");

    resposta->deleteLater();

}

void TelaMenu::on_btnPesquisar_clicked()
{
    QString pesquisa = ui->leBarraPesquisa->text();
    ui->leBarraPesquisa->clear();

    if (pesquisa.isEmpty()) {
        carregarAlunos();
    } else {
        pesquisarAlunos(pesquisa);
    }
}


void TelaMenu::on_btnAdicionar_clicked()
{
    TelaAdicionar *telaAdicionar = new TelaAdicionar(this);
    telaAdicionar->setAttribute(Qt::WA_DeleteOnClose);
    telaAdicionar->setWindowFlags(Qt::Window);
    telaAdicionar->setWindowTitle("Cadastro de Aluno");
    telaAdicionar->resize(836,522);
    telaAdicionar->setJwtToken(jwtToken);
    connect(telaAdicionar, &TelaAdicionar::dadosInseridos,
            this, &TelaMenu::atualizarLista);
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

    // Dessa maneira evita o fundo da TelaEditar sobrepor a MainWindow e ficar sem fundo!
    TelaEditar *editar = new TelaEditar(this);
    editar->setAttribute(Qt::WA_DeleteOnClose);
    editar->dadosAlunos(rmAluno, nomeAluno, dataNascimentoAluno, sexoAluno, cpfAluno, rgAluno, nomeResponsavel,telefoneResponsavel);
    editar->setWindowFlags(Qt::Window);
    editar->setWindowTitle("Editar dados do Aluno");
    editar->resize(926,643);
    editar->setJwtToken(jwtToken);
    connect(editar, &TelaEditar::dadosInseridos,
            this, &TelaMenu::atualizarLista);
    editar->show();
}

void TelaMenu::onDeletarReply(QNetworkReply *resposta)
{
    if (resposta->error()) {
        QMessageBox::critical(this, "Erro", "Erro ao deletar os dados do aluno!" + resposta->errorString());
        resposta->deleteLater();
        return;
    }

    QByteArray respostaData = resposta->readAll();

    QMessageBox::information(this, "Sucesso", "Aluno e responsável deletado com sucesso!");
    carregarAlunos();
    resposta->deleteLater();
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

    auto resposta = QMessageBox::question(
        this,
        "Confirmação",
        QString("Tem certeza que deseja excluir este aluno com o ID %1? (Será excluido os dados do responsável também!)").arg(idAluno),
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::No){
        return;
    }

    QUrl url(QString("http://127.0.0.1:8080/alunos/%1").arg(idAluno));
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + jwtToken).toUtf8());

    QNetworkReply *reply = conexao->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [=](){
        onDeletarReply(reply);
    });
}


void TelaMenu::on_btnAtualizar_clicked()
{
    carregarAlunos();
}

void TelaMenu::atualizarLista() {
    carregarAlunos();
}

void TelaMenu::carregarAlunos() {
    QUrl url("http://127.0.0.1:8080/alunos");

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + jwtToken).toUtf8());

    QNetworkReply *resposta = conexao->get(request);
    connect(resposta, &QNetworkReply::finished, this, [=]() {
        onListarReply(resposta);
    });
}

void TelaMenu::pesquisarAlunos(const QString &pesquisa) {
    QUrl url("http://127.0.0.1:8080/alunos/search");
    QUrlQuery query;

    query.addQueryItem("q", pesquisa);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + jwtToken).toUtf8());

    QNetworkReply *resposta = conexao->get(request);
    connect(resposta, &QNetworkReply::finished, this, [=]() {
        onListarReply(resposta);
    });
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

void TelaMenu::fazerLogout()
{
    auto resposta = QMessageBox::question(this,
                                          "Confirmação",
                                          "Deseja realmente sair?",
                                          QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        this->close();
        jwtToken.clear();
        if (telaLogin) {
            telaLogin->show();
        }
    }
}
