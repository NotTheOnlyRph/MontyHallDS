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

	MontyHallSimuPgrm() Function

	Using for CPU to simulate the game

	Used by: SimulateMontyHall()

	Using: MontyHallInit().

-------------------------------------------------
*/

void MontyHallSimuPgrm(int speed) {


	int Doorx[] = {40, 120, 200};
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
	
	NF_CreateSprite(1, 10, 10, 10, Doorx[WrongDoor] - 24, 48); //Creates the opened door over the background
	NF_CreateSprite(1, 11, 11, 11, Doorx[WrongDoor] - 24, 112);
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

	NF_DeleteSprite(1, 10);
	NF_DeleteSprite(1, 11);

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
