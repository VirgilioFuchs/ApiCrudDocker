package com.anglo.database

import com.anglo.utils.Env
import com.zaxxer.hikari.HikariConfig
import com.zaxxer.hikari.HikariDataSource
import org.jetbrains.exposed.sql.Database
import org.jetbrains.exposed.sql.StdOutSqlLogger
import org.jetbrains.exposed.sql.addLogger
import org.jetbrains.exposed.sql.transactions.transaction

object DatabaseFactory {
    fun init(){

        var attempts = 0
        val maxAttempts = 10
        while (attempts < maxAttempts) {
            try {
                val config = HikariConfig().apply {
                    jdbcUrl = Env.jdbcUrl
                    driverClassName = "com.mysql.cj.jdbc.Driver"
                    username = Env.dbUser
                    password = Env.dbPassword
                    maximumPoolSize = 10
                }

                val dataSource = HikariDataSource(config)
                Database.connect(dataSource)

                // Testa conexão
                transaction {
                    addLogger(StdOutSqlLogger)
                    exec("SELECT 1")
                }

                println("✅ Banco de dados conectado com sucesso!")
                return // sai do loop se conseguiu
            } catch (e: Exception) {
                attempts++
                println("⚠️ Tentativa $attempts de conexão falhou: ${e.message}")
                Thread.sleep(3000) // espera 3 segundos antes de tentar de novo
            }
        }

        throw IllegalStateException("❌ Não foi possível conectar ao banco de dados após $maxAttempts tentativas")
    }
}