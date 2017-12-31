#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	//enum ilman classia globaalissa scopessa, esim enum EGuessStatus {}
	InvalidStatus,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;  //kaikki Getterit const tyyppisiä
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; //TODO make a more rich return value.

	void Reset(); // TODO make a more rich return value.
	
	//counts bulls & cows, and increases try # assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};
