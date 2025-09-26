package com.anglo.routes

import com.anglo.models.LoginRequest
import com.anglo.services.UsuarioService
import com.anglo.utils.Env
import com.auth0.jwt.JWT
import io.ktor.http.HttpStatusCode
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.Route
import io.ktor.server.routing.post
import java.util.Date

fun Route.userRoutes() {
    val usuarioService = UsuarioService()

    post("/register") {
        val body = call.receive<LoginRequest>()

        if(body.nome.isBlank() || body.senha.isBlank()) {
            call.respond(HttpStatusCode.BadRequest, "Nome e senha são obrigatórios!")
            return@post
        }

        val novoUsuario = usuarioService.cadastrarUsuario(body)

        if(novoUsuario != null) {
            call.respond(HttpStatusCode.Created, "Usuário Cadastrado com sucesso!")
        } else{
            call.respond(HttpStatusCode.BadRequest, "Usuario já existente!")
        }
    }

    post("/login") {
        val body = call.receive<LoginRequest>()

        if (usuarioService.login(body)) {
            val token = JWT.create()
                .withAudience(Env.jwtAudience)
                .withIssuer(Env.jwtIssuer)
                .withClaim("nome", body.nome)
                .withExpiresAt(Date(System.currentTimeMillis() + 3600000))
                .sign(com.auth0.jwt.algorithms.Algorithm.HMAC256(Env.jwtSecret))

            call.respond(mapOf("token" to token))
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Usuário ou senha inválidos")
        }
    }
}