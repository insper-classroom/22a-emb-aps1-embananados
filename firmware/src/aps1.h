/*
 * aps1.h
 *
 * Created: 14/03/2022 16:39:28
 *  Author: berna
 */ 


#ifndef APS1_H_
#define APS1_H_

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

#define x 94
#define y 12
#define tamanho_barra_x 32
#define tamanho_barra_y 9

#define name_starwars "Star Wars"
#define name_nokia "Nokia"
#define name_badinerie "Badinerie"

volatile int but1_flag;
volatile int but2_flag;
volatile int but3_flag;
volatile int mudar;


typedef struct{
	char name[9];
	int tempo;
	int wholenote;
	int notes;
	int *melody;
} music;

void configure_pio_output(Pio *pio, const pio_type_t ul_type, const uint32_t ul_mask, const uint32_t ul_attribute, uint32_t ul_id);
void configure_pio_input(Pio *pio, const pio_type_t ul_type, const uint32_t ul_mask, const uint32_t ul_attribute, uint32_t ul_id);
void configure_interruption(Pio *pio, uint32_t ul_id, const uint32_t ul_mask,  uint32_t ul_attr, void (*p_handler) (uint32_t, uint32_t));
void init_structs(music *musica, const char name[9], int tempo, int *melody_vec, int size_array, int size_array_element);
void io_init(void);
void change_LED(int num);
void tone(int freq, int time, int *num);
void play_music(music *musica, int *num);
void draw(int num_musica);

#endif /* APS1_H_ */