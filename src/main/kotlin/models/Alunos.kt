package com.anglo.models

import kotlinx.serialization.Serializable

@Serializable
data class AlunosRequest(
    val nomeAluno: String,
    val dataNascimento: String,
    val sexoAluno: String,
    val rgAluno: String,
    val cpfAluno: String,
    val id_Responsavel: Int
)

@Serializable
data class AlunosResponse(
    val id: Int,
    val nomeAluno: String,
    val dataNascimento: String,
    val sexoAluno: String,
    val rgAluno: String,
    val cpfAluno: String,
    val id_Responsavel: ResponsavelResponse
)

@Serializable
data class AlunosUpdateRequest(
    val nomeAluno: String,
    val dataNascimento: String,
    val sexoAluno: String,
    val id_Responsavel: Int
)
