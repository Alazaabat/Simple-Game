// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<cstdlib>
#include <iostream>
using namespace std;
enum enLevel
{
	Easy=1,Med,Hard,Mix
};
enum enOpType
{
	Add=1,Sub,Mult,Div,MixOp
};
struct StQuestions
{
	int Number1;
	int Number2;
	enOpType opType;
	enLevel Level;
	int Correct_Answer;
	int PlayerAnswer;
	bool Question_Result;
};
struct Stquizz
{
	int Questions_Numbers;
	StQuestions Quesionslist[100];
	enOpType OpType;
	enLevel Level;
	int TrueAnswers=0;
	int FalseAnswers = 0;
	bool FailorPass;

};
int getrandom(int From, int To) {
	return (rand() % (To - From + 1) + From);

}
int get_Questions_number() {
	cout << "Enter question number : ";
	int Number;
	cin >> Number;
	return Number;

}
enOpType get_quizz_op() {
	cout << "\nPlease enter The operation Type \n \t\t\t [1] :: Add,[2] :: Sub,[3] :: Mult,[4] :: Div,[5] :: Mix :  ";
	int Number;
	cin >> Number;
	return (enOpType)Number;
}
enLevel get_Quizz_level() {
	cout << "\nPlease enter The Quizz Level Type \n \t\t\t [1] :: Easy,[2] :: Med,[3] :: Hard,[4] :: Mix :   ";
	int Number;
	cin >> Number;
	return (enLevel)Number;

}
int GetcorrectAnswer(int Number1, int Number2, enOpType Type) {
	switch (Type)
	{
	case Add:
		return Number1 + Number2;
		break;
	case Sub:
		return Number1 - Number2;

		break;
	case Mult:
		return Number1 * Number2;

		break;
	case Div:
		return Number1 / Number2;

		break;
	
	}
}
StQuestions FilloneQuestion(enOpType OpType, enLevel Level) {
	StQuestions Question;
	if ( OpType == enOpType::MixOp)
	{
			OpType = enOpType(getrandom(1, 4));
	}
	if (Level == enLevel::Mix)
		Level = enLevel(getrandom(1, 3));

	Question.opType = OpType;

	switch (Level)
	{
	case Easy:
		Question.Number1 = getrandom(1, 10);
		Question.Number2 = getrandom(1, 10);
		Question.Level = Level;
		Question.Correct_Answer=GetcorrectAnswer(Question.Number1, Question.Number2, Question.opType);
		return Question;
		break;
	case Med:
		Question.Number1 = getrandom(10, 30);
		Question.Number2 = getrandom(10, 30);
		Question.Level = Level;
		Question.Correct_Answer = GetcorrectAnswer(Question.Number1, Question.Number2, Question.opType);
		return Question;

		break;
	case Hard:
		Question.Number1 = getrandom(30, 100);
		Question.Number2 = getrandom(30, 100);
		Question.Level = Level;
		Question.Correct_Answer = GetcorrectAnswer(Question.Number1, Question.Number2, Question.opType);
		return Question;

		break;
	
	}




}
string  getOpSyembol(enOpType Type) {
	switch (Type)
	{
	case Add:
		return "+";
		break;
	case Sub:
		return "-";
		break;
	case Mult:
		return "x";
		break;
	case Div:
		return "/";
		break;
	case MixOp:
		return "Mix";
		break;
	default:
		break;
	}
}
void GenerateRandomQuestions(Stquizz& Quizz) {
	for (int QuistionNumber = 0; QuistionNumber <Quizz.Questions_Numbers; QuistionNumber++)
	{
		Quizz.Quesionslist[QuistionNumber] = FilloneQuestion(Quizz.OpType, Quizz.Level);
	}
}
void 	PrintQuestion(Stquizz Quizz,int QuestionNumber) {
	cout << Quizz.Quesionslist[QuestionNumber].Number1<<endl;
	cout << Quizz.Quesionslist[QuestionNumber].Number2<<"\t"<<getOpSyembol(Quizz.Quesionslist[QuestionNumber].opType)<<endl;
	cout << "---------------\n";


}
int GetPlayerAnswer() {
	int Number;
	cin >> Number;
	return Number;
}
bool GetQuestionResult(Stquizz Quizz,int QuistionNumber) {
	if (Quizz.Quesionslist[QuistionNumber].PlayerAnswer== Quizz.Quesionslist[QuistionNumber].Correct_Answer)
	{
		cout << "You r Correct :) ";
		system("color 2F");
		return true;
	}
	else
	{
		cout << "You r Failed  :-( The correct Answer is "<< Quizz.Quesionslist[QuistionNumber].Correct_Answer;
		system("color 4F");
		cout << "\a";
		return false;
	}
}
Stquizz CorrectAnswerAndprint(Stquizz Quizz) {
	for (int QuistionNumber = 0; QuistionNumber < Quizz.Questions_Numbers; QuistionNumber++)
	{
		cout << "\n\n";
		PrintQuestion(Quizz,QuistionNumber);
		Quizz.Quesionslist[QuistionNumber].PlayerAnswer = GetPlayerAnswer();
		Quizz.Quesionslist[QuistionNumber].Question_Result=GetQuestionResult(Quizz, QuistionNumber);
		if (Quizz.Quesionslist[QuistionNumber].Question_Result==true)
		{
			Quizz.TrueAnswers++;
		}
		else
		{
			Quizz.FalseAnswers++;

		}
	}
	Quizz.FailorPass = (Quizz.FalseAnswers <= Quizz.TrueAnswers);
	return Quizz;

}
string GetFailOrPass(bool pass) {
	if (pass)
	{
		system("color 2F");
		return "Seccuss";
	}
	cout << "\a";
	system("color 4F");
	return "Fail";
}
string QuestionLevelinstring(enLevel Level) {
	string Levels[] = { "Easy" ,"Med","Hard","Mix" };
	return Levels[Level - 1];
}
void PrintFinalResult(Stquizz Quizz) {
	
	cout << "\n\n\n" << "\t\t\t\t" <<"--------------------------" << GetFailOrPass(Quizz.FailorPass)<<"---------------<<\n";
	cout  << "\t\t\t\t" << "--------------------------" << "--------" << "---------------"<<endl;
	cout << "\t\t\t\t" << "Number of Questions is : " << Quizz.Questions_Numbers<<endl;
	cout << "\t\t\t\t" << "Question Level  is : " << QuestionLevelinstring(Quizz.Level) << endl;
	cout << "\t\t\t\t" << "OpType   is : " << getOpSyembol(Quizz.OpType) << endl;
	cout << "\t\t\t\t" << "Number of Right Answrs  is : " << Quizz.TrueAnswers << endl;
	cout << "\t\t\t\t" << "Number of False Answrs  is : " << Quizz.FalseAnswers << endl;
	cout << "\t\t\t\t" << "--------------------------" << "--------" << "---------------" << endl;







}
void Playgame() {

	Stquizz Quizz;
	Quizz.Questions_Numbers = get_Questions_number();
	Quizz.OpType = get_quizz_op();
	Quizz.Level = get_Quizz_level();
	GenerateRandomQuestions(Quizz);
	Quizz = CorrectAnswerAndprint(Quizz);
	PrintFinalResult(Quizz);
}
void restScreen() {
	system("color 0F");
	system("cls");
}
void Playgames() {
	char Answer;
	do
	{
		restScreen();
		Playgame();
		cout << "\n\n \t\t Do you want To play again : Y/N : ";
			cin >> Answer;

	} while (Answer!='N');

}
int main()
{
	srand(std::time(0));

	Playgame();

}

