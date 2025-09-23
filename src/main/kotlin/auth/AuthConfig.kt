package com.anglo.auth

import com.anglo.utils.Env
import com.auth0.jwt.JWT
import com.auth0.jwt.algorithms.Algorithm
import io.ktor.server.application.Application
import io.ktor.server.application.install
import io.ktor.server.auth.Authentication
import io.ktor.server.auth.jwt.JWTPrincipal
import io.ktor.server.auth.jwt.jwt

fun Application.configureSecurity() {
    install(Authentication) {
        jwt("auth-jwt") {
            realm = "Área de Usuários"
            verifier(
                JWT
                    .require(Algorithm.HMAC256(Env.jwtSecret))
                    .withAudience(Env.jwtAudience)
                    .withIssuer(Env.jwtIssuer)
                    .build()
            )
            validate { credential ->
                if (credential.payload.getClaim("nome").asString().isNotEmpty())
                    JWTPrincipal(credential.payload)
                else
                    null
            }
        }
    }
}