/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

#include <nds.h> //Libnds
#include <fat.h>
#include <filesystem.h>
#include <nf_lib.h> //NFLib

#include <maxmod9.h>    // Audio with Maxmod
#include "soundbank.h"  // Soundbank definitions

#include "game.h"
#include "simu.h"
#include "title.h"
#include "montyhall.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
-------------------------------------------------

	Titlescreen() Function

	Program part for titlescreen option selection

	Used by: main()

-------------------------------------------------
*/

void Title(){
	
	int arrowposy[] = {48, 112};

	NF_MoveSprite(1, 5, arrowposx, arrowposy[option]); //Reloads arrow's position

	NF_SpriteOamSet(0);	//These five blocks update the screens. They are used on the program lotsa times.
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	//Arrow horizontal animation
	if (arrowposx == 5) {
		arrowposx = 15;
	}
	else {
		arrowposx -= 0.5;
	}

	NF_MoveSprite(1, 5, arrowposx, arrowposy[option]);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);	

	for (int wait=0; wait<=120; wait++) {
		scanKeys();	//Check for key detection

		if ((KEY_UP & keysDown()) || (KEY_DOWN & keysDown())) {
			
			option = 1 - option;
			NF_MoveSprite(1, 5, arrowposx, arrowposy[option]);
			
			mmLoadEffect(SFX_MOVE);
			mmEffect(SFX_MOVE);

		}

		if (KEY_A & keysDown()) {
			game = 1;	//Ends titlescreen
			mmLoadEffect(SFX_CONFIRM);
			mmEffect(SFX_CONFIRM);
			
		}
		
		if (KEY_SELECT & keysHeld()) {
			select_hold += 1;
		}
		else {
			select_hold = 0;
		}
		
		if (select_hold >= 10800){ //If SELECT is held more than 3 seconds (120 = 2 frames, 3 secs = 180 frames)
			
			game = 1;	//Ends titlescreen
			quit = 1;	//Quits game
			option = 2;
		}

		touchRead(&Stylus);

		if(KEY_TOUCH & keysDown()) {

			//PLay button size: 128, 46 / Button pos: 80, 41
			if(Stylus.px >= 80 && Stylus.px <= 208 && Stylus.py >= 41 && Stylus.py <= 87){

				option = 0;
				NF_MoveSprite(1, 5, arrowposx, arrowposy[option]);
				game = 1;
				mmLoadEffect(SFX_CONFIRM);
				mmEffect(SFX_CONFIRM);

			}
			//Simulate button pos: 80, 105
			if(Stylus.px >= 80 && Stylus.px <= 208 && Stylus.py >= 105 && Stylus.py <= 151){

				option = 1;
				NF_MoveSprite(1, 5, arrowposx, arrowposy[option]);
				game = 1;
				mmLoadEffect(SFX_CONFIRM);
				mmEffect(SFX_CONFIRM);
	
			}

		}

	}
}
