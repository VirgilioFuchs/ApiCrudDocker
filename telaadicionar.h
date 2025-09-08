#ifndef TELAADICIONAR_H
#define TELAADICIONAR_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class TelaAdicionar;
}

class TelaAdicionar : public QWidget
{
    Q_OBJECT

public:
    explicit TelaAdicionar(QWidget *parent = nullptr);
    ~TelaAdicionar();

private slots:
    void on_btnAdicionarFoto_clicked();

    void on_btnCadastrar_clicked();

    void respostaSelecionadaSexo(int id);

    void on_btnFechar_clicked();

private:
    Ui::TelaAdicionar *ui;

    QButtonGroup *grupoSexoAluno;
    int respostaSexo;
};

#endif // TELAADICIONAR_H
