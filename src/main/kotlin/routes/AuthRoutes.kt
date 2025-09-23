package com.anglo.routes

import com.anglo.controllers.validarUsuario
import com.anglo.utils.Env
import com.auth0.jwt.JWT
import com.auth0.jwt.algorithms.Algorithm
import io.ktor.http.HttpStatusCode
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.Route
import io.ktor.server.routing.post
import java.sql.Date

data class LoginRequest (val nome: String, val senha: String)

fun Route.authRoutes() {
    post("/login") {
        val body = call.receive<LoginRequest>()

        if (validarUsuario(body.nome, body.senha)){
            val token = JWT.create()
                .withAudience(Env.jwtAudience)
                .withIssuer(Env.jwtIssuer)
                .withClaim("nome", body.nome)
                .withExpiresAt(Date(System.currentTimeMillis() + 3600000))
                .sign(Algorithm.HMAC256(Env.jwtSecret))

            call.respond(mapOf("token" to token))
            println("Usuário validado e conectado com sucesso!")
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Usuário ou senha inválidos")
            println("Erro ao validar as credenciais do usuário!")
        }
    }
}