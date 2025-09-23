#ifndef TELALOGIN_H
#define TELALOGIN_H

#include <QLineEdit>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

    QString getJwtToken() const;

private slots:
    void on_btnLogin_clicked();
    void on_btnCadastrar_clicked();
    void onLoginFinalizado();

private:
    Ui::TelaInicial *ui;
    QNetworkAccessManager *conexao;
    QNetworkReply *resposta;
    QString jwtToken;
};
#endif // TELALOGIN_H
