package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class LoginRequest(
    val nome: String,
    val senha: String
)

@Serializable
data class LoginResponse(
    val id: Int,
    val nome: String
)