#ifndef TELAMENU_H
#define TELAMENU_H

#include <QMainWindow>

namespace Ui {
class TelaMenu;
}

class TelaMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelaMenu(QWidget *parent = nullptr);
    ~TelaMenu();

private slots:
    void on_btnPesquisar_clicked();

    void on_btnAdicionar_clicked();

    void on_btnEditar_clicked();

    void on_btnExcluir_clicked();

private:
    Ui::TelaMenu *ui;
};

#endif // TELAMENU_H
