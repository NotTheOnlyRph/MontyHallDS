/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

#include <nds.h> //Libnds
#include <nf_lib.h> //NFLib
#include <fat.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arrowposx;	//Defines position for arrow (on menus) 
int arrowposy;	//Same
int option;	//Used in many ways, like choosed option or sprite number calculator
int game;	//Determines if exiting of the selecting loop (ex: titlescreen)

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

	Titlescreen() Function

	Program part for titlescreen option selection

	Used by: main()

-------------------------------------------------
*/

void Titlescreen(){

	NF_MoveSprite(1, 5, arrowposx, arrowposy); //Reloads arrow's position

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

	NF_MoveSprite(1, 5, arrowposx, arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);	

	for (int wait=0; wait<=120; wait++) {
		scanKeys();	//Check for key detection

		if ((KEY_UP & keysDown()) || (KEY_DOWN & keysDown())) {
			
			if (option == 1) {
				option = 2; //Option 2: simulate option
				arrowposy = 112;
				NF_MoveSprite(1, 5, arrowposx, arrowposy);
				break; //This is needed because the game would do the second if and go back to 1.
			}
			if (option == 2) {
				option = 1; //Option 1: play option
				arrowposy = 48;
				NF_MoveSprite(1, 5, arrowposx, arrowposy);
			}
		}

		if (KEY_A & keysDown()) {
			game = 1;	//Ends titlescreen
		}

		touchRead(&Stylus);

		if(KEY_TOUCH & keysDown()) {

			//PLay button size: 128, 46 / Button pos: 80, 41
			if(Stylus.px >= 80 && Stylus.px <= 208 && Stylus.py >= 41 && Stylus.py <= 87){
				NF_MoveSprite(1, 5, arrowposx, arrowposy);
				game = 1;
			}
			//Simulate button pos: 80, 105
			if(Stylus.px >= 80 && Stylus.px <= 208 && Stylus.py >= 105 && Stylus.py <= 151){
				option = 2;
				game = 1;
			} //No need to load the arrow position because you directly move to the next step.

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

	NF_CreateSprite(1, 10, 10, 10, 16, 48);	//The 6 doors
	NF_CreateSprite(1, 11, 11, 11, 16, 112);
	NF_CreateSprite(1, 12, 12, 12, 96, 48);
	NF_CreateSprite(1, 13, 13, 13, 96, 112);
	NF_CreateSprite(1, 14, 14, 14, 176, 48);
	NF_CreateSprite(1, 15, 15, 15, 176, 112);

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

	NF_MoveSprite(1, 6, arrowposx, arrowposy);

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

	NF_MoveSprite(1, 6, arrowposx, arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=120; wait++) {
		scanKeys();

		if (KEY_RIGHT & keysDown()) {
			option = option % 3 + 1;
		}
		if (KEY_LEFT & keysDown()) {
			option -= 1;
		}

		if (option == 1) {
			arrowposx = 40;
		}
		if (option == 2) {
			arrowposx = 120;
		}
		if ((option == 3) || (option == 0)) {
			option = 3;
			arrowposx = 200;
		}

		if (KEY_A & keysDown()) {
			game = 1;
		}

		touchRead(&Stylus);

		if(KEY_TOUCH & keysDown()) {

			//Door size: 64, 128 / There's a gap of 16 between 2 doors, or between 1 door and the border. The Y position is 48.
			if(Stylus.px >= 16 && Stylus.px <= 80 && Stylus.py >= 48 && Stylus.py <= 176){
				option = 1;
				game = 1;
			}	//No need to load the arrow position because you directly move to the next step.
			if(Stylus.px >= 96 && Stylus.px <= 160 && Stylus.py >= 48 && Stylus.py <= 176){
				option = 2;
				game = 1;
			}
			if(Stylus.px >= 176 && Stylus.px <= 240 && Stylus.py >= 48 && Stylus.py <= 176){
				option = 3;
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

	NF_MoveSprite(1, 7, arrowposx, arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	if ((arrowposx == 20) || (arrowposx == 142)) { //The only diference here is the arrow movement, because the arrow animation AND option position is horizontal.
		arrowposx += 10;
	}
	else {
		arrowposx -= 0.5;
	}

	NF_MoveSprite(1, 7, arrowposx, arrowposy); //Actually arrowposy doesn't change in this function.

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=120; wait++) {
		scanKeys();

		if (KEY_RIGHT & keysDown()) {
			option = option % 2 + 1;
			
			if (option == 1) {
				arrowposx = 30;
			}
			if (option == 2) {
				arrowposx = 152;
			}
		}
		if (KEY_LEFT & keysDown()) {
			option -= 1;
			
			if (option == 1) {
				arrowposx = 30;
			}
			if (option == 2) {
				arrowposx = 152;
			}
		}

		if (KEY_A & keysDown()) {
			game = 1;
		}

		touchRead(&Stylus);

		if(KEY_TOUCH & keysDown()) {

			//Stay button size: 64, 24 / Button pos: 64, 11
			if(Stylus.px >= 64 && Stylus.px <= 128 && Stylus.py >= 11 && Stylus.py <= 35){
				option = 1;
				game = 1;
			//Change button pos: 186, 11
			}	//No need to load the arrow position because you directly move to the next step.
			if(Stylus.px >= 186 && Stylus.px <= 250 && Stylus.py >= 11 && Stylus.py <= 35){
				option = 2;
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

	NF_LoadTiledBg("bg/Bottom3", "Bottom3", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom3");
	NF_UnloadTiledBg("Bottom2");

	CarDoor = rand() % 3 + 1;	//Door where the car is

	MontyHallInit();
	
		for (int wait=0; wait<=60; wait++) {
			swiWaitForVBlank();	//Waits for the next instruction. The DS is running at 60fps so waiting 60 times = wait 1 second 
		}

	NF_LoadTiledBg("bg/Top2", "Top2", 256, 256);
	NF_DeleteTiledBg(0, 3);
	NF_CreateTiledBg(0, 3, "Top2");
	NF_UnloadTiledBg("Top1_alt");
	
	NF_CreateSprite(1, 6, 6, 6, 120, 15);	//Arrow

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	arrowposx = 120;
	arrowposy = 15;
	option = 2;
	game = 0;

	while (game == 0) {	//Game changes to 1 in this function
		ChooseDoor();
	}

	ChosenDoor = option;	//Used to calculate the x position of the door (top-left based)
	option = (ChosenDoor - 1) * 80 + 16;
	NF_CreateSprite(1, 9, 9, 9, option, 48);	//Creates the door highlight
	NF_CreateSprite(1, 8, 8, 8, option, 112);

	NF_DeleteSprite(1, 6);	//Arrow
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	NF_LoadTiledBg("bg/Top1_alt", "Top1_alt", 256, 256);
	NF_DeleteTiledBg(0, 3);
	NF_CreateTiledBg(0, 3, "Top1_alt");
	NF_UnloadTiledBg("Top2");
	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

	do {
		WrongDoor = rand() % 3 + 1;	//Choses the wrong door, diferent from the car and chosen door. It picks a random door because of the case where the car door is the chosen door (there are in this case 2 posibilities, 1 the rest of the time)
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));

	option = WrongDoor * 2 + 8;
	NF_DeleteSprite(1, option);	//Deletes the doors
	option += 1;
	NF_DeleteSprite(1, option);
	
	option = WrongDoor * 80 - 48;	
	NF_CreateSprite(1, 4, 4, 4, option, 96);	//Goat
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}

	NF_LoadTiledBg("bg/Bottom3_alt", "Bottom3_alt", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom3_alt");
	NF_UnloadTiledBg("Bottom3");
	
	NF_LoadTiledBg("bg/Top3", "Top3", 256, 256);
	NF_DeleteTiledBg(0, 3);
	NF_CreateTiledBg(0, 3, "Top3");
	NF_UnloadTiledBg("Top1_alt");

	NF_CreateSprite(1, 7, 7, 7, 30, 15);	//Arrow

	arrowposx = 30;
	arrowposy = 15;
	option = 1;
	game = 0;

	while (game == 0) {
		ChangeDoor();
	}

	NF_DeleteSprite(1, 7);	//Arrow

	NF_LoadTiledBg("bg/Top1_alt", "Top1_alt", 256, 256);
	NF_DeleteTiledBg(0, 3);
	NF_CreateTiledBg(0, 3, "Top1_alt");
	NF_UnloadTiledBg("Top3");
	
	NF_LoadTiledBg("bg/Bottom3", "Bottom3", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom3");
	NF_UnloadTiledBg("Bottom3_alt");

	ChosenDoorCopy = ChosenDoor;	//Used to change ChosenDoor while still knowing the original chosen door.

	if (option == 2)
	{
		while ((ChosenDoor == ChosenDoorCopy) || (ChosenDoor == WrongDoor)){
			ChosenDoor =  rand () % 3 + 1;	//Determines the new door
		}

		option = (ChosenDoor - 1) * 80 + 16;	//Deletes the new door
		NF_MoveSprite(1, 9, option, 48);
		NF_MoveSprite(1, 8, option, 112);
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
			ChosenDoorCopy = rand() % 3 + 1;	//Determines the door to delete
		} while ((ChosenDoorCopy == ChosenDoor) || (ChosenDoorCopy == WrongDoor));
	}
	
	option = ChosenDoor * 2 + 8;	//Door chosen by the player
	NF_DeleteSprite(1, option);
	option += 1;
	NF_DeleteSprite(1, option);
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
			
	for (int wait=0; wait<=120; wait++) {
		swiWaitForVBlank();
	}
	
	option = ChosenDoorCopy * 2 + 8;	//3rd door left
	NF_DeleteSprite(1, option);
	option += 1;
	NF_DeleteSprite(1, option);
	
	NF_DeleteSprite(1, 4);
	NF_DeleteSprite(1, 8);
	NF_DeleteSprite(1, 9);

	if (ChosenDoor == CarDoor) {
		NF_LoadTiledBg("bg/Win", "Win", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Win");
		NF_UnloadTiledBg("Bottom3");
		option = 1; //Set option to 1 to remember used BG
	}
	else {
		NF_LoadTiledBg("bg/Lose", "Lose", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Lose");
		NF_UnloadTiledBg("Bottom3");
		option = 2; //Set option to 2 to remember used BG
	}
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	for (int wait=0; wait<=60; wait++) {
			swiWaitForVBlank();
		}
	
	NF_CreateSprite(1, 3, 3, 3, 235, 171);	//A button
	
	game = 0;
	int state = 0;
	
	while (game == 0) {
		
		if (state == 0) {
			state = 1;
			NF_ShowSprite(1,  3 , true);
		}
		else {
			state = 0;
			NF_ShowSprite(1,  3 , false);	//This part makes the A button flashing
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
	
	NF_DeleteSprite(1,3);	
	NF_LoadTiledBg("bg/Bottom2", "Bottom2", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom2");

	if (option == 1) {
		NF_UnloadTiledBg("Win");
	} 
	else {
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
	
	CarDoor = rand() % 3 + 1;
	ChosenDoor = rand() % 3 + 1;
	option = ChosenDoor * 80 - 40;
	
	NF_CreateSprite(1, 6, 6, 6, option, 15);	//Creates a sprite to show CPU chosen door
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}
	
	option = (ChosenDoor - 1) * 80 + 16;
	
	NF_CreateSprite(1, 9, 9, 9, option, 48);
	NF_CreateSprite(1, 8, 8, 8, option, 112);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	NF_DeleteSprite(1, 6);
	
	do {
		WrongDoor = rand() % 3 + 1;
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));
	
	option = WrongDoor * 2 + 8;
	NF_DeleteSprite(1, option);
	option += 1;
	NF_DeleteSprite(1, option);
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}
	
	NF_LoadTiledBg("bg/Bottom3_alt", "Bottom3_alt", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom3_alt");
	NF_UnloadTiledBg("Bottom3");
	
	option = strategy * 122 - 92;
	NF_CreateSprite(1, 7, 7, 7, option, 15);	//Creates a sprite to show CPU's choice (stay (1) or change (2), determined by the strategy variable)
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	for (int wait=0; wait<=speed; wait++) {
		swiWaitForVBlank();
	}
	
	NF_DeleteSprite(1, 7);

	ChosenDoorCopy = ChosenDoor;	//See 

	if (strategy == 2)
	{
		while ((ChosenDoor == ChosenDoorCopy) || (ChosenDoor == WrongDoor)){
			ChosenDoor =  rand () % 3 + 1;
		}
	}

	if (ChosenDoor == ChosenDoorCopy) {
		do {
			ChosenDoorCopy = rand() % 3 + 1;
		} while ((ChosenDoorCopy == ChosenDoor) || (ChosenDoorCopy == WrongDoor));
	}
	
	option = ChosenDoor * 2 + 8;
	NF_DeleteSprite(1, option);
	option += 1;
	NF_DeleteSprite(1, option);
	
	option = ChosenDoorCopy * 2 + 8;
	NF_DeleteSprite(1, option);
	option += 1;
	NF_DeleteSprite(1, option);

	NF_DeleteSprite(1, 8);
	NF_DeleteSprite(1, 9);

	if (ChosenDoor == CarDoor) {
		NF_LoadTiledBg("bg/Win", "Win", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Win");
		NF_UnloadTiledBg("Bottom3_alt");
		option = 1; //Set option to 1 to remember used BG
	}
	else {
		NF_LoadTiledBg("bg/Lose", "Lose", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Lose");
		NF_UnloadTiledBg("Bottom3_alt");
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
	
	if (option == 1) {
		NF_UnloadTiledBg("Win");

		if (strategy == 1) {
			StayStrategy -=	1;
			StayWins += 1;
		}
		else {
			ChangeStrategy -=	1;
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
			ChangeStrategy -=	1;
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
	
	CarDoor = rand() % 3 + 1;
	ChosenDoor = rand() % 3 + 1;
	
	do {
		WrongDoor = rand() % 3 + 1;
	} while ((WrongDoor == ChosenDoor) || (WrongDoor == CarDoor));

	ChosenDoorCopy = ChosenDoor;

	if (strategy == 2)
	{
		while ((ChosenDoor == ChosenDoorCopy) || (ChosenDoor == WrongDoor)){
			ChosenDoor =  rand () % 3 + 1;
		}
	}

	if (ChosenDoor == ChosenDoorCopy) {
		do {
			ChosenDoorCopy = rand() % 3 + 1;
		} while ((ChosenDoorCopy == ChosenDoor) || (ChosenDoorCopy == WrongDoor));
	}
	
	if (ChosenDoor == CarDoor) {

		if (strategy == 1) {
			StayStrategy -=	1;
			StayWins += 1;
		}
		else {
			ChangeStrategy -=	1;
			ChangeWins += 1;
		}
	} 
	else {
		
		if (strategy == 1) {
			StayStrategy -=	1;
			StayLoses += 1;
		}
		else {
			ChangeStrategy -=	1;
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

	option = 1;

	for (int wait=0; wait<=11; wait++) {
		NF_DeleteSprite(0, option);	//Deletes the number to replace it by the new one. I don't know how to do sprite frames, so I did like that.
		option += 1;
	}

	//Determines numbers shown by the sprites

	option = (StayWins - (StayWins % 100)) / 100 + 20;	//Thousands
	NF_CreateSprite(0, 1, option, 2, 105, 96);
	option = ((StayWins % 100) - (StayWins % 10)) / 10 + 20;	//Dozens
	NF_CreateSprite(0, 2, option, 2, 120, 96);
	option = (StayWins % 10) + 20;	//Units
	NF_CreateSprite(0, 3, option, 2, 135, 96);


	option = (StayLoses - (StayLoses % 100)) / 100 + 20;
	NF_CreateSprite(0, 4, option, 2, 175, 96);
	option = ((StayLoses % 100) - (StayLoses % 10)) / 10 + 20;
	NF_CreateSprite(0, 5, option, 2, 190, 96);
	option = (StayLoses % 10) + 20;
	NF_CreateSprite(0, 6, option, 2, 205, 96);


	option = (ChangeWins - (ChangeWins % 100)) / 100 + 20;
	NF_CreateSprite(0, 7, option, 2, 105, 128);
	option = ((ChangeWins % 100) - (ChangeWins % 10)) / 10 + 20;
	NF_CreateSprite(0, 8, option, 2, 120, 128);
	option = (ChangeWins % 10) + 20;
	NF_CreateSprite(0, 9, option, 2, 135, 128);


	option = (ChangeLoses - (ChangeLoses % 100)) / 100 + 20;
	NF_CreateSprite(0, 10, option, 2, 175, 128);
	option = ((ChangeLoses % 100) - (ChangeLoses % 10)) / 10 + 20;
	NF_CreateSprite(0, 11, option, 2, 190, 128);
	option = (ChangeLoses % 10) + 20;
	NF_CreateSprite(0, 12, option, 2, 205, 128);


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

	NF_LoadTiledBg("bg/Bottom3", "Bottom3", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom3");
	NF_UnloadTiledBg("Bottom2");
	
	NF_LoadTiledBg("bg/Top4", "Top4", 256, 256);
	NF_DeleteTiledBg(0, 3);
	NF_CreateTiledBg(0, 3, "Top4");
	NF_UnloadTiledBg("Top1_alt");
	
	NF_CreateSprite(0, 1, 20, 2, 105, 96);	//Initiates sprites for the first time.
	NF_CreateSprite(0, 2, 20, 2, 120, 96);
	NF_CreateSprite(0, 3, 20, 2, 135, 96);
	NF_CreateSprite(0, 4, 20, 2, 175, 96);
	NF_CreateSprite(0, 5, 20, 2, 190, 96);
	NF_CreateSprite(0, 6, 20, 2, 205, 96);
	NF_CreateSprite(0, 7, 20, 2, 105, 128);
	NF_CreateSprite(0, 8, 20, 2, 120, 128);
	NF_CreateSprite(0, 9, 20, 2, 135, 128);
	NF_CreateSprite(0, 10, 20, 2, 175, 128);
	NF_CreateSprite(0, 11, 20, 2, 190, 128);
	NF_CreateSprite(0, 12, 20, 2, 205, 128);
	
	ChangeStrategy = 1000;
	ChangeLoses = 0;
	ChangeWins = 0;
	
	StayStrategy = 1000;
	StayLoses = 0;
	StayWins = 0;
	
	for (int wait=0; wait<=3; wait++) {

		strategy = rand() % 2 + 1;	//Determines the strategy (1: Stay, 2: Change)

		MontyHallSimuPgrm(29);	//29 is the number of frames to wait, a demi-second (one more frame is automatically added)

		NF_LoadTiledBg("bg/Bottom3", "Bottom3", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Bottom3");

		MontyHallSimuResults();

	}

	
	for (int wait=0; wait<=5; wait++) {
				
		strategy = rand() % 2 + 1;

		MontyHallSimuPgrm(14);

		NF_LoadTiledBg("bg/Bottom3", "Bottom3", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Bottom3");	

		MontyHallSimuResults();
	
	}
	
	NF_LoadTiledBg("bg/Bottom4", "Bottom4", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom4");
	NF_UnloadTiledBg("Bottom3");
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	
	while ((StayStrategy >= 10) || (ChangeStrategy >= 10)) {

		for (int i=0; i<=9; i++) {	//Does 10 tests on 1 frame, 600 on 1 second.
			strategy = rand() % 2 + 1;
			MontyHallSimuFast();
		}
		MontyHallSimuResults();

	}
	
	// Do the last tests (to have 1000 on each)
	
	if (StayStrategy <= 10) {
			
		game = 9 - StayStrategy;	
		for (int i=0; i<=game; i++) {		
			strategy = 2;	
			MontyHallSimuFast();
		}
		
		game = StayStrategy;
		for (int i=0; i<=game; i++) {		
			strategy = 1;	
			MontyHallSimuFast();
		}
		
		MontyHallSimuResults();
		
		while (ChangeStrategy >= 1) {
			for (int i=0; i<=9; i++) {		
					strategy = 2;	
				MontyHallSimuFast();
			}
		
			MontyHallSimuResults();
		}
	}
	else {
			
		game = 9 - ChangeStrategy;	
		for (int i=0; i<=game; i++) {		
			strategy = 1;	
			MontyHallSimuFast();
		}
		
		game = ChangeStrategy;
		for (int i=0; i<=game; i++) {		
			strategy = 2;	
			MontyHallSimuFast();
		}
		
		MontyHallSimuResults();
		
		while (StayStrategy >= 1) {
			for (int i=0; i<=9; i++) {		
					strategy = 1;	
				MontyHallSimuFast();
			}
		
			MontyHallSimuResults();
		}
	}


	game = 0;
	int state = 0;
	
	NF_LoadTiledBg("bg/Bottom5", "Bottom5", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom5");
	NF_UnloadTiledBg("Bottom4");
	
	for (int wait=0; wait<=60; wait++) {
		swiWaitForVBlank();
	}
	
	NF_CreateSprite(1, 3, 3, 3, 235, 171);
	
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

	NF_DeleteSprite(1, 3);

	for (int wait=0; wait<=11; wait++) {
		NF_DeleteSprite(0, wait+1);
	}

	NF_LoadTiledBg("bg/Bottom2", "Bottom2", 256, 256);
	NF_DeleteTiledBg(1, 3);
	NF_CreateTiledBg(1, 3, "Bottom2");
	NF_UnloadTiledBg("Bottom5");
	
	NF_LoadTiledBg("bg/Top1_alt", "Top1_alt", 256, 256);
	NF_DeleteTiledBg(0, 3);
	NF_CreateTiledBg(0, 3, "Top1_alt");
	NF_UnloadTiledBg("Top4");

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

int main()
{
	srand (time (NULL)); //Init random
	consoleDemoInit(); 
	consoleClear();
	iprintf("\n The Monty Hall Problem\n DS port by Rph\n\n Please wait for NitroFS to init\n\n\n (If it takes too much time,\n it probably doesn't work. See\n readme.txt for information.)");
	//Print a waiting / bug message
	swiWaitForVBlank();
	soundEnable();
	NF_SetRootFolder("NITROFS");
	NF_Set2D(0,0);	//Init 2D
    NF_Set2D(1,0);
    
    NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);

	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);

	NF_InitRawSoundBuffers();
	
	LoadSprites();

	while (1){

		NF_LoadTiledBg("bg/Top1", "Top1", 256, 256);
		NF_LoadTiledBg("bg/Bottom1", "Bottom1", 256, 256);
		NF_CreateTiledBg(0, 3, "Top1");
		NF_CreateTiledBg(1, 3, "Bottom1");
		
		option = 1;
		arrowposx = 15;
		arrowposy = 48;
		game = 0;
		
		NF_CreateSprite(1, 5, 5, 5, 15, 48);

		while(game == 0)
		{
			Titlescreen();
		}

		NF_DeleteSprite(1, 5);

		NF_LoadTiledBg("bg/Top1_alt", "Top1_alt", 256, 256);
		NF_DeleteTiledBg(0, 3);
		NF_CreateTiledBg(0, 3, "Top1_alt");
		NF_UnloadTiledBg("Top1");

		NF_LoadTiledBg("bg/Bottom2", "Bottom2", 256, 256);
		NF_DeleteTiledBg(1, 3);
		NF_CreateTiledBg(1, 3, "Bottom2");
		NF_UnloadTiledBg("Bottom1");

		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		for (int wait=0; wait<=30; wait++) {
			swiWaitForVBlank();
		}
		
		if (option == 2) {
			SimulateMontyHall();
		}
		else {
			PlayMontyHall();
		}
		
			NF_DeleteTiledBg(1, 3);
			NF_UnloadTiledBg("Bottom2");

			NF_DeleteTiledBg(0, 3);
			NF_UnloadTiledBg("Top1_alt");

	}
	return 0;
}
