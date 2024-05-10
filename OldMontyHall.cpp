#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

// global parameters
const int DoorNumber = 3; // number of doors

//Programme du choix de la porte

void DoorGame ()
{
  // determine door where the car is	
  int CarDoor = rand () % DoorNumber + 1;
  // default initialization of chosen door
  int ChosenDoor = 0; 
  // default initialization of strategy
  char Change = 'u';
  while (ChosenDoor >= 1 && ChosenDoor =< DoorNumber)
	{
	  std::cout << "Door (Between 1 and 3): ";
	  std::cin >> ChosenDoor;
	  std::cin.ignore();
	}

  // find a door different from the chosen one and not containing the car
  // at most 2 possibilites, maybe only one
  // choose a door at random and increment until appropriate door is found
  int WrongDoor = rand() % DoorNumber + 1;
  while (WrongDoor == ChosenDoor | WrongDoor == CarDoor)
	{
	  WrongDoor = WrongDoor % DoorNumber + 1;
	}

  std::cout << "The door number " << WrongDoor <<
	" doesn't contain the car. Do you want to change? [Y/N]: ";
  std::cin >> Change;
  cout << endl;

  while (Change != 'Y' && Change != 'N')
	{
	  std::cout << "Your answer is incorrect. The door n°" << WrongDoor <<
		" doesn't contain the car. Do you want to change? [Y/N]: ";
          std::cin >> Change;
	}

  // tirer au hasard parmi les portes restantes
  // implementation : tant qu'on n'a pas choisi une porte différente de WrongDoor et ChosenDoor, on continue
  // variable type ChangeChosenDoor
  int ChosenDoorCache = ChosenDoor
  
  if (Change == 'Y')
	{
		while (ChosenDoorCache == ChosenDoor){
			ChosenDoorCache =  rand () % DoorNumber + 1;
		}
	}

  if (ChosenDoor == 0)
	{
	  ChosenDoor == 3;
	}

  std::cout << std::endl << "Chosen door : " << ChosenDoor << endl << "Correct door" << CarDoor << std::endl << std::endl;

  if (CarDoor == ChosenDoor)
	std::cout << "You won" << std::endl;
  else
	std::cout << "You lost" << std::endl;
}


//Programme de base

int
main ()
{
  srand ((unsigned) time (NULL));
  int CarDoor = 1, DoorNumber = 3, Menu = 1, ChosenDoor = 1;
  std::cout << "The Monty Hall problem" << std::endl << "nds port by Rph" << std::endl << "Press any key to continue" << std::endl;
  std::cin.ignore ();

  // Debut du programme

  DoorGame ();

  return 0;
}
