# Diretório de Arquivos de Cabeçalho do Projeto

Um arquivo de cabeçalho é um arquivo que contém declarações C e definições de macros que serão compartilhadas entre vários arquivos de código-fonte do projeto. Você solicita o uso de um arquivo de cabeçalho no seu arquivo de código-fonte (C, C++, etc.), localizado na pasta `src`, incluindo-o com a diretiva de pré-processamento C `#include`.

```c
// src/main.c

#include "header.h"

int main (void) {
  ...
}
```

Incluir um arquivo de cabeçalho produz os mesmos resultados que copiar o arquivo de cabeçalho em cada arquivo-fonte que precisa dele. Fazer essa cópia manual seria demorado e propenso a erros. Com um arquivo de cabeçalho, as declarações relacionadas aparecem em apenas um lugar. Se for necessário alterá-las, basta modificar o arquivo de cabeçalho, e os programas que o incluem usarão automaticamente a nova versão na próxima recompilação. O arquivo de cabeçalho elimina o trabalho de encontrar e modificar todas as cópias, além do risco de que a falha em encontrar uma cópia possa resultar em inconsistências dentro de um programa.

Em C, a convenção usual é dar aos arquivos de cabeçalho nomes que terminem com `.h`. É mais portátil usar apenas letras, dígitos, traços e sublinhados nos nomes dos arquivos de cabeçalho, e no máximo um ponto.

## Leia mais sobre o uso de arquivos de cabeçalho na documentação oficial do GCC:

- **[Sintaxe de Inclusão](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)**  
- **[Operação de Inclusão](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)**  
- **[Cabeçalhos de Inclusão Única](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)**  
- **[Inclusões Computadas](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)**

[Acesse a documentação completa aqui](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)
