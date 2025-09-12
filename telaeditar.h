#ifndef TELAEDITAR_H
#define TELAEDITAR_H

#include <QWidget>
#include <QDate>
#include <QButtonGroup>

namespace Ui {
class TelaEditar;
}

class TelaEditar : public QWidget
{
    Q_OBJECT

signals:
    void dadosInseridos();

public:
    explicit TelaEditar(QWidget *parent = nullptr);
    ~TelaEditar();

void dadosAlunos(int rmAluno,
                 const QString &nomeAluno,
                 const QDate &dataNascimentoAluno,
                 const QString &sexoAluno,
                 const QString &cpfAluno,
                 const QString &rgAluno,
                 const QString &nomeResponsavel,
                 const QString &telefoneResponsavel
                    );

private slots:
    void on_btnAlterarDados_clicked();

    void on_btnVoltar_clicked();

private:
    Ui::TelaEditar *ui;
    QButtonGroup *grupoSexo;
    int idAluno;
};

#endif // TELAEDITAR_H
