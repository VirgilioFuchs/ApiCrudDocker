package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class AlunoResponsavel(
    //Dados do Aluno
    val nomeAluno: String,
    val dataNascimento: String,
    val sexoAluno: String,
    val rgAluno: String,
    val cpfAluno: String,

    // Dados do Responsável
    val nomeResponsavel: String,
    val telefoneResponsavel: String
)
