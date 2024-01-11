#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>


using namespace std;

enum enQuestionLevel {
    Easy = 1,
    Med = 2,
    Hard = 3,
    MixLevel = 4
};
enum enOperations {
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5
};

struct stQuestion {
    int UpperNumber = 0;
    int DownNumber = 0;
    enOperations operatorType;
    enQuestionLevel questionLevel;
    int answer = 0;
    int userAnswer = 0;
    bool isAnswerCorrect = false;
};

struct stQuizzes {
    stQuestion questionList[100];
    short numberOfQuestion = 0;
    enQuestionLevel questionLevel;
    enOperations operatorType;
    int numberOfWrongAnswer = 0;
    int numberOfRightAnswer = 0;
    bool isPass = false;
};

int randomNumbers(int from, int to) {
    int random = rand() % (to - from + 1) + from;
    return random;
}

int readPositiveNumber(const string& msg) {
    int number;
    cout << msg;
    cin >> number;
    return number;
}

short readHowManyQuestion() {
    short questionCount = 0;
    do {
        questionCount = (short) readPositiveNumber("How Many Question Do You Want? :");
    } while (questionCount < 1 || questionCount > 10);
    return questionCount;
}

enQuestionLevel readLevel() {
    short level;
    do {
        level = (short) readPositiveNumber("What the Level u Want [1]:Easy , [2]:Med , [4]Hard , [4]:Mix:\n");
    } while (level < 1 || level > 4);
    return (enQuestionLevel) level;
}

enOperations readOperations() {
    short operand;
    do {
        operand = (short) readPositiveNumber("Select Operation [1]:Add , [2]:Sub , [3]:Mul , [4]:Div , [5]:Mix :\n");
    } while (operand < 1 || operand > 5);
    return (enOperations) operand;
}

enOperations getRandomOperations() {
    return (enOperations) randomNumbers(1, 4);
}

enQuestionLevel getRandomLevel() {
    return (enQuestionLevel) randomNumbers(1, 3);
}

int sampleCalculater(int number1, int number2, enOperations operations) {
    switch (operations) {
        case Add:
            return number1 + number2;
        case Sub:
            return number1 - number2;
        case Mul:
            return number1 * number2;
        case Div:
            return number1 / number2;
        case MixOp:
            return number1 + number2;
    }
}

stQuestion getRandomQuestion(enQuestionLevel questionLevel, enOperations operations) {
    stQuestion question;
    if (questionLevel == enQuestionLevel::MixLevel) {
        questionLevel = getRandomLevel();
    }
    if (operations == enOperations::MixOp) {
        operations = getRandomOperations();
    }
    question.operatorType = operations;

    switch (questionLevel) {
        case Easy: {
            question.UpperNumber = randomNumbers(1, 10);
            question.DownNumber = randomNumbers(1, 10);
            question.answer = sampleCalculater(question.UpperNumber, question.DownNumber, operations);
            question.questionLevel = questionLevel;
            return question;
        }
        case Med: {
            question.UpperNumber = randomNumbers(10, 50);
            question.DownNumber = randomNumbers(10, 50);
            question.answer = sampleCalculater(question.UpperNumber, question.DownNumber, operations);
            question.questionLevel = questionLevel;
            return question;
        }
        case Hard: {
            question.UpperNumber = randomNumbers(50, 100);
            question.DownNumber = randomNumbers(50, 100);
            question.answer = sampleCalculater(question.UpperNumber, question.DownNumber, operations);
            question.questionLevel = questionLevel;
            return question;
        }
    }
    return question;
}

void genrateQuestions(stQuizzes &quizzes) {
    for (int i = 0; i < quizzes.numberOfQuestion; ++i) {
        quizzes.questionList[i] = getRandomQuestion(quizzes.questionLevel, quizzes.operatorType);
    }
}

string getOperationTypeAsSting(enOperations operations) {
    switch (operations) {
        case Add:
            return "+";
        case Sub:
            return "-";
        case Mul:
            return "*";
        case Div:
            return "/";
        case MixOp:
            return "Mix";
    }
}

void printQuestion(stQuizzes quizzes, int questionNumber) {
    cout << "----------\n";
    cout << "[" << questionNumber + 1 << "/" << quizzes.numberOfQuestion << "]\n";
    cout << quizzes.questionList[questionNumber].UpperNumber << "\n" << quizzes.questionList[questionNumber].DownNumber
         << " "
         << getOperationTypeAsSting(quizzes.questionList[questionNumber].operatorType)
         << "\n";
    cout << "_________" << endl;
}

int readAnswerFromUser() {
    int answer;
    cin >> answer;
    return answer;
}

void setScreenColorDependOnAnswer(bool right) {
    if (right)
        system("color 2F");
    else
        system("color 4F");
}

void checkTheAnswerAndGetTheRightOne(stQuizzes &quizzes, int number) {
    if (quizzes.questionList[number].userAnswer == quizzes.questionList[number].answer) {
        quizzes.numberOfRightAnswer++;
        quizzes.questionList[number].isAnswerCorrect = true;
        cout << "The Answer Is Right :-)\n";
    } else {
        quizzes.numberOfWrongAnswer++;
        quizzes.questionList[number].isAnswerCorrect = false;
        cout << "The Answer Is Wrong :-(\n";
        cout << "The Right Answer is : " << quizzes.questionList[number].answer << endl;
    }
    setScreenColorDependOnAnswer(quizzes.questionList[number].isAnswerCorrect);
}

void getTheAnswerFromUserAndCheckIt(stQuizzes &quizzes) {
    for (int i = 0; i < quizzes.numberOfQuestion; ++i) {
        printQuestion(quizzes, i);
        quizzes.questionList[i].userAnswer = readAnswerFromUser();
        checkTheAnswerAndGetTheRightOne(quizzes, i);
    }
    quizzes.isPass = quizzes.numberOfRightAnswer >= quizzes.numberOfWrongAnswer;
}

string printResultOfPassingOrNot(bool pass) {
    if (pass)
        return "Pass";
    else
        return "Fail";
}

string getQuestionLevelAsSting(enQuestionLevel questionLevel) {
    string arr[4] = {"Easy", "Mes", "Hard", "MixLevel"};
    return arr[questionLevel - 1];
}

string getQuestionOperandAsSting(enOperations operations) {
    string arr[5] = {"Add", "Sub", "Mul", "Dic", "MixOp"};
    return arr[operations - 1];
}


void printFinalResult(stQuizzes quizzes) {
    cout << "---------------------------------\n";
    cout << "Question Numbers is :" << quizzes.numberOfQuestion << "\n";
    cout << "Question Level :" << getQuestionLevelAsSting(quizzes.questionLevel) << "\n";
    cout << "Question Operation :" << getQuestionOperandAsSting(quizzes.operatorType) << "\n";
    cout << "Number Of Right Answer :" << quizzes.numberOfRightAnswer << "\n";
    cout << "Number Of Wrong Answer :" << quizzes.numberOfWrongAnswer << "\n";
    cout << "Is Pass :" << printResultOfPassingOrNot(quizzes.isPass) << "\n";
    setScreenColorDependOnAnswer(quizzes.isPass);
    cout << "---------------------------------\n";
}

void playGame() {
    stQuizzes quizzes;
    quizzes.numberOfQuestion = readHowManyQuestion();
    quizzes.questionLevel = readLevel();
    quizzes.operatorType = readOperations();

    genrateQuestions(quizzes);
    getTheAnswerFromUserAndCheckIt(quizzes);
    printFinalResult(quizzes);
}

void resetScreen() {
    system("cls");
    system("color 0F");
}

void startGame() {
    char playAgain = 'Y';
    do {
        resetScreen();
        playGame();
        cout << "Do You Want To Play Again Y/N ? :";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
}


int main() {
    srand((unsigned) time(nullptr));
    startGame();
}
