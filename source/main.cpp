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

#include "montyhall.h"
#include "title.h"
#include "simu.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int select_hold;
int arrowposx;	//Defines position for arrow (on menus) 
int arrowposy;	//Same
int option;	//Used in many ways, like choosed option or sprite number calculator
int game;	//Determines if exiting of the selecting loop (ex: titlescreen)
int quit = 0;	//If you quit the game

int blink; //Effect for the titlescreen buttons

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

int volume = 1;

int strategy;	//Change or stay on choice

bool rumble = false; //Used for rumble pack detection
uint8_t intensity = 0; //Rumbling max intensity

touchPosition Stylus;


/*
-------------------------------------------------

	LoadSprite() Function

	Loads all the graphics and palettes for sprites to RAM and VRAM.

	Used by: main()

-------------------------------------------------
*/

void LoadSprites() {
	
	NF_LoadSpriteGfx("sprites/numbers/Numbers", 20, 16, 16); //Numbers are showing when you simulate 2000 games.


	for (int sprite=1; sprite<=12; sprite++){

		NF_VramSpriteGfx(0, 20, sprite, true);
	}
	
	NF_LoadSpritePal("sprites/numbers/Numbers", 2); //Numbers is the common palette for the numbers's graphics
	NF_VramSpritePal(0, 2, 2);
	
	NF_LoadSpriteGfx("sprites/A button", 3, 16, 16); //Used to tell the player he can press A to continue. This can be useless if you're a big Nintendo gamer, BUT I am showing this project to non-gamers, so I need to make it intuitive.
	NF_LoadSpritePal("sprites/A button", 3);	//Bro is telling his life LOL
	NF_VramSpriteGfx(1, 3, 3, false);
	NF_VramSpritePal(1, 3, 3);

	NF_LoadSpriteGfx("sprites/Goat", 4, 32, 32); //Goat showing on wrong door to tell it's the wrong door.
	NF_LoadSpritePal("sprites/Goat", 4);
	NF_VramSpriteGfx(1, 4, 4, false);
	NF_VramSpritePal(1, 4, 4);

	NF_LoadSpriteGfx("sprites/Arrowbeta_vertical", 6, 16, 32); //Like the arrowbeta but smaller and vertical. Used in door selection.
	NF_LoadSpritePal("sprites/Arrowbeta_vertical", 6);
	NF_VramSpriteGfx(1, 6, 6, false);
	NF_VramSpritePal(1, 6, 6);

	NF_LoadSpriteGfx("sprites/Arrowbeta_small", 7, 32, 16);	//Like the arrowbeta but smaller. Used to ask the player if he/she wants to change.
	NF_LoadSpritePal("sprites/Arrowbeta_small", 7);
	NF_VramSpriteGfx(1, 7, 7, false);
	NF_VramSpritePal(1, 7, 7);

	NF_LoadSpriteGfx("sprites/CurrentDoorBottom", 8, 64, 64);	//Red Highlight on chosen door, top part (this sprite is split, because of the 64x64 limit with GRIT).
	NF_LoadSpritePal("sprites/CurrentDoorBottom", 8);
	NF_VramSpriteGfx(1, 8, 8, false);
	NF_VramSpritePal(1, 8, 8);

	NF_LoadSpriteGfx("sprites/CurrentDoorTop", 9, 64, 64);	//Red Highlight on chosen door, bottom part
	NF_LoadSpritePal("sprites/CurrentDoorTop", 9);
	NF_VramSpriteGfx(1, 9, 9, false);
	NF_VramSpritePal(1, 9, 9);

	NF_LoadSpriteGfx("sprites/UsedDoorTop", 10, 64, 64);	//Red Highlight on chosen door, top part
	NF_LoadSpritePal("sprites/UsedDoorTop", 10);
	NF_VramSpriteGfx(1, 10, 10, false);
	NF_VramSpritePal(1, 10, 10);

	NF_LoadSpriteGfx("sprites/UsedDoorBottom", 11, 64, 64);	//Red Highlight on chosen door, bottom part
	NF_LoadSpritePal("sprites/UsedDoorBottom", 11);
	NF_VramSpriteGfx(1, 11, 11, false);
	NF_VramSpritePal(1, 11, 11);

	NF_LoadSpriteGfx("sprites/TS_sheet", 12, 64, 64);	//Yellow highlight on titlescreen
	NF_VramSpriteGfx(1, 12, 12, true);
	NF_VramSpriteGfx(1, 12, 13, true);

	NF_LoadSpritePal("sprites/TS_sheet", 12); //Its palette
	NF_VramSpritePal(1, 12, 12);

}


/*
-------------------------------------------------

	Rumble functions

	Used if the player has a rumble pak inserted into his DS (Phat or Lite)

	Used by: many codes I presume

-------------------------------------------------
*/

void CheckRumble(){
	
	peripheralSlot2InitDefault();
	
	if(rumble == false){
		rumble = isRumbleInserted(); //Checks if a rumble pak has been inserted
		
		if(rumble== true){
			
			intensity = (rumble + 1) % (rumbleGetMaxRawStrength() + 1);
			rumbleInit();
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
		setRumble(intensity);
		
	}	
	
}

void RumbleEnd() {
	
	CheckRumble();
	
	if(rumble == true){
		setRumble(0);
		
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



	while (quit == 0){

		
		soundDisable();
		
		if (volume == 1) {
			soundEnable();
		}


		NF_LoadTiledBg("bg/Top/Title", "Title_T", 256, 256);
		NF_LoadTiledBg("bg/Bottom/Title", "Title_B", 256, 256);
		NF_CreateTiledBg(0, 3, "Title_T");
		NF_CreateTiledBg(1, 3, "Title_B");
		
		option = 1;
		game = 0;
		blink = 0;
		
		NF_CreateSprite(1, 12, 12, 12, 63, 43);
		NF_SpriteFrame(1, 12, 2);
		NF_CreateSprite(1, 13, 13, 12, 127, 43);
		NF_SpriteFrame(1, 13, 3);

		while(game == 0)
		{
			Title();
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
		
		NF_DeleteSprite(1, 12);
		NF_DeleteSprite(1, 13);

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
		
		if (option == 1) {
			PlayMontyHall();
			option = 0; //Set this to avoid game playing simulation without asking
		}
		if (option == 2) {
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
	//NF_DeleteSprite(1, 5);
	NF_DeleteSprite(1, 12);
	NF_DeleteSprite(1, 13);

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
