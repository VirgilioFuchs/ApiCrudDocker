package com.anglo.controllers

import com.anglo.tables.Alunos
import org.jetbrains.exposed.sql.and
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

fun validarAluno(rg: String, cpf: String): Boolean {
    return transaction {
        Alunos.selectAll().where {
            (Alunos.rgAluno eq rg) and (Alunos.cpfAluno eq cpf)
        }.count() > 0
    }
}

fun verificarVazioAluno(nomeAluno: String, dataNascimento: String, sexoAluno: String, rgAluno: String, cpfAluno: String): Boolean {
    return nomeAluno.isBlank()
            || dataNascimento.isBlank()
            || sexoAluno.isBlank()
            || rgAluno.isBlank()
            || cpfAluno.isBlank()
}