// montyhall.h
#ifndef MONTYHALL_H
#define MONTYHALL_H

// Déclaration de la fonction
void UnloadSFX();
void RumbleStart();
void RumbleEnd();

//Et des variables

extern int select_hold;
extern int arrowposx;	//Defines position for arrow (on menus) 
extern int arrowposy;	//Same
extern int option;	//Used in many ways, like choosed option or sprite number calculator
extern int game;	//Determines if exiting of the selecting loop (ex: titlescreen)
extern int quit;	//If you quit the game

extern int CarDoor;	//Door where the car is
extern int ChosenDoor;	//Door chosen by the player/computer
extern int ChosenDoorCopy;	//Duplicate of ChosenDoor (for the changing part of the program)
extern int WrongDoor;	//Door with the goat opened when you choose a door

extern int ChangeStrategy;		//Equal to 1000, number of times you simulate a game where you change
extern int StayStrategy;	//Equal to 1000, number of times you simulate a game where you stay on your choice

extern int StayWins;	//Speaks by itself
extern int StayLoses;	//Same
extern int ChangeWins;	//I should put something random here instead of saying it speaks by itself too
extern int ChangeLoses;	//How are you?

extern int strategy;	//Change or stay on choice

extern touchPosition Stylus;

#endif
