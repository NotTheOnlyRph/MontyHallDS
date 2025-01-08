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

	ChooseDoor() Function

	Same loop system as Titlescreen()

	Used by: PlayMontyHall()

-------------------------------------------------
*/

void ChooseDoor(){

	int arrowposx[] = {40, 120, 200};

	NF_MoveSprite(1, 6, arrowposx[option], arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	if (arrowposy == 5) {
		arrowposy = 15;
	}
	else {
		arrowposy -= 0.5;
	}

	NF_MoveSprite(1, 6, arrowposx[option], arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=120; wait++) {

		scanKeys();

		if (KEY_RIGHT & keysDown()) {
			mmLoadEffect(SFX_MOVE);
			mmEffect(SFX_MOVE);
			option += 1;
		}
		if (KEY_LEFT & keysDown()) {
			mmLoadEffect(SFX_MOVE);
			mmEffect(SFX_MOVE);
			option -= 1;
		}
		option = (option + 3) % 3;

		if (KEY_A & keysDown()) {
			game = 1;
		}

		touchRead(&Stylus);

		if(KEY_TOUCH & keysDown()) {

			//Door size: 64, 128 / There's a gap of 16 between 2 doors, or between 1 door and the border. The Y position is 48.
			if(Stylus.px >= 16 && Stylus.px <= 80 && Stylus.py >= 48 && Stylus.py <= 176){
				option = 0;
				game = 1;
			}	//No need to load the arrow position because you directly move to the next step.
			if(Stylus.px >= 96 && Stylus.px <= 160 && Stylus.py >= 48 && Stylus.py <= 176){
				option = 1;
				game = 1;
			}
			if(Stylus.px >= 176 && Stylus.px <= 240 && Stylus.py >= 48 && Stylus.py <= 176){
				option = 2;
				game = 1;
			}
		}
	}


}

/*
-------------------------------------------------

	ChangeDoor() Function

	Same loop system as Titlescreen()

	Used by: PlayMontyHall()


-------------------------------------------------
*/

void ChangeDoor(){

	int baseposx[] = {20, 142};

	NF_MoveSprite(1, 7, arrowposx + baseposx[option], arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	if (arrowposx == 0) {
		arrowposx += 10;
	}
	else {
		arrowposx -= 0.5;
	}

	NF_MoveSprite(1, 7, arrowposx + baseposx[option], arrowposy); //Actually arrowposy doesn't change in this function.

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=120; wait++) {
		scanKeys();

		if (KEY_RIGHT & keysDown()) {
			mmLoadEffect(SFX_MOVE);
			mmEffect(SFX_MOVE);
			option += 1;
		}

		if (KEY_LEFT & keysDown()) {
			mmLoadEffect(SFX_MOVE);
			mmEffect(SFX_MOVE);
			option -= 1;
		}
		
		option = (option + 2) % 2;

		if (KEY_A & keysDown()) {
			game = 1;
		}

		touchRead(&Stylus);

		if(KEY_TOUCH & keysDown()) {

			//Stay button size: 64, 24 / Button pos: 64, 11
			if(Stylus.px >= 64 && Stylus.px <= 128 && Stylus.py >= 11 && Stylus.py <= 35){
				option = 0;
				game = 1;
			//Change button pos: 186, 11
			}	//No need to load the arrow position because you directly move to the next step.
			if(Stylus.px >= 186 && Stylus.px <= 250 && Stylus.py >= 11 && Stylus.py <= 35){
				option = 1;
				game = 1;
			}
		}
	}

}

/*
-------------------------------------------------

	PlayMontyall() Function

	Using for player to play the game

	Used by: main()

	Using: MontyHallInit(), ChooseDoor(), ChangeDoor().

-------------------------------------------------
*/

void PlayMontyHall(){

	int Doorx[] = {16, 96, 176};

	NF_LoadTiledBg("bg/Bottom/Game_doors", "Doors_B", 256, 256);
	NF_CreateTiledBg(1, 1, "Doors_B");

	CarDoor = rand() % 3;	//Door where the car is
	
	Wait(60);

	NF_LoadTiledBg("bg/Top/Game_choose_door", "Choose_T", 256, 256);
	NF_CreateTiledBg(0, 1, "Choose_T");
	
	NF_CreateSprite(1, 6, 6, 6, 120, 15);	//Arrow

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	arrowposx = 120;
	arrowposy = 15;
	option = 1;
	game = 0;

	while (game == 0) {	//Game changes to 1 in this function
		ChooseDoor();
	}
	
	mmLoadEffect(SFX_SELECT);
	mmEffect(SFX_SELECT);

	ChosenDoor = option;	//Used to calculate the x position of the door (top-left based)
	NF_CreateSprite(1, 9, 9, 9, Doorx[option], 48);	//Creates the door highlight
	NF_CreateSprite(1, 8, 8, 8, Doorx[option], 112);

	NF_DeleteSprite(1, 6);	//Arrow
	
	NF_DeleteTiledBg(0, 1);
	NF_UnloadTiledBg("Choose_T");
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
		
	Wait(60);

	do {
		WrongDoor = rand() % 3;	//Choses the wrong door, diferent from the car and chosen door. It picks a random door because of the case where the car door is the chosen door (there are in this case 2 posibilities, 1 the rest of the time)
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));


	NF_CreateSprite(1, 12, 10, 10, Doorx[WrongDoor], 48); //Creates the opened door over the background
	NF_CreateSprite(1, 13, 11, 11, Doorx[WrongDoor], 112);
	NF_CreateSprite(1, 4, 4, 4, Doorx[WrongDoor] + 16, 96);	//Goat
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	Wait(60);

	NF_LoadTiledBg("bg/Bottom/Game_change_select", "Change_B", 256, 256);
	NF_CreateTiledBg(1, 0, "Change_B");
	
	NF_LoadTiledBg("bg/Top/Game_change_door", "Change_T", 256, 256);
	NF_CreateTiledBg(0, 0, "Change_T");

	NF_CreateSprite(1, 7, 7, 7, 20, 15);	//Arrow

	arrowposx = 0;
	arrowposy = 15;
	option = 0;
	game = 0;

	UnloadSFX();


	while (game == 0) {
		ChangeDoor();
	}
	
	mmLoadEffect(SFX_SELECT);
	mmEffect(SFX_SELECT);

	NF_DeleteSprite(1, 7);	//Arrow

	NF_DeleteTiledBg(0, 0);
	NF_UnloadTiledBg("Change_T");
	NF_DeleteTiledBg(1, 0);
	NF_UnloadTiledBg("Change_B");
	

	ChosenDoorCopy = ChosenDoor;	//Used to change ChosenDoor while still knowing the original chosen door.

	if (option == 1)
	{
		while ((ChosenDoor == ChosenDoorCopy) || (ChosenDoor == WrongDoor)){
			ChosenDoor =  rand() % 3;	//Determines the new door
		}

		//Moves the highlight to the new door
		NF_MoveSprite(1, 9, Doorx[ChosenDoor], 48);
		NF_MoveSprite(1, 8, Doorx[ChosenDoor], 112);
	}

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	Wait(60);

	NF_CreateSprite(1, 14, 10, 10, Doorx[ChosenDoor], 48); //Creates the final door over the background
	NF_CreateSprite(1, 15, 11, 11, Doorx[ChosenDoor], 112);
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	RumbleStart();
	
	mmLoadEffect(SFX_DRUMROLL);
	mmEffect(SFX_DRUMROLL);
	
	Wait(150);
	
	//Time to check if you guessed correctly!
	
	if (cheat == 0) { //Unless you cheated
		
		if (ChosenDoor == CarDoor) {
			NF_CreateSprite(1, 3, 2, 2, Doorx[ChosenDoor] + 16, 96);
			option = 0; //Set option to 0 to remember win

		}
		else{
			NF_CreateSprite(1, 3, 4, 4, Doorx[ChosenDoor] + 16, 96);
			option = 1; //Set option to 1 to remember lose
		}
	}
	else { //Cheaters time!
		
		if (cheat == 1) {
			NF_CreateSprite(1, 3, 2, 2, Doorx[ChosenDoor] + 16, 96);
			option = 0; //Set option to 0 to remember win

		}
		if (cheat == 2) {
			NF_CreateSprite(1, 3, 4, 4, Doorx[ChosenDoor] + 16, 96);
			option = 1; //Set option to 1 to remember lose
		}
	
	}
	
	
	RumbleEnd();
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);	

	Wait(60);

	mmUnloadEffect(SFX_DRUMROLL);

	NF_DeleteSprite(1, 3);
	NF_DeleteSprite(1, 4);
	NF_DeleteSprite(1, 8);
	NF_DeleteSprite(1, 9);
	
	NF_DeleteSprite(1, 12);
	NF_DeleteSprite(1, 13);
	NF_DeleteSprite(1, 14);
	NF_DeleteSprite(1, 15);


	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);	

	if (option == 0) { //I told you to remember!
		NF_LoadTiledBg("bg/Win", "Win", 256, 256);
		NF_CreateTiledBg(1, 0, "Win");
		
		mmLoad(MOD_GAME_WIN);
		mmStart(MOD_GAME_WIN, MM_PLAY_ONCE);
		
	}
	else {
		NF_LoadTiledBg("bg/Lose", "Lose", 256, 256);
		NF_CreateTiledBg(1, 0, "Lose");
		
		mmLoad(MOD_GAME_LOSE);
		mmStart(MOD_GAME_LOSE, MM_PLAY_ONCE);
	}

	int JingleWaitTime[] = {240, 180};
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=JingleWaitTime[option]; wait++) { //Waits for the end of the jingle, who has a different length for win and lose
		swiWaitForVBlank();
	}
	
	NF_CreateSprite(1, 3, 3, 3, 235, 171);	//A button
	
	game = 0;
	int state = 0;
	
	UnloadSFX();
	
	while (game == 0) {
		
		if (state == 0) {
			state = 1;
			NF_ShowSprite(1,  3 , true);
		}
		else {
			state = 0;
			NF_ShowSprite(1,  3 , false);	//This part makes the A button blinking
		}
		
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		
		for (int wait=0; wait<=30; wait++) {
			swiWaitForVBlank();
			scanKeys();
			touchRead(&Stylus);

			if ((KEY_A & keysDown()) || (KEY_TOUCH & keysDown())) {
				game = 1;
			}
		}
	}
		
	mmLoadEffect(SFX_SELECT);
	mmEffect(SFX_SELECT);
		
	NF_DeleteSprite(1,3);	
	NF_DeleteTiledBg(1, 0);
	NF_DeleteTiledBg(1, 1);
	
	if (option == 0) {
		
		mmUnload(MOD_GAME_WIN);
		NF_UnloadTiledBg("Win");
	} 
	else {

		mmUnload(MOD_GAME_LOSE);
		NF_UnloadTiledBg("Lose");
	}
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	Wait(60);
}
