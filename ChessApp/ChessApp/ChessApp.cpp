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
//int mode;
int task;

int n, m;

/*
void timer(chrono::seconds delay)
{
	this_thread::sleep_for(delay);
	std::cout << "\n\tPress a number on your keyboard to navigate the menu!\n";
}
*/

void basic_print(int table[50][50])
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << table[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

int attacked_table[50][50];

int xcoord[50] = { 0 };
int ycoord[50] = { 0 };

void make_attacked_table(int table[50][50])
{
	int k = 0;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (table[i][j] == 1)
			{
				xcoord[k] = i;
				ycoord[k] = j;
				//std::cout << xcoord[k] << ' ' << ycoord[k] << '\n';
				k++;
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			attacked_table[i][j] = 0;

			for (int l = 0; l < k; ++l)
			{
				if (xcoord[l] == i && ycoord[l] == j)
				{
					attacked_table[i][j] = 2; // 2 jelzi ha kiralyno van az adott kockan
				}
				else if ((xcoord[l] == i || ycoord[l] == j) && table[i][j] != 1)
				{
					attacked_table[i][j] = 1; // 1 jelzi ha tamadva van a pont
				}
				else if (std::abs((xcoord[l]) - i) == std::abs((ycoord[l]) - j) && table[i][j] != 1)
				{
					attacked_table[i][j] = 1;
				}
			}
		}
	}
}

void chess_table_print(int table[50][50]) // detailed chess table printer
{
	char abc = 'A';

	make_attacked_table(table);

	bool larger = false;
	int temp = 0;
	int number = 1;

	if (n < 39)
	{
		int rows = 0;

		while (rows < n)
		{
			if (abc > 'Z' && !larger)
			{
				abc = 'a';
				larger = true;
			}
			std::cout << "   " << abc << "  ";
			abc++;
			rows++;
		}

		std::cout << "\n";

		rows = 0;

		while (rows < n)
		{
			std::cout << "------";
			rows++;
		}

		std::cout << "-\n";

		for (int i = 0; i < n; ++i)
		{
			while (temp < 3)
			{
				for (int j = 0; j < n; ++j)
				{
					if (attacked_table[i][j] == 0)
					{
						std::cout << "|     ";
					}
					if (attacked_table[i][j] == 1)
					{
						std::cout << "|#####";
					}
					if (attacked_table[i][j] == 2)
					{
						if (temp != 1)
						{
							std::cout << "|     ";
						}
						else
						{
							std::cout << "|  Q  ";
						}
					}
				}

				std::cout << '|';

				if (temp == 1)
				{
					std::cout << "   " << number;
					number++;
				}

				temp++;

				std::cout << '\n';
			}
			temp = 0;

			rows = 0;
			while (rows < n)
			{
				std::cout << "------";
				rows++;
			}

			std::cout << "-\n";
		}
	}
}

bool dominating_safe_queen(int table[50][50],int s, int o) // Backtracking Dominating Queens safety checker
{
	for (int i = 0; i < n; ++i) 
	{
		if (table[i][o] == 1) 
		{
			return false;
		}
	}

	for (int i = 0; i < n; ++i) 
	{
		if (table[s][i] == 1) 
		{
			return false;
		}
	}

	int i = s;
	int j = o;

	while (i >= 0 && j >= 0) // ellenorizzuk a bal felso atlot
	{
		if (table[i][j] == 1)
		{
			return false;
		}

		--i;
		--j;
	}

	i = s;
	j = o;

	while (i < n && j >= 0) // ellenorizzuk a bal also atlot
	{
		if (table[i][j] == 1)
		{
			return false;
		}

		++i;
		--j;
	}

	i = s;
	j = o;

	while (i < n && j < n) // ellenorizzuk a jobb also atlot
	{
		if (table[i][j] == 1)
		{
			return false;
		}

		++i;
		++j;
	}

	i = s;
	j = o;

	while (i >= 0 && j < n) // ellenorizzuk a jobb also atlot
	{
		if (table[i][j] == 1)
		{
			return false;
		}

		--i;
		++j;
	}

	return true;

}

bool safe_queen(int table[50][50], int s, int o) // Backtracking N-Queen safety checker
{
	for (int i = 0; i < o; ++i) // megnezzuk az oszlopat ha ures
	{
		if (table[s][i] == 1)
		{
			return false;
		}
	}

	int i = s;
	int j = o;

	while (i >= 0 && j >= 0) // ellenorizzuk a bal felso atlot
	{
		if (table[i][j] == 1)
		{
			return false;
		}

		--i;
		--j;
	}

	i = s;
	j = o;

	while (i < n && j >= 0) // ellenorizzuk a bal also atlot
	{
		if (table[i][j] == 1)
		{
			return false;
		}

		++i;
		--j;
	}

	return true;
}

bool safe_queen_man(int table[50][50], int s, int o) // Backtracking N-Queen safety checker, with text
{
	if (btn == 'a')
	{
		return false;
	}

	for (int i = 0; i < o; ++i)
	{
		if (table[s][i] == 1)
		{
			if (lan)
			{
				std::cout << "The queen placed on [" << s << "] , [" << i << "]";
				Sleep(40);
				std::cout<< "dominates her row.\n";
			}
			else
			{
				std::cout << "[" << s << "] , [" << i << "] kiralyno miatt";
				Sleep(40);
				std::cout << " a sora le van fedve.\n";
			}

			btn = _getch();

			return false;
		}
	}

	int i = s;
	int j = o;

	while(i>=0 && j>=0)
	{
		if (table[i][j] == 1)
		{
			if (lan)
			{
				std::cout << "The queen placed on [" << i << "] , [" << j << "]";
				Sleep(40);
				std::cout << " attacks her lower right diagonal.\n";
				Sleep(40);
			}
			else
			{
				std::cout << "[" << i << "] , [" << j << "]-re helyezett kiralyno";
				Sleep(40);
				std::cout << " lefedi a jobb also atlojat.\n";
				Sleep(40);
			}

			btn = _getch();

			return false;
		}

		--i;
		--j;
	}

	i = s;
	j = o;

	while (i<n && j>=0)
	{
		if (table[i][j] == 1)
		{
			if (lan)
			{
				std::cout << "The queen placed on [" << i << "] , [" << j << "]";
				Sleep(40);
				std::cout << " attacks her upper right diagonal.\n";
				Sleep(40);
			}
			else
			{
				std::cout << "[" << i << "] , [" << j << "]-re helyezett kiralyno";
				Sleep(40);
				std::cout << " lefedi a jobb felso atlojat.\n";
				Sleep(40);
			}

			btn = _getch();

			return false;
		}

		++i;
		--j;
	}

	return true;
}

bool bt_queen_auto(int table[50][50], int j) // Backtracking N-Queen, automatic iteration
{
	if (j == n)
	{
		chess_table_print(table);
		return true;
	}

	for (int i = 0; i < n; ++i)
	{
		if (safe_queen(table, i, j))
		{

			if(interval)
				system("cls");

			table[i][j] = 1;
			
			//basic_print(table);
			if (interval)
			{
				chess_table_print(table);

				Sleep(interval);
			}

			if (bt_queen_auto(table, j + 1))
				return true;

			table[i][j] = 0;

			if (interval)
			{
				system("cls");

				//basic_print(table);
				chess_table_print(table);

				Sleep(interval);
			}
		}
	}

	return false;
}

bool bt_queen_man(int table[50][50], int j) // Backtracking N-Queen, manual iteration
{
	if (btn == 'a')
	{
		return false;
	}

	if (j == n)
	{
		return true;
	}

	for (int i = 0; i < n; ++i)
	{
		if (safe_queen_man(table, i, j))
		{
			system("cls");

			table[i][j] = 1;
			//Sleep(50);
			//basic_print(table);
			chess_table_print(table);

			if (lan)
			{
				Sleep(40);
				std::cout << "\nPlaced a queen on the [" << i << "] , [" << j << "] coordinates.\n";
			}
			else
			{
				Sleep(40);
				std::cout << "\nElhelyezett egy kiralynot a(z) [" << i << "] , [" << j << "] koordinatakra.\n";
			}

			btn = _getch();

			if (btn == 'a')
			{
				if (lan)
				{
					std::cout << "\nProgram aborted.";
				}
				else
				{
					std::cout << "\nProgram megallitva.";
				}
				return true;
			}

			if (bt_queen_man(table, j + 1))
				return true;

			if (btn == 'a')
				return false;

			table[i][j] = 0;

			system("cls");

			//basic_print(table);
			chess_table_print(table);

			if (btn == 'a')
			{
				if (lan)
				{
					std::cout << "\nProgram aborted.";
				}
				else
				{
					std::cout << "\nProgram megallitva.";
				}
				return true;
			}

			if (lan)
			{
				Sleep(40);
				std::cout << "\nRemoved [" << i << "] , [" << j << "]\n";
				Sleep(40);
				std::cout << "Backtracking to a previous state.\n";
			}
			else
			{
				Sleep(40);
				std::cout << "\nTorolve lett [" << i << "] , [" << j << "]\n";
				Sleep(40);
				std::cout << "Backtrack - el, vagyis visszafele lepked egy elozo allapothoz.\n";
			}

			btn = _getch();


		}
	}

	return false;
}

int min_nr = 99;

bool bt_dominating_queen_man(int table[50][50],int nr) // Backtracking Independent Dominating Queens Problem, manual
{
	if (btn == 'a')
	{
		return false;
	}

	if (nr >= min_nr)
	{
		return true;
	}

	bool found = false;
	bool nul = false;

	while (!found)
	{
		make_attacked_table(table);

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (attacked_table[i][j] == 0)
				{
					nul = true;
					break;
				}
			}
		}

		if (nul)
		{
			found = true;
		}

		if (found)
		{
			break;
		}

		system("cls");
		chess_table_print(table);
		min_nr = nr;
		if (lan)
		{
			if(min_nr == n/2+1 || min_nr == n/2)
				std::cout << "Found an optimal solution!\n";
			else
				std::cout << "Found a partial solution!\n";
		}
		else
		{
			if (min_nr == n / 2 + 1 || min_nr == n / 2)
				std::cout << "Talalt egy optimalis megoldast!\n";
			else
				std::cout << "Talalt egy parcialis megoldast!\n";
		}

		std::cout << min_nr << '\n';
		btn = _getch();

		if (btn == 'a')
		{
			if (lan)
			{
				std::cout << "\nProgram aborted.";
			}
			else
			{
				std::cout << "\nProgram megallitva.";
			}
			return true;
		}

		break;

	}

	bool temp = false;

	for (int i = 0; i < n; ++i) 
	{
		for (int j = 0; j < n;++j)
		{

			if (dominating_safe_queen(table, i, j))
			{

				if (nr > n / 2 + 1 && !temp)
				{
					if (lan)
					{
						std::cout << "Has placed more than n/2+1 pieces, backtracking.\n";
					}
					else
					{
						std::cout << "Mar tobb mint n/2+1 darabot tett le, backtrack-el.\n";
					}
					temp = true;
					btn = _getch();
					continue;
				}

				if (temp)
				{
					continue;
				}

				system("cls");

				table[i][j] = 1;

				chess_table_print(table);

				btn = _getch();

				if (btn == 'a')
				{
					if (lan)
					{
						std::cout << "\nProgram aborted.";
					}
					else
					{
						std::cout << "\nProgram megallitva.";
					}
					return false;
				}

				if (bt_dominating_queen_man(table, nr + 1))
					return true;

				if (btn == 'a')
				{
					return false;
				}

				table[i][j] = 0;

				system("cls");

				chess_table_print(table);

				btn = _getch();

				if (btn == 'a')
				{
					if (lan)
					{
						std::cout << "\nProgram aborted.";
					}
					else
					{
						std::cout << "\nProgram megallitva.";
					}
					return false;
				}
			}
		}
	}

	return false;
}

bool bt_dominating_queen_auto(int table[50][50],int nr)
{

	bool found = false;
	bool nul = false;

	while (!found)
	{
		make_attacked_table(table);

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (attacked_table[i][j] == 0)
				{
					nul = true;
					break;
				}
			}
		}

		if (nul)
		{
			found = true;
		}

		if (found)
		{
			break;
		}

		system("cls");
		min_nr = nr;

		if (min_nr == n / 2 + 1 || min_nr == n / 2)
		{
			chess_table_print(table);
			if (lan)
			{
				std::cout << "Found an optimal solution!\n";
			}
			else
			{
				std::cout << "Talalt egy optimalis megoldast!\n";
			}
			return true;
		}

		break;

	}

	int k = 1;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; j++)
		{
			if (dominating_safe_queen(table, i, j))
			{

				if (nr >= n / 2 + 1)
				{
					continue;
				}


				if (interval)
					system("cls");

				table[i][j] = 1;

				if (interval)
				{
					chess_table_print(table);
				
					Sleep(interval);
				}

				if (bt_dominating_queen_auto(table, nr + 1))
					return true;

				table[i][j] = 0;

				if (interval)
				{
					system("cls");

					chess_table_print(table);

					Sleep(interval);
				}
			}
		}
	}

	return false;
}

int attacked_nr(int table[50][50], int s, int o)
{
	int count = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == s && table[i][j] == 0)
			{
				count++;
			}

			else if (j == o && table[i][j] == 0)
			{
				count++;
			}

			else if (std::abs(s - i) == std::abs(o - j) && table[i][j] == 0)
			{
				count++;
			}
		}
	}

	return count;
}

void dominating_queens_man(int table[50][50]) // Greedy Queen Domintation, manual
{
	make_attacked_table(table);

	int nul = false;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (attacked_table[i][j] == 0)
			{
				nul = true;
				break;
			}
		}
	}

	if (!nul)
	{
		if (lan)
		{
			std::cout << "The table has no empty spaces left.\n";
		}
		else
		{
			std::cout << "Nem maradt a tablan tobb ures mezo.\n";
		}
		return;
	}

	int xcoord, ycoord;
	int max = -1;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (max < attacked_nr(attacked_table, i, j))
			{
				max = attacked_nr(attacked_table, i, j);
				xcoord = i;
				ycoord = j;
			}
		}
	}

	table[xcoord][ycoord] = 1;

	system("cls");

	chess_table_print(table);

	if (lan)
	{
		std::cout << "[" << xcoord << "] , [" << ycoord << "] point has the most attacked spaces. Placing queen.\n";
	}
	else
	{
		std::cout << "[" << xcoord << "] , [" << ycoord << "] pont tamadja a legtobb mezot. Kiralynot helyezunk erre.\n";
	}

	btn = _getch();

	dominating_queens_man(table);
}

void dominating_queens_auto(int table[50][50]) // Greedy Queen Domintation, automatic
{
	make_attacked_table(table);

	int nul = false;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (attacked_table[i][j] == 0)
			{
				nul = true;
				break;
			}
		}
	}

	if (!nul)
	{
		return;
	}

	int xcoord, ycoord;
	int max = -1;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (max < attacked_nr(attacked_table, i, j))
			{
				max = attacked_nr(attacked_table, i, j);
				xcoord = i;
				ycoord = j;
			}
		}
	}

	//std::cout << "x : " << xcoord << " , " << " y : " << ycoord << '\n';
	
	table[xcoord][ycoord] = 1;

	if (interval)
	{
		system("cls");
		
		chess_table_print(table);
		
		Sleep(interval);
	}

	dominating_queens_auto(table);
}

void guider()
{

	auto started = std::chrono::high_resolution_clock::now();
	auto done = std::chrono::high_resolution_clock::now();

	std::ofstream out("data.txt",std::ofstream::app);

	system("cls");

	if (lan)
	{
		std::cout << "\n\t Numbers above 10 might take longer!";
		Sleep(40);
		std::cout << "\n\t Please enter the chess tables dimension (NxN) : ";
		std::cin >> n;
	}
	else
	{
		std::cout << "\n\t 10 folotti szamok tobb idot vehetnek igenybe!";
		Sleep(40);
		std::cout << "\n\t Kerem adja meg a sakk tabla meretet (NxN) : ";
		std::cin >> n;
	}

	system("cls");

	if (!(n > 0 && m > 0) && !(n <= 50 && m <= 50))
	{
		std::cout << "\n\tInvalid data";
		goto Guider_End;
	}

	int table[50][50];

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			table[i][j] = 0;
		}
	}

	/*
	if (lan)
	{
		std::cout << "\n\tCompiling...";
	}
	else
	{
		std::cout << "\n\tKompilal...";
	}
	*/

	// Backtracking algorithms
		
	switch (task)
	{
	case 1: // N-Queen
		started = std::chrono::high_resolution_clock::now();

		if (run_mode)
		{
			bt_queen_man(table, 0);
			out << 1 << ' ';
		}
		else
		{
			bt_queen_auto(table, 0);
			out << 0 << ' ';
		}

		/*

		system("cls");

		chess_table_print(table);

		if (lan)
		{
			std::cout << "\nThe algorithm has finished.\n";
		}
		else
		{
			std::cout << "\nAz algoritmus veget ert.\n";
		}

		*/

		done = std::chrono::high_resolution_clock::now();

		system("cls");

		chess_table_print(table);

		if (lan)
		{
			std::cout << "\nTotal running time : ";
		}
		else
		{
			std::cout << "\nTeljes futasi ido : ";
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count()<<" ms\n";

		out  << 1 << ' ' << n << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';

		btn = _getch();
		break;

	case 2: // Dominating Independent Queens
		started = std::chrono::high_resolution_clock::now();
		if (run_mode)
		{
			out << 1 << ' ';
			if (!bt_dominating_queen_man(table, 0))
			{
				if (lan)
				{
					//std::cout << "No solution has been found.\n";
				}
				else
				{
					//std::cout << "Nem talalt megoldast.\n";
				}
			}
		}
		else
		{
			out << 0 << ' ';
			if (!bt_dominating_queen_auto(table, 0))
			{
				if (lan)
				{
					//std::cout << "No solution has been found.\n";
				}
				else
				{
					//std::cout << "Nem talalt megoldast.\n";
				}
			}
		}
		done = std::chrono::high_resolution_clock::now();
		if (lan)
		{
			std::cout << "\nTotal running time : ";
		}
		else
		{
			std::cout << "\nTeljes futasi ido : ";
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";

		out << 2 << ' ' <<n<<' '<< std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';

		min_nr = 99;
		btn = _getch();
		break;

	case 3:
		started = std::chrono::high_resolution_clock::now();
		if (run_mode)
		{
			dominating_queens_man(table);
			out << 1 << ' ';
		}
		else
		{
			dominating_queens_auto(table);
			out << 0 << ' ';
		}

		done = std::chrono::high_resolution_clock::now();
		if (lan)
		{
			std::cout << "\nTotal running time : ";
		}
		else
		{
			std::cout << "\nTeljes futasi ido : ";
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";

		out << 3 << ' ' << n << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';

		btn = _getch();
		break;
	case 4:
		break;
	default:
		break;
	}

	out.close();

Guider_End:
		
	system("cls");

}

void chess_menu() 
{

Chess_Menu:

	system("cls");

	if (lan)
	{
		std::cout << "\n\tSelect a chess problem!";
		Sleep(40);
		std::cout << "\n\n\t1. N - Queen problem";
		Sleep(40);
		std::cout << "\n\t2. Queens independent dominating";
		Sleep(40);
		std::cout << "\n\t3. Queens dominating";
		Sleep(40);
		std::cout << "\n\t4. Knights tour";
		Sleep(40);
		std::cout << " \n\t5. Back to Main Menu";
	}
	else
	{
		std::cout << "\n\tValassza ki a sakk problemat";
		Sleep(40);
		std::cout << "\n\n\t1. N Kiralynos problema";
		Sleep(40);
		std::cout << "\n\t2. Kiralyno kulonallo lefedes";
		Sleep(40);
		std::cout << "\n\t3. Kiralyno lefedes";
		Sleep(40);
		std::cout << "\n\t4. Huszar turne";
		Sleep(40);
		std::cout << " \n\t5. Vissza a Fo Menube";
	}

	btn = _getch();

	switch (btn)
	{
	case '1':
		task = 1;
		break;
	case '2':
		task = 2;
		break;
	case '3':
		task = 3;
		break;
	case '4':
		task = 4;
		break;
	case '5':
		goto Chess_Menu_End;
		break;
	default :
		goto Chess_Menu;
		break;
	}

Chess_Menu_Mid:

	system("cls");

	/*

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

	switch (btn)
	{
	case '1':
		mode = 1;
		break;
	case '2':
		mode = 2;
		break;
	case '3':
		mode = 3;
		break;
	default :
		goto Chess_Menu_Mid;
		break;
	}

	*/

	guider();

Chess_Menu_End:

	system("cls");

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
			std::cout << "Lepesrol-lepesre iteralo\n";
	}
	else
	{
		if (lan)
			std::cout << "Automatic mode\n";
		else
			std::cout << "Automatikus mod\n";
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
			interval = 0;
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
		std::cout << "\n\tStep-by-step mode : Each time a button is pressed, the algorithm advances one step. \n\tWhile running, the program can be aborted by pressing the 'a' button.\n\tHighly recommended running mode!\n";
		Sleep(40);
		std::cout << "\n\tAutomatic mode : The algorithm runs without any user input.";
		Sleep(40);
		std::cout << "\n\tIn the Automatic mode, the algorithm advances in the given value, representing milliseconds between each step.";
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
		std::cout << "\n\tLepesrol-lepesre iteralas : Minden alkalommal amikor megnyomjunk egy gombot, egy lepest tesz az algoritmus. \n\tFutas kozben az 'a' gomb megnyomasaval megszakithatjuk a programot.\n\tAjanlott futtatasi modszer!\n";
		Sleep(40);
		std::cout << "\n\tAutomatikus mod : Az algoritmus felhasznaloi bemenetek nelkul lepked.";
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

	//btn = _getch();

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
	std::cout << "  /_____\\      )__(     / ____|| |                     _     /\\    | |           /  \\       (\\=,  \n";
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
		std::cout << "\n\t\t\t   Nyomjon Barmilyen Gombot a Tovabblepeshez!";
	}

	btn = _getch();
}

int main()
{
	char c[5];

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
