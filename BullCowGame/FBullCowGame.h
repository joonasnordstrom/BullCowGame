/* THe game logic (no ciew code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

using FString = std::string;  //only a naming standard / to make syntax Unreal friendly
using int32 = int;

struct FBullCowCount {  //structs are like simple classes/objects that can hold in some variables, not sure about functions
	int32 Bulls = 0;
	int32 Cows = 0;
}/*t‰ss‰ voidaan m‰‰ritt‰‰ heti k‰ytett‰v‰t muuttujat tyyliin bullcowgame,BCgame; tai BCGame[4]*/;

//enum ilman classia globaalissa scopessa, esim enum EGuessStatus {}
enum class EGuessStatus {
	InvalidStatus,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;  //kaikki Getterit const tyyppisi‰
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; //TODO make a more rich return value.

	void Reset(); // TODO make a more rich return value.
	
	//counts bulls & cows, and increases try # assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const; 
	bool IsLowercase(FString) const;
};
