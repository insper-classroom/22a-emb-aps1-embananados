#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "musicas.h"

//Definindo tudo do LED da placa:
#define LED_PIO           PIOC                 // periferico que controla o LED
// #
#define LED_PIO_ID        ID_PIOC                 // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Definindo tudo do botão SW300 da placa:
#define BUT_PIO PIOA
#define BUT_PIO_ID ID_PIOA
#define BUT_PIO_IDX 11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX) // esse já está pronto.

// Definindo tudo do botão 1:
#define BUT1_PIO PIOD
#define BUT1_PIO_ID ID_PIOD
#define BUT1_PIO_IDX 28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX) // esse já está pronto.

// Definindo tudo do LED 1:
#define LED1_PIO           PIOA                 // periferico que controla o LED
// #
#define LED1_PIO_ID        ID_PIOA                 // ID do periférico PIOC (controla LED)
#define LED1_PIO_IDX       0                    // ID do LED no PIO
#define LED1_PIO_IDX_MASK  (1 << LED1_PIO_IDX)   // Mascara para CONTROLARMOS o LED


// Definindo tudo do botão 2:
#define BUT2_PIO PIOC
#define BUT2_PIO_ID ID_PIOC
#define BUT2_PIO_IDX 31
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX) // esse já está pronto.

// Definindo tudo do LED 2:
#define LED2_PIO           PIOC                 // periferico que controla o LED
// #
#define LED2_PIO_ID        ID_PIOC                 // ID do periférico PIOC (controla LED)
#define LED2_PIO_IDX       30                    // ID do LED no PIO
#define LED2_PIO_IDX_MASK  (1 << LED2_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Definindo tudo do botão 3:
#define BUT3_PIO PIOA
#define BUT3_PIO_ID ID_PIOA
#define BUT3_PIO_IDX 19
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX) // esse já está pronto.

// Definindo tudo do LED 3:
#define LED3_PIO           PIOB                 // periferico que controla o LED
// #
#define LED3_PIO_ID        ID_PIOB                 // ID do periférico PIOC (controla LED)
#define LED3_PIO_IDX       2                    // ID do LED no PIO
#define LED3_PIO_IDX_MASK  (1 << LED3_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Buzzer
#define BUZ_PIO      PIOD
#define BUZ_PIO_ID   ID_PIOD
#define BUZ_IDX      30
#define BUZ_IDX_MASK (1 << BUZ_IDX)


typedef struct{
	int tempo;
	int wholenote;
	int notes;
	int melody[1000];
	} music;

void tone(int freq, int time){
	int n = (double) freq * ((double) time/1000);
	float T = (1.0/freq) * 1E6; //ms
	
	for (int i = 0; i <= n; i++){
		pio_set(BUZ_PIO, BUZ_IDX_MASK);
		delay_us(T/2);
		pio_clear(BUZ_PIO, BUZ_IDX_MASK);
		delay_us(T/2);
	}
}

void io_init(void){
	pmc_enable_periph_clk(BUZ_PIO_ID);
	pio_configure(BUZ_PIO, PIO_OUTPUT_0, BUZ_IDX_MASK, PIO_DEFAULT);

}

void play_music(music *musica){
	for (int thisNote = 0; thisNote < ((*musica).notes)*2; thisNote = thisNote + 2) {
		// calculates the duration of each note
		int divider = (*musica).melody[thisNote + 1];
			
		int noteDuration = ((*musica).wholenote) / abs(divider);
		if (divider < 0) {
			noteDuration *= 1.5; // increases the duration in half for dotted notes
		}
			
		if ((*musica).melody[thisNote] == 0){
			// Wait for the specief duration before playing the next note.
			delay_us(noteDuration);
		}
		else{
			// we only play the note for 90% of the duration, leaving 10% as a pause
			tone((*musica).melody[thisNote], noteDuration * 0.9);
				
			// Wait for the specief duration before playing the next note.
			delay_us(noteDuration);
		}
			
	}
		
}


int main (void)
{
	board_init();
	io_init();

	sysclk_init();
	delay_init();

  // Init OLED
	gfx_mono_ssd1306_init();
	
	music *starwars;
	music *nokia;
	
	music starwarsProperties;
	starwars = &starwarsProperties;
		
	music nokiaProperties;
	nokia = &nokiaProperties;
	
	(*starwars).tempo = 108;
	(*starwars).melody[1000] = melody_starwars;
	(*starwars).wholenote = (6000 * 4)/((*starwars).tempo);
	(*starwars).notes = sizeof(melody_starwars) / sizeof(melody_starwars[0]) / 2;

	int tempo = 108;
	int wholenote = (6000 * 4)/tempo;
	int notes = sizeof(melody_starwars) / sizeof(melody_starwars[0]) / 2;

	(*nokia).tempo = 180;
	(*nokia).melody[1000] = melody_nokia;
	(*nokia).wholenote = (6000 * 4)/((*nokia).tempo);
	(*nokia).notes = sizeof((*nokia).melody) / sizeof((*nokia).melody[0]) / 2;
	

	
  /* Insert application code here, after the board has been initialized. */
	while(1){
		//play_music(starwars);
		
		for (int thisNote = 0; thisNote < notes*2; thisNote = thisNote + 2) {
			// calculates the duration of each note
			int divider = melody_starwars[thisNote + 1];
			
			int noteDuration = (wholenote) / abs(divider);
			if (divider < 0) {
				noteDuration *= 1.5; // increases the duration in half for dotted notes
			}
			
			if (melody_starwars[thisNote] == 0){
				// Wait for the specief duration before playing the next note.
				delay_us(noteDuration);
			}
			else{
				// we only play the note for 90% of the duration, leaving 10% as a pause
				tone(melody_starwars[thisNote], noteDuration * 0.9);
				
				// Wait for the specief duration before playing the next note.
				delay_us(noteDuration);
			}
			
		}
	}
}
