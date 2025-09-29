#include "telaadicionar.h"
#include "telamenu.h"
#include "ui_telaadicionar.h"
#include <QDate>
#include <QMessageBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
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

    conexao = new QNetworkAccessManager(this);

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
    QString dataFormatada = dataNascimento.toString("yyyy-MM-dd");
    QString rgAluno = ui->leRG->text();
    QString cpfAluno = ui->leCPF->text();
    QString nomeResponsavel = ui->leNomeResponsavel->text();
    QString telefoneResponsavel = ui->leContato->text();

    if (nomeAluno.isEmpty() || rgAluno.isEmpty()
        || cpfAluno.isEmpty() || nomeResponsavel.isEmpty() || telefoneResponsavel.isEmpty()){
        QMessageBox::critical(this, "Erro!", "Preencha todos os campos!");
        return;
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

    QUrl url("http://127.0.0.1:8080/registerAlunoAndResponsavel");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["nomeAluno"] = nomeAluno;
    json["dataNascimento"] = dataFormatada;
    json["sexoAluno"] = sexoAluno;
    json["rgAluno"] = rgAluno;
    json["cpfAluno"] = cpfAluno;
    json["nomeResponsavel"] = nomeResponsavel;
    json["telefoneResponsavel"] = telefoneResponsavel;

    QJsonDocument docJson(json);
    QByteArray data = docJson.toJson();

    conexao->post(request,data);

    connect(conexao, &QNetworkAccessManager::finished, this, &TelaAdicionar::onCadastroReply);
}

void TelaAdicionar::respostaSelecionadaSexo(int id)
{
    respostaSexo = id;
    QAbstractButton *button = grupoSexoAluno->button(id);
    qDebug() << "Foi selecionado o botão:" << button->text();
}

void TelaAdicionar::onCadastroReply(QNetworkReply *resposta)
{
    if(resposta->error()) {
        QMessageBox::critical(this, "Erro", "Erro ao Cadastrar!" + resposta->errorString());
        resposta->deleteLater();
        return;
    }

    QByteArray respostaData = resposta->readAll();
    QString resp = QString::fromUtf8(respostaData);

    if (resp.contains("Aluno e Responsável cadastrados com sucesso!", Qt::CaseInsensitive)) {
        QMessageBox::information(this, "Sucesso!", "Cadastro realizado com sucesso!");
        ui->leNomeAluno->clear();
        ui->dateNascimento->clear();
        ui->leRG->clear();
        ui->leCPF->clear();
        ui->leNomeResponsavel->clear();
        ui->leContato->clear();

        emit dadosInseridos();
        this->close();
    } else {
        QMessageBox::critical(this, "ERRO!", "Resposta Inesperada: " + resp);
    }
    resposta->deleteLater();
}

void TelaAdicionar::on_btnFechar_clicked()
{
    close();
}

