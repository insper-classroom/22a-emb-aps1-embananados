# 21a-emb-aps1

Embarcados - APS 1 - Musical!

Para maiores informações acesse:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

Issues serão abertos neste repositório para guiar o desenvolvimento
da dupla. **Vocês não devem fechar os issues, apenas a equipe de professores!**, porém devem referenciar nos commits quando um issue 
foi concluído! Isso gerará um PR no classroom que será avaliado pela equipe.

## Autores do Projeto :black_nib::

:sassy_man: Bernardo Cunha Capoferri.

:sassy_woman: Lívia Sayuri Makuta.

## Linguagem utilizada :desktop_computer::
<img src="https://img.shields.io/static/v1?label=Code&message=C&color=important&style=plastic&labelColor=black&logo=c"/>  
 &nbsp; &nbsp; :heavy_check_mark: C.
                                                                                                                                       
## Ferramental utilizado:wrench::

 &nbsp; &nbsp; :heavy_check_mark: Um microcontrolador SAME70 da Microchip;
 
 &nbsp; &nbsp; :heavy_check_mark: A placa de extensão OLED1 Xplained Pro;
 
 &nbsp; &nbsp; :heavy_check_mark: Piezo Buzzer;                
 
 &nbsp; &nbsp; :heavy_check_mark: Jumpers fêmea-fêmea.
                                                                                                                                                                                      
## Documentação :bookmark_tabs::

| Função  | PINO (ex: PA11) |
|---------|-----------------|
| BUZZER  |     PD30   e GND         |
| START/ PAUSE   |     BUT1 (PD28)            |
| SELEÇÃO |     BUT2 (PC31)           |

## Imagem da montagem :camera_flash::

![foto_montagem](https://user-images.githubusercontent.com/62647438/158377963-65ad2f9a-d91f-4b8d-ae89-054cf75126f7.jpeg)

![foto_montagem2](https://user-images.githubusercontent.com/62647438/158377994-96d5d4be-df68-45a7-badd-d758d49227fb.jpeg)

:exclamation: :heavy_exclamation_mark: O jumper laranja faz ligação com o pino energizado e o jumper preto faz ligação com o GND.

Como pode ser visto, a parte positiva do Buzzer foi conectada no pino PD30, enquanto a outra parte foi conectada no pino do GND (Ground) - que fica acima do pino PD30, porém no primeiro nível de pinos. 

Assim, basta utilizar dois jumpers fêmea-fêmea e conectar as saídas dos pinos no polo positivo e negativo do buzzer. Feito isso, basta rodar o código que o programa estará funcionando.
 
## Vídeo do projeto :film_strip::

[![APS1 de Embarcados](https://img.youtube.com/vi/fg6qixo6t4E/0.jpg)](https://youtu.be/fg6qixo6t4E "APS1 de Embarcados")

 &nbsp; &nbsp; :heavy_check_mark: Para utilizar o projeto, após rodar o programa, basta apertar o botão 1 para tocar e, uma vez que estiver tocando, basta apertá-lo outra vez para pausar.

 &nbsp; &nbsp; :heavy_check_mark: Para trocar de música, basta apertar o botão 2, e conforme as músicas mudam, os LED's 1,2 e 3 indicarão visualmente qual música está sendo selecionada:
  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; :white_medium_small_square:		A música 1 (Star Wars theme) acende o LED 1.
  
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; :white_medium_small_square:	A música 2 (Nokia Ringtone) acende o LED 2.
   
 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; :white_medium_small_square:	A música 3 (Badinerie) acende o LED 3.
  
 &nbsp; &nbsp; :heavy_check_mark: E conforma as músicas tocam, o LED da placa irá piscar de acordo com as notas da música. 

 &nbsp; &nbsp; :heavy_check_mark: Por fim, no LCD estarão indicados o nome da música que está sendo tocada e a barra de progresso que mostra a duração de cada música.  

## Como o software foi estruturado :file_folder::	

O software foi estruturado em quatro arquivos: `musicas.h`, `aps1.h`, `aps1.c` e `main.c`. 

 &nbsp; &nbsp; :heavy_check_mark: No arquivo `musicas.h` foram definidas as notas e os arrays de cada conjunto de notas, as melodias. Sendo assim, como são três músicas, foram montados três arrays de melodia.

 &nbsp; &nbsp; :heavy_check_mark: Já no `aps1.h` foram definidos todos os botões, LED's e o buzzer utilizado para conseguir utilizar os pinos e botões configurados. Além disso, nesse mesmo arquivo, outros #defines foram feitos para as constantes usadas, protótipos das funções usadas no trabalho foram definidos e a struct das músicas também.

 &nbsp; &nbsp; :heavy_check_mark: No `aps1.c` por sua vez, as funções declaradas no aps1.h foram escritas, ou seja, todas as funções utilizadas no trabalho estão lá. Desde os callsbacks's e funções que inicializam os LED's e botões, até as funções para tocar e pausar as músicas.

 &nbsp; &nbsp; :heavy_check_mark: Por fim, no arquivo `main.c` estão os vetores de structs (ponteiros) das músicas e a função principal main() que irá rodar todas as outras funções que foram definidas no `aps1.c` para o funcionamento do projeto.


## Músicas e Direitos autorais :musical_score:: 

As músicas utilizadas na APS são:

 &nbsp; &nbsp; :heavy_check_mark: Star Wars Main Theme

 &nbsp; &nbsp; :heavy_check_mark: Nokia Ringtone

 &nbsp; &nbsp; :heavy_check_mark: Badinerie - Bach 

Todas as músicas foram retiradas do repositório que pode ser encontrado no link a seguir: https://github.com/robsoncouto/arduino-songs/ . Além disso, a função
`play_music` que se encontra na `aps1.c` foi adaptada desse mesmo repositório citado anteriormente. 

## Checagem dos conceitos feitos:

### C
- [x] Repositório contém README.mdcom ligações elétrica e passos de como usar o projeto, assim como link para o vídeo e referência a outros códigos
- [x] Funcionalidade de PAUSE/ PLAY
- [x] Botão de seleção musical
- [x] Indicação visual de qual música foi selecionada
- [x] Reproduz duas músicas (de forma inteligível)
- [x] Utiliza músicas do repositório indicado
- [x] Fecha todos os issues que forem abertos pela equipe

### C +
- [x] LED piscando de acordo com a música (adicionar um LED ao projeto)

### B
- [x] Música separadas em arquivos .h
- [x] Utiliza struct para organizar as músicas
- [x] Código organizado em funções e que recebem struct contendo música
- [x] Exibir o nome da música no OLED
- [ ] Fecha todos os issues que forem abertos após a entrega (ainda não foram abertos esses issues)

### B +

- [x] README.md explica como o software foi estruturado
- [x] Faz uso de #define sempre que possível 
- [x] Terceira música
- [x] Exibir uma barra com a indicação do progresso da música

### A

- [x] Utiliza interrupção nos botões
- [x] Cria um arquivo .c .h com as funções de reprodução musical

### A +

- [x] Músicas organizadas em vetores de structs (ponteiros)

