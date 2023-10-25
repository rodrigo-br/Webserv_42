[![English](https://upload.wikimedia.org/wikipedia/en/thumb/a/a4/Flag_of_the_United_States.svg/22px-Flag_of_the_United_States.svg.png)](README.md) **English**
<h1 align=center>Webserv</h1>

## Sobre a implementação

Um projeto para colocar fotos dos nossos cães na web.

<h4 align=center>
	<b>Emily e Nico</b>
</h4>
<p align="center">
    <img src="wwwroot/assets/Dogs.png" alt="Dogs" style="display: block; margin: auto;">
</p>

<h4 align=center>
	<b>Arya</b>
</h4>
<p align="center">
    <img src="wwwroot/assets/arya2.png" alt="Arya" style="display: block; margin: auto;">
</p>

## Webserv: Um Servidor HTTP em C++98

O projeto Webserv é um servidor HTTP escrito em C++98, seguindo o protocolo HTTP (Hypertext Transfer Protocol). HTTP é um protocolo de aplicação que serve como base para a comunicação de dados na World Wide Web, permitindo a distribuição de documentos de hipertexto com hiperlinks para recursos acessíveis por meio de navegadores da web.

## Objetivo
O principal objetivo deste projeto é implementar um servidor HTTP eficiente e não bloqueante que possa ser configurado por meio de um arquivo de configuração. Ele pode definir portas, hosts, páginas de erro padrão, limites de tamanho do corpo da solicitação e muito mais. O servidor suporta métodos HTTP, incluindo GET, POST e DELETE, tornando-o adequado para servir páginas da web e lidar com vários pedidos HTTP.

## Requisitos

Para compilar e executar este projeto, você precisará dos seguintes itens:

- Compilador C++ com suporte para o padrão C++98 (recomenda-se GCC ou Clang).
    ```sh
    sudo apt update && sudo apt install g++
    ```
- Biblioteca libcurl (para recursos de solicitação HTTP).
    ```sh
    sudo apt update && sudo apt install libcurl4-openssl-dev
    ```

## Compilação

Para compilar o projeto, siga estas etapas:

1. Clone este repositório para o seu sistema local.
2. Verifique se você tem um compilador C++ instalado em sua máquina.
3. Verifique se você tem a biblioteca libcurl instalada em seu sistema.
4. Navegue até o diretório raiz do projeto (onde está localizado o Makefile).
5. Execute o comando `make` para compilar o projeto.

## Como Executar o Webserv

 ```sh
./webserv [arquivo de configuração]
```

## Sobre a configuração

- Arquivo de Configuração Padrão

Existe um arquivo de configuração padrão no caminho conf/default.conf que contém as configurações iniciais do servidor.
```sh
./webserv conf/default.conf
```
- Extensão de Arquivo .conf

Todos os arquivos de configuração devem ter a extensão .conf para que o sistema os reconheça corretamente como arquivos de configuração.

- Comentários Restritos

É importante enfatizar que os arquivos de configuração não devem incluir comentários, e nem devem conter ";".

## Configuração do Servidor

#### Porta 

Para especificar a porta na qual o servidor irá escutar, use a diretiva `listen` seguida pelo número de porta desejado.
```
listen 8000
```

#### Diretório Raiz 
Para definir o diretório raiz para o servidor, use a diretiva "root" e especifique o caminho para o diretório desejado.

```
root wwwroot
```
#### Nomes do Servidor 

Para definir os nomes do servidor, use a diretiva "server_names" seguida pelos nomes de servidor desejados, cada um em uma linha separada:

```
server_names lade-lim.42.fr
server_names localhost
```

#### Limite de Tamanho do Corpo da Solicitação
Para estabelecer um limite para o tamanho do corpo da solicitação, use a diretiva "body_size_limit" e especifique o valor desejado.
```
body_size_limit 6666666
```
#### Página de Erro 

Para especificar uma página de erro personalizada para um erro específico, mencione o erro que você deseja personalizar, seguido do código de erro desejado, e do caminho para a nova página de erro:

```
404 /index.html;
```

#### Localizações

Location com definição de métodos 
```
location / {
    http_methods 1; # Permite apenas o método GET (1)
    index index.html; # Define o arquivo de índice para esta localização
}
location / {
    http_methods 2; # Permite apenas o método POST (2)
    index index.html; # Define o arquivo de índice para esta localização
}

location / {
    http_methods 4; # Permite apenas o método DELETE (4)
    index index.html; # Define o arquivo de índice para esta localização
}

location / {
    http_methods 5; # Permite os métodos GET (1) e DELETE (4)
    index index.html; # Define o arquivo de índice para esta localização
}

location / {
    http_methods 6; # Permite os métodos POST (2) e DELETE (4)
    index index.html; # Define o arquivo de índice para esta localização
}

location / {
    http_methods 7; # Permite os métodos GET (1), POST (2), e DELETE (4)
    index index.html; # Define o arquivo de índice para esta localização
}
```

Location com CGI
```
location /cgi-bin {
    http_methods 7; # Permite os métodos GET (1), POST (2), e DELETE (4)
    index cavalinho.html; # Define o arquivo de índice para esta localização
    cgi_pass .py; # Especifica que os arquivos .py serão executados como CGI nesta localização
}
```

 Location com listagem_de_diretório
```
location /directory {
    directory_listing on; # Habilita a listagem de diretório para esta localização
}
```

 Location com redirecionamento

```
    location /redirect {
        redirect index.html; # Define um redirecionamento para index.html
    }
```


