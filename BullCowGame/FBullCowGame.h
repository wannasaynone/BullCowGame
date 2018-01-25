#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// 預設為0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Worng_Length,
	Not_Lowercase,
	Not_Vaild
};

class FBullCowGame{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	void Reset(int);
	EGuessStatus CheckGuessValidity(FString);
	FBullCowCount SubmitVaildGuess(FString);

private:
	bool bGameIsWon;
	int32 MyCurrentTry;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowecase(FString) const;
};