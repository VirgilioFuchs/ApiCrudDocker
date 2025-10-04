package com.anglo.tables

import org.jetbrains.exposed.sql.Table

object Responsavel : Table("responsavel") {
    val id = integer("id").autoIncrement()
    val nomeResponsavel = varchar("nomeResponsavel", 100)
    val telefoneResponsavel = varchar("telefoneResponsavel", 15)
    override val primaryKey = PrimaryKey(id)
}