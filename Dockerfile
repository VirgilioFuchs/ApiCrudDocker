# Usa imagem com JDK
FROM eclipse-temurin:24-jdk

# Cria diretório no container
WORKDIR /app

# Copia build do Ktor
COPY build/libs/*.jar app.jar
COPY .env .env

# Define variáveis de ambiente (podem vir do docker-compose ou .env)
ENV PORT=8080
EXPOSE 8080

# Comando para rodar a API
ENTRYPOINT ["java", "-jar", "app.jar"]