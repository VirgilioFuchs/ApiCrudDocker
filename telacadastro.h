#ifndef TELACADASTRO_H
#define TELACADASTRO_H

#include <QMainWindow>

namespace Ui {
class TelaCadastro;
}

class TelaCadastro : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelaCadastro(QWidget *parent = nullptr);
    ~TelaCadastro();

signals:
    void enviarDados(const QString &nomeUsuario, QString &senhaUsuario);

private slots:
    void on_btnCadastrar_clicked();

    void on_btnVoltar_clicked();

private:
    Ui::TelaCadastro *ui;
};

#endif // TELACADASTRO_H
