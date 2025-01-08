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

	ToggleCheatMode() Function

	Determines the cheat mode and the jingle to play

	Used by: Titlescreen()

-------------------------------------------------
*/

void ToggleCheatMode(){
	
	cheat = cheat + 1 % 3;
	start_hold = 0;

	if (cheat == 0) {
		mmLoadEffect(SFX_CANCEL);
		mmEffect(SFX_CANCEL);
	}	
	
	if (cheat == 1) {
		mmLoadEffect(SFX_SIMU_WIN);
		mmEffect(SFX_SIMU_WIN);
	}
	
	if (cheat == 2) {
		mmLoadEffect(SFX_SIMU_LOSE);
		mmEffect(SFX_SIMU_LOSE);
	}

}


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
			
			if (volume == 1) {
				volume = 0;
				soundDisable();
			}
			else {
				volume = 1;
				soundEnable();
				mmLoadEffect(SFX_SELECT);
				mmEffect(SFX_SELECT);
			}
			
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
		
	if (select_hold >= 180){ //If SELECT is held more than 3 seconds (1 sec = 60 frames)
		
		game = 1;	//Ends titlescreen
		quit = 1;	//Quits game
	}
	
	
	if (KEY_START & keysHeld()) {
		start_hold += 1;
		blink = 0;
	}
	else {
		start_hold = 0;
	}
	if (start_hold >= 720){ //If START is held more than 12 seconds (1 sec = 60 frames)
		
		ToggleCheatMode();
		
	}
	

	touchRead(&Stylus);

	if(KEY_TOUCH & keysDown()) {

		//PLay button size: 130, 49 / Button pos: 63, 43
		if(Stylus.px >= 63 && Stylus.px <= 193 && Stylus.py >= 43 && Stylus.py <= 92){

			option = 1;
			game = 1;
			mmLoadEffect(SFX_CONFIRM);
			mmEffect(SFX_CONFIRM);
			blink = 0;
		}
		//Simulate button pos: 63, 103
		if(Stylus.px >= 63 && Stylus.px <= 193 && Stylus.py >= 103 && Stylus.py <= 152){

			option = 2;
			game = 1;
			mmLoadEffect(SFX_CONFIRM);
			mmEffect(SFX_CONFIRM);
			blink = 0;
		}
		//Volume button size: 29, 29 / Volume button pos: 215, 6
		if(Stylus.px >= 215 && Stylus.px <= 244 && Stylus.py >= 6 && Stylus.py <= 35){
	
			if (volume == 1) {
				volume = 0;
				soundDisable();
			}
			else {
				volume = 1;
				soundEnable();
				mmLoadEffect(SFX_SELECT);
				mmEffect(SFX_SELECT);
			}
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
	
	NF_SpriteFrame(1, 5, volume);
	
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

