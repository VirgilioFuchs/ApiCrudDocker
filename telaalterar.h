#ifndef TELAALTERAR_H
#define TELAALTERAR_H

#include <QWidget>

namespace Ui {
class TelaAlterar;
}

class TelaAlterar : public QWidget
{
    Q_OBJECT

public:
    explicit TelaAlterar(QWidget *parent = nullptr);
    ~TelaAlterar();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TelaAlterar *ui;
};

#endif // TELAALTERAR_H
