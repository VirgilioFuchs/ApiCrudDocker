#ifndef TELAMENU_H
#define TELAMENU_H

#include "alunotablemodel.h"
#include "telalogin.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardItemModel>

namespace Ui {
class TelaMenu;
}

class TelaMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelaMenu(QWidget *parent = nullptr);
    ~TelaMenu();

    void setTelaLogin(TelaInicial *login) { telaLogin = login; }

    QString getJwtToken() const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_btnPesquisar_clicked();

    void on_btnAdicionar_clicked();

    void on_btnEditar_clicked();

    void on_btnExcluir_clicked();

    void onDeletarReply(QNetworkReply *resposta);

    void on_btnAtualizar_clicked();

    void atualizarLista();

    // void onPesquisarReply(QNetworkReply *resposta);

    void onListarReply(QNetworkReply *resposta);

    void fazerLogout();

private:
    Ui::TelaMenu *ui;
    TelaInicial *telaLogin;
    QNetworkAccessManager *conexao;
    AlunoTableModel *modelo;
    QString jwtToken;
    void carregarAlunos();
    void pesquisarAlunos(const QString &);
};

#endif // TELAMENU_H
