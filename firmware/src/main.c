#include "asf.h"
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "aps1.h"
#include "musicas.h"

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

	music starwars;
	music nokia;
	music badinerie;
	
	int array_musica[3];
	int *p1 = &starwars;
	int *p2 = &nokia;
	int *p3 = &badinerie;
	
	array_musica[0] = p1;
	array_musica[1] = p2;
	array_musica[2] = p3;
	
	starwars.name[9] = "Star Wars";
	starwars.tempo = 108;
	starwars.melody = &melody_starwars[0];
	starwars.wholenote = (6000 * 4)/(starwars.tempo);
	starwars.notes = sizeof(melody_starwars) / sizeof(melody_starwars[0]) / 2;

	nokia.name[9] = "Nokia";
	nokia.tempo = 180;
	nokia.melody = &melody_nokia[0];
	nokia.wholenote = (6000 * 4)/(nokia.tempo);
	nokia.notes = sizeof(melody_nokia) / 4 / 2;
	
	badinerie.name[9] = "Badinerie";
	badinerie.tempo = 120;
	badinerie.melody = &melody_badinerie[0];
	badinerie.wholenote = (6000 * 4)/(badinerie.tempo);
	badinerie.notes = sizeof(melody_badinerie) / sizeof(melody_badinerie[0]) / 2;
	
	but1_flag = 0;
	mudar = 0;
	int num_musica = 0;
	/* Insert application code here, after the board has been initialized. */
	while(1){
		draw(num_musica);
		play_music(array_musica[num_musica], &num_musica);
		if(mudar){
			mudar = 0;
		}
	}
}
