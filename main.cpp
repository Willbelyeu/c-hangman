#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for std::find
#include <cstdlib>   // for srand and rand
#include <ctime>     // for time
#include <thread>    // for std::this_thread::sleep_for
#include <chrono>    // for std::chrono::seconds

using namespace std;

string createDashes(int length) {
    return string(length, '-'); // Create a string of dashes
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z'); // Check if a character is a letter
}

int main() {
    // 1. Make a list of words.
    vector<string> wordList = {"ant", "basketball", "cow", "dragon", "elf", "fan", "gold", "house", "ireland", "jumpercables", "kangaroo", "lemon"};
    // Test the other way of inputing to the list/vector
    wordList.emplace_back("money");
    wordList.emplace_back("name");
    wordList.emplace_back("old");
    wordList.emplace_back("purse");
    wordList.emplace_back("quail");
    wordList.emplace_back("ring");
    wordList.emplace_back("string");
    wordList.emplace_back("tank");

    bool play=true;
    while (play==true){
        // 2. Randomly select a word
        srand(static_cast<unsigned int>(time(0))); // Seed for randomness
        string hiddenWord = wordList[rand() % wordList.size()];

        // Convert hiddenWord to lowercase for case-insensitive comparison
        string hiddenWordLower = hiddenWord;
        transform(hiddenWordLower.begin(), hiddenWordLower.end(), hiddenWordLower.begin(), ::tolower);

        // 3. Create a string of dashes for the guessed word
        string guessedWord = createDashes(hiddenWordLower.size());
        vector<char> guessedWordChars(guessedWord.begin(), guessedWord.end());

        // To keep track of guessed letters
        vector<char> guessedLetters;

        // Build the while loop that will hold things together.
        int failures = 0;
        const int chances = 5;
        while (failures < chances && guessedWord != hiddenWordLower) {
            cout << guessedWord << " | Chances left: " << chances - failures << endl;
            cout << "Enter a letter: ";
            char guessedLetter;
            cin >> guessedLetter;
            guessedLetter = tolower(guessedLetter); // Convert to lowercase for cleaner compare

            // Check if the letter has already been guessed
            if (find(guessedLetters.begin(), guessedLetters.end(), guessedLetter) != guessedLetters.end()) {
                cout << "That letter has already been used." << endl;
                continue; // Skip the rest of the loop iteration
            }
            if (isLetter(guessedLetter)!=true) {
                cout << "That is not a letter." << endl;
                continue; // Skip the rest of the loop iteration
            }

            // Add the guessed letter to the list of guessed letters
            guessedLetters.emplace_back(guessedLetter);

            // Check if the guessed letter is in the hidden word
            auto charInWord = find(hiddenWordLower.begin(), hiddenWordLower.end(), guessedLetter);
            if (charInWord != hiddenWordLower.end()) {
                // Update guessedWordChars for every match
                for (size_t i = 0; i < hiddenWordLower.size(); ++i) {
                    if (hiddenWordLower[i] == guessedLetter) {
                        guessedWordChars[i] = guessedLetter; // Reveal the guessed letter
                    }
                }
                guessedWord = string(guessedWordChars.begin(), guessedWordChars.end()); // Update guessedWord
            } else {
                failures += 1; // Increment failures for incorrect guesses
            }
        }


        if (guessedWord == hiddenWordLower) {
            cout << "You guessed " << guessedWord << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Congratulations! You guessed correctly! The man yet lives." << endl;
        }
        else {
            cout << "You guessed " << guessedWord << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "The right word was " << hiddenWord << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "The man has been hung." << endl;
        }

        string choice;
        while (choice!="n" && choice!="y") {
            cout << "Play again? y/n";
            cin>>choice;
            if (choice!="n" && choice!="y") {
                cout << "Not an option. Try y or n." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            }
        }
        if (choice=="n") {
            play=false;
            cout << "Have a good day! Thanks for playing.";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (choice=="y") {
            cout<< "We shall continue with a new word.";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }


    return 0;
}