package com.anglo.services

import com.anglo.controllers.validarResponsavel
import com.anglo.models.ResponsavelRequest
import com.anglo.models.ResponsavelResponse
import com.anglo.tables.Responsavel
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.transactions.transaction

class ResponsavelService{
    fun cadastrarResponsavel(req: ResponsavelRequest): ResponsavelResponse? {
        if (validarResponsavel(req.nome, req.telefone)) {
            return null
        }

        var idGerado: Int? = null

        transaction {
            idGerado = Responsavel.insert {
                it[nomeResponsavel] = req.nome
                it[telefoneResponsavel] = req.telefone
            } get Responsavel.id
        }
        return ResponsavelResponse(idGerado!!, req.nome, req.telefone)
    }
}