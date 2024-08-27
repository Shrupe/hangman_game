#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm> 

class HangMan {
    public:
        std::string selectedWord;
        std::vector<bool> correctGuesses;
        std::vector<char> wrongGuesses;
        int maxAttempts = 6;
        int wrongGuessCount = 0;

        std::string select_word() {
            std::string wordList[13] = {
                                "ADANA", 
                                "IZMIR", 
                                "BURSA", 
                                "ANKARA", 
                                "ADIYAMAN",
                                "BURDUR",
                                "DENIZLI",
                                "MUGLA",
                                "MERSIN",
                                "ISTANBUL",
                                "ANTALYA",
                                "VAN",
                                "SINOP"};
            std::srand(std::time(nullptr));
            int length = sizeof(wordList) / sizeof(wordList[0]);
            int selectedWordPos = std::rand() % length;

            return wordList[selectedWordPos];
        }

        void display_word(
                        const std::string& word,
                        const std::vector<bool>& correctGuesses
                        ) {
            for (size_t i = 0; i < word.length(); i++) {
                if (correctGuesses[i]) {
                    std::cout << word[i] << " ";
                } else {
                    std::cout << "_ ";
                }
            }
            std::cout << std::endl;
        }

        bool is_word_guessed(const std::vector<bool>& correctGuesses) {
            for (bool guessed : correctGuesses) {
                if (!guessed)
                    return false;
            }
            return true;
        }

        bool word_contains(char guess, int leftAttempt) {
            if (std::find(wrongGuesses.begin(), wrongGuesses.end(), guess) ==\
                wrongGuesses.end()) {
                wrongGuesses.push_back(guess);
                wrongGuessCount++;
                std::cout << "Incorrect guess! You have " << leftAttempt \
                << " attempts left." << std::endl;
                return false;
            }
        }

        bool is_word_contains(char guess) {
            bool correct = false;
            for (size_t i = 0; i < selectedWord.length(); i++) {  
                if (selectedWord[i] == guess) {
                    correctGuesses[i] = true;
                    correct = true;
                }
            }
            return correct;
        }

        void hangman_game() {
            selectedWord = select_word();

            // Initialize correctGuesses vector
            correctGuesses = std::vector<bool>(selectedWord.length(), false);  

            char guess;
            bool gameWon = false;

            std::cout << "Welcome to Hangman Game!\n" << "You have " <<\
            maxAttempts << " guesses.\n" << "Use upper case letters please." <<\
            std::endl;

            // Game loop.
            while (wrongGuessCount < maxAttempts && !gameWon) {
                display_word(selectedWord, correctGuesses);

                std::cout << "Enter a letter: ";
                std::cin >> guess;
                std::cout << std::endl;

                bool correct = is_word_contains(guess);

                int leftAttempt = maxAttempts - wrongGuessCount;

                if (!correct) {
                    word_contains(guess, leftAttempt);
                }

                if (is_word_guessed(correctGuesses)) {
                    gameWon = true;
                }
            }

            if (gameWon) {
                std::cout << "Congratulations! You've guessed the word: " <<\
                selectedWord << std::endl;
            } else {
                std::cout << "You've run out of attempts. The word was: " <<\
                selectedWord << std::endl;
            }
        }
};

int main() {
    HangMan HG;
    HG.hangman_game();
    return 0;
}

