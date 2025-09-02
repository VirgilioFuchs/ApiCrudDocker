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

Database::Database(){}

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

    if (!QSqlDatabase::isDriverAvailable("QMYSQL")) {
        qWarning() << "Driver QMYSQL não está disponível.";
        return false;
    }

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setDatabaseName("LoginBD");
    m_db.setUserName("root");
    m_db.setPassword("Anglopp.g12");

    // 1) Diagnóstico: desativa TLS para ver se a conexão sobe
    m_db.setConnectOptions("MYSQL_OPT_RECONNECT=1");

    if (!m_db.open()) {
        qWarning() << "Falha ao conectar ao banco de dados:" << m_db.lastError().text();
        return false;
    }

    qInfo() << "Banco de dados conectado com sucesso!";

    // Cria a tabela de usuários se ela não existir
    QSqlQuery query(m_db);

    const char* ddl =
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "  id INT AUTO_INCREMENT PRIMARY KEY,"
        "  nome VARCHAR(50) UNIQUE NOT NULL,"
        "  senha CHAR(64) NOT NULL"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci";

    if (!query.exec(ddl)) {
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

    // Criptografia de senha
    const QString senhaHash =QString::fromLatin1(QCryptographicHash::hash(senha.toUtf8(),QCryptographicHash::Sha256).toHex());

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO usuarios (nome, password_hash) VALUES (:nome, :password_hash)");
    query.bindValue(":nome", usuario);
    query.bindValue(":password_hash", senhaHash);

    if (!query.exec()) {
        const auto err = query.lastError();
        // 1062 = ER_DUP_ENTRY (nome duplicado)
        if (err.nativeErrorCode() == "1062")
            qWarning() << "Falha ao registrar: usuário já existe.";
        else
            qWarning() << "Falha ao registrar usuário:" << err.text();
        return false;
    }

    qInfo() << "Usuário" << usuario << "registrado com sucesso!";
    return true;
}

bool Database::validarLogin(const QString &usuario, const QString &senha)
{

    const QString senhaHash = QString::fromLatin1(QCryptographicHash::hash(senha.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query(m_db);
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
            return true;
        }
    }

    qWarning() << "Falha na validação: usuário ou senha incorretos para" << usuario;
    return false;
}
