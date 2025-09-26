package com.anglo.controllers

fun validarResponsavel(nome: String, telefone: String): Boolean {
    return nome.isNotEmpty() && telefone.isNotEmpty()
}