#include <iostream>
#include <string>
using namespace std;

class student
{
	private:
		//Student name
		string name;
	
		//Values are the scores in points,
		//not percentage of grade.
		int pts_earned[4];
		
		//Possible Points
		int pts_possible[4] = {10, 10, 100, 100};
		
		//Value of each assessment w.r.t. total grade
		double point_values[4] = {12.5, 12.5, 25, 50};
		
		//Earned percentage grade per assessment
		double percentage[4] = {0, 0, 0, 0};
		
		//Total Percentage
		double pcnt_total = 0;
		
		//Received Grade
		char grade;
		
	public:
		student(string str, int a, int b, int c, int d) {
			input_scores(a, b, c, d);
			name = str;
		}
		student();
		void input_scores(int a, int b, int c, int d) {
			pts_earned[0] = a;
			pts_earned[1] = b;
			pts_earned[2] = c;
			pts_earned[3] = d;
			compute_scores();
		}
		void compute_scores() {
			for(int i=0; i<4; i++) {
				percentage[i] = 100*(double(pts_earned[i])/pts_possible[i]);
				pcnt_total = pcnt_total + percentage[i];
			}
			pcnt_total = pcnt_total/4;
			if(pcnt_total>=90) {
				grade = 'A';
			} else if (pcnt_total>=80) {
				grade = 'B';
			} else if (pcnt_total>=70) {
				grade = 'C';
			} else if (pcnt_total>=60) {
				grade = 'D';
			} else {
				grade = 'F';
			}
		}
		void output() {
			cout << "\n==================================================";
			cout << "\nGrades for student " << name << ":";
			cout << "\n--------------------------------------------------";
			cout << "\nAssessment\tEarned\tPossible\tPercent";
			cout << "\nQuiz1\t\t" << pts_earned[0] << "\t" << pts_possible[0] << "\t\t" << percentage[0] << "%";
			cout << "\nQuiz2\t\t" << pts_earned[1] << "\t" << pts_possible[1] << "\t\t" << percentage[1] << "%";
			cout << "\nMidterm\t\t" << pts_earned[2] << "\t" << pts_possible[2] << "\t\t" << percentage[2] << "%";
			cout << "\nFinal\t\t" << pts_earned[3] << "\t" << pts_possible[3] << "\t\t" << percentage[3] << "%";
			cout << "\n--------------------------------------------------";
			cout << "\nTOTAL Percent: " << pcnt_total << "\nGRADE: " << grade;
			cout << "\n--------------------------------------------------\n\n\n";
		}
	
};


int main()
{
	system("cls");
	
	student Trump("Trump", 6, 7, 80, 70);
	Trump.output();
	
	student Clinton("Clinton", 8, 9, 90, 84);
	Clinton.output();
	
	return 0;
}

