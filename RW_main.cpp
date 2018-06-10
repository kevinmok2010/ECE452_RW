#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include "RW_main.h"

using namespace std;

int board_arr[] = { 0 };
int cbet = 0;
int nbet = 0;
int won_value = 0;

bool color_bet_flag = false;
bool num_bet_flag = false;
bool MS_bet_flag = false;

string color_bet = "Nothing Bet";
int bet_num[38] = { 0 };
int money = 1000;
bool status = false;

bool win = true;

	void RW_Classification::winning(RW_Classification arr[], int num) {
		won_value = 0;
		if (color_bet_flag) {
			//RED & BLACK
			if (arr[num].color == color_bet) {
				//win Bet * 2 (1:1)
				won_value += cbet;
				win = true;
			}
			else {
				//win nothing
				won_value = won_value - cbet;
				win = false;
			}
		}

		if (num_bet_flag) {
		//0-37
			if (arr[num].number == bet_num[num]) {
				won_value += 35;
			}
			else {
				won_value = won_value - 35;
			}
		}
		money = money + won_value;
		cout << "Amount bet: $" << cbet << endl;
		cout << "Money gain/loss for last round: $" << won_value << "	New Balance: $" << money << endl << endl;

	

	}

	void RW_Classification::result(RW_Classification arr[], int num){
		cout << "Result drawn for this round: " << num << endl
			<< "Color: " << arr[num].color ;
		int eo_check = 0;
		eo_check = num % 2;

		if (eo_check != 0) {
			cout << "	ODD" << endl;
		}
		else {
			cout << "	EVEN" << endl;
		}
	}

	//Assinging color to number
	void RW_Classification::assign_color(RW_Classification arr[], int i){

		switch (i)
		{
		//red as 1
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 12:
		case 14:
		case 16:
		case 18:
		case 19:
		case 21:
		case 23:
		case 25:
		case 27:
		case 30:
		case 32:
		case 34:
		case 36:
			arr[i].color = "red";
			break;

		//black as 2
		case 2:
		case 4:
		case 6:
		case 8:
		case 10:
		case 11:
		case 13:
		case 15:
		case 17:
		case 20:
		case 22:
		case 24:
		case 26:
		case 28:
		case 29:
		case 31:
		case 33:
		case 35:
			arr[i].color = "black";
			break;

		//green as 3
		case 0:
		case 37:
			arr[i].color = "green";
			break;

		default:
			arr[i].color = "Nothing Bet";
			break;
		}
	}

	void RW_Classification::num_init(RW_Classification arr[]) {
		for (int i = 0; i < 38; i++) {
			arr[i].number = i;
			assign_color(arr, i);
			//cout << "Number Added:	" << arr[i].number << "	Color: " << arr[i].color << endl;
		}
	}




int main() {
	//init board
	RW_Classification my_board;
	RW_Classification my_num_arr[38];
	my_board.num_init(my_num_arr);
	int out_bet = 10;
	int in_bet = 1;
	int number = 99;
	int color = 1;
	int menu_flag = 0;
	int round = 0;
	int cbet_init_ = 0;
	int bet_limit = 0;
	srand(time(NULL));
	ofstream myfile;

	myfile.open("Profit_Result.txt");
	myfile << "Writing results to file." << endl
		<< "Trial	Bet Ammout	Win/Loss	New Balance" << endl;

	myfile.close();

	while (1) {
		int result = 0;
		int num_index = 0;
		while (MS_bet_flag == false) {
			cout << "Place your bet..." << endl
				<< "Please choose from one of the following betting option" << endl
				<< "[1] Color" << endl
				<< "[2] Number" << endl
				<< "[3] Finished Betting" << endl
				<< "[4] Fast Simulation (Martingale Strategy)" << endl;

			cin >> menu_flag;

			if (menu_flag == 1) {
				cout << "Red or Black?" << endl
					<< "red" << endl
					<< "black" << endl;
				cin >> color_bet;
				cout << "Bet Amount?" << endl;
				cin >> cbet;
				color_bet_flag = true;
			}
			else if (menu_flag == 2) {
				cout << "What number? (0-36, 00 is represented by 37)" << endl;
				cin >> bet_num[num_index];
				cout << "Bet Amount?" << endl;
				cin >> nbet;
				num_index++;
				num_bet_flag = true;
			}
			else if (menu_flag == 3) {
				break;
			}
			else if (menu_flag == 4) {
				//Select strategy
				//Martingale Strategy (Only on Black or Red)
				cout << "Choose a color to bet on" << endl
					<< "Red" << endl
					<< "Black" << endl;
				//min 10 for reality 
				cin >> color_bet;
				cout << "Initial Bet Amount?" << endl;
				cin >> cbet;
				cbet_init_ = cbet;
				color_bet_flag = true;
				MS_bet_flag = true;
				break;
			}
		}
		
		/////////////////////////////////////////////////////////
		//MS
		if (menu_flag == 4) {
			if (!win) {
				cbet = cbet * 2;
			}
			else {
				cbet = cbet_init_;
			}
			bet_limit = money - cbet;
			if (bet_limit < 0) {
				cbet = money;
			}
		}
		/////////////////////////////////////////////////////////
		result = rand() % 38;         // v1 in the range 0 to 99

		my_board.result(my_num_arr, result);

		//check win or not
		my_board.winning(my_num_arr, result);

		myfile.open("Profit_Result.txt", fstream::app);
		myfile << round << "	" << cbet << "	" << won_value << "	" << money << endl;
		myfile.close();

		if (money <= 0) {
			cout << "Game Over." << endl;
			cout << "Total number of round passed: " << round << endl;
			break;
		}

		round++;
		
	}
	

	
	
	//RW_init
	//spin wheel 1000x
	//compare result
	//output result to text file
}