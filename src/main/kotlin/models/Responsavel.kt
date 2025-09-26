package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class ResponsavelRequest(
    val nome: String,
    val telefone: String
)

@Serializable
data class ResponsavelResponse(
    val id: Int,
    val nome: String,
    val telefone: String
)