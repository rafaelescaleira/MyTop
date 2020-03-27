<div align = "center">
<img src="Assets/logo.png" width="10%" />
</div>

# <div align = "center"> MyTop </div>

<p></p>

<p align="center">
<img src="https://img.shields.io/badge/Linguagem-C-orange.svg" alt="Linguagem C"/>
</p>

A feramenta deve listar processos ativos no sistema operacional, de maneira similar à ferramenta top, apresentando para cada um deles:
* PID: identificador do processo no sistema.
* USER: nome do usuário dono do processo.
* PR: a prioridade do processo a ser utilizada para o escalonamento.
* S: o estado do processo.
* %CPU: porcentagem de utilização de CPU do processo desde a última atualização da métrica. - TIME: tempo total de CPU do processo desde sua criação.
* COMMAND: a linha de comando utilizada para iniciar o processo.
Ao menos 15 processos devem ser listados em MyTop. A ordem de apresentação deve privilegiar a visualização dos processos que consomem mais CPU. **O intervalo de atualização das informações apresentadas deve ser o menor possível**.
**Implementação**
O trabalho deve ser implementado em C e, para prover a interface texto, pode-se utilizar a biblioteca ncurses (https://en.wikipedia.org/wiki/Ncurses).
Toda a ferramenta deve ser feita utilizando processos (não é permitido o uso de threads!). Para a comunicação entre esses processos, pode-se utilizar memória compartilhada, pipes, arquivos... Cada grupo deve encontrar sua maneira de implementar essa comunicação (consulte a seção sobre Comunicação entre Processos (IPC) do livro do Silberschatz para detalhes).
As informações devem ser obtidas a partir do diretório /proc do Linux (man proc). Este diretório consiste em uma interface de leitura para as estruturas do kernel que manipulam informações dos processos. No diretório /proc há uma listagem de todos os processos ativos do sistema. Cada diretório com um número representa um processo.
O arquivo /proc/%pid/stat, onde %pid deve ser substituído pelo identificador do processo a ser monitorado, apresenta muitas das informações pedidas. Para acessar o conteúdo dos arquivos, use o comando cat. Por exemplo cat /proc/1234/stat.
