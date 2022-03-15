/*
 * aps1.c
 *
 * Created: 14/03/2022 16:39:51
 *  Author: berna
 */ 

#include "asf.h"
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "aps1.h"

void but1_callback(void)
{
	if(!but1_flag){
		but1_flag = 1;
	}
	else{
		but1_flag = 0;
	}

}

void but2_callback(void)
{
	but2_flag = 1;
}

void but3_callback(void)
{
	but3_flag = 1;
}


void io_init(void)
{
	pmc_enable_periph_clk(BUZ_PIO_ID);
	pio_configure(BUZ_PIO, PIO_OUTPUT_0, BUZ_IDX_MASK, PIO_DEFAULT);

	// Configura led
	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_configure(LED1_PIO, PIO_OUTPUT_0, LED1_PIO_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_configure(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(LED3_PIO_ID);
	pio_configure(LED3_PIO, PIO_OUTPUT_0, LED3_PIO_IDX_MASK, PIO_DEFAULT);

	// Inicializa clock do perifï¿½rico PIO responsavel pelo botao
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);

	// Configura PIO para lidar com o pino do botï¿½o como entrada
	// com pull-up
	//pio_configure(BUT_PIO, PIO_INPUT, BUT_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT1_PIO, BUT1_PIO_IDX_MASK, 60);

	pio_configure(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT2_PIO, BUT2_PIO_IDX_MASK, 60);
	
	pio_configure(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT3_PIO, BUT3_PIO_IDX_MASK, 60);

	// Configura interrupï¿½ï¿½o no pino referente ao botao e associa
	// funï¿½ï¿½o de callback caso uma interrupï¿½ï¿½o for gerada
	// a funï¿½ï¿½o de callback ï¿½ a: but_callback()
	pio_handler_set(BUT1_PIO,
	BUT1_PIO_ID,
	BUT1_PIO_IDX_MASK,
	PIO_IT_FALL_EDGE,
	but1_callback);

	pio_handler_set(BUT2_PIO,
	BUT2_PIO_ID,
	BUT2_PIO_IDX_MASK,
	PIO_IT_EDGE,
	but2_callback);
	
	pio_handler_set(BUT3_PIO,
	BUT3_PIO_ID,
	BUT3_PIO_IDX_MASK,
	PIO_IT_EDGE,
	but3_callback);

	//PIO_IT_RISE_EDGE, PIO_IT_FALL_EDGE
	// Ativa interrupï¿½ï¿½o e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT1_PIO);

	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT2_PIO);
	
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT3_PIO);
	
	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais prï¿½ximo de 0 maior)
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 4); // Prioridade 4
}


void change_LED(int *num){
	if(*num == 0){
		pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	}
	else if(*num ==1){
		pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	}
	else if(*num ==2){
		pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
	}
}

void tone(int freq, int time, int *num){
	// a frequência em segundos e time em ms
	int n = (double) freq * ((double) time/100);
	float T = (1.0/freq) * 1E6; //us
	
	for (int i = 0; i <= n;){
		if(but1_flag && !mudar){
			pio_set(BUZ_PIO, BUZ_IDX_MASK);
			pio_set(LED_PIO, LED_PIO_IDX_MASK);
			delay_us(T/2);
			pio_clear(BUZ_PIO, BUZ_IDX_MASK);
			pio_clear(LED_PIO, LED_PIO_IDX_MASK);
			delay_us(T/2);
			pio_set(LED_PIO, LED_PIO_IDX_MASK);
			i++;
		}
		if (but2_flag){
			mudar = 1;
			if(*num < 2){
				*num = *num + 1;
			}
			else{
				*num = 0;
			}
			delay_ms(200);
			but2_flag = 0;
		}
		
		change_LED(num);
		
		if(but1_flag && mudar){  // se ele tivesse pausado e você quer mudar pra próxima música, garante que a última nota da música anterior não vai ser tocada
			pio_set(LED_PIO, LED_PIO_IDX_MASK);
			break;
		}
	}
	if(mudar){
		pio_set(LED_PIO, LED_PIO_IDX_MASK);
		return;
	}
}

void play_music(music *musica, int *num){
	int x = 94;
	int y = 12;
	int i = 1;

	gfx_mono_generic_draw_filled_rect(x+1, y+1, 32, 9, GFX_PIXEL_CLR);
	gfx_mono_generic_draw_rect(x, y, 33, 10, GFX_PIXEL_SET);
	
	for (int thisNote = 0; thisNote < ((*musica).notes)*2; thisNote = thisNote + 2) {
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
			gfx_mono_generic_draw_filled_rect(x, y, ((double)32/musica->notes)+((double)32/musica->notes*i), 10, GFX_PIXEL_SET);
			tone((*musica).melody[thisNote], noteDuration * 0.9, num);
			i++;
			
			
			if (mudar){
				return;
			}
			
			// Wait for the specief duration before playing the next note.
			delay_ms(10);
		}
		
	}
	delay_ms(100);
	
}


void draw(int num_musica){
	if (num_musica == 0){
		gfx_mono_draw_string("             ", 0,10, &sysfont);
		gfx_mono_draw_string("Star Wars", 0,10, &sysfont);
	}
	else if (num_musica == 1){
		gfx_mono_draw_string("             ", 0,10, &sysfont);
		gfx_mono_draw_string("Nokia", 0,10, &sysfont);
		} else if (num_musica == 2){
		gfx_mono_draw_string("             ", 0,10, &sysfont);
		gfx_mono_draw_string("Badinerie", 0,10, &sysfont);
	}
}
