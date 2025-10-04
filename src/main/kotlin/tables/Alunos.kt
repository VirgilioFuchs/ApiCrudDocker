package com.anglo.tables

import org.jetbrains.exposed.sql.Table
import org.jetbrains.exposed.sql.javatime.date

object Alunos : Table("alunos") {
    val id = integer("id").autoIncrement()
    val nomeAluno = varchar("nomeAluno", 100)
    val dataNascimento = date("dataNascimento")
    val sexoAluno = char("sexoAluno", 1)
    val rgAluno = varchar("rgAluno", 12)
    val cpfAluno = varchar("cpfAluno", 14)
    val id_Responsavel = integer("id_Responsavel").references(Responsavel.id)
    override val primaryKey = PrimaryKey(id)
}