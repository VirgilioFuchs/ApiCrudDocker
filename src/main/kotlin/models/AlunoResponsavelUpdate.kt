package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class AlunoResponsavelUpdate(
    val nomeAluno: String,
    val dataNascimento: String,
    val sexoAluno: String,

    val nomeResponsavel: String,
    val telefoneResponsavel: String
)