# Math Quiz Game

## Overview
The **Math Quiz Game** is a simple yet engaging C++ application designed to help users practice arithmetic operations while tracking their performance. The game generates math questions based on user preferences, such as difficulty level and operation type, and evaluates the user's answers in real-time. With its clean design and intuitive interface, this project is an excellent example of how simplicity can lead to powerful learning tools.

---

## Features
### 1. **Customizable Difficulty Levels**
   - Users can choose from four difficulty levels:
     - **Easy**: Simple arithmetic with smaller numbers.
     - **Medium**: Moderate arithmetic with medium-sized numbers.
     - **Hard**: Complex arithmetic with larger numbers.
     - **Mixed**: Randomly selects difficulty levels for each question.

### 2. **Flexible Operation Types**
   - Supports five types of arithmetic operations:
     - **Addition (+)**
     - **Subtraction (-)**
     - **Division (/)**
     - **Multiplication (*)**
     - **Mixed Operations**: Randomly selects operations for each question.

### 3. **Dynamic Question Generation**
   - Questions are generated dynamically based on the selected difficulty and operation type.
   - Ensures a unique experience every time the game is played.

### 4. **Real-Time Feedback**
   - Immediate feedback on each answer, including correctness and the correct answer if the user is wrong.
   - Console color changes to indicate success (green) or failure (red).

### 5. **Performance Tracking**
   - Tracks the number of correct and incorrect answers.
   - Provides a final summary of the user's performance, including pass/fail status.

### 6. **Replayability**
   - Users can play multiple sessions without restarting the program.
   - Option to continue playing or exit after each session.

---

## Why This Project?
This project demonstrates the power of simplicity in software development. By focusing on a single goal—helping users practice math—the game achieves its purpose effectively without unnecessary complexity. It also serves as an excellent starting point for beginners learning C++ programming, showcasing key concepts such as:
- **Enums**: For representing fixed sets of values (e.g., difficulty levels, operation types).
- **Structs**: For organizing related data (e.g., questions, results).
- **Randomization**: For generating dynamic content.
- **Input Validation**: For ensuring robust user interaction.
- **Modular Design**: For maintaining clean and reusable code.

---

## How to Use
### 1. **Setup**
   - Ensure you have a C++ compiler installed (e.g., GCC, Clang, or MSVC).
   - Compile the code using your preferred IDE or command-line tool:
     ```bash
     g++ -o math_quiz math_quiz.cpp
     ```
   - Run the executable:
     ```bash
     ./math_quiz
     ```

### 2. **Game Flow**
   - **Step 1**: Choose the number of questions you want to answer.
   - **Step 2**: Select a difficulty level (Easy, Medium, Hard, Mixed).
   - **Step 3**: Choose an operation type (Addition, Subtraction, Division, Multiplication, Mixed).
   - **Step 4**: Answer the generated questions one by one.
   - **Step 5**: View your performance summary at the end of the session.
   - **Step 6**: Decide whether to play again or exit.

### 3. **Example Interaction**
```plaintext
How many questions do you want to answer? 5
Select Questions Difficulty [1] Easy, [2] Medium, [3] Hard, [4] Mixed? 1
Select Operation Type [1] Addition, [2] Subtraction, [3] Division, [4] Multiplication, [5] Mixed? 1

Question [1/5]
5 + 3 = 
8
Correct!

Question [2/5]
7 + 2 = 
9
Correct!

...

----------------------------
 Final Result: PASS :->)
----------------------------
Number of Questions    : 5
Questions Difficulty   : Easy
Operation Type         : Add
Number of Correct Answers : 5
Number of Wrong Answers   : 0

Do you want to play again? Y/N? y
```

---

## Learning Objectives
This project is ideal for:
- **Beginners**: Learn fundamental C++ concepts like enums, structs, loops, and functions.
- **Intermediate Developers**: Practice modular design and code organization.
- **Educators**: Use the game as a teaching tool for arithmetic practice.

---

## Future Enhancements
While the current version is functional and user-friendly, there are several ways to enhance the game further:
- **Timer Mode**: Add a timer to challenge users to answer questions within a set time limit.
- **Leaderboard**: Store and display high scores across multiple sessions.
- **Graphical Interface**: Develop a GUI version using libraries like SFML or Qt.
- **Advanced Operations**: Include more complex operations like exponents, square roots, or fractions.
- **Localization**: Support multiple languages for broader accessibility.

---

## Conclusion
The **Math Quiz Game** is a testament to the idea that simplicity can be powerful. By focusing on core functionality and user experience, this project delivers a fun and educational tool for practicing math skills. Whether you're a beginner looking to learn C++ or an educator seeking a practical teaching aid, this game is a valuable resource.

Feel free to contribute, modify, or expand upon this project to suit your needs. Happy coding! 🚀
