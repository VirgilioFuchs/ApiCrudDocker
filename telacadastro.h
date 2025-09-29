#ifndef TELACADASTRO_H
#define TELACADASTRO_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class TelaCadastro;
}

class TelaCadastro : public QDialog
{
    Q_OBJECT

public:
    explicit TelaCadastro(QWidget *parent = nullptr);
    ~TelaCadastro();

private slots:
    void on_btnCadastrar_clicked();
    void on_btnVoltar_clicked();
    void onCadastroReply(QNetworkReply *resposta);

private:
    Ui::TelaCadastro *ui;
    QNetworkAccessManager *conexao;
};

#endif // TELACADASTRO_H
