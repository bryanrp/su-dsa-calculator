#include "include/calculator.h"
#include "include/string_parser.h"
#include <iostream>
using namespace std;

int main() {
  string name;
   Calculator calculator;

	system("Color E8");
    cout << " _____________________  " << endl;
    cout << "|  _________________  | " << endl;
    cout << "| |                 | | " << endl;
    cout << "| |_________________| | " << endl;
    cout << "|  ___ ___ ___   ___  | " << endl;
    cout << "| | 7 | 8 | 9 | | + | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "| | 4 | 5 | 6 | | - | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "| | 1 | 2 | 3 | | x | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "| | . | 0 | = | | / | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "|_____________________| " << endl;
	cout << "Hello, what's your name?\n";
	cin  >> name;
	system("cls");
	while (true) { 
		menu:
		system("cls");
		cout << "Hello " << name <<", what would you like to do today?\n" << endl;//show menu
		cout << "Option" << endl;
		cout << "1. Calculate an expression" << endl;
		cout << "2. Check calculator history" << endl;
		cout << "3. Clear history" << endl;
		cout << "4. Glossary" << endl;
		cout << "5. End session" << endl;
		cout << "Enter Option: ";
		system("Color F5");//change color again because aesthetic
		
		int choice;
		cin >> choice; //get menu command
		if (choice == 1) {
		system("cls");
      input:
			cout << "Input your expression: ";
      string input, dummy;
      getline(cin, dummy);
      getline(cin, input);
			double result = calculator.calculate(input, true);
      cout << "Result:\n" << result;
      cout <<"\nWould you like to continue calculating?\n" << "y/n\n";
      
      string opt1;
      cin >> opt1;
      if (opt1=="y" || opt1=="Y") {
      	system("cls");
        goto input;
      }
      else if (opt1=="n" || opt1=="N") {
        goto menu;
      }
		}
		else if (choice == 2) {
      list<string> history = calculator.getHistory();
      cout << history.size() << '\n';
      if (history.empty()) {
      	system("cls");
        cout << "There is no history detected.\n";
      }
      else {
      	system("cls");
        int number = 1;
        for (string str : history) {
          cout << number++ << ". " << str << '\n' << endl;
        }
    }
        cout << "Enter any key to return\n";
        string any;
        cin >> any;
        if (any=="1"){
        	goto menu;
		}
		else {
			goto menu;
		}
			}
		else if (choice == 3){
			calculator.deleteAllHistory();
		}
    else if (choice == 4) {
      glossary:
      system("cls");
      system("Color F5");
      cout << "Glossary:" << endl;
      cout << "1. sqrt(x) :  square root of x" << endl;
      cout << "2. exp(x,y):  x to the power of y" << endl;
      cout << "3. log(x)  :  log of x" << endl;
      cout << "4. ln(x)   :  ln of x" << endl;
      cout << "5. sin(x)  :  sinus of x" << endl;
      cout << "6. cos(x)  :  cosinus of x" << endl;
      cout << "7. tan(x)  :  tan of x\n" << endl;
      cout << "8. The x for the trigonometry is in radian instead of degree." << endl;
      cout << "Where would you like to go?" << endl;
      cout << "1. Calculate an expression" << endl;
      cout << "2. Back to menu" << endl;
      string opt2;
      cin >> opt2;
      if (opt2 == "1") {
      	cout << '\n';
        goto input;
      }
      else if (opt2 == "2") {
        goto menu;
      }
      else {
        cout << "\nThere is no such option" << endl;
			  system("Color 4F");
			  goto glossary;
      }
    } 
      
		else if (choice == 5) {
			break; //ends session
		}
		else {
			cout << "\nInvalid. There is no such option." << endl;
			system("Color 4F"); //screen flash then back to normal menu
		}
	}
	system("cls");
    cout << " _____________________  " << endl;
    cout << "|  _________________  | " << endl;
    cout << "| |                 | | " << endl;
    cout << "| |_________________| | " << endl;
    cout << "|  ___ ___ ___   ___  | " << endl;
    cout << "| | 7 | 8 | 9 | | + | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "| | 4 | 5 | 6 | | - | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "| | 1 | 2 | 3 | | x | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "| | . | 0 | = | | / | | " << endl;
    cout << "| |___|___|___| |___| | " << endl;
    cout << "|_____________________| " << endl;
	cout << "Thank you for using our service, have a great day" << endl;
	system("Color 8E"); //goodbye
}