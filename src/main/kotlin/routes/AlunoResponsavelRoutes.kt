package com.anglo.routes

import com.anglo.controllers.verificarVazioAluno
import com.anglo.controllers.verificarVazioResponsavel
import com.anglo.models.AlunoResponsavel
import com.anglo.models.AlunoResponsavelUpdate
import com.anglo.models.AlunosRequest
import com.anglo.models.AlunosUpdateRequest
import com.anglo.models.ResponsavelRequest
import com.anglo.services.AlunoService
import com.anglo.services.ResponsavelService
import com.anglo.tables.Alunos
import io.ktor.http.HttpStatusCode
import io.ktor.server.application.log
import io.ktor.server.auth.authenticate
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.Route
import io.ktor.server.routing.application
import io.ktor.server.routing.delete
import io.ktor.server.routing.get
import io.ktor.server.routing.post
import io.ktor.server.routing.put
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

fun Route.alunoResponsavelRoutes() {
    val alunoService = AlunoService()
    val responsavelService = ResponsavelService()


    authenticate("auth-jwt") {
        post("/registerAlunoAndResponsavel") {
            val body = call.receive<AlunoResponsavel>()

            if (verificarVazioAluno(body.nomeAluno, body.dataNascimento, body.sexoAluno, body.rgAluno, body.cpfAluno) ||
                verificarVazioResponsavel(body.nomeResponsavel, body.telefoneResponsavel)
            ) {
                call.respond(HttpStatusCode.BadRequest, "Preencha todos os campos!")
                return@post
            }

            var statusCode: HttpStatusCode = HttpStatusCode.Created
            var message = "Aluno e Responsável cadastrados com sucesso!"

            try {
                transaction {
                    val responsavelReq = ResponsavelRequest(body.nomeResponsavel, body.telefoneResponsavel)
                    val novoResponsavel = responsavelService.cadastrarResponsavel(responsavelReq)

                    if (novoResponsavel == null) {
                        statusCode = HttpStatusCode.Conflict
                        message = "Responsável já cadastrado"
                        throw IllegalArgumentException(message)
                    }

                    val alunoReq = AlunosRequest(
                        nomeAluno = body.nomeAluno,
                        dataNascimento = body.dataNascimento,
                        sexoAluno = body.sexoAluno,
                        rgAluno = body.rgAluno,
                        cpfAluno = body.cpfAluno,
                        id_Responsavel = novoResponsavel.id
                    )

                    val novoAluno = alunoService.cadastrarAluno(alunoReq)

                    if (novoAluno == null) {
                        statusCode = HttpStatusCode.Conflict
                        message = "Aluno já cadastrado"
                        throw IllegalArgumentException(message)
                    }
                }

                call.respond(HttpStatusCode.Created, "Aluno e Responsável cadastrados com sucesso!")
            } catch (e: IllegalStateException) {
                statusCode = HttpStatusCode.InternalServerError
                message = e.message ?: "Erro de Validação"
                application.log.info("Cadastro revertido: $message")
            } catch (e: Exception) {
                statusCode = HttpStatusCode.InternalServerError
                message = "Ocorreu um erro interno no servidor"
                application.log.info("Erro inesperado durante o cadastro: ", e)
            }
            call.respond(statusCode, mapOf("message" to message))
        }

        put("/alunos/{id}") {
            val idAluno = call.parameters["id"]?.toIntOrNull()
            if (idAluno == null) {
                call.respond(HttpStatusCode.BadRequest, "ID do aluno inválido")
                return@put
            }

            val body = call.receive<AlunoResponsavelUpdate>()

            var statusCode: HttpStatusCode = HttpStatusCode.OK
            var message = "Aluno e Responsavel atualizados com sucesso!"

            try {
                transaction {
                    val aluno = Alunos.selectAll().where { Alunos.id eq idAluno }.singleOrNull()
                    if (aluno == null) {
                        throw NoSuchElementException("Aluno não encontrado")
                    }
                    val idResponsavel = aluno[Alunos.id_Responsavel]

                    responsavelService.atualizarResponsavel(
                        idResponsavel,
                        body.nomeResponsavel,
                        body.telefoneResponsavel
                    )

                    val alunoUpdateReq = AlunosUpdateRequest(
                        nomeAluno = body.nomeAluno,
                        dataNascimento = body.dataNascimento,
                        sexoAluno = body.sexoAluno,
                        id_Responsavel = idResponsavel
                    )

                    alunoService.atualizarAluno(idAluno, alunoUpdateReq)
                }
            } catch (e: NoSuchElementException) {
                statusCode = HttpStatusCode.NotFound
                message = "Aluno não encontrado com o ID fornecido."
                application.log.error("Erro ao atualizar aluno/responsável: ", e)
            } catch (e: Exception) {
                statusCode = HttpStatusCode.InternalServerError
                message = "Ocorreu um erro inesperado durante a atualização."
                application.log.error("Erro ao atualizar aluno/responsável: ", e)
            }

            call.respond(statusCode, mapOf("message" to message))
        }

        get("/alunos/search") {
            val q = call.request.queryParameters["q"] ?: ""

            if (q.isBlank()) {
                call.respond(
                    HttpStatusCode.BadRequest,
                    "O padrão de busca 'nome, cpf, rg ou nome do responsavel' é obrigatório"
                )
                return@get
            }

            try {
                val resultados = alunoService.pesquisarAluno(q)

                call.respond(HttpStatusCode.OK, resultados)
            } catch (e: Exception) {
                call.respond(HttpStatusCode.InternalServerError, "Ocorreu um erro de pesquisa: ${e.message}")
            }
        }

        get("/alunos") {
            try {
                val listaDeAlunos = alunoService.listarTodosAlunos()

                call.respond(HttpStatusCode.OK, listaDeAlunos)
            } catch (e: Exception) {
                application.log.error("Erro ao listar alunos: ", e)
                call.respond(HttpStatusCode.InternalServerError, "Ocorreu um erro ao buscar os dados.")
            }
        }

        delete("/alunos/{id}") {
            val id = call.parameters["id"]?.toIntOrNull()
            if (id == null) {
                call.respond(HttpStatusCode.BadRequest, "ID do aluno inválido ou ausente.")
                return@delete
            }

            try {
                val resultado = alunoService.deletarAlunoEVerificarResponsavel(id)

                if (resultado.contains("não encontrado")) {
                    call.respond(HttpStatusCode.NotFound, mapOf("mensagem" to resultado))
                } else {
                    call.respond(HttpStatusCode.OK, mapOf("mensagem" to resultado))
                }

            } catch (e: Exception) {
                application.log.error("Erro ao deletar aluno e verificar responsável: ", e)
                call.respond(HttpStatusCode.InternalServerError, "Ocorreu um erro ao deletar.")
            }
        }
    }
}