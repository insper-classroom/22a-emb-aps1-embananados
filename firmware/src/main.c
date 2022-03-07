#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "musicas.h"

//Definindo tudo do LED da placa:
#define LED_PIO           PIOC                 // periferico que controla o LED
// #
#define LED_PIO_ID        ID_PIOC                 // ID do perif�rico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Definindo tudo do bot�o SW300 da placa:
#define BUT_PIO PIOA
#define BUT_PIO_ID ID_PIOA
#define BUT_PIO_IDX 11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX) // esse j� est� pronto.

// Definindo tudo do bot�o 1:
#define BUT1_PIO PIOD
#define BUT1_PIO_ID ID_PIOD
#define BUT1_PIO_IDX 28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX) // esse j� est� pronto.

// Definindo tudo do LED 1:
#define LED1_PIO           PIOA                 // periferico que controla o LED
// #
#define LED1_PIO_ID        ID_PIOA                 // ID do perif�rico PIOC (controla LED)
#define LED1_PIO_IDX       0                    // ID do LED no PIO
#define LED1_PIO_IDX_MASK  (1 << LED1_PIO_IDX)   // Mascara para CONTROLARMOS o LED


// Definindo tudo do bot�o 2:
#define BUT2_PIO PIOC
#define BUT2_PIO_ID ID_PIOC
#define BUT2_PIO_IDX 31
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX) // esse j� est� pronto.

// Definindo tudo do LED 2:
#define LED2_PIO           PIOC                 // periferico que controla o LED
// #
#define LED2_PIO_ID        ID_PIOC                 // ID do perif�rico PIOC (controla LED)
#define LED2_PIO_IDX       30                    // ID do LED no PIO
#define LED2_PIO_IDX_MASK  (1 << LED2_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Definindo tudo do bot�o 3:
#define BUT3_PIO PIOA
#define BUT3_PIO_ID ID_PIOA
#define BUT3_PIO_IDX 19
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX) // esse j� est� pronto.

// Definindo tudo do LED 3:
#define LED3_PIO           PIOB                 // periferico que controla o LED
// #
#define LED3_PIO_ID        ID_PIOB                 // ID do perif�rico PIOC (controla LED)
#define LED3_PIO_IDX       2                    // ID do LED no PIO
#define LED3_PIO_IDX_MASK  (1 << LED3_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Buzzer
#define BUZ_PIO      PIOD
#define BUZ_PIO_ID   ID_PIOD
#define BUZ_IDX      30
#define BUZ_IDX_MASK (1 << BUZ_IDX)

volatile char but_flag; 
volatile int tocando;

typedef struct{
	int tempo;
	int wholenote;
	int notes;
	int *melody;
} music;

void but_callback(void)
{
	but_flag = 1;
	
}

void tone(int freq, int time){
	// a freq t� em segundos e time em ms
	int n = (double) freq * ((double) time/100);
	float T = (1.0/freq) * 1E6; //ms
	
	for (int i = 0; i <= n; i++){
		pio_set(BUZ_PIO, BUZ_IDX_MASK);
		delay_us(T/2);
		pio_clear(BUZ_PIO, BUZ_IDX_MASK);
		delay_us(T/2);
	}
}

void play_music(music *musica){
	if (tocando){
		for (int thisNote = 0; thisNote < ((*musica).notes)*2; thisNote = thisNote + 2) {
			if (!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK) && tocando == 1){
				tocando = 0;
				delay_ms(200);
				break;
			}
			// calculates the duration of each note
			int divider = (*musica).melody[thisNote + 1];
			
			int noteDuration = ((*musica).wholenote) / abs(divider);
			if (divider < 0) {
				noteDuration *= 1.5; // increases the duration in half for dotted notes
			}
			
			if ((*musica).melody[thisNote] == 0){
				// Wait for the specief duration before playing the next note.
				delay_ms(noteDuration);
			}
			else{
				// we only play the note for 90% of the duration, leaving 10% as a pause
				tone((*musica).melody[thisNote], noteDuration * 0.9);
				
				// Wait for the specief duration before playing the next note.
				delay_ms(10);
			}
			
		}
		
	}
	
}

void io_init(void)
{
	pmc_enable_periph_clk(BUZ_PIO_ID);
	pio_configure(BUZ_PIO, PIO_OUTPUT_0, BUZ_IDX_MASK, PIO_DEFAULT);

	// Configura led
	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_configure(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK, PIO_DEFAULT);

	// Inicializa clock do perif�rico PIO responsavel pelo botao
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);

	// Configura PIO para lidar com o pino do bot�o como entrada
	// com pull-up
	//pio_configure(BUT_PIO, PIO_INPUT, BUT_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT1_PIO, BUT1_PIO_IDX_MASK, 60);

	pio_configure(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT2_PIO, BUT2_PIO_IDX_MASK, 60);
	
	pio_configure(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT3_PIO, BUT3_PIO_IDX_MASK, 60);

	// Configura interrup��o no pino referente ao botao e associa
	// fun��o de callback caso uma interrup��o for gerada
	// a fun��o de callback � a: but_callback()
	pio_handler_set(BUT1_PIO,
	BUT1_PIO_ID,
	BUT1_PIO_IDX_MASK,
	PIO_IT_EDGE,
	but_callback);

	pio_handler_set(BUT2_PIO,
	BUT2_PIO_ID,
	BUT2_PIO_IDX_MASK,
	PIO_IT_EDGE,
	but_callback);
	
	pio_handler_set(BUT3_PIO,
	BUT3_PIO_ID,
	BUT3_PIO_IDX_MASK,
	PIO_IT_EDGE,
	but_callback);

	//PIO_IT_RISE_EDGE, PIO_IT_FALL_EDGE
	// Ativa interrup��o e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT1_PIO);

	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT2_PIO);
	
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT3_PIO);
	
	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais pr�ximo de 0 maior)
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 4); // Prioridade 4
}

int main (void)
{
	board_init();
	sysclk_init();
	delay_init();

	io_init();

  // Init OLED
	gfx_mono_ssd1306_init();
	
	/* Disable the watchdog */

	WDT->WDT_MR = WDT_MR_WDDIS;

	

	int tempo_starwars = 108;
	int notes_starwars = sizeof(melody_starwars) / sizeof(melody_starwars[0]) / 2;
	int wholenote_starwars = (6000 * 4)/tempo_starwars; // est� em ms

	music starwars;
	music nokia;
	
	
	starwars.tempo = 108;
	starwars.melody = &melody_starwars[0];
	starwars.wholenote = (6000 * 4)/(starwars.tempo);
	starwars.notes = sizeof(melody_starwars) / sizeof(melody_starwars[0]) / 2;


	nokia.tempo = 180;
	nokia.melody = &melody_nokia[0];
	nokia.wholenote = (6000 * 4)/(nokia.tempo);
	nokia.notes = sizeof(melody_nokia) / 4 / 2;
	
	tocando = 0;
  /* Insert application code here, after the board has been initialized. */
	while(1){	
		if (!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK) && tocando == 0){
			tocando = 1;
			delay_ms(200);
			play_music(&starwars);
		} 
				
	}
		
}
