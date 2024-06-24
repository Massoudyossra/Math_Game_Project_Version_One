// Projet2: Math Game.

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

enum enQuestionLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };
enum enQuestionType { Add = 1, Sub = 2, Mult = 3, Div = 4, Mixed = 5 };
enum enRightOrWrong { Right = 1 , Wrong = 2 };
enum enPassOrFail {Pass=1,Fail=2};

struct stQuestionInfo
{
	short Number1 = 0;
	short Number2 = 0;
	enQuestionType OperationType;
	short MyAnswer = 0;
	short ComputerAnswer = 0;
	enRightOrWrong RightOrWrong;
	string Result = "";
};

struct stChoices
{
	enQuestionLevel QuestionLevel;
	enQuestionType QuestionType;
};

struct stFinalResultInfo
{
	short NumberOfQuestions = 0;
	enPassOrFail PassOrFail;
	string PassOrFailFinalResult = "";
	string QuestionLevelName = "";
	string OpTypeName = "";
	short NumebrOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
};

int RandomNumber(int From, int To)
{
	// Function to generate a Random Number
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}

short ReadHowManyQuestions()
{
	short HowManyQuestions = 1;

	do
	{

		cout << "\nHow Many Questions Do You Want To Answer ? ";
		cin >> HowManyQuestions;
	} while (HowManyQuestions <= 0);

	return HowManyQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 1;

	do
	{
		cout << "\nEnter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel>4);

	return (enQuestionLevel)QuestionLevel;
}

enQuestionType ReadQuestionType()
{
	short QuestionType = 1;

	do
	{
		cout << "\nEnter Question Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> QuestionType;

	} while (QuestionType < 1 || QuestionType > 5);

	return (enQuestionType)QuestionType;
}

void FillQuestionValues(stQuestionInfo& QuestionInfo,stChoices Choices)
{
	if (Choices.QuestionType == enQuestionType::Mixed)
	{
		QuestionInfo.OperationType = (enQuestionType)RandomNumber(1, 4);
	}

	else
	{
		QuestionInfo.OperationType = Choices.QuestionType;
	}

	switch (Choices.QuestionLevel)
	{

	case enQuestionLevel::Easy:
	{
		QuestionInfo.Number1 = RandomNumber(1, 10);
		QuestionInfo.Number2 = RandomNumber(1, 10);
		break;
	}
	case enQuestionLevel::Medium:
	{
		QuestionInfo.Number1 = RandomNumber(10, 50);
		QuestionInfo.Number2 = RandomNumber(10, 50);
		break;
	}

	case enQuestionLevel::Hard:
	{
		QuestionInfo.Number1 = RandomNumber(50, 100);
		QuestionInfo.Number2 = RandomNumber(50, 100);
		break;
	}

	case enQuestionLevel::Mix:
	{
		QuestionInfo.Number1 = RandomNumber(1, 100);
		QuestionInfo.Number2 = RandomNumber(1, 100);
		break;
	}

	}
		
}

char GetOperator(stQuestionInfo QuestionInfo)
{
	char arr[4] = { '+','-','*','/' };
	return arr[QuestionInfo.OperationType - 1];
}

void PrintQuestion(stQuestionInfo QuestionInfo)
{
	
	cout << "\n" <<  QuestionInfo.Number1 << endl;
	cout << QuestionInfo.Number2 << " " << GetOperator(QuestionInfo) << "\n";
	cout << "_________________\n";

}

short GetComputerAnswer(stQuestionInfo QuestionInfo)
{
	switch (QuestionInfo.OperationType)
	{
	case enQuestionType::Add:
		return QuestionInfo.Number1 + QuestionInfo.Number2;
	case enQuestionType::Sub:
		return QuestionInfo.Number1 - QuestionInfo.Number2;
	case enQuestionType::Mult:
		return QuestionInfo.Number1 * QuestionInfo.Number2;
	case enQuestionType::Div:
		return QuestionInfo.Number1 / QuestionInfo.Number2;
	}
}

enRightOrWrong CheckResult(stQuestionInfo QuestionInfo)
{
	if (QuestionInfo.MyAnswer == QuestionInfo.ComputerAnswer)
		return enRightOrWrong::Right;
	else
		return enRightOrWrong::Wrong;
}

string GetResult(stQuestionInfo QuestionInfo)
{
	string arr[2] = { "Right Answer :-)","Wrong Answer :-(\nThe Right Answer is : " };
	return arr[QuestionInfo.RightOrWrong - 1];
}

void SetScreenColor(stQuestionInfo Questioninfo)
{
	if (Questioninfo.RightOrWrong == enRightOrWrong::Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void PrintQuestionResult(stQuestionInfo QuestionInfo)
{
	if (QuestionInfo.RightOrWrong == enRightOrWrong::Right)
		cout << "\n" << QuestionInfo.Result << endl;
	else
		cout << "\n" << QuestionInfo.Result << QuestionInfo.ComputerAnswer << endl << endl; 
	SetScreenColor(QuestionInfo);
}

string QuestionLevelName(stChoices Choices)
{
	string arr[4] = { "Easy","Med","Hard","Mix" };
	return arr[Choices.QuestionLevel - 1];
}

string OpTypeName(stChoices Choices)
{
	string arr[5] = { "+","-","*","/","Mix" };
	return arr[Choices.QuestionType - 1];
}

enPassOrFail PassOrFail(stFinalResultInfo FinalResults)
{
	if (FinalResults.NumebrOfRightAnswers >= FinalResults.NumberOfWrongAnswers)
		return enPassOrFail::Pass;
	else
		return enPassOrFail::Fail;
}

string PassOrFailResult(stFinalResultInfo FinalResults)
{
	string arr[2] = { "Pass : - )","Fail : - (" };
	return arr[FinalResults.PassOrFail - 1];
}

void SetFinalResultScreenColor(stFinalResultInfo FinalResults)
{
	if (FinalResults.PassOrFail == enPassOrFail::Pass)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void printFinalResultsInfo(stFinalResultInfo FinalResults)
{
	cout << "\n\n________________________________________________________________\n\n";
	cout << "               Final Results is  " << FinalResults.PassOrFailFinalResult << "\n";
	cout << "________________________________________________________________\n\n";
	cout << "Number Of Questions : " << FinalResults.NumberOfQuestions << "\n\n";
	cout << "Question level : " << FinalResults.QuestionLevelName << "\n\n";
	cout << "OpType : " << FinalResults.OpTypeName << "\n\n";
	cout << "Number Of Right Answers : " << FinalResults.NumebrOfRightAnswers << "\n\n";
	cout << "Number Of Wrong Answers : " << FinalResults.NumberOfWrongAnswers << "\n\n";
	cout << "________________________________________________________________\n\n";

	SetFinalResultScreenColor(FinalResults);
}

void BeginPlaying(short HowManyQuestions, stChoices Choices)
{
	stQuestionInfo QuestionInfo;
	stFinalResultInfo FinalResults;

	for (short i = 1; i <= HowManyQuestions; i++)
	{
		cout << "\nQuestion [" << i << "/" << HowManyQuestions << "]\n";

		FillQuestionValues(QuestionInfo,Choices);
		QuestionInfo.ComputerAnswer = GetComputerAnswer(QuestionInfo);
		PrintQuestion(QuestionInfo);
		cin >> QuestionInfo.MyAnswer;
		QuestionInfo.RightOrWrong = CheckResult(QuestionInfo);
		QuestionInfo.Result = GetResult(QuestionInfo);
		PrintQuestionResult(QuestionInfo);
		

		if (QuestionInfo.RightOrWrong == enRightOrWrong::Right)
			FinalResults.NumebrOfRightAnswers++;
		else
			FinalResults.NumberOfWrongAnswers++;
	}

	FinalResults.NumberOfQuestions = HowManyQuestions;
	FinalResults.PassOrFail = PassOrFail(FinalResults);
	FinalResults.PassOrFailFinalResult = PassOrFailResult(FinalResults);
	FinalResults.QuestionLevelName = QuestionLevelName(Choices);
	FinalResults.OpTypeName = OpTypeName(Choices);
	
	printFinalResultsInfo(FinalResults);

}

void PlayAgainOrNot(char& PlayAgain)
{

	cout << "\nDo You Want To Play Again (Y/N) ? : ";
	cin >> PlayAgain;
	
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	stChoices Choices;
	char PlayAgain = 'Y';
	short HowManyQuestions = 1;

	do
	{

		ResetScreen();
		HowManyQuestions = ReadHowManyQuestions();
		Choices.QuestionLevel = ReadQuestionLevel();
		Choices.QuestionType = ReadQuestionType();

		BeginPlaying(HowManyQuestions, Choices);
		PlayAgainOrNot(PlayAgain);

		
	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{

	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}





