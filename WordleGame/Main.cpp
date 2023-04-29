#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>

bool wordInVector(const std::string& word, const std::vector<std::string>& vec)
{
	for (const auto& el : vec)
	{
		if (el == word)
			return true;
	}

	return false;
}

void gradeTheGuess(const std::string& guess, const std::string& answer)
{
	for (size_t i = 0; i < guess.size(); i++)
	{
		if (answer.find(guess[i]) != std::string::npos)
		{
			if (guess[i] == answer[i])
			{
				std::cout << guess[i] << " - CORRECT PLACE" << std::endl;
			}
			else
			{
				std::cout << guess[i] << " - INCORRECT PLACE" << std::endl;
			}
		}
		else
		{
			std::cout << guess[i] << " - NO MATCH" << std::endl;
		}
	}
}

int main()
{
	//Load the list of words
	std::vector<std::string> wordsList;
	std::ifstream wordsFile("sgb-words.txt");
	std::string word;
	while (wordsFile >> word)
	{
		wordsList.emplace_back(word);
	}

	//Chose a target word at random
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> wordsDist(0, wordsList.size() - 1);

	const std::string target = wordsList[wordsDist(rng)];

	//std::cout << target << std::endl;
	int tries = 0;
	//Game loop
	while (tries < 5)
	{
		std::cout << "Guess a five letter word: ";
		std::string guess;
		std::cin >> guess;

		if (guess.size() != 5)
		{
			std::cout << "The word must have 5 letters" << std::endl;
			continue;
		}

		if (!wordInVector(guess, wordsList))
		{
			std::cout << "This is not a real word, guess again" << std::endl;
			continue;
		}

		gradeTheGuess(guess, target);
		if (guess == target)
		{
			std::cout << "Congrats you guessed the word" << std::endl;
			break;
		}

		if (tries == 4)
		{
			std::cout << "The word was: " << target <<  " Better luck next time" << std::endl;
		}
		tries++;
		
	}

	std::cin.get();
}