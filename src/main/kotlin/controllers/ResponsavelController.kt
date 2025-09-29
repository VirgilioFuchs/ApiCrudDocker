package com.anglo.controllers

import com.anglo.tables.Responsavel
import org.jetbrains.exposed.sql.or
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

fun validarResponsavel(nome: String, telefone: String): Boolean {
    return transaction {
        Responsavel.selectAll().where {
            (Responsavel.nomeResponsavel eq nome) or (Responsavel.telefoneResponsavel eq telefone)
        }.count() > 0
    }
}

fun verificarVazioResponsavel(nome: String, telefone: String): Boolean {
    return nome.isBlank() || telefone.isBlank()
}