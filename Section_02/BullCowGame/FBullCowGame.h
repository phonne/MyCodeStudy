/*
The game logic (no view code or direct user interaction)
The game is a simple guess  the word game based on Mastermind
*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

//all integers initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_Statis,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase, 
};

class FBullCowGame
{
public:
	FBullCowGame();
	bool IsGameWon() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	EWordStatus CheckGuessValidity(FString) const; 
	int32 GetWordLength() const;
	bool IsLowerCase(FString) const;
	
	void Reset(); 
	// provide a method for counting bulls & cows, and increasing try
	FBullCowCount SubmitValidGuess(FString);
	FString SubmitLength(int32);
// just try~
private:
	// initialize in Reset
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool bIsIsogram (FString)const;
};	