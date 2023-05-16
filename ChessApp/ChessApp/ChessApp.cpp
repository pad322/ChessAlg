#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <future>
#include <fstream>

char btn;
bool run_mode = true;
bool lan = true;
bool intro = true;
int interval = 500;

/*
void timer(chrono::seconds delay)
{
	this_thread::sleep_for(delay);
	std::cout << "\n\tPress a number on your keyboard to navigate the menu!\n";
}
*/

void chess_menu() 
{
	system("cls");

	if (lan)
	{
		std::cout << "\n\tSelect a chess problem!";
		std::cout << "\n\n\t1. Queen problem with minimal nr. of pieces";
		std::cout << "\n\t2. Queens dominating";
		std::cout << "\n\t3. Queen on horseback";
		std::cout << "\n\t4. Independent rooks";
	}
	else
	{
		std::cout << "\n\tValassza ki a sakk problemat";
		std::cout << "\n\n\t1. Kiralyno problema legkevesebb darabbal";
		std::cout << "\n\t2. Kiralyno lefedes";
		std::cout << "\n\t3. Kiralyno lohaton lefedes";
		std::cout << "\n\t4. Kulonallo bastyak";
	}

	btn = _getch();

	system("cls");



	if (lan)
	{
		std::cout << "\n\tSelect a programming approach!";
		std::cout << "\n\n\t1. Dynamic";
		std::cout << "\n\t2. Greedy";
		std::cout << "\n\t3. Backtracking";
	}
	else
	{
		std::cout << "\n\tValassza ki a programozasi modszert!";
		std::cout << "\n\n\t1. Dinamikus";
		std::cout << "\n\t2. Greedy";
		std::cout << "\n\t3. Backtracking";
	}

	btn = _getch();

}

void settings_menu()
{
	std::ofstream out("data.txt", std::ofstream::trunc);

Settings:
	system("cls");

	if (lan)
		std::cout << "\n\t1. Change Running mode - ";
	else
		std::cout << "\n\t1. Futasi mod valtoztatasa - ";

	if (run_mode)
	{
		if (lan)
			std::cout << "Step-by-step iteration\n";
		else
			std::cout << "Lepesrol-lepesre iteralva\n";
	}
	else
	{
		if (lan)
			std::cout << "Pausing mode\n";
		else
			std::cout << "Szunetelheto mod\n";
	}

	if (lan)
		std::cout << "\t2. Step interval - ";
	else
		std::cout << "\t2. Lepesenkenti idotartam - ";

	std::cout << interval << '\n';


	if (lan)
		std::cout << "\t3. Language - ";
	else
		std::cout << "\t3. Nyelv - ";

	if (lan)
	{
		std::cout << "English\n";
	}
	else
	{
		std::cout << "Magyar\n";
	}

	if (lan)
	{
		std::cout << "\t4. Skip intro - ";

		if (intro)
		{
			std::cout<< "Disabled\n";
		}
		else
			std::cout << "Enabled\n";
	}
	else
	{
		std::cout << "\t4. Bevezeto atugrasa - ";

		if (intro)
		{
			std::cout << "Kikapcsolva\n";
		}
		else
			std::cout << "Bekapcsolva\n";
	}

	if (lan)
		std::cout << "\t5. Back to Main Menu\n";
	else
		std::cout << "\t5. Vissza a Fo Menube\n";

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
		intro = !intro;
		goto Settings;
		break;
	case '5':
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
		std::cout << "\n\t\t Chess:Alg\n";
		std::cout << "\t Created by Torok Csongor\n";
		std::cout << "\n\tThe app is meant for displaying and solving different mathematical chess problems\n\tcomparing these in terms of time and optimization.\n";
		std::cout << "\n\tStep-by-step mode : Each time Space is pressed, the algorithm advances one step.";
		std::cout << "\n\tPausing mode : Each time Space is pressed, the algorithm stops.";
		std::cout << "\n\tIn the Pausing mode, the algorithm advances in the given intervals value, representing milliseconds between each step.";
		std::cout << "\n\n\tPress any button to return to the Main menu!";
	}
	else
	{
		std::cout << "\n\t\t Chess:Alg\n";
		std::cout << "\t     Keszitette Torok Csongor\n";
		std::cout << "\n\tAz alkalmazast kulonbozo sakkos matematikai problemak megjelenitesere es megoldasara keszult\n\tilletve ezek osszehasonlitasara ido es optimalizalas szempontjabol.\n";
		std::cout << "\n\tLepesrol-lepesre iteralas : Minden alkalommal amikor megnyomja a Space-t, egy lepest tesz az algoritmus.";
		std::cout << "\n\tSzunetelo mod : Minden Space gomb lenyomasakor, szunetel az algoritmus futasa.";
		std::cout << "\n\tEbben a modban az algoritmus az allithato idotartam erteke szerint lepked, miliszekundumokban szamolva.";
		std::cout << "\n\n\tNyomjon meg barmilyen gombot a Fo Menuhoz valo visszatereshez!";
	}

	btn = _getch();
}

void exit_part()
{
}

void intro_screen()
{
	Sleep(500);

	std::cout << '\n';
	std::cout << "    _:_\n";
	Sleep(40);
	std::cout << "   '-.-'\n";
	Sleep(40);
	std::cout << "  __.'.__       ()   \n";
	Sleep(40);
	std::cout << " |_______|   .-:--:-.\n";
	Sleep(40);
	std::cout << "  \\=====/     \\____/                                                              ()\n";
	Sleep(40);
	std::cout << "   )___(      {====}     _____  _                                   _             /\\  \n";
	Sleep(40);
	std::cout << "  /_____\\      )__(     / ____|| |                     _     /\\    | |           /  \\       (\=,  \n";
	Sleep(40);
	std::cout << "   |   |      /____\\   | |     | |__    ___  ___  ___ (_)   /  \\   | |  __ _    (    )    //  .\\ \n";
	Sleep(40);
	std::cout << "   |   |       |  |    | |     | '_ \\  / _ \\/ __|/ __|     / /\\ \\  | | / _` |    )__(    (( \\_  \\\n";
	Sleep(40);
	std::cout << "   |   |       |  |    | |____ | | | ||  __/\\__ \\__  \\ _  / ____ \\ | || (_| |   /____\\    ))  `\\_) \n";
	Sleep(40);
	std::cout << "   |   |       |  |     \\_____||_| |_| \\___||___/|___/(_)/_/    \\_\\|_| \\__, |    |  |    (/     \\ \n";
	Sleep(40);
	std::cout << "   |   |       |  |                                                     __/ |    |  |     | _.-'| \n";
	Sleep(40);
	std::cout << "  /_____\\     /____\\                                                   |___/    /____\\     )___( \n";
	Sleep(40);
	std::cout << " (=======)   (======)                                                          (======)   (=====)\n";
	Sleep(40);
	std::cout << " }======={   }======{                                                          }======{   }====={\n";
	Sleep(40);
	std::cout << "(_________) (________)                                                        (________) (_______)\n";

	Sleep(1000);
	if (lan)
	{
		std::cout << "\n\t\t\t\t   Press Any Button to Continue!";
	}
	else
	{
		std::cout << "\n\tNyomjon meg barmilyen gombot a tovabblepeshez!";
	}

	btn = _getch();
}

int main()
{
	do
	{
		if (intro)
			intro_screen();
	} while (0);

MainMenu :

	system("cls");

	//auto timer1 = async(launch::async, get_btn);
	//auto timer2 = async(launch::async, timer, chrono::seconds(3));


	if(lan)
	{
		std::cout << "\n\t\tMain Menu\n\n";
		std::cout << "\t1. Chess Problems\n";
		std::cout << "\t2. Settings\n";
		std::cout << "\t3. Notes\n";
		std::cout << "\t4. Exit\n";
	}
	else
	{
		std::cout << "\n\t\tFo menu\n\n";
		std::cout << "\t1. Sakk problemak\n";
		std::cout << "\t2. Beallitasok\n";
		std::cout << "\t3. Jegyzetek\n";
		std::cout << "\t4. Kilepes\n";
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

		Exit :

		system("cls");

		if (lan)
		{
			std::cout << "\n\tAre you sure you want to quit?\n";
			std::cout << "\t1. Yes\t2. No";
		}
		else
		{
			std::cout << "\n\tBiztos ki szeretne lepni?\n";
			std::cout << "\t1. Igen\t2. Nem";
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
		default :
			goto Exit;
		}

		break;
	}
	goto MainMenu;
}
