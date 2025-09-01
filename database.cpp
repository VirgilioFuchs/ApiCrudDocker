#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QCryptographicHash>

// Inicializa a instância estática
Database* Database::m_instance = nullptr;

Database* Database::instance()
{
    if (!m_instance) {
        m_instance = new Database();
    }
    return m_instance;
}

Database::Database()
{
    // O corpo pode ficar vazio, pois a conexão é feita no método conectar().
}

Database::~Database()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
    m_instance = nullptr;
}

bool Database::conectar()
{
    if (m_db.isOpen()) {
        return true;
    }

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("127.0.0.1");
    m_db.setPort(3306);
    m_db.setDatabaseName("LoginBD"); // <-- MUDE AQUI
    m_db.setUserName("root");           // <-- MUDE AQUI
    m_db.setPassword("Anglopp.g12");             // <-- MUDE AQUI

    if (!m_db.open()) {
        qWarning() << "Falha ao conectar ao banco de dados:" << m_db.lastError().text();
        return false;
    }

    qInfo() << "Banco de dados conectado com sucesso!";

    // Cria a tabela de usuários se ela não existir
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS usuarios ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "nome VARCHAR(50) UNIQUE NOT NULL, "
                    "senha VARCHAR(64) NOT NULL)")) {
        qWarning() << "Falha ao criar a tabela 'usuarios':" << query.lastError().text();
        return false;
    }

    return true;
}

void Database::desconectar()
{
    m_db.close();
}

bool Database::estaConectado() const
{
    return m_db.isOpen();
}

bool Database::cadastrarUsuario(const QString &usuario, const QString &senha)
{
    if (usuario.isEmpty() || senha.isEmpty()) {
        qWarning() << "Usuário ou senha não podem ser vazios.";
        return false;
    }

    // Criptografa a senha antes de salvar (MUITO IMPORTANTE!)
    QString senhaHash = QString(QCryptographicHash::hash(senha.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nome, password_hash) VALUES (:nome, :password_hash)");
    query.bindValue(":nome", usuario);
    query.bindValue(":password_hash", senhaHash);

    if (!query.exec()) {
        qWarning() << "Falha ao registrar usuário:" << query.lastError().text();
        return false;
    }

    qInfo() << "Usuário" << usuario << "registrado com sucesso!";
    return true;
}

bool Database::validarLogin(const QString &usuario, const QString &senha)
{
    // Criptografa a senha fornecida para comparar com a que está no banco
    QString senhaHash = QString(QCryptographicHash::hash(senha.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("SELECT senha FROM usuarios WHERE nome = :nome");
    query.bindValue(":nome", usuario);

    if (!query.exec()) {
        qWarning() << "Falha ao validar login:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString senhaDoBanco = query.value(0).toString();
        if (senhaDoBanco == senhaHash) {
            qInfo() << "Login de" << usuario << "validado com sucesso!";
            return true; // Senha correta
        }
    }

    qWarning() << "Falha na validação: usuário ou senha incorretos para" << usuario;
    return false; // Usuário não encontrado ou senha incorreta
}
