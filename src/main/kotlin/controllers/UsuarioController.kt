package com.anglo.controllers

import com.anglo.models.Usuarios
import org.apache.commons.codec.digest.DigestUtils
import org.jetbrains.exposed.sql.and
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.transactions.transaction

fun validarUsuario(nome: String, senhaNormal: String): Boolean {
    val senhaHash = DigestUtils.sha256Hex(senhaNormal)

    return transaction {
        Usuarios.select {
            (Usuarios.nome eq nome) and (Usuarios.senha eq senhaHash)
        }.count() > 0
    }
}