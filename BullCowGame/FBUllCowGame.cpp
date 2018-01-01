#pragma once //file to be included only once in a singe compilation

#include "FBullCowGame.h"
#include <map>
#define TMap std::map   //identifier replacement / to make syntax Unreal friendly

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

//FString FBullCowGame::GetWordForGame(int32 WordLength) const{
//	TMap<int32, FString> HiddenWordsList{ {3,"asd"},{4,"asdf"} };
//	return HiddenWordsList[WordLength];
//}

void FBullCowGame::Reset() {
	//primitive tyyppien kanssa constexpr / compiler muotoinen
	const FString HIDDEN_WORD = "planet"; //this must be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != (unsigned)GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::Ok;
	}
	return EGuessStatus::Ok; // TODO make actual error
}

//receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount FBullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++) {
		for (int32 j = 0; j < HiddenWordLength; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					FBullCowCount.Bulls++;
				}
				else {
					FBullCowCount.Cows++;
				}	
			} 
		}
	}
	if (FBullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return FBullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;// = TMap<char, bool>();
	for (auto Letter : Word) // foreach käytännössä     auto = var 
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { //returns false if letter not found in map
			return false;
		}
		else {
			LetterSeen[Letter] = true; // adds the letter to the map as seen
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}