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
	
	init_structs(&starwars, name_starwars, 108, melody_starwars, sizeof(melody_starwars), sizeof(melody_starwars[0]));
	init_structs(&nokia, name_nokia, 180, melody_nokia, sizeof(melody_nokia), sizeof(melody_nokia[0]));
	init_structs(&badinerie, name_badinerie, 120, melody_badinerie, sizeof(melody_badinerie), sizeof(melody_badinerie[0]));
	
	but1_flag = 0;
	mudar = 0;
	int num_musica = 0;
	while(1){
		draw(num_musica);
		play_music(array_musica[num_musica], &num_musica);
		if(mudar){
			mudar = 0;
		}
	}
}
