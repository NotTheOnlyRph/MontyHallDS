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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arrowposx;	//Defines position for arrow (on menus) 
int arrowposy;	//Same
int option;	//Used in many ways, like choosed option or sprite number calculator
int game;	//Determines if exiting of the selecting loop (ex: titlescreen)
int quit = 0;	//If you quit the game

int CarDoor;	//Door where the car is
int ChosenDoor;	//Door chosen by the player/computer
int ChosenDoorCopy;	//Duplicate of ChosenDoor (for the changing part of the program)
int WrongDoor;	//Door with the goat opened when you choose a door

int ChangeStrategy;		//Equal to 1000, number of times you simulate a game where you change
int StayStrategy;	//Equal to 1000, number of times you simulate a game where you stay on your choice

int StayWins;	//Speaks by itself
int StayLoses;	//Same
int ChangeWins;	//I should put something random here instead of saying it speaks by itself too
int ChangeLoses;	//How are you?

int strategy;	//Change or stay on choice

bool rumble = false; //Used for rumble pack detection
uint8_t intensity = 0; //Rumbling max intensity

int select_hold; //The time to check if SELECT button is held

touchPosition Stylus;






/*
-------------------------------------------------

	LoadSprite() Function

	Loads all the graphics and palettes for sprites to RAM and VRAM.

	Used by: main()

-------------------------------------------------
*/

void LoadSprites() {
	
	NF_LoadSpritePal("sprites/Numbers", 2); //Numbers is the common palette for the numbers's graphics
	NF_VramSpritePal(0, 2, 2);
	
	NF_LoadSpriteGfx("sprites/0", 20, 16, 16); //Numbers are showing when you simulate 2000 games.
	NF_VramSpriteGfx(0, 20, 20, false); //Actually I could have just VRAMd them on slot 1 instead of 21. But I wanted at first to load them also on the bottom screen.
	
	NF_LoadSpriteGfx("sprites/1", 21, 16, 16);
	NF_VramSpriteGfx(0, 21, 21, false);
	
	NF_LoadSpriteGfx("sprites/2", 22, 16, 16);
	NF_VramSpriteGfx(0, 22, 22, false);
	
	NF_LoadSpriteGfx("sprites/3", 23, 16, 16);
	NF_VramSpriteGfx(0, 23, 23, false);
	
	NF_LoadSpriteGfx("sprites/4", 24, 16, 16);
	NF_VramSpriteGfx(0, 24, 24, false);
	
	NF_LoadSpriteGfx("sprites/5", 25, 16, 16);
	NF_VramSpriteGfx(0, 25, 25, false);
	
	NF_LoadSpriteGfx("sprites/6", 26, 16, 16);
	NF_VramSpriteGfx(0, 26, 26, false);
	
	NF_LoadSpriteGfx("sprites/7", 27, 16, 16);
	NF_VramSpriteGfx(0, 27, 27, false);
	
	NF_LoadSpriteGfx("sprites/8", 28, 16, 16);
	NF_VramSpriteGfx(0, 28, 28, false);
	
	NF_LoadSpriteGfx("sprites/9", 29, 16, 16);
	NF_VramSpriteGfx(0, 29, 29, false);

	NF_LoadSpriteGfx("sprites/A button", 3, 16, 16); //Used to tell the player he can press A to continue. This can be useless if you're a big Nintendo gamer, BUT I am showing this project to non-gamers, so I need to make it intuitive.
	NF_LoadSpritePal("sprites/A button", 3);	//Bro is telling his life LOL
	NF_VramSpriteGfx(1, 3, 3, false);
	NF_VramSpritePal(1, 3, 3);

	NF_LoadSpriteGfx("sprites/Goat", 4, 32, 32); //Goat showing on wrong door to tell it's the wrong door.
	NF_LoadSpritePal("sprites/Goat", 4);
	NF_VramSpriteGfx(1, 4, 4, false);
	NF_VramSpritePal(1, 4, 4);

	NF_LoadSpriteGfx("sprites/Arrowbeta", 5, 64, 32);	//Why "beta"? i don't know. I should rename all my sprites and backgrounds.
	NF_LoadSpritePal("sprites/Arrowbeta", 5);	//Used in Titlescreen
	NF_VramSpriteGfx(1, 5, 5, false);
	NF_VramSpritePal(1, 5, 5);

	NF_LoadSpriteGfx("sprites/Arrowbeta_vertical", 6, 16, 32); //Like the arrowbeta but smaller and vertical. Used in door selection.
	NF_LoadSpritePal("sprites/Arrowbeta_vertical", 6);
	NF_VramSpriteGfx(1, 6, 6, false);
	NF_VramSpritePal(1, 6, 6);

	NF_LoadSpriteGfx("sprites/Arrowbeta_small", 7, 32, 16);	//Like the arrowbeta but smaller. Used to ask the player if he/she wants to change.
	NF_LoadSpritePal("sprites/Arrowbeta_small", 7);
	NF_VramSpriteGfx(1, 7, 7, false);
	NF_VramSpritePal(1, 7, 7);

	NF_LoadSpriteGfx("sprites/CurrentDoorTop", 8, 64, 64);	//Red Highlight on chosen door, top part (this sprite is split, because of the 64x64 limit with GRIT).
	NF_LoadSpritePal("sprites/CurrentDoorTop", 8);
	NF_VramSpriteGfx(1, 8, 8, false);
	NF_VramSpritePal(1, 8, 8);

	NF_LoadSpriteGfx("sprites/CurrentDoorBottom", 9, 64, 64);	//Red Highlight on chosen door, bottom part
	NF_LoadSpritePal("sprites/CurrentDoorBottom", 9);
	NF_VramSpriteGfx(1, 9, 9, false);
	NF_VramSpritePal(1, 9, 9);

	NF_LoadSpriteGfx("sprites/Door1Top", 10, 64, 64);	//Sprites must be split because of the size limit
	NF_LoadSpritePal("sprites/Door1Top", 10);
	NF_VramSpriteGfx(1, 10, 10, false);
	NF_VramSpritePal(1, 10, 10);

	NF_LoadSpriteGfx("sprites/Door1Bottom", 11, 64, 64);
	NF_LoadSpritePal("sprites/Door1Bottom", 11);
	NF_VramSpriteGfx(1, 11, 11, false);
	NF_VramSpritePal(1, 11, 11);

	NF_LoadSpriteGfx("sprites/Door2Top", 12, 64, 64);
	NF_LoadSpritePal("sprites/Door2Top", 12);
	NF_VramSpriteGfx(1, 12, 12, false);
	NF_VramSpritePal(1, 12, 12);
	
	NF_LoadSpriteGfx("sprites/Door2Bottom", 13, 64, 64);
	NF_LoadSpritePal("sprites/Door2Bottom", 13);
	NF_VramSpriteGfx(1, 13, 13, false);
	NF_VramSpritePal(1, 13, 13);

	NF_LoadSpriteGfx("sprites/Door3Top", 14, 64, 64);
	NF_LoadSpritePal("sprites/Door3Top", 14);
	NF_VramSpriteGfx(1, 14, 14, false);
	NF_VramSpritePal(1, 14, 14);

	NF_LoadSpriteGfx("sprites/Door3Bottom", 15, 64, 64);
	NF_LoadSpritePal("sprites/Door3Bottom", 15);
	NF_VramSpriteGfx(1, 15, 15, false);
	NF_VramSpritePal(1, 15, 15);
}


/*
-------------------------------------------------

	Rumble functions

	Used if the player has a rumble pak inserted into his DS (Phat or Lite)

	Used by: many codes I presume

-------------------------------------------------
*/

void CheckRumble(){
	
	if(rumble == false){
		rumble = isRumbleInserted(); //Checks if a rumble pak has been inserted
		
		if(rumble== true){
			
			intensity = rumbleGetMaxRawStrength();
			peripheralSlot2InitDefault();
		}
	} 
}


void SmallRumble(){

	CheckRumble();
	
	if(rumble == true){
		rumbleTick(intensity);
		
	}
}

void RumbleStart() {
	
	CheckRumble();
	
	if(rumble == true){
		setRumble(1, intensity);
		
	}	
	
}

void RumbleEnd() {
	
	CheckRumble();
	
	if(rumble == true){
		setRumble(0, intensity);
		
	}	
	
}


void UnloadSFX(){
	
	mmUnloadEffect(SFX_CONFIRM);
	mmUnloadEffect(SFX_CANCEL);
	mmUnloadEffect(SFX_SELECT);
	mmUnloadEffect(SFX_MOVE);

}


/*
-------------------------------------------------

	Titlescreen() Function

	Program part for titlescreen option selection

	Used by: main()

-------------------------------------------------
*/

void Titlescreen(){
	
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

/*
-------------------------------------------------

	MontyHallInit() Function

	Loads the assets needed to play the Monty Hall problem.

	Used by: MontyHallSimuPgrm(), PlayMontyHall()

-------------------------------------------------
*/

void MontyHallInit(){
	
	int slot[] = {10, 11, 12, 13, 14, 15};
	int spawnx[] = {16, 16, 96, 96, 176, 176};
	int spawny[] = {48, 112, 48, 112, 48, 112};

	for (int a = 0; a < 6; a++) {
		NF_CreateSprite(1, slot[a], slot[a], slot[a], spawnx[a], spawny[a]);	//The 6 doors
	}

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
}

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
	int SpriteDelete[] = {10, 12, 14};

	NF_LoadTiledBg("bg/Bottom/Game_doors", "Doors_B", 256, 256);
	NF_CreateTiledBg(1, 1, "Doors_B");

	CarDoor = rand() % 3;	//Door where the car is

	MontyHallInit();
	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();	//Waits for the next instruction. The DS is running at 60fps so waiting 60 times = wait 1 second 
	}

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
		
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

	do {
		WrongDoor = rand() % 3;	//Choses the wrong door, diferent from the car and chosen door. It picks a random door because of the case where the car door is the chosen door (there are in this case 2 posibilities, 1 the rest of the time)
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));


	NF_DeleteSprite(1, SpriteDelete[WrongDoor]);	//Deletes the doors
	NF_DeleteSprite(1, SpriteDelete[WrongDoor] + 1);
	
	NF_CreateSprite(1, 4, 4, 4, Doorx[WrongDoor] + 16, 96);	//Goat
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

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

		//Deletes the new door
		NF_MoveSprite(1, 9, Doorx[ChosenDoor], 48);
		NF_MoveSprite(1, 8, Doorx[ChosenDoor], 112);
	}

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

	if (ChosenDoor == ChosenDoorCopy) {	//If the player hasn't changed his choice
		do {
			ChosenDoorCopy = rand() % 3;	//Determines the door to delete
		} while ((ChosenDoorCopy == ChosenDoor) || (ChosenDoorCopy == WrongDoor));
	}
	
	NF_DeleteSprite(1, SpriteDelete[ChosenDoor]);	//Deletes the chosen door
	NF_DeleteSprite(1, SpriteDelete[ChosenDoor] + 1);
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	RumbleStart();
	
	mmLoadEffect(SFX_DRUMROLL);
	mmEffect(SFX_DRUMROLL);
	
	for (int wait=0; wait<=150; wait++) {
		swiWaitForVBlank();
	}
	
	if (ChosenDoor == CarDoor) {
		NF_CreateSprite(1, 3, 10, 10, Doorx[ChosenDoor] + 16, 96);
	}
	else{
		NF_CreateSprite(1, 3, 4, 4, Doorx[ChosenDoor] + 16, 96);
	}
	
	RumbleEnd();
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);	

	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

	mmUnloadEffect(SFX_DRUMROLL);

	NF_DeleteSprite(1, SpriteDelete[ChosenDoorCopy]);	//Deletes the last door
	NF_DeleteSprite(1, SpriteDelete[ChosenDoorCopy] + 1);
	
	NF_DeleteSprite(1, 3);
	NF_DeleteSprite(1, 4);
	NF_DeleteSprite(1, 8);
	NF_DeleteSprite(1, 9);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);	

	if (ChosenDoor == CarDoor) {
		NF_LoadTiledBg("bg/Win", "Win", 256, 256);
		NF_CreateTiledBg(1, 0, "Win");
		
		mmLoad(MOD_GAME_WIN);
		mmStart(MOD_GAME_WIN, MM_PLAY_ONCE);
		
		option = 0; //Set option to 0 to remember win
	}
	else {
		NF_LoadTiledBg("bg/Lose", "Lose", 256, 256);
		NF_CreateTiledBg(1, 0, "Lose");
		
		mmLoad(MOD_GAME_LOSE);
		mmStart(MOD_GAME_LOSE, MM_PLAY_ONCE);
		
		option = 1; //Set option to 1 to remember lose
	}

	int JingleWaitTime[] = {240, 180};
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=JingleWaitTime[option]; wait++) {
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
	
	if (ChosenDoor == CarDoor) {
		
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
	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}
}

/*
-------------------------------------------------

	MontyHallSimuPgrm() Function

	Using for CPU to simulate the game

	Used by: SimulateMontyHall()

	Using: MontyHallInit().

-------------------------------------------------
*/

void MontyHallSimuPgrm(int speed) {

	MontyHallInit();
	
	int Doorx[] = {40, 120, 200};
	int SpriteDelete[] = {10, 12, 14};
	int StayOrChange[] = {30, 152};
	
	CarDoor = rand() % 3;
	ChosenDoor = rand() % 3;
	
	NF_CreateSprite(1, 6, 6, 6, Doorx[ChosenDoor], 15);	//Creates a sprite to show CPU chosen door
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	mmLoadEffect(SFX_SELECT);
	mmEffect(SFX_SELECT);
	
	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}
	
	
	NF_CreateSprite(1, 9, 9, 9, Doorx[ChosenDoor] - 24, 48); // -24 because Doorx[ChosenDoor] is too much on the right
	NF_CreateSprite(1, 8, 8, 8, Doorx[ChosenDoor] - 24, 112);
	

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	NF_DeleteSprite(1, 6);
	
	do {
		WrongDoor = rand() % 3;
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));
	
	NF_DeleteSprite(1, SpriteDelete[WrongDoor]);
	NF_DeleteSprite(1, SpriteDelete[WrongDoor] + 1);
	NF_CreateSprite(1, 4, 4, 4, Doorx[WrongDoor] - 8, 96);	//Goat
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	mmLoadEffect(SFX_MOVE);
	mmEffect(SFX_MOVE);

	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}

	
	NF_LoadTiledBg("bg/Bottom/Game_change_select", "Change_B", 256, 256);
	NF_CreateTiledBg(1, 0, "Change_B");
	
	NF_CreateSprite(1, 7, 7, 7, StayOrChange[strategy - 1], 15);	//Creates a sprite to show CPU's choice (stay (1) or change (2), determined by the strategy variable)
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	mmLoadEffect(SFX_MOVE);
	mmEffect(SFX_MOVE);

	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}
	
	NF_DeleteSprite(1, 7);

	ChosenDoorCopy = ChosenDoor;	//See 

	if (strategy == 2)
	{
		while ((ChosenDoor == ChosenDoorCopy) || (ChosenDoor == WrongDoor)){
			ChosenDoor =  rand () % 3;
		}
	}

	if (ChosenDoor == ChosenDoorCopy) {
		do {
			ChosenDoorCopy = rand() % 3;
		} while ((ChosenDoorCopy == ChosenDoor) || (ChosenDoorCopy == WrongDoor));
	}

	NF_DeleteSprite(1, SpriteDelete[ChosenDoor]);
	NF_DeleteSprite(1, SpriteDelete[ChosenDoor] + 1);
	
	NF_DeleteSprite(1, SpriteDelete[ChosenDoorCopy]);
	NF_DeleteSprite(1, SpriteDelete[ChosenDoorCopy] + 1);

	NF_DeleteSprite(1, 4);
	NF_DeleteSprite(1, 8);
	NF_DeleteSprite(1, 9);

	if (ChosenDoor == CarDoor) {
		NF_LoadTiledBg("bg/Win", "Win", 256, 256);
		NF_DeleteTiledBg(1, 0);
		NF_CreateTiledBg(1, 0, "Win");
		NF_UnloadTiledBg("Change_B");
		
		mmLoadEffect(SFX_SIMU_WIN);
		mmEffect(SFX_SIMU_WIN);
		
		option = 1; //Set option to 1 to remember used BG
	}
	else {
		NF_LoadTiledBg("bg/Lose", "Lose", 256, 256);
		NF_DeleteTiledBg(1, 0);
		NF_CreateTiledBg(1, 0, "Lose");
		NF_UnloadTiledBg("Change_B");
		
		mmLoadEffect(SFX_SIMU_LOSE);
		mmEffect(SFX_SIMU_LOSE);
		
		option = 2; //Set option to 2 to remember used BG
	}
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	
	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}
	
	NF_DeleteTiledBg(1, 0);
	
	if (option == 1) {
		NF_UnloadTiledBg("Win");

		if (strategy == 1) {
			StayStrategy -=	1;
			StayWins += 1;
		}
		else {
			ChangeStrategy -= 1;
			ChangeWins += 1;
		}
	} 
	else {
		NF_UnloadTiledBg("Lose");
		
		if (strategy == 1) {
			StayStrategy -=	1;
			StayLoses += 1;
		}
		else {
			ChangeStrategy -= 1;
			ChangeLoses += 1;
		}
	}
	
}

/*
-------------------------------------------------

	MontyHallSimuFast() Function

	Faster version of MontyHallSimuPgrm(), with no graphics.

	Used by: SimulateMontyHall()

-------------------------------------------------
*/

void MontyHallSimuFast() {
	
	CarDoor = rand() % 3;
	ChosenDoor = rand() % 3;
	
	do {
		WrongDoor = rand() % 3;
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));

	ChosenDoorCopy = ChosenDoor;

	if (strategy == 2)
	{
		while ((ChosenDoor == ChosenDoorCopy) || (ChosenDoor == WrongDoor)){
			ChosenDoor =  rand () % 3;
		}
	}

	if (ChosenDoor == ChosenDoorCopy) {
		do {
			ChosenDoorCopy = rand() % 3;
		} while ((ChosenDoorCopy == ChosenDoor) || (ChosenDoorCopy == WrongDoor));
	}
	
	if (ChosenDoor == CarDoor) {

		if (strategy == 1) {
			StayStrategy -= 1;
			StayWins += 1;
		}
		if (strategy == 2) {
			ChangeStrategy -= 1;
			ChangeWins += 1;
		}
	} 
	if (ChosenDoor != CarDoor) {
		
		if (strategy == 1) {
			StayStrategy -= 1;
			StayLoses += 1;
		}
		if (strategy == 2) {
			ChangeStrategy -= 1;
			ChangeLoses += 1;
		}
	}
	
}

/*
-------------------------------------------------

	MontyHallSimuResults() Function

	Updates the numbers on top

	Used by: SimulateMontyHall()

-------------------------------------------------
*/

void MontyHallSimuResults() {

	int NumbersX[] = {105, 120, 135, 175, 190, 205, 105, 120, 135, 175, 190, 205};
	int NumbersY[] = {96, 96, 96, 96, 96, 96, 128, 128, 128, 128, 128, 128};
	int Variables[] = {StayWins, StayLoses, ChangeWins, ChangeLoses};

	option = 1;
	int number;

	for (int wait=0; wait<=11; wait++) {
		NF_DeleteSprite(0, option);	//Deletes the number to replace it by the new one. I don't know how to do sprite frames, so I did like that.
		option += 1;
	}

	//Determines numbers shown by the sprites
	option = 0;

	for (int sprite=0; sprite<=3; sprite++) {
		
		number = (Variables[sprite] - (Variables[sprite] % 100)) / 100 + 20;	//Thousands
		NF_CreateSprite(0, option + 1, number, 2, NumbersX[option], NumbersY[option]);
		option +=1;
		
		number = ((Variables[sprite] % 100) - (Variables[sprite] % 10)) / 10 + 20;	//Dozens
		NF_CreateSprite(0, option + 1, number, 2, NumbersX[option], NumbersY[option]);
		option +=1;
		
		number = (Variables[sprite] % 10) + 20;	//Units
		NF_CreateSprite(0, option + 1, number, 2, NumbersX[option], NumbersY[option]);
		option +=1;
		
	}


	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
}

/*
-------------------------------------------------

	SimulateMontyHall() Function

	Simulates over 1000 games for each strategy.

	Used by: main()

-------------------------------------------------
*/

void SimulateMontyHall(){

	NF_LoadTiledBg("bg/Bottom/Game_doors", "Doors_B", 256, 256);
	NF_CreateTiledBg(1, 1, "Doors_B");
	
	NF_LoadTiledBg("bg/Top/Simu", "Simu_T", 256, 256);
	NF_CreateTiledBg(0, 1, "Simu_T");
	
	int NumbersX[] = {105, 120, 135, 175, 190, 205, 105, 120, 135, 175, 190, 205};
	int NumbersY[] = {96, 96, 96, 96, 96, 96, 128, 128, 128, 128, 128, 128};	
	
	for (int sprite=1; sprite<=12; sprite++) {
	
		NF_CreateSprite(0, sprite, 20, 2, NumbersX[sprite - 1], NumbersY[sprite - 1]);	//Initiates sprites for the first time.

	}
	
	ChangeStrategy = 1000;
	ChangeLoses = 0;
	ChangeWins = 0;
	
	StayStrategy = 1000;
	StayLoses = 0;
	StayWins = 0;
	
	for (int wait=0; wait<4; wait++) {

		strategy = rand() % 2 + 1;	//Determines the strategy (1: Stay, 2: Change)

		MontyHallSimuPgrm(29);	//29 is the number of frames to wait, a demi-second (one more frame is automatically added)

		MontyHallSimuResults();

	}

	
	for (int wait=0; wait<6; wait++) {
				
		strategy = rand() % 2 + 1;

		MontyHallSimuPgrm(14);

		MontyHallSimuResults();
	
	}

	//Here the games start simulating fast
	
	NF_LoadTiledBg("bg/Bottom/Simu_progress", "Simu_B", 256, 256);
	NF_CreateTiledBg(1, 0, "Simu_B");
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	NF_DeleteTiledBg(1, 1);
	NF_UnloadTiledBg("Doors_B");

	while((ChangeStrategy > 9) && (StayStrategy > 9)) {

		for (int i=0; i<10; i++) {	//Does 10 tests on 1 frame, 600 on 1 second.

			strategy = rand() % 2 + 1;

			MontyHallSimuFast();
		}
		MontyHallSimuResults();

	}


	while(ChangeStrategy > 0) {
		strategy = 2;
		MontyHallSimuFast();
	}
	while(StayStrategy > 0) {
		strategy = 1;
		MontyHallSimuFast();
	}
	
	MontyHallSimuResults();

	
	NF_LoadTiledBg("bg/Bottom/Simu_finished", "Simu_B_END", 256, 256);
	NF_CreateTiledBg(1, 1, "Simu_B_END");

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	NF_DeleteTiledBg(1, 0);
	NF_UnloadTiledBg("Simu_B");
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}
	
	NF_CreateSprite(1, 3, 3, 3, 235, 171);

	game = 0;
	int state = 0;
	
	while (game == 0) {

		if (state == 0) {
			state = 1;
			NF_ShowSprite(1,  3 , true);
		}
		else {
			state = 0;
			NF_ShowSprite(1,  3 , false);
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

			if((KEY_A & keysDown()) || (KEY_TOUCH & keysDown())){
				game = 1;
			}
		}
	}

	mmLoadEffect(SFX_SELECT);
	mmLoadEffect(SFX_SELECT);
	mmEffect(SFX_SELECT);

	NF_DeleteSprite(1, 3);

	for (int wait=0; wait<=11; wait++) {
		NF_DeleteSprite(0, wait+1);
	}

	NF_DeleteTiledBg(1, 1);
	NF_UnloadTiledBg("Simu_B_END");
	
	NF_DeleteTiledBg(0, 1);
	NF_UnloadTiledBg("Simu_T");

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

}

/*
-------------------------------------------------

	main

	Base function of the program

	Using: LoadSprites(), Titlescreen(), PlayMontyHall(), SimulateMontyHall()

-------------------------------------------------
*/

int main(){

	srand (time (NULL)); //Init random
	consoleDemoInit(); 
	consoleClear();
	printf("\n The Monty Hall Problem\n DS port by Rph\n\n Please wait for NitroFS to init\n\n\n (If it takes too much time,\n it probably doesn't work. See\n readme.txt for information.)");
	//Print a waiting / bug message
	swiWaitForVBlank();
	
    bool init_ok = nitroFSInit(NULL);
    if (!init_ok)
    {
        perror("nitroFSInit()");
		return 0;
    }
    
    NF_SetRootFolder("NITROFS");
	
	NF_Set2D(0,0);	//Init 2D
    NF_Set2D(1,0);
    
    NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);

	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	
	mmInitDefault("nitro:/soundbank.bin"); //Init audio

	LoadSprites();

	soundEnable();

	while (quit == 0){

		
		soundDisable();
		soundEnable();


		NF_LoadTiledBg("bg/Top/Title", "Title_T", 256, 256);
		NF_LoadTiledBg("bg/Bottom/Title", "Title_B", 256, 256);
		NF_CreateTiledBg(0, 3, "Title_T");
		NF_CreateTiledBg(1, 3, "Title_B");
		
		option = 0;
		arrowposx = 15;
		arrowposy = 48;
		game = 0;
		
		NF_CreateSprite(1, 5, 5, 5, 15, 48);

		while(game == 0)
		{
			Titlescreen();
		}
				
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		if (quit == 1){	
			break;
		}

		SmallRumble();
		
		for (int wait=0; wait<=60; wait++) {
			swiWaitForVBlank();
		}
		
		NF_DeleteSprite(1, 5);

		NF_LoadTiledBg("bg/Top/Blurred", "Blurred_T", 256, 256);
		NF_CreateTiledBg(0, 2, "Blurred_T");
		NF_LoadTiledBg("bg/Bottom/Empty", "Empty_B", 256, 256);
		NF_CreateTiledBg(1, 2, "Empty_B");

		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		
		NF_DeleteTiledBg(0, 3);
		NF_UnloadTiledBg("Title_T");	
		NF_DeleteTiledBg(1, 3);
		NF_UnloadTiledBg("Title_B");
		
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		for (int wait=0; wait<=30; wait++) {
			swiWaitForVBlank();
		}
		
		UnloadSFX();
		
		if (option == 0) {
			PlayMontyHall();
			option = 0; //Set this to avoid game playing simulation without asking
		}
		if (option == 1) {
			SimulateMontyHall();
		}
				
		NF_DeleteTiledBg(1, 2);
		NF_UnloadTiledBg("Empty_B");
		NF_DeleteTiledBg(0, 2);
		NF_UnloadTiledBg("Blurred_T");

	}
	
	UnloadSFX();
	mmLoadEffect(SFX_CANCEL);
	mmEffect(SFX_CANCEL);
	
	NF_DeleteTiledBg(0, 3);
	NF_DeleteTiledBg(1, 3);
	NF_DeleteSprite(1, 5);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}
	
	UnloadSFX();
	
	return 0;
}
