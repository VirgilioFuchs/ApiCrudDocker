package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class AlunoResponsavelList(
    //Dados do Aluno
    val idAluno: Int,
    val nomeAluno: String,
    val dataNascimento: String,
    val sexoAluno: String,
    val rgAluno: String,
    val cpfAluno: String,

    // Dados do Responsável
    val idResponsavel: Int,
    val nomeResponsavel: String,
    val telefoneResponsavel: String
)
