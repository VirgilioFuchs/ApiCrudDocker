#ifndef TELAMENU_H
#define TELAMENU_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class TelaMenu;
}

class TelaMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelaMenu(QWidget *parent = nullptr);
    ~TelaMenu();

    void setTelaLogin(QWidget *login);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_btnPesquisar_clicked();

    void on_btnAdicionar_clicked();

    void on_btnEditar_clicked();

    void on_btnExcluir_clicked();

    void on_btnAtualizar_clicked();

    void fazerLogout();

private:
    Ui::TelaMenu *ui;
    void atualizarTabela();
    QWidget *telaLogin;
};

#endif // TELAMENU_H
