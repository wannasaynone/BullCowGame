#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() {}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,7},{5,10},{6,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
		return true;

	TMap<wchar_t, bool> LetterSeen;

	for (wchar_t Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
			return false;
		else
			LetterSeen[Letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowecase(FString Word) const
{
	for (auto Letter : Word) // auto->char
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}

void FBullCowGame::Reset(int WordLength)
{
	bGameIsWon = false;

	const FString HIDDEN_WORD_3 = "ant";
	const FString HIDDEN_WORD_4 = "taxi";
	const FString HIDDEN_WORD_5 = "least";
	const FString HIDDEN_WORD_6 = "unreal";

	switch (WordLength)
	{
	case 3:
		MyHiddenWord = HIDDEN_WORD_3;
		break;
	case 4:
		MyHiddenWord = HIDDEN_WORD_4;
		break;
	case 5:
		MyHiddenWord = HIDDEN_WORD_5;
		break;
	case 6:
		MyHiddenWord = HIDDEN_WORD_6;
		break;
	default:
		MyHiddenWord = HIDDEN_WORD_4; // 預設最簡單
		break;
	}

	MyCurrentTry = 1;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowecase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != MyHiddenWord.length())
	{
		return EGuessStatus::Worng_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitVaildGuess(FString Guess)
{
	MyCurrentTry++;
	
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessWordLengh = Guess.length();

	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < GuessWordLengh; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;

	return BullCowCount;
}

