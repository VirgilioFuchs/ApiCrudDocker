package com.anglo.utils

import java.security.MessageDigest

fun hashSenha(senha: String): String {
    return MessageDigest
        .getInstance("SHA-256")
        .digest(senha.toByteArray())
        .joinToString("") { "%02x".format(it) }
}