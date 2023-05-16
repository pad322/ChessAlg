#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <future>
#include <fstream>

char btn;
bool run_mode;
bool lan;
bool intro;
int interval;
char c[5]={'0','0','0','0'};

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
		Sleep(40);
		std::cout << "\n\n\t1. Queen problem with minimal nr. of pieces";
		Sleep(40);
		std::cout << "\n\t2. Queens dominating";
		Sleep(40);
		std::cout << "\n\t3. Queen on horseback";
		Sleep(40);
		std::cout << "\n\t4. Independent rooks";
	}
	else
	{
		std::cout << "\n\tValassza ki a sakk problemat";
		Sleep(40);
		std::cout << "\n\n\t1. Kiralyno problema legkevesebb darabbal";
		Sleep(40);
		std::cout << "\n\t2. Kiralyno lefedes";
		Sleep(40);
		std::cout << "\n\t3. Kiralyno lohaton lefedes";
		Sleep(40);
		std::cout << "\n\t4. Kulonallo bastyak";
	}

	btn = _getch();

	system("cls");



	if (lan)
	{
		std::cout << "\n\tSelect a programming approach!";
		Sleep(40);
		std::cout << "\n\n\t1. Dynamic";
		Sleep(40);
		std::cout << "\n\t2. Greedy";
		Sleep(40);
		std::cout << "\n\t3. Backtracking";
	}
	else
	{
		std::cout << "\n\tValassza ki a programozasi modszert!";
		Sleep(40);
		std::cout << "\n\n\t1. Dinamikus";
		Sleep(40);
		std::cout << "\n\t2. Greedy";
		Sleep(40);
		std::cout << "\n\t3. Backtracking";
		Sleep(40);
	}

	btn = _getch();

}

void fill_settings()
{
	std::ofstream out("settings.txt", std::ofstream::trunc);

	char output[3];

	if (run_mode)
	{
		output[0] = '1';
	}
	else
	{
		output[0] = '0';
	}

	if (lan)
	{
		output[1] = '1';
	}
	else
	{
		output[1] = '0';
	}

	if (intro)
	{
		output[2] = '1';
	}
	else
	{
		output[2] = '0';
	}

	out << output[0] << output[1] << output[2] << ' ' << interval;

	out.close();

}

void settings_menu()
{

Settings:
	system("cls");

	Sleep(40);

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

	Sleep(40);

	if (lan)
		std::cout << "\t2. Step interval - ";
	else
		std::cout << "\t2. Lepesenkenti idotartam - ";

	std::cout << interval << '\n';

	Sleep(40);


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

	Sleep(40);

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

	Sleep(40);

	if (lan)
		std::cout << "\t5. Back to Main Menu\n";
	else
		std::cout << "\t5. Vissza a Fo Menube\n";

	btn = _getch();

	switch (btn)
	{
	case '1':
		run_mode = !run_mode;
		fill_settings();
		goto Settings;
		break;
	case '2':
		interval += 100;
		if (interval > 1000)
			interval = 100;
		fill_settings();
		goto Settings;
		break;
	case '3':
		lan = !lan;
		fill_settings();
		goto Settings;
		break;
	case '4':
		intro = !intro;
		fill_settings();
		goto Settings;
		break;
	case '5':
		break;
	default :
		goto Settings;
		break;
	}
}

void record_menu()
{
	system("cls");
	if (lan)
	{

	}
	else
	{

	}

	btn = _getch();
}

void notes_menu()
{
	system("cls");
	if(lan)
	{
		std::cout << "\n\t\t Chess:Alg\n";
		Sleep(40);
		std::cout << "\t Created by Torok Csongor\n";
		Sleep(40);
		std::cout << "\n\tThe app was made for displaying and solving different mathematical chess problems\n\tcomparing these in terms of running time and optimization.\n";
		Sleep(40);
		std::cout << "\n\tStep-by-step mode : Each time Space is pressed, the algorithm advances one step.";
		Sleep(40);
		std::cout << "\n\tPausing mode : Each time Space is pressed, the algorithm stops.";
		Sleep(40);
		std::cout << "\n\tIn the Pausing mode, the algorithm advances in the given intervals value, representing milliseconds between each step.";
		Sleep(40);
		std::cout << "\n\n\tThe Recorded Times menu shows the best running times for each algorithm, categorized into the programming techniques.\n";
		Sleep(40);
		std::cout << "\n\n\tPress any button to return to the Main menu!";
	}
	else
	{
		std::cout << "\n\t\t Chess:Alg\n";
		Sleep(40);
		std::cout << "\t     Keszitette Torok Csongor\n";
		Sleep(40);
		std::cout << "\n\tAz alkalmazast kulonbozo sakkos matematikai problemak megjelenitesere es megoldasara keszult\n\tilletve ezek osszehasonlitasara ido es optimalizalas szempontjabol.\n";
		Sleep(40);
		std::cout << "\n\tLepesrol-lepesre iteralas : Minden alkalommal amikor megnyomja a Space-t, egy lepest tesz az algoritmus.";
		Sleep(40);
		std::cout << "\n\tSzunetelo mod : Minden Space gomb lenyomasakor, szunetel az algoritmus futasa.";
		Sleep(40);
		std::cout << "\n\tEbben a modban az algoritmus az allithato idotartam erteke szerint lepked, miliszekundumokban szamolva.";
		Sleep(40);
		std::cout << "\n\n\tA mentett idok menupontban az algoritmusok futasi idejei vannak elmentve, technikak szerint kategorizalva.\n";
		Sleep(40);
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

	btn = _getch();

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
	std::cout << "   |   |       |  |    | |____ | | | ||  __/\\__ \\\\__ \\ _  / ____ \\ | || (_| |   /____\\    ))  `\\_) \n";
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
		std::cout << "\n\t\t\t   Nyomjon meg barmilyen gombot a tovabblepeshez!";
	}

	btn = _getch();
}

int main()
{

	std::ifstream in("settings.txt");

	for (int i = 0; i < 3; ++i)
	{
		in >> c[i];
	}

	in >> interval;

	if (c[0] == '1')
		run_mode = true;
	else
		run_mode = false;

	if (c[1] == '1')
		lan = true;
	else
		lan = false;

	if (c[2] == '1')
		intro = true;
	else
		intro = false;

	in.close();

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
		Sleep(40);
		std::cout << "\t1. Chess Problems\n";
		Sleep(40);
		std::cout << "\t2. Settings\n";
		Sleep(40);
		std::cout << "\t3. Notes\n";
		Sleep(40);
		std::cout << "\t4. Recorded Times\n";
		Sleep(40);
		std::cout << "\t5. Exit\n";
	}
	else
	{
		std::cout << "\n\t\tFo menu\n\n";
		Sleep(40);
		std::cout << "\t1. Sakk problemak\n";
		Sleep(40);
		std::cout << "\t2. Beallitasok\n";
		Sleep(40);
		std::cout << "\t3. Jegyzetek\n";
		Sleep(40);
		std::cout << "\t4. Mentett idok\n";
		Sleep(40);
		std::cout << "\t5. Kilepes\n";
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
		record_menu();
		break;
	case '5':

		Exit :

		system("cls");

		if (lan)
		{
			std::cout << "\n\tAre you sure you want to quit?\n";
			Sleep(40);
			std::cout << "\t1. Yes\t2. No";
			Sleep(40);
		}
		else
		{
			std::cout << "\n\tBiztos ki szeretne lepni?\n";
			Sleep(40);
			std::cout << "\t1. Igen\t2. Nem";
			Sleep(40);
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
