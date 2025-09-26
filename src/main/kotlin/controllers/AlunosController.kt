package com.anglo.controllers

import com.anglo.tables.Alunos
import org.jetbrains.exposed.sql.and
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.transactions.transaction

fun validarAluno(rg: String, cpf: String): Boolean {
    return transaction {
        Alunos.select{
            (Alunos.rgAluno eq rg) and (Alunos.cpfAluno eq cpf)
        }.count() > 0
    }
}