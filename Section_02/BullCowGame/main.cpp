#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame; //instance a new game 

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();

		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit application
}

void PrintIntro()
{
	// introduce the game 
	int32 WORD_LENGTH = BCGame.GetWordLength();
	std::cout << "\n\nWelcome to Bull and Cow Game \n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter word I'm thinking of?";
	std::cout << std::endl;
	return;
}

//play a single game to completion
void PlayGame()
{

	BCGame.Reset();
	// loop number of truns asking guess
	int32 MaxTry = BCGame.GetMaxTries();
	
	//Ask guess while  
	//is NOt won, and try number is less than maximum try
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry () <= MaxTry)
	{
		FText Guess = GetValidGuess();  
		//submit valid guess to the game 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "you guess was : " << Guess << std::endl;
		std::cout << "Bull: " << BullCowCount.Bulls << ". Cow: " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}


FText GetValidGuess() 
{
	EWordStatus Status = EWordStatus::Invalid_Statis;
	FText Guess = "";
	do 
	{
		// get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() <<" .Please inter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please input a " << BCGame.GetWordLength() << " letter word. \n ";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "plsase enter a word without repeating letters! \n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "plase tner lowercase! \n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK); // keep looping until we get valid input
			return Guess;

}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well done! you win!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!" << std::endl;
	}
}

bool AskToPlayAgain()
{
	std::cout << "do you want play the game? with the same word?(y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}