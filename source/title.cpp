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
	
	int PosX[] = {151, 63, 63};
	int PosY[] = {6, 43, 103};

	scanKeys();	//Check for key detection

	if (KEY_DOWN & keysDown()) {
		
		option = (option + 1) % 3;
		
		mmLoadEffect(SFX_MOVE);
		mmEffect(SFX_MOVE);
		blink = 0;

	}

	if (KEY_UP & keysDown()) {
		
		option = (option + 2) % 3; //Adding 2 then modulo is equal to substracting 1 
		
		mmLoadEffect(SFX_MOVE);
		mmEffect(SFX_MOVE);
		blink = 0;

	}

	if (KEY_A & keysDown()) {
		
		if (option == 0) { //If you are selecting volume
			
			if (volume == 1
			
		}
		else {
			game = 1;	//Ends titlescreen
			mmLoadEffect(SFX_CONFIRM);
			mmEffect(SFX_CONFIRM);
			blink = 0;
		}
	}
	
	if (KEY_SELECT & keysHeld()) {
		select_hold += 1;
		blink = 0;
	}
	else {
		select_hold = 0;
	}
		
	if (select_hold >= 10800){ //If SELECT is held more than 3 seconds (120 = 2 frames, 3 secs = 180 frames)
		
		game = 1;	//Ends titlescreen
		quit = 1;	//Quits game
	}

	touchRead(&Stylus);

	if(KEY_TOUCH & keysDown()) {

		//PLay button size: 128, 46 / Button pos: 80, 41
		if(Stylus.px >= 80 && Stylus.px <= 208 && Stylus.py >= 41 && Stylus.py <= 87){

			option = 1;
			game = 1;
			mmLoadEffect(SFX_CONFIRM);
			mmEffect(SFX_CONFIRM);
			blink = 0;

		}
		//Simulate button pos: 80, 105
		if(Stylus.px >= 80 && Stylus.px <= 208 && Stylus.py >= 105 && Stylus.py <= 151){

			option = 2;
			game = 1;
			mmLoadEffect(SFX_CONFIRM);
			mmEffect(SFX_CONFIRM);
			blink = 0;

		}

	}

	if (select_hold >= 1) {
		
		NF_SpriteFrame(1, 12, 6);
		NF_MoveSprite(1, 12, 38, 167);
		NF_SpriteFrame(1, 13, 7); // No need to move this sprite since it is empty
		
	}
	else {

		NF_MoveSprite(1, 12, PosX[option], PosY[option]);
		NF_MoveSprite(1, 13, PosX[option] + 64, PosY[option]);
		
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		NF_SpriteFrame(1, 12, option * 2);
		NF_SpriteFrame(1, 13, option * 2 + 1);

	}
	
	blink += 1;

	if (blink > 15) {
		
		NF_ShowSprite(1, 12, false);
		NF_ShowSprite(1, 13, false);
		blink %= 30; //Reset to 0 when blink >= 30
	}
	else {
		
		NF_ShowSprite(1, 12, true);
		NF_ShowSprite(1, 13, true);	
		
	}

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

}

