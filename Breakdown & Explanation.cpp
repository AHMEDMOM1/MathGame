//Breakdown & Explanation of the Math Quiz Game
//This C++ program is a Math Quiz Game that allows users to answer arithmetic questions while tracking their performance. Below is a detailed breakdown of the code.

//1. Importing Libraries//
//--------------------------------------------
#include <iostream>   // For input/output operations (cin, cout).
#include <cstdlib>    // For system functions (e.g., clearing the screen, color changes).
#include <ctime>      // For random number generation (seeding rand()).
#include <vector>     // For storing multiple rounds of questions.
using namespace std;  // To avoid writing std:: before standard functions.

//iostream : Used for input (cin) and output (cout).
//cstdlib : Used for system-related functions (e.g., clearing the console, changing colors).
//ctime : Used to seed the random number generator (srand(time(NULL))).
//vector : Used to store multiple rounds of questions dynamically.
//using namespace std; : Allows direct use of cout, cin, and other standard library features.
//---------------------------------------------

//2. Enums for Question Levels & Operations//

enum QuestionDifficulty { Easy = 1, Medium, Hard, Mixed };
enum OperationType { Addition = 1, Subtraction, Division, Multiplication, MixedOperations };

//QuestionDifficulty : Defines difficulty levels for questions:
//Easy: Simple arithmetic with smaller numbers.
//Medium: Moderate arithmetic with medium-sized numbers.
//Hard: Complex arithmetic with larger numbers.
//Mixed: Randomly selects difficulty levels.
//OperationType : Defines arithmetic operations available in the quiz:
//Addition: Addition operation (+).
//Subtraction: Subtraction operation (-).
//Division: Division operation (/).
//Multiplication: Multiplication operation (*).
//MixedOperations: Randomly selects operations.
//----------------------------------------------

//3. Converting Enums to Readable Text//

string getOperationSymbol(OperationType type) {
    switch (type) {
        case Addition: return "+";
        case Subtraction: return "-";
        case Division: return "/";
        case Multiplication: return "*";
        default: return "Mixed";
    }
}

string getDifficultyName(QuestionDifficulty level) {
    string difficultyNames[4] = { "Easy", "Medium", "Hard", "Mixed" };
    return difficultyNames[level - 1];
}

//getOperationSymbol : Converts an OperationType enum to its corresponding symbol (e.g., +, -, *, /).
//getDifficultyName : Converts a QuestionDifficulty enum to its readable text representation (e.g., "Easy", "Medium")
//----------------------------------------------

//4. Generating Random Numbers

short generateRandomNumber(short lowerBound = 1, short upperBound = 101) {
    return lowerBound + rand() % (upperBound - lowerBound);
}

//Generates a random number between lowerBound and upperBound.
//Used to create random operands for math questions.
//----------------------------------------------

//5. Changing Console Color

int changeConsoleColor(bool isCorrect) {
    if (isCorrect) {
        return system("Color 2F"); // Green for correct answers.
    }
    cout << '\a'; // Play an alert sound.
    return system("Color 4F"); // Red for incorrect answers.
}

//Changes the console color based on whether the user's answer is correct or incorrect:
//Green (2F) : Correct answer.
//Red (4F) : Incorrect answer
//----------------------------------------------

//6. Reading User Preferences

short getNumberOfQuestions() {
    short numberOfQuestions{};
    do {
        cout << "How many questions do you want to answer? ";
        cin >> numberOfQuestions;
    } while (numberOfQuestions < 0 || numberOfQuestions > 100);
    return numberOfQuestions;
}

QuestionDifficulty selectDifficultyLevel() {
    short level{};
    do {
        cout << "Select Questions Difficulty [1] Easy, [2] Medium, [3] Hard, [4] Mixed? ";
        cin >> level;
    } while (level < 1 || level > 4);
    return (QuestionDifficulty)level;
}

OperationType selectOperationType() {
    short type{};
    do {
        cout << "Select Operation Type [1] Addition, [2] Subtraction, [3] Division, [4] Multiplication, [5] Mixed? ";
        cin >> type;
    } while (type < 1 || type > 5);
    return (OperationType)type;
}

//getNumberOfQuestions : Ensures the user enters a valid number of questions (between 1 and 100).
//selectDifficultyLevel : Prompts the user to select a difficulty level.
//selectOperationType : Prompts the user to select an operation type.
//---------------------------------------------------

//7. Data Structures for Quiz Storage

struct RoundDetails {
    short roundNumber{};
    short firstOperand{};
    short secondOperand{};
    char operationSymbol{};
    short correctResult{};
    short userAnswer{};
    QuestionDifficulty difficultyLevel{};
    OperationType operationType{};
    bool isAnswerCorrect{};
};

struct GameResults {
    short totalRounds{};
    QuestionDifficulty difficultyLevel{};
    OperationType operationType{};
    short correctAnswersCount{};
    short incorrectAnswersCount{};
    vector<RoundDetails> rounds{};
};

//RoundDetails : Stores information for a single math question, including operands, operation type, and results.
//GameResults : Stores overall game data, such as the total number of rounds, difficulty level, operation type, and performance metrics.
//-------------------------------------------------

//8. Performing Calculations
int calculateEquationResult(OperationType type, int num1, int num2) {
    switch (type) {
        case Addition: return num1 + num2;
        case Subtraction: return num1 - num2;
        case Division: return num1 / num2;
        case Multiplication: return num1 * num2;
    }
    return num1 + num2; // Default fallback.
}
//Performs the correct math operation based on the chosen operation type.
//-------------------------------------------------

//9. Generating Quiz Questions

RoundDetails createQuestion(RoundDetails round, GameResults results, int roundIndex) {
    round.roundNumber = roundIndex + 1;
    round.operationType = results.operationType;
    round.difficultyLevel = results.difficultyLevel;
    handleMixedChoice(round.difficultyLevel, round.operationType, results);
    round.firstOperand = generateRandomNumber(getLowerBoundForDifficulty(round.difficultyLevel), getUpperBoundForDifficulty(round.difficultyLevel));
    round.secondOperand = generateRandomNumber(getLowerBoundForDifficulty(round.difficultyLevel), getUpperBoundForDifficulty(round.difficultyLevel));
    round.operationSymbol = getOperationSymbolFromType(round.operationType);
    round.correctResult = calculateEquationResult(round.operationType, round.firstOperand, round.secondOperand);
    return round;
}

//Generates a random question based on difficulty and operation type.
//Handles mixed difficulty and operation types by randomizing them.
//---------------------------------------------------

//10. Running the Quiz

void validateUserAnswers(GameResults& results) {
    for (size_t i = 0; i < results.rounds.size(); i++) {
        displayEquation(results, i);
        results.rounds.at(i).userAnswer = getUserAnswer();
        results.rounds.at(i).isAnswerCorrect = (results.rounds.at(i).userAnswer == results.rounds.at(i).correctResult);
        updateScore(results, results.rounds.at(i).isAnswerCorrect);
        changeConsoleColor(results.rounds.at(i).isAnswerCorrect);
        displayAnswerFeedback(results.rounds.at(i).isAnswerCorrect, results.rounds.at(i).correctResult);
    }
}
//Loops through each question, validates the user's answer, updates the score, and provides feedback.
//--------------------------------------------------

//Final Steps

void startGameSession() {
    GameResults results{};
    results.totalRounds = getNumberOfQuestions();
    results.difficultyLevel = selectDifficultyLevel();
    results.operationType = selectOperationType();
    prepareGameRounds(results);
    validateUserAnswers(results);
    displayGameSummary(results);
}

void startGameLoop() {
    do {
        clearScreen();
        startGameSession();
    } while (wantsToPlayAgain(askToPlayAgain()));
}

int main() {
    srand(time(NULL));
    startGameLoop();
    return 0;
}

//startGameSession : Runs a single session of the game.
//startGameLoop : Controls the game loop, allowing the user to play again.
//main : Initializes the game and starts the loop.
//--------------------------------------------------
//🚀 Conclusion
//This breakdown provides everything you need to understand the logic and structure of your Math Quiz Game.
//Each section of the code has been explained in detail, making it easier to maintain or modify as needed. 
//Let me know if you need further assistance!







  
