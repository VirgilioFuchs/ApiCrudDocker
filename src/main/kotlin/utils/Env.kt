package com.anglo.utils

import io.github.cdimascio.dotenv.dotenv

object Env {
    private val dotenv = dotenv {
        ignoreIfMissing = false
    }

    val jdbcUrl: String? get() = dotenv["JDBC_URL"]
    val dbUser: String? get() = dotenv["DB_USER"]
    val dbPassword: String? get() = dotenv["DB_PASSWORD"]
    val jwtSecret: String? get() = dotenv["JWT_SECRET"]
    val jwtIssuer: String? get() = dotenv["JWT_ISSUER"]
    val jwtAudience: String? get() = dotenv["JWT_AUDIENCE"]
}