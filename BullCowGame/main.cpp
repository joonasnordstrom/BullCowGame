/*
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; //FText unrealissa käytettävä standardi "user interaction" eli käyttäjän kanssa kommunikointiin tms.
using int32 = int; // unreal standardi

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which is re-used across plays

int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; //exit application
}

void PrintIntro() {
	std::cout << "\n\nWelcome to b&C game \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}

//plays a single game to completion <- onks toi englantia?
void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of turns asking for guess
	// TODO change from FOR to while loop once we are validating tries
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); // TODO make loop checking valid
									   //submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

FText GetValidGuess() {
	int32 CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	FText Guess = "";

	do {
		//get guess from player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Not isogram";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Not lowercase";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Wrong length";
			break;
		default:
			break;
		}

		std::cout << std::endl;
	} while (Status != EGuessStatus::Ok);
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << " WELL DON YOU WIN!";
	}
	else {
		std::cout << "Better luck next time!";
	}
}