package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class ResponsavelRequest(
    val nomeResponsavel: String,
    val telefoneResponsavel: String
)

@Serializable
data class ResponsavelResponse(
    val id: Int,
    val nomeResponsavel: String,
    val telefoneResponsavel: String
)