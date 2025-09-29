package com.anglo.services

import com.anglo.controllers.validarAluno
import com.anglo.models.AlunosRequest
import com.anglo.models.AlunosResponse
import com.anglo.models.AlunosUpdateRequest
import com.anglo.models.ResponsavelResponse
import com.anglo.tables.Alunos
import com.anglo.tables.Responsavel
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction
import org.jetbrains.exposed.sql.update
import java.time.LocalDate

class AlunoService {
    fun cadastrarAluno(req: AlunosRequest): AlunosResponse? {
        if (validarAluno(req.rgAluno, req.cpfAluno)) {
            return null
        }

        var idGerado: Int? = null
        val dataNascimentoConvertida = LocalDate.parse(req.dataNascimento)

        transaction {
            idGerado = Alunos.insert {
                it[nomeAluno] = req.nomeAluno
                it[dataNascimento] = dataNascimentoConvertida
                it[sexoAluno] = req.sexoAluno
                it[rgAluno] = req.rgAluno
                it[cpfAluno] = req.cpfAluno
                it[id_Responsavel] = req.id_Responsavel
            } get Alunos.id
        }
        var responsavelResponse: ResponsavelResponse? = null

        transaction {
            val responsavel = Responsavel.selectAll().where {
                Responsavel.id eq req.id_Responsavel
            }.single()
            responsavelResponse = ResponsavelResponse(
                id = responsavel[Responsavel.id],
                nomeResponsavel = responsavel[Responsavel.nomeResponsavel],
                telefoneResponsavel = responsavel[Responsavel.telefoneResponsavel]
            )
        }

        return AlunosResponse(
            id = idGerado!!,
            nomeAluno = req.nomeAluno,
            dataNascimento = req.dataNascimento,
            sexoAluno = req.sexoAluno,
            rgAluno = req.rgAluno,
            cpfAluno = req.cpfAluno,
            id_Responsavel = responsavelResponse!!
        )
    }

    fun atualizarAluno(idAluno: Int, req: AlunosUpdateRequest): Boolean {
        val dataNascimentoConvertida = LocalDate.parse(req.dataNascimento)

        val atualizado = transaction {
            Alunos.update ({Alunos.id eq idAluno}) {
                it[nomeAluno] = req.nomeAluno
                it[dataNascimento] = dataNascimentoConvertida
                it[sexoAluno] = req.sexoAluno
                it[id_Responsavel] = req.id_Responsavel
            }
        }
        return atualizado > 0
    }
}