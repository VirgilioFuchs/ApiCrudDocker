#ifndef TELAINICIAL_H
#define TELAINICIAL_H

#include <QLineEdit>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class TelaInicial;
}
QT_END_NAMESPACE

class TelaInicial : public QMainWindow
{
    Q_OBJECT

public:
    TelaInicial(QWidget *parent = nullptr);
    ~TelaInicial();

private slots:
    void on_btnLogin_clicked();

    void receberDadosCadastro(const QString &nomeUsuario, QString &senhaUsuario);

    void on_btnCadastrar_clicked();

private:
    Ui::TelaInicial *ui;

    // variáveis para receber os dados
    QString dadoNomeCadastrado;
    QString dadoSenhaCadastrado;
};
#endif // TELAINICIAL_H
