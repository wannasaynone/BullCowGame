#include <iostream>
#include <string>

#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
int32 SelectWordLength();
void PlayGame();
FText GetVaildGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int32 main()
{
	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl << "--------------------------------" << std::endl;
	} while (bPlayAgain);

	std::cout << std::endl;
	return 0;
}

void PlayGame()
{
	BCGame.Reset(SelectWordLength());

	std::cout << "猜 " << BCGame.GetHiddenWordLength() << " 個字母的單字\n\n";

	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetVaildGuess();
		FBullCowCount BullCowCount = BCGame.SubmitVaildGuess(Guess);

		std::cout << "位置正確、字母正確 = " << BullCowCount.Bulls;
		std::cout << ". 只有字母正確 = " << BullCowCount.Cows;
		std::cout << ", 你猜的是 " << Guess << std::endl;
		std::cout << std::endl;
	}

	return;
}

void PrintIntro()
{
	std::cout << "Welcome To Bulls And Cows\n";
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;
	return;
}

int32 SelectWordLength()
{
	FString Input = "";

	std::cout << "輸入阿拉伯數字3~6決定字長" << std::endl;
	std::getline(std::cin, Input);
	return std::stoi(Input);
}

FText GetVaildGuess()
{
	EGuessStatus status = EGuessStatus::Not_Vaild;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "第 " << CurrentTry << " 次猜，總共 " << BCGame.GetMaxTries() << " 次機會\n輸入你的猜測:";
		std::getline(std::cin, Guess);

		status = BCGame.CheckGuessValidity(Guess);

		switch (status)
		{
		case EGuessStatus::Worng_Length:
			std::cout << "錯誤：輸入一個 " << BCGame.GetHiddenWordLength() << " 字母長的單字\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "錯誤：輸入一個沒有重複字母的單字\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "錯誤：輸入的單字不能包含大寫字母\n";
			break;
		default:
			break;
		}

		std::cout << std::endl;
	} while (status != EGuessStatus::OK);

	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "再玩一次？ (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}

void PrintGameSummary()
{
	if(BCGame.IsGameWon())
		std::cout << "你猜到了！!\n";
	else
		std::cout << "你沒猜到！\n";

	return;
}
