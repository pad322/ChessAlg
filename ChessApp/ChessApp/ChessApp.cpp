#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <future>

using namespace std;

char btn;
bool run_mode = true;
bool lan = true;
int interval = 500;

void timer(chrono::seconds delay)
{
	this_thread::sleep_for(delay);
	cout << "\n\tPress a number on your keyboard to navigate the menu!\n";
}

void chess_menu() 
{
	system("cls");
	if (lan)
	{
		cout << "\n\tSelect a programming approach!";
		cout << "\n\n\t1. Dynamic";
		cout << "\n\t2. Greedy";
		//cout << "\n\t3. Divide et impera";
	}
	else
	{
		cout << "\n\tValassza ki a programozasi modszert!";
		cout << "\n\n\t1. Dinamikus";
		cout << "\n\t2. Greedy";
		//cout << "\n\t3. Divide et Impera";
	}

	btn = _getch();

	system("cls");
	if (lan)
	{
		cout << "\n\tSelect a chess problem!";
		cout << "\n\n\t1. Queen problem with minimal nr. of pieces";
		cout << "\n\t2. Queens dominating";
		cout << "\n\t3. Queen on horseback";
		cout << "\n\t4. Independent rooks";
	}
	else
	{
		cout << "\n\tValassza ki a sakk problemat";
		cout << "\n\n\t1. Kiralyno problema legkevesebb darabbal";
		cout << "\n\t2. Kiralyno lefedes";
		cout << "\n\t3. Kiralyno lohaton lefedes";
		cout << "\n\t4. Kulonallo bastyak";
	}

	btn = _getch();

}

void settings_menu()
{
Settings:
	system("cls");

	if (lan)
		cout << "\n\t1. Change Running mode - ";
	else
		cout << "\n\t1. Futasi mod valtoztatasa - ";

	if (run_mode)
	{
		if (lan)
			cout << "Step-by-step iteration\n";
		else
			cout << "Lepesrol-lepesre iteralva\n";
	}
	else
	{
		if (lan)
			cout << "Pausing mode\n";
		else
			cout << "Szunetelheto mod\n";
	}

	if (lan)
		cout << "\t2. Step interval - ";
	else
		cout << "\t2. Lepesenkenti idotartam - ";

	cout << interval << '\n';


	if (lan)
		cout << "\t3. Language - ";
	else
		cout << "\t3. Nyelv - ";

	if (lan)
	{
		cout << "English\n";
	}
	else
	{
		cout << "Magyar\n";
	}

	if (lan)
		cout << "\t4. Back to Main Menu\n";
	else
		cout << "\t4. Vissza a Fo Menube\n";

	btn = _getch();

	switch (btn)
	{
	case '1':
		run_mode = !run_mode;
		goto Settings;
		break;
	case '2':
		interval += 100;
		if (interval > 1000)
			interval = 100;
		goto Settings;
		break;
	case '3':
		lan = !lan;
		goto Settings;
		break;
	case '4':
		break;
	default :
		goto Settings;
		break;
	}
}

void notes_menu()
{
	system("cls");
	if(lan)
	{
		cout << "\n\t\t Chess App\n";
		cout << "\t Created by Torok Csongor\n";
		cout << "\n\tThe app is meant for displaying and solving different mathematical chess problems\n\tand comparing these in terms of time and optimization.\n";
		cout << "\n\tStep-by-step mode : Each time Space is pressed, the algorithm advances once.";
		cout << "\n\tPausing mode : Each time Space is pressed, the algorithm stops.";
		cout << "\n\tIn the this mode the algorithm advances in the given intervals value, representing milliseconds between each step.";
		cout << "\n\nPress any button to return to the Main menu!";
	}
	else
	{
		cout << "\n\t\t Sakk Alkalmazas\n";
		cout << "\t Keszitette Torok Csongor\n";
		cout << "\n\tAz alkalmazast kulonbozo sakkos matematikai problemak megjelenitesere es megoldasara keszult\n\tilletve ezek osszehasonlitasara ido es optimalizalas szempontjabol.\n";
		cout << "\n\tLepesrol-lepesre iteralas : Minden alkalommal amikor megnyomja a Space-t, egy lepest tesz az algoritmus.";
		cout << "\n\tSzunetelo mod : Minden Space gomb lenyomasakor, szunetel az algoritmus futasa.";
		cout << "\n\tEbben a modban az algoritmus az allithato idotartam erteke szerint lepked, miliszekundumokban szamolva.";
		cout << "\n\nNyomjon meg barmilyen gombot a Fo Menuhoz valo visszatereshez!";
	}

	btn = _getch();
}

void exit_part()
{
}

int main()
{
MainMenu :

	system("cls");

	//auto timer1 = async(launch::async, get_btn);
	//auto timer2 = async(launch::async, timer, chrono::seconds(3));


	if(lan)
	{
		cout << "\n\t\tMain Menu\n\n";
		cout << "\t1. Chess Problems\n";
		cout << "\t2. Settings\n";
		cout << "\t3. Notes\n";
		cout << "\t4. Exit\n";
	}
	else
	{
		cout << "\n\t\tFo menu\n\n";
		cout << "\t1. Sakk problemak\n";
		cout << "\t2. Beallitasok\n";
		cout << "\t3. Jegyzetek\n";
		cout << "\t4. Kilepes\n";
	}

	btn = _getch();

	switch (btn)
	{
	case '1':
		chess_menu();
		break;
	case '2':
		settings_menu();
		break;
	case '3':
		notes_menu();
		break;
	case '4':
		
		system("cls");

		if (lan)
		{
			cout << "\n\tAre you sure you want to quit?\n";
			cout << "\t1. Yes\t2. No";
		}
		else
		{
			cout << "\n\tBiztos ki szeretne lepni?\n";
			cout << "\t1. Igen\t2. Nem";
		}

		btn = _getch();

		switch (btn)
		{
		case '1':
			system("cls");
			return 0;
			break;
		case '2':
			goto MainMenu;
			break;
		}

		break;
	}
	goto MainMenu;
}
