/*
-------------------------------------------------

	NightFox's Lib Template
	Ejemplo de 3D Sprites

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com
	Inicio 10 de Octubre del 2009

	(c)2009 - 2011 NightFox & Co.

-------------------------------------------------
*/

/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Includes LibNDS
#include <nds.h>
#include <nds/touch.h>
#include <nds/input.h>

// Includes NFlib
#include <nf_lib.h>

#define click() (keysDown() & KEY_TOUCH)
#define release() (keysUp() & KEY_TOUCH)
#define hold() (keysHeld() & KEY_TOUCH)

#define MAXSPRITES 32


/*
-------------------------------------------------
	void() - Blocs de définition
-------------------------------------------------
*/

void DoorGame ()
{
  // Determine door where the car is	
  int CarDoor = rand () % 3 + 1;
  // default initialization of chosen door
  int ChosenDoor = 0;
  // default initialization of strategy
  char Change = 'u';
  
  while (ChosenDoor != 1 && ChosenDoor != 2 && ChosenDoor != 3)
	{
	  //std::cout << "Door (Between 1 and 3): ";
	  //std::cin >> ChosenDoor;
	}

  // find a door different from the chosen one and not containing the car
  // at most 2 possibilites, maybe only one
  // choose a door at random and increment until appropriate door is found
  int WrongDoor = rand() % 3 + 1;
  while (WrongDoor == ChosenDoor | WrongDoor == CarDoor)
	{
	  WrongDoor = WrongDoor % 3 + 1;
	}

  //std::cout << "The door number " << WrongDoor << " doesn't contain the car. Do you want to change? [Y/N]: ";
  //std::cin >> Change;
  //cout << endl;

  // tirer au hasard parmi les portes restantes
  // implementation : tant qu'on n'a pas choisi une porte différente de WrongDoor et ChosenDoor, on continue
  int ChangeChosenDoor = ChosenDoor;
  
  if (Change == 'Y')
	{
	  do {
		  ChangeChosenDoor == rand () % 3 + 1;
	  } while ((ChangeChosenDoor == WrongDoor) | (ChangeChosenDoor == ChosenDoor));
	}

	ChosenDoor == ChangeChosenDoor;

  if (CarDoor == ChosenDoor) {
	//std::cout << "You won" << std::endl;
	}
  else
  {
	//std::cout << "You lost" << std::endl;
	}
}


/*
-------------------------------------------------
	Main() - Bloque general del programa
-------------------------------------------------
*/

int main(int argc, char **argv) {

	// Inicializa el random
	srand(time(NULL));

	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();
	iprintf("\n The Monty Hall Problem\n DS port by Rph\n\n Please wait for NitroFS to init\n\n\n (If it takes too much time,\n it probably doesn't work. See\n [PLACEHOLDER URL]\n for information.)");
	swiWaitForVBlank();

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

	// Inicializa el motor 2D
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);				// Modo 2D_0 en la pantalla inferior

	// Inicializa los fondos tileados
	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitTiledBgSys(0);		// Inicializa los fondos Tileados para la pantalla superior
	NF_InitTiledBgSys(1);		// Inicializa los fondos Tileados para la pantalla inferior

	// Inicializa los buffers de los Sprites
	NF_InitSpriteBuffers();		// Inicializa los buffers para almacenar sprites y paletas

	touchPosition touch;
	soundEnable();

       while(true) {
		scanKeys();
		touchRead(&touch);
		
		//Titlescreen
				
       }


	// Espera al sincronismo vertical
	swiWaitForVBlank();

	return 0; 

}
