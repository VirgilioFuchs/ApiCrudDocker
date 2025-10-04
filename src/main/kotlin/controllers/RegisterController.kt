package com.anglo.controllers

import com.anglo.tables.Usuarios
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

fun validarRegistro(nome: String): Boolean {
    return transaction {
        Usuarios.selectAll().where {
            Usuarios.nome eq nome
        }.count() > 0
    }
}