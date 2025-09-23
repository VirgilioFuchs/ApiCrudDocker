package com.anglo.routes

import com.anglo.controllers.validarRegistro
import com.anglo.controllers.validarUsuario
import com.anglo.models.Usuarios
import com.anglo.utils.hashSenha
import io.ktor.http.HttpStatusCode
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.Route
import io.ktor.server.routing.post
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.transactions.transaction

data class RegisterRequest (val nome: String, val senha: String)

fun Route.registerRoute() {
    post("/register") {

        val body = call.receive<RegisterRequest>()

        if (body.nome.isBlank() || body.senha.isBlank()) {
            call.respond(HttpStatusCode.BadRequest,"Nome e senha são obrigatórios!")
            return@post
        }

        if (validarRegistro(body.nome)){
            call.respond(HttpStatusCode.Conflict, "Usuário já existe")
            return@post
        }

//        Criptografa a senha
        val senhaHash = hashSenha(body.senha)

        transaction {
            Usuarios.insert {
                it[nome] = body.nome
                it[senha] = senhaHash
            }
        }

        call.respond(HttpStatusCode.Created, "Usuário cadastrado com sucesso!")
    }
}