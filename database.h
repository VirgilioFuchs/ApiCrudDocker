#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class Database
{
public:
    // Método para obter a instância única (Singleton)
    static Database* instance();

    // Conecta ao banco de dados e cria a tabela se não existir
    bool conectar();
    void desconectar();
    bool estaConectado() const;

    // Funções de negócio
    bool cadastrarUsuario(const QString &usuario, const QString &senha);
    bool validarLogin(const QString &usuario, const QString &senha);

private:
    // Construtor privado para garantir que apenas uma instância exista
    Database();
    ~Database();

    // Impede cópia
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QSqlDatabase m_db;
    static Database* m_instance;
};

#endif // DATABASE_H
