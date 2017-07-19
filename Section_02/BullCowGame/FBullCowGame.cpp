#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,9}, {6,13}, {7, 17} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}




EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if not isogram 
	if (!bIsIsogram(Guess) )
	{
		return EWordStatus::Not_Isogram; 
		//return not_isogram
	}
	//if not lowercass
	else if (!IsLowerCase(Guess))
	{
		//return not_lowercase
		return EWordStatus::Not_Lowercase; 
	}
	//if wrong length
	else if (Guess.length() != GetWordLength())
	{
		//return wrong_length
		return EWordStatus::Wrong_Length;
	}
	//else ok
	else
	{
		return EWordStatus::OK; 
	}
}


void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	const FString HIDEN_WORD = "bullcow"; // This must isogame
	MyHiddenWord = HIDEN_WORD;

	bGameIsWon = false;

	return;
} 

FBullCowGame::FBullCowGame()
{
	Reset();
}



// revice a valid guess, increase trun, returns count of bull and cow
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	//setup return varible
	FBullCowCount BullCowCount;
	int32 Word_LENGTH = MyHiddenWord.length();
	//loop through all letters in the HidenWord
	for (int32 MYHWChar = 0; MYHWChar < Word_LENGTH; MYHWChar++) 
	{
		//compare letters against the Guess
		for (int32 GChar = 0; GChar < Word_LENGTH; GChar++) 
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MYHWChar]) 
			{
				if (MYHWChar == GChar) //if they are in the same place
				{
					BullCowCount.Bulls++;	// increase bulls 
				}
				else 
				{
					BullCowCount.Cows++; //increase cows
				}
			}							
	 	}
	}
	if (BullCowCount.Bulls == Word_LENGTH) {
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;  
	}
	return BullCowCount;
}
/*
FString FBullCowGame::SubmitLength(int32 MLength)
{
	TMap<int32, FString> LengthToWord{ {3, "add"},{4, "moon"}, {5, "apple"},{6, "banana"},{7, ""} };// setup our map
	return LengthToWord[MLength];
}
*/


bool FBullCowGame::bIsIsogram(FString Word) const 
{ 
	//treat 0 or 1 letter words as isograms
	if (Word.length () < 2) {
		return true;
	}
	//loop through all the letters of the word
	TMap<char, bool> LetterSeen; //setup our map
	for(auto Letter:Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		//if the letter is in the map
		if (LetterSeen[Letter]) //if the letter is in the map
		{
			// we do NOT have isogram
			return false;
		}else{
		//add the letter to the map as seen
			LetterSeen[Letter] = true;
		}
	}
	return true; //for example in case where /0 is entered 
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) //if not a lower case letter
		{
			return false;
		} 
	}
	return true;
}
