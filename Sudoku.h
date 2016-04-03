#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
class Sudoku{
	public:
		static const int sudokuSize=81;
		void giveQuestion();
		void printOut(int arr[]);
		void readIn();
		void solve(); 
		bool checkNoRepeat(int p);
		bool isCorrect();
		void possibility();
		int violence();
		void copyAns();
		void changeNum(int,int);
		void changeRow(int,int);
		void changeCol(int,int);
		void rotate(int);
		void flip(int);
		void transform();
	private:
		int ques[sudokuSize];
		int tempAns[sudokuSize];
		int ansCount;
		bool possible[sudokuSize][9]; //�����Ӯ�i�� 
		int remainNum[sudokuSize]; //�����Ӯ�w�R�i��� 
};
