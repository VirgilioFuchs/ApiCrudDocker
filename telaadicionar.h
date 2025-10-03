#ifndef TELAADICIONAR_H
#define TELAADICIONAR_H

#include <QWidget>
#include <QButtonGroup>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class TelaAdicionar;
}

class TelaAdicionar : public QWidget
{
    Q_OBJECT

signals:
    void dadosInseridos();

public:
    explicit TelaAdicionar(QWidget *parent = nullptr);
    ~TelaAdicionar();

    void setJwtToken(const QString &token) { jwtToken = token;}

private slots:
    void on_btnAdicionarFoto_clicked();

    void on_btnCadastrar_clicked();

    void respostaSelecionadaSexo(int id);

    void onCadastroReply(QNetworkReply *resposta);

    void on_btnFechar_clicked();

private:
    Ui::TelaAdicionar *ui;

    QButtonGroup *grupoSexoAluno;
    int respostaSexo;
    QNetworkAccessManager *conexao;
    QString jwtToken;
};

#endif // TELAADICIONAR_H
