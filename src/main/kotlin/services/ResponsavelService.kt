package com.anglo.services

import com.anglo.controllers.validarResponsavel
import com.anglo.models.ResponsavelRequest
import com.anglo.models.ResponsavelResponse
import com.anglo.tables.Responsavel
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.transactions.transaction
import org.jetbrains.exposed.sql.update

class ResponsavelService{
    fun cadastrarResponsavel(req: ResponsavelRequest): ResponsavelResponse? {
        if (validarResponsavel(req.nomeResponsavel, req.telefoneResponsavel)) {
            return null
        }

        var idGerado: Int? = null

        transaction {
            idGerado = Responsavel.insert {
                it[nomeResponsavel] = req.nomeResponsavel
                it[telefoneResponsavel] = req.telefoneResponsavel
            } get Responsavel.id
        }
        return ResponsavelResponse(idGerado!!, req.nomeResponsavel, req.telefoneResponsavel)
    }

    fun atualizarResponsavel(idResponsavel: Int, nome: String, telefone: String): Boolean {
        val atualizado = transaction {
            Responsavel.update({Responsavel.id eq idResponsavel}) {
                it[nomeResponsavel] = nome
                it[telefoneResponsavel] = telefone
            }
        }
        return atualizado > 0
    }
}