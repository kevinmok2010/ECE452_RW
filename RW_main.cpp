#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include "RW_main.h"

using namespace std;

Result object;

int board_arr[38] = { 0 };
int cbet = 0;
int hlbet = 0;
int nbet[38] = { 0 };
int won_value = 0;
int bet_total = 0;

int color_bet_flag = 0;
int num_bet_flag = 0;
int hl_bet_flag = 0;
bool MS_bet_flag = false;
bool RW_MS_bet_flag = false;
bool CDA_bet_flag = false;
bool DA_bet_flag = false;
bool fibon_bet_flag = false;
bool jb_bet_flag = false;

int jb_arr[8] = { 13,14,15,16,17,18,0,37 };
int jb_nbet_arr_init_[8] = { 10,5,10,10,5,10,10,10 };
int jb_nbet_arr[8] = { 10,5,10,10,5,10,10,10 };

string color_bet = "Nothing Bet";
string high_low = "Nothing Bet";
int bet_num[38] = { 0 };
int money = 1000;
int num_index = 0;
bool status = false;

bool win = true;

	void RW_Classification::winning(RW_Classification arr[], int num) {
		won_value = 0;
		while (1) {
			if (color_bet_flag) {
				//RED & BLACK
				if (object.result_color == color_bet) {
					won_value += cbet;
					color_bet_flag = 0;
				}
				else {
					//win nothing
					won_value = won_value - cbet;
					color_bet_flag = 0;
				}
			}
			else if (num_bet_flag) {
				//0-37
				for (int i = 0; i < num_index; i++) {
					if (object.result_number == bet_num[i]) {
						won_value = won_value + (35 * nbet[i]);
					}
					else {
						won_value = won_value - nbet[i];
					}
				}
				num_bet_flag = 0;
			}
			else if (hl_bet_flag) {
				//HIGH & LOW
				if (object.result_hl == high_low) {
					won_value += hlbet;
				}
				else {
					//win nothing
					won_value = won_value - hlbet;
				}
				hl_bet_flag = 0;
			}
			else 
			{break;}
		}

		if (won_value > 0) { win = true;}
		else { win = false;}

		money = money + won_value;
		cout << "Money gain/loss for last round: $" << won_value << "	New Balance: $" << money << endl << endl;

	}

	void RW_Classification::result(RW_Classification arr[], int num){
		cout << "Result drawn for this round: " << num << endl
			<< "Color: " << arr[num].color ;
		object.result_color = arr[num].color;
		object.result_number = num;
		int eo_check = 0;
		eo_check = num % 2;

		if (eo_check != 0) {
			cout << "	ODD" << endl;
			object.result_eo = "odd";
		}
		else {
			cout << "	EVEN" << endl;
			object.result_eo = "even";
		}
		if (arr[num].number >= 1 && arr[num].number <= 18) {
			cout << "LOW" << endl;
			object.result_hl = "low";
		}
		else if (arr[num].number >= 19 && arr[num].number <= 36) {
			cout << "HIGH" << endl;
			object.result_hl = "high";
		}
		else {
			cout << "ZERO" << endl;
			object.result_number = 0;
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
	int hlbet_init_ = 0;
	int bet_limit = 0;
	int fibon_pre = 0;
	int jb_pre[] = { 0 };
	int jb_temp[] = { 0 };

	srand(time(NULL));
	ofstream myfile;

	myfile.open("Profit_Result.txt");
	myfile << "Writing results to file." << endl
		<< "Trial	Bet Ammout	Win/Loss	New Balance" << endl;

	myfile.close();
	color_bet_flag = 0;
	num_bet_flag = 0;
	hl_bet_flag = 0;
	MS_bet_flag = false;
	RW_MS_bet_flag = false;
	CDA_bet_flag = false;
	DA_bet_flag = false;
	fibon_bet_flag = false;
	jb_bet_flag = false;
	num_index = 0;
	cout << "huh? " << cbet << endl;
	while (1) {
		int result = 0;

		while (MS_bet_flag == false && RW_MS_bet_flag == false && CDA_bet_flag == false && DA_bet_flag == false && fibon_bet_flag == false && jb_bet_flag == false) {
			cout << "Place your bet..." << endl
				<< "Please choose from one of the following betting option" << endl
				<< "[1] Color" << endl
				<< "[2] Number" << endl
				<< "[3] Finished Betting" << endl
				<< "[4] Fast Simulation (Martingale Strategy)" << endl
				<< "[5] Fast Simulation (Reverse Martingale Strategy)" << endl
				<< "[6] Fast Simulation (Contre DAlembert Strategy)" << endl
				<< "[7] Fast Simulation (DAlembert Strategy)" << endl
				<< "[8] Fast Simulation (Fibonacci Strategy)" << endl
				<< "[9] Fast Simulation (Jame Bond Strategy)" << endl;

			cin >> menu_flag;

			if (menu_flag == 1) {
				cout << "Red or Black?" << endl
					<< "red" << endl
					<< "black" << endl;
				cin >> color_bet;
				cout << "Bet Amount?" << endl;
				cin >> cbet;
				color_bet_flag = 1;
			}
			else if (menu_flag == 2) {
				cout << "What number? (0-36, 00 is represented by 37)" << endl;
				cin >> bet_num[num_index];
				cout << "Bet Amount?" << endl;
				cin >> nbet[num_index];
				num_index++;
				num_bet_flag = 1;
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
				MS_bet_flag = true;
				cout << "huh? " << cbet << endl;
				break;
			}
			else if (menu_flag == 5) {
				//Select strategy
				//Reverse Martingale Strategy (Only on Black or Red)
				cout << "Choose a color to bet on" << endl
					<< "Red" << endl
					<< "Black" << endl;
				//min 10 for reality 
				cin >> color_bet;
				cout << "Initial Bet Amount?" << endl;
				cin >> cbet;
				cbet_init_ = cbet;
				RW_MS_bet_flag = true;
				break;
			}
			else if (menu_flag == 6) {
				//Select strategy
				// Contre D¡¯Alembert strategy (Only on Black or Red)
				cout << "Choose a color to bet on" << endl
					<< "Red" << endl
					<< "Black" << endl;
				//min 10 for reality 
				cin >> color_bet;
				cout << "Initial Bet Amount?" << endl;
				cin >> cbet;
				cbet_init_ = cbet;
				CDA_bet_flag = true;
				break;
			}
			else if (menu_flag == 7) {
				//Select strategy
				//D¡¯Alembert strategy (Only on Black or Red)
				cout << "Choose a color to bet on" << endl
					<< "Red" << endl
					<< "Black" << endl;
				//min 10 for reality 
				cin >> color_bet;
				cout << "Initial Bet Amount?" << endl;
				cin >> cbet;
				cbet_init_ = cbet;
				DA_bet_flag = true;
				break;
			}
			else if (menu_flag == 8) {
				//Select strategy
				//Fibonacci strategy (Only on Black or Red)
				cout << "Choose a color to bet on" << endl
					<< "Red" << endl
					<< "Black" << endl;
				//min 10 for reality 
				cin >> color_bet;
				cout << "Initial Bet Amount?" << endl;
				cin >> cbet;
				cbet_init_ = cbet;
				fibon_bet_flag = true;
				break;
			}
			else if (menu_flag == 9) {
				//Select strategy
				//Jame Bond strategy
				//min 10 for reality 
				high_low = "high";
				hlbet = 140;
				hlbet_init_ = hlbet;
				for (int i = 0; i < 8; i++) {
					//new betting array reset to init_ (coz won or init stage)
					nbet[i] = jb_nbet_arr_init_[i];
					bet_num[i] = jb_arr[i];
				}
				jb_bet_flag = true;
				break;
			}
		}

//		hl_bet_flag = 1;
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
			bet_total = cbet;
			color_bet_flag = 1;
			cout << "Amount bet: $" << bet_total << endl;
		}
		/////////////////////////////////////////////////////////
		//RW_MS
		if (menu_flag == 5) {
			if (!win) {
				cbet = cbet_init_;
			}
			else {
				cbet = cbet * 2;
			}
			bet_limit = money - cbet;
			if (bet_limit < 0) {
				cbet = money;
			}
			bet_total = cbet;
			color_bet_flag = 1;
			cout << "Amount bet: $" << bet_total << endl;
		}
		/////////////////////////////////////////////////////////
		// Contre D¡¯Alembert strategy
		if (menu_flag == 6) {
			if (!win) {
				cbet = cbet - 1;
				if (cbet < cbet_init_) {
					cbet = cbet_init_;
				}
			}
			else {
				cbet++;
			}
			bet_limit = money - cbet;
			if (bet_limit < 0) {
				cbet = money;
			}
			bet_total = cbet;
			color_bet_flag = 1;
			cout << "Amount bet: $" << bet_total << endl;
		}
		/////////////////////////////////////////////////////////
		// D¡¯Alembert strategy
		if (menu_flag == 7) {
			if (!win) {
				cbet ++;
			}
			else {
				cbet = cbet - 1;
				if (cbet < cbet_init_) {
					cbet = cbet_init_;
				}
			}
			bet_limit = money - cbet;
			if (bet_limit < 0) {
				cbet = money;
			}
			bet_total = cbet;
			color_bet_flag = 1;
			cout << "Amount bet: $" << bet_total << endl;
		}
		/////////////////////////////////////////////////////////
		//The Fibonacci Strategy
		if (menu_flag == 8) {
			if (!win) {
				cbet += fibon_pre;
				fibon_pre = cbet;
			}
			else {
				cbet = cbet - fibon_pre;
				if (cbet < cbet_init_) {
					cbet = cbet_init_;
				}
				fibon_pre = cbet;
			}
			bet_limit = money - cbet;
			if (bet_limit < 0) {
				cbet = money;
			}
			bet_total = cbet;
			color_bet_flag = 1;
			cout << "Amount bet: $" << bet_total << endl;
		}
		/////////////////////////////////////////////////////////
		//James Bond Strategy
		if (menu_flag == 9) {
			int bet_total = 0;
			num_index = 8;
			if (!win) {
				hlbet = hlbet * 2;
				for (int i = 0; i < num_index; i++) {
					nbet[i] = jb_nbet_arr[i] * 2;
					jb_nbet_arr[i] = nbet[i];
					bet_total += nbet[i];
				}
				bet_total += hlbet;
			}
			else {
				hlbet = hlbet_init_;
				for (int i = 0; i < num_index; i++) {
					//temp = nbet init_
					//new betting array reset to init_ (coz won or init stage)
					nbet[i] = jb_nbet_arr_init_[i];
					jb_nbet_arr[i] = nbet[i];
					bet_total += nbet[i];
				}
				bet_total += hlbet;
			}
			bet_limit = money - bet_total;
			if (bet_limit < 0) {
				cout << "Don't have enough money for the next bet" << endl;
				break;
			}
			cout << "Amount bet: $" << bet_total << endl;
			num_bet_flag = 1;
			hl_bet_flag = 1;
			color_bet_flag = 0;
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