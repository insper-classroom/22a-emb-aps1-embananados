# 21a-emb-aps1

Embarcados - APS 1 - Musical!

Para maiores informações acesse:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

Issues serão abertos neste repositório para guiar o desenvolvimento
da dupla. **Vocês não devem fechar os issues, apenas a equipe de professores!**, porém devem referenciar nos commits quando um issue 
foi concluído! Isso gerará um PR no classroom que será avaliado pela equipe.


## Linguagem utilizada :desktop_computer::
<img src="https://img.shields.io/static/v1?label=Code&message=C&color=important&style=plastic&labelColor=black&logo=c"/>  
-C.
                                                                                                                                       
## Ferramental utilizado:wrench::
- Um microcontrolador SAME70 da Microchip;
- A placa de extensão OLED1 Xplained Pro;
- Piezo Buzzer.                                                                                                                                
                                                                                                                                                                                      

## Documentação :bookmark_tabs::

| Função  | PINO (ex: PA11) |
|---------|-----------------|
| BUZZER  |     PD30            |
| START   |     BUT1 (PD28)            |
| SELEÇÃO |     BUT2 (PC31)           |

## Imagem da montagem :camera_flash::

![foto_montagem](https://user-images.githubusercontent.com/62647438/158377963-65ad2f9a-d91f-4b8d-ae89-054cf75126f7.jpeg)

![foto_montagem2](https://user-images.githubusercontent.com/62647438/158377994-96d5d4be-df68-45a7-badd-d758d49227fb.jpeg)

Obs: O jumper laranja faz ligação com o pino energizado e o jumper preto faz ligação com o GND.

Como pode ser visto, a parte positiva do Buzzer foi conectada no pino PD30, enquanto a outra parte foi conectada no pino do GND (Ground) - que fica acima do pino PD30, porém
no primeiro nível de pinos. Assim, basta utilizar dois jumpers fêmea-fêmea e conectar as saídas dos pinos no polo positivo e negativo do buzzer. Feito isso, basta rodar o código que o programa estará funcionando.
 
## Vídeo do projeto :film_strip::

TODO: Inserir link para vídeo do projeto funcionando

* Para utilizar o projeto, após rodar o programa, basta apertar o botão 1 para tocar e, uma vez que estiver tocando, basta apertá-lo outra vez para pausar.
* Para trocar de música, basta apertar o botão 2, e conforme as músicas mudam, os LED's 1,2 e 3 indicarão visualmente qual música está sendo selecionada:
  * A música 1 (Star Wars theme) acende o LED 1.
  * A música 2 (Nokia Ringtone) acende o LED 2.
  * A música 3 (Badinerie) acende o LED 3.
* E conforma as músicas tocam, o LED da placa irá piscar de acordo com as notas da música. 
* Por fim, no LCD estarão indicados o nome da música que está sendo tocada e a barra de progresso que mostra a duração de cada música.  

## Como o software foi estruturado :file_folder::	

O software foi estruturado em quatro arquivos: musicas.h, aps1.h, aps1.c e main.c . 

* No arquivo musicas.h foram definidas as notas e os arrays de cada conjunto de notas, as
melodias. Sendo assim, como são três músicas, foram montados três arrays de melodia.

* Já no aps1.h foram definidos todos os botões, LED's e o buzzer utilizado para conseguir utilizar os pinos e botões configurados. Além disso, nesse mesmo
arquivo, os protótipos das funções usadas no trabalho foram definidos e a struct das músicas também.

* No aps.c por sua vez, as funções declaradas no aps1.h foram escritas, ou seja, todas as funções utilizadas no trabalho estão lá. Desde os callsbacks's até as funções para
tocar as músicas.

* Por fim, no arquivo main.c estão os vetores de structs (ponteiros) e a função principal main() que irá rodar todas as outras funções que foram definidas no aps.c para o 
funcionamento do projeto.


## Músicas e Direitos autorais :musical_score:: 

As músicas utilizadas na APS são:

- Star Wars Main Theme
- Nokia Ringtone
- Badinerie - Bach 

Todas as músicas foram retiradas do repositório que pode ser encontrado no link a seguir: https://github.com/robsoncouto/arduino-songs/ .
