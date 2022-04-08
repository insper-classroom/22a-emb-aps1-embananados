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
#include "string.h"

void but1_callback(void)
{
	but1_flag =! but1_flag;
}

void but2_callback(void)
{
	but2_flag = 1;
}

void but3_callback(void)
{
	but3_flag = 1;
}

void configure_pio_output(Pio *pio, const pio_type_t ul_type, const uint32_t ul_mask, const uint32_t ul_attribute, uint32_t ul_id){
	pmc_enable_periph_clk(ul_id);
	pio_configure(pio, ul_type, ul_mask, ul_attribute);
}

void configure_pio_input(Pio *pio, const pio_type_t ul_type, const uint32_t ul_mask, const uint32_t ul_attribute, uint32_t ul_id){
	pmc_enable_periph_clk(ul_id);
	pio_configure(pio, ul_type, ul_mask, ul_attribute);
	pio_set_debounce_filter(pio, ul_mask, 60);
}

void configure_interruption(Pio *pio, uint32_t ul_id, const uint32_t ul_mask,  uint32_t ul_attr, void (*p_handler) (uint32_t, uint32_t)){
	pio_handler_set(pio, ul_id, ul_mask , ul_attr, p_handler);
	pio_enable_interrupt(pio, ul_mask);
	pio_get_interrupt_status(pio);
	NVIC_EnableIRQ(ul_id);
	NVIC_SetPriority(ul_id, 4); // Prioridade 4
}

void init_structs(music *musica, const char name[9], int tempo, int *melody_vec, int size_array, int size_array_element){
	strcpy(musica->name, name);
	musica->tempo = tempo;
	musica->melody = &melody_vec[0];
	musica->wholenote = (6000*4)/(musica->tempo);
	musica->notes = size_array / size_array_element / 2;
}

void io_init(void)
{
	// Configura Buzzer
	configure_pio_output(BUZ_PIO, PIO_OUTPUT_0, BUZ_IDX_MASK, PIO_DEFAULT, BUZ_PIO_ID);

	// Configura LED1
	configure_pio_output(LED1_PIO, PIO_OUTPUT_0, LED1_PIO_IDX_MASK, PIO_DEFAULT, LED1_PIO_ID);

	// Configura LED2
	configure_pio_output(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK, PIO_DEFAULT, LED2_PIO_ID);

	// Configura LED3
	configure_pio_output(LED3_PIO, PIO_OUTPUT_0, LED3_PIO_IDX_MASK, PIO_DEFAULT, LED3_PIO_ID);


	// Configura botões e interrupções
	
	configure_pio_input(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP|PIO_DEBOUNCE, BUT1_PIO_ID);
	configure_pio_input(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK, PIO_PULLUP|PIO_DEBOUNCE, BUT2_PIO_ID);
	configure_pio_input(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK, PIO_PULLUP|PIO_DEBOUNCE, BUT3_PIO_ID);

	configure_interruption(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but1_callback);
	configure_interruption(BUT2_PIO, BUT2_PIO_ID, BUT2_PIO_IDX_MASK, PIO_IT_EDGE, but2_callback);
	configure_interruption(BUT3_PIO, BUT3_PIO_ID, BUT3_PIO_IDX_MASK, PIO_IT_EDGE, but3_callback);
}


void change_LED(int num){
	if(num == 0){
		pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	}
	else if(num ==1){
		pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	}
	else if(num ==2){
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
		
		change_LED(*num);
		
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
	int i = 1;

	gfx_mono_generic_draw_filled_rect(x+1, y+1, tamanho_barra_x, tamanho_barra_y, GFX_PIXEL_CLR);
	gfx_mono_generic_draw_rect(x, y, tamanho_barra_x+1, tamanho_barra_y+1, GFX_PIXEL_SET);
	
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
			gfx_mono_generic_draw_filled_rect(x, y, ((double)tamanho_barra_x/musica->notes*i)+1, tamanho_barra_y+1, GFX_PIXEL_SET);
			tone((*musica).melody[thisNote], noteDuration * 0.9, num);
			i++;
			
			
			if (mudar){
				return;
			}
			// Wait for the specified duration before playing the next note.
			delay_ms(noteDuration * 0.4);
		}
		
	}
	delay_ms(100);
	
}


void draw(music *musica){
	gfx_mono_draw_string("             ", 0,10, &sysfont);
	gfx_mono_draw_string(musica->name, 0,10, &sysfont);
}
