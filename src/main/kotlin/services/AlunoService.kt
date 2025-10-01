package com.anglo.services

import com.anglo.controllers.validarAluno
import com.anglo.models.AlunoResponsavelList
import com.anglo.models.AlunoResponsavelSearch
import com.anglo.models.AlunosRequest
import com.anglo.models.AlunosResponse
import com.anglo.models.AlunosUpdateRequest
import com.anglo.models.ResponsavelResponse
import com.anglo.tables.Alunos
import com.anglo.tables.Responsavel
import org.jetbrains.exposed.sql.SqlExpressionBuilder.eq
import org.jetbrains.exposed.sql.and
import org.jetbrains.exposed.sql.deleteWhere
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.or
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction
import org.jetbrains.exposed.sql.update
import org.slf4j.LoggerFactory
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
            Alunos.update({ Alunos.id eq idAluno }) {
                it[nomeAluno] = req.nomeAluno
                it[dataNascimento] = dataNascimentoConvertida
                it[sexoAluno] = req.sexoAluno
                it[id_Responsavel] = req.id_Responsavel
            }
        }
        return atualizado > 0
    }

    fun pesquisarAluno(q: String?): List<AlunoResponsavelSearch> {
        return transaction {
            Alunos.join(
                otherTable = Responsavel,
                onColumn = Alunos.id_Responsavel,
                otherColumn = Responsavel.id,
                joinType = org.jetbrains.exposed.sql.JoinType.INNER
            )
                .selectAll()
                .where {
                    (Alunos.nomeAluno like "%${q}%") or
                            (Responsavel.nomeResponsavel like "%${q}%") or
                            (Alunos.cpfAluno like "%${q}%") or
                            (Alunos.rgAluno like "%${q}%")
                }
                .map { linha ->
                    AlunoResponsavelSearch(
                        idAluno = linha[Alunos.id],
                        nomeAluno = linha[Alunos.nomeAluno],
                        dataNascimento = linha[Alunos.dataNascimento].toString(),
                        sexoAluno = linha[Alunos.sexoAluno],
                        rgAluno = linha[Alunos.rgAluno],
                        cpfAluno = linha[Alunos.cpfAluno],
                        idResponsavel = linha[Responsavel.id],
                        nomeResponsavel = linha[Responsavel.nomeResponsavel],
                        telefoneResponsavel = linha[Responsavel.telefoneResponsavel]
                    )
                }
        }
    }

    fun listarTodosAlunos(): List<AlunoResponsavelList> {
        return transaction {
            Alunos.join(
                otherTable = Responsavel,
                onColumn = Alunos.id_Responsavel,
                otherColumn = Responsavel.id,
                joinType = org.jetbrains.exposed.sql.JoinType.INNER
            )
                .selectAll()
                .orderBy(Alunos.nomeAluno)
                .map { linha ->
                    AlunoResponsavelList(
                        idAluno = linha[Alunos.id],
                        nomeAluno = linha[Alunos.nomeAluno],
                        dataNascimento = linha[Alunos.dataNascimento].toString(),
                        sexoAluno = linha[Alunos.sexoAluno],
                        rgAluno = linha[Alunos.rgAluno],
                        cpfAluno = linha[Alunos.cpfAluno],
                        idResponsavel = linha[Responsavel.id],
                        nomeResponsavel = linha[Responsavel.nomeResponsavel],
                        telefoneResponsavel = linha[Responsavel.telefoneResponsavel]
                    )
                }
        }
    }

    fun deletarAlunoEVerificarResponsavel(idAluno: Int): String {
        return transaction {
            val aluno = Alunos.selectAll().where { Alunos.id eq idAluno }.singleOrNull()

            if (aluno == null) {
                return@transaction "Aluno não encontrado."
            }

            val idResponsavel = aluno[Alunos.id_Responsavel]

            Alunos.deleteWhere { Alunos.id eq idAluno }

            val outrosAlunosCount = Alunos.selectAll().where { Alunos.id_Responsavel eq idResponsavel }.count()

            if (outrosAlunosCount == 0L) {
                Responsavel.deleteWhere { Responsavel.id eq idResponsavel }
                return@transaction "Aluno e seu último responsável foram deletados."
            } else {
                return@transaction "Aluno deletado. O responsável foi mantido pois possui outros alunos."
            }
        }
    }
}