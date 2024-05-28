#include <nds.h>
#include <nf_lib.h>
#include <fat.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arrowposx = 15;
int	arrowposy = 48;
int	option = 1;
int game = 0;


void Titlescreen(){

	NF_MoveSprite(1, 5, arrowposx, arrowposy);

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

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
		scanKeys();

		if ((KEY_UP & keysDown()) || (KEY_DOWN & keysDown())) {
			
			if (option == 1) {
				option = 2;
				arrowposy = 112;
				NF_MoveSprite(1, 5, arrowposx, arrowposy);
				break;
			}
			if (option == 2) {
				option = 1;
				arrowposy = 48;
				NF_MoveSprite(1, 5, arrowposx, arrowposy);
			}
		}
		if (KEY_A & keysDown()) {
			game = 1;
		}
	}
}

void PlayMontyHall() {
		
	NF_DeleteTiledBg(1, 3);
	NF_UnloadTiledBg("Bottom2");
	NF_LoadTiledBg("bg/Bottom3", "Bottom3", 256, 256);
	NF_CreateTiledBg(1, 3, "Bottom3");

	NF_CreateSprite(1, 10, 10, 10, 16, 48);
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

		for (int wait=0; wait<=60; wait++) {
			swiWaitForVBlank();
		}	

	NF_DeleteTiledBg(0, 3);
	NF_UnloadTiledBg("Top1_alt");
	NF_LoadTiledBg("bg/Top2", "Top2", 256, 256);
	NF_CreateTiledBg(0, 3, "Top2");	
	
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

		while (1) {
			swiWaitForVBlank();
		}	

}


int main()
{
    srand (time (NULL)); //Init random
    consoleDemoInit(); 
	consoleClear();
	iprintf("\n The Monty Hall Problem\n DS port by Rph\n\n Please wait for NitroFS to init\n\n\n (If it takes too much time,\n it probably doesn't work. See\n [PLACEHOLDER URL]\n for information.)");
	//Print a waiting / bug message
	swiWaitForVBlank();		
	soundEnable();
	NF_SetRootFolder("NITROFS");
	NF_Set2D(0,0);
    NF_Set2D(1,0);
    
    NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);
	
    NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	
    NF_InitRawSoundBuffers();
        
	NF_LoadSpriteGfx("sprites/Arrowbeta", 5, 64, 32);
	NF_LoadSpritePal("sprites/Arrowbeta", 5);
	NF_VramSpriteGfx(1, 5, 5, false);
	NF_VramSpritePal(1, 5, 5);
	
	NF_LoadSpriteGfx("sprites/Door1Top", 10, 64, 64);
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
	
    while (1)   
    {	
		NF_LoadTiledBg("bg/Top1", "Top1", 256, 256);
		NF_LoadTiledBg("bg/Bottom1", "Bottom1", 256, 256);
		NF_CreateTiledBg(0, 3, "Top1");
		NF_CreateTiledBg(1, 3, "Bottom1");
		NF_CreateSprite(1, 5, 5, 5, 15, 32);

		while(1)
		{
			Titlescreen();

			if (game == 1)
			{
				break;
			}
		}

		NF_DeleteSprite(1, 5);

		NF_DeleteTiledBg(0, 3);
		NF_UnloadTiledBg("Top1");
		NF_LoadTiledBg("bg/Top1_alt", "Top1_alt", 256, 256);
		NF_CreateTiledBg(0, 3, "Top1_alt");

		NF_DeleteTiledBg(1, 3);
		NF_UnloadTiledBg("Bottom1");
		NF_LoadTiledBg("bg/Bottom2", "Bottom2", 256, 256);
		NF_CreateTiledBg(1, 3, "Bottom2");

		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		for (int wait=0; wait<=30; wait++) {
			swiWaitForVBlank();
		}
		
		if (option == 2) {
			
		}
		else {
			PlayMontyHall();
		}
		
		game = 0;
		
    }
    return 0;
}
