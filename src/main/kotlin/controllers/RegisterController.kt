package com.anglo.controllers

import com.anglo.models.Usuarios
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.transactions.transaction

fun validarRegistro(nome: String): Boolean {
    return transaction {
        Usuarios.select {
            Usuarios.nome eq nome
        }.count() > 0
    }
}