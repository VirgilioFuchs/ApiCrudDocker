package com.anglo.services

import com.anglo.controllers.validarRegistro
import com.anglo.controllers.validarUsuario
import com.anglo.models.LoginRequest
import com.anglo.models.LoginResponse
import com.anglo.tables.Usuarios
import com.anglo.utils.hashSenha
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.transactions.transaction

class UsuarioService {
    fun cadastrarUsuario(req: LoginRequest): LoginResponse? {
        if (validarRegistro(req.nome)) {
            return null
        }

        var idGerado: Int? = null
        val senhaHashed = hashSenha(req.senha)

        transaction {
            idGerado = Usuarios.insert {
                it[nome] = req.nome
                it[senha] = senhaHashed
            } get Usuarios.id
        }
        return LoginResponse(idGerado!!, req.nome)
    }

    fun login(req: LoginRequest): Boolean {
        return validarUsuario(req.nome, req.senha)
    }
}