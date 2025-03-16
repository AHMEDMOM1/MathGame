enum QuestionDifficulty { Easy = 1, Medium, Hard, Mixed };
enum OperationType { Addition = 1, Subtraction, Division, Multiplication, MixedOperations };

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

bool wantsToPlayAgain(char choice) {
    return choice == 'y' || choice == 'Y';
}

char askToPlayAgain() {
    char choice{};
    do {
        cout << "Do you want to play again? Y/N?";
        cin >> choice;
    } while (!(choice == 'y' || choice == 'Y' || choice == 'N' || choice == 'n'));
    return choice;
}

string getOperationSymbol(OperationType type) {
    switch (type) {
    case Addition:
        return "Add";
    case Subtraction:
        return "Sub";
    case Division:
        return "Div";
    case Multiplication:
        return "Multi";
    }
    return "Mixed";
}

string getDifficultyName(QuestionDifficulty level) {
    string difficultyNames[4] = { "Easy", "Medium", "Hard", "Mixed" };
    return difficultyNames[level - 1];
}

void displayFinalGameResult(GameResults results) {
    cout << "----------------------------\n";
    if (results.correctAnswersCount > results.incorrectAnswersCount) {
        cout << " Final Result: PASS :->)\n";
    }
    else if (results.correctAnswersCount < results.incorrectAnswersCount) {
        cout << " Final Result: FAIL :-(\n";
    }
    else {
        cout << " Final Result: AVERAGE :-|\n";
    }
    cout << "----------------------------\n\n";
}

void displayGameSummary(GameResults results) {
    displayFinalGameResult(results);
    cout << "Number of Questions    : " << results.totalRounds << endl;
    cout << "Questions Difficulty   : " << getDifficultyName(results.difficultyLevel) << endl;
    cout << "Operation Type         : " << getOperationSymbol(results.operationType) << endl;
    cout << "Number of Correct Answers : " << results.correctAnswersCount << endl;
    cout << "Number of Wrong Answers   : " << results.incorrectAnswersCount << "\n\n";
    cout << "----------------------------\n\n";
}

int changeConsoleColor(bool isCorrect) {
    if (isCorrect) {
        return system("Color 2F");
    }
    cout << '\a';
    return system("Color 4F");
}

void displayAnswerFeedback(bool isCorrect, short correctResult) {
    if (isCorrect) {
        cout << "Correct Answer :->)" << "\n\n";
    }
    else {
        cout << "Wrong Answer :-(" << endl;
        cout << "The correct answer is: " << correctResult << "\n\n";
    }
}

void updateScore(GameResults& results, bool isCorrect) {
    if (isCorrect) {
        results.correctAnswersCount++;
    }
    else {
        results.incorrectAnswersCount++;
    }
}

void handleInvalidInput(short& number) {
    while (!(cin >> number)) {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

short getUserAnswer() {
    short userAnswer{};
    if (!(cin >> userAnswer)) {
        handleInvalidInput(userAnswer);
    }
    return userAnswer;
}

void displayEquation(GameResults results, int roundIndex) {
    cout << "Question [" << roundIndex + 1 << "/" << results.totalRounds << "]\n\n";
    cout << results.rounds.at(roundIndex).firstOperand << endl;
    cout << results.rounds.at(roundIndex).secondOperand << " " << results.rounds.at(roundIndex).operationSymbol << "\n\n";
    cout << "--------\n";
}

int calculateEquationResult(OperationType type, int num1, int num2) {
    switch (type) {
    case Addition:
        return num1 + num2;
    case Subtraction:
        return num1 - num2;
    case Division:
        return num1 / num2;
    }
    return num1 * num2;
}

char getOperationSymbolFromType(OperationType type) {
    switch (type) {
    case Addition:
        return '+';
    case Subtraction:
        return '-';
    case Division:
        return '/';
    }
    return '*';
}

short getUpperBoundForDifficulty(QuestionDifficulty level) {
    switch (level) {
    case Easy:
        return 33;
    case Medium:
        return 66;
    }
    return 100;
}

short getLowerBoundForDifficulty(QuestionDifficulty level) {
    switch (level) {
    case Easy:
        return 1;
    case Medium:
        return 34;
    }
    return 64;
}

short generateRandomNumber(short lowerBound = 1, short upperBound = 101) {
    return lowerBound + rand() % (upperBound - lowerBound);
}

void handleMixedChoice(QuestionDifficulty& difficulty, OperationType& type, GameResults results) {
    if (results.operationType == MixedOperations) {
        type = (OperationType)generateRandomNumber(1, 5);
    }
    if (results.difficultyLevel == Mixed) {
        difficulty = (QuestionDifficulty)generateRandomNumber(1, 4);
    }
}

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

GameResults populateQuestions(GameResults results) {
    RoundDetails round{};
    results.rounds.resize(results.totalRounds);

    for (short i = 0; i < results.totalRounds; i++) {
        results.rounds.at(i) = createQuestion(round, results, i);
    }

    return results;
}

OperationType selectOperationType() {
    short type{};
    do {
        cout << "Select Operation Type [1] Addition, [2] Subtraction, [3] Division, [4] Multiplication, [5] Mixed ?";
        if (!(cin >> type)) {
            handleInvalidInput(type);
        }
    } while (type < 1 || type > 5);
    cout << "\n\n";
    return (OperationType)type;
}

QuestionDifficulty selectDifficultyLevel() {
    short level{};
    do {
        cout << "Select Questions Difficulty [1] Easy, [2] Medium, [3] Hard, [4] Mixed ?";
        if (!(cin >> level)) {
            handleInvalidInput(level);
        }
    } while (level < 1 || level > 4);
    return (QuestionDifficulty)level;
}

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

void prepareGameRounds(GameResults& results) {
    results = populateQuestions(results);
}

short getNumberOfQuestions() {
    short numberOfQuestions{};
    do {
        cout << "How many questions do you want to answer? ";
        if (!(cin >> numberOfQuestions)) {
            handleInvalidInput(numberOfQuestions);
        }
    } while (numberOfQuestions < 0 || numberOfQuestions > 100);
    return numberOfQuestions;
}

void startGameSession() {
    GameResults results{};

    results.totalRounds = getNumberOfQuestions();
    results.difficultyLevel = selectDifficultyLevel();
    results.operationType = selectOperationType();

    prepareGameRounds(results);
    validateUserAnswers(results);
    displayGameSummary(results);
}

void clearScreen() {
    system("cls");
    system("Color 0f");
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
