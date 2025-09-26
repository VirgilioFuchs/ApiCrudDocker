package com.anglo.tables

import org.jetbrains.exposed.sql.Table

object Usuarios: Table("usuarios") {
    val id = integer("id").autoIncrement()
    val nome = varchar("nome", 50)
    val senha = varchar("senha", 255)
    override val primaryKey = PrimaryKey(id)
}