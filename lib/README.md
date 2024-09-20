# Diretório de Bibliotecas Específicas do Projeto

Este diretório é destinado para bibliotecas específicas (privadas) do projeto. O PlatformIO irá compilar essas bibliotecas em bibliotecas estáticas e vinculá-las ao arquivo executável.

O código-fonte de cada biblioteca deve ser colocado em seu próprio diretório separado ("lib/nome_da_sua_biblioteca/[aqui estão os arquivos-fonte]").

Por exemplo, veja a estrutura das seguintes bibliotecas `Foo` e `Bar`:

```
|--lib
|  |
|  |--Bar
|  |  |--docs
|  |  |--examples
|  |  |--src
|  |     |- Bar.c
|  |     |- Bar.h
|  |  |- library.json (opcional, opções de build personalizadas, etc) [mais informações](https://docs.platformio.org/page/librarymanager/config.html)
|  |
|  |--Foo
|  |  |- Foo.c
|  |  |- Foo.h
|  |
|  |- README --> ESTE ARQUIVO
|
|- platformio.ini
|--src
   |- main.c
```

E o conteúdo de `src/main.c`:

```c
#include <Foo.h>
#include <Bar.h>

int main (void) {
  ...
}
```

O Localizador de Dependências de Bibliotecas do PlatformIO encontrará automaticamente as bibliotecas dependentes ao escanear os arquivos-fonte do projeto.

## Mais informações sobre o Localizador de Dependências de Bibliotecas do PlatformIO:

- **[PlatformIO Library Dependency Finder](https://docs.platformio.org/page/librarymanager/ldf.html)**
