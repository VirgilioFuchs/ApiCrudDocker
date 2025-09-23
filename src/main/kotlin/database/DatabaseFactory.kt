package com.anglo.database

import com.anglo.utils.Env
import com.zaxxer.hikari.HikariConfig
import com.zaxxer.hikari.HikariDataSource
import org.jetbrains.exposed.sql.Database
import org.jetbrains.exposed.sql.StdOutSqlLogger
import org.jetbrains.exposed.sql.addLogger
import org.jetbrains.exposed.sql.transactions.transaction

object DatabaseFactory {
    fun init() {
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

            // Faz um teste com uma transação simples
            transaction {
                addLogger(StdOutSqlLogger)
                exec("SELECT 1") // Se der erro aqui a conexão falha
            }
            println("Banco de dados conectado com sucesso!")
        } catch (e: Exception) {
            println("Erro ao conectar ao banco de dados!")
            e.printStackTrace()
        }
    }
}