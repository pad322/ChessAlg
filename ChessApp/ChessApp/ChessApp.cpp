#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <fstream>

char btn;
bool run_mode;
bool lan;
bool intro;
int interval;
//int mode;
int task;

int n, m;

int cursor_x = -1;
int cursor_y = -1;

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

int xcoord[100] = { 0 };
int ycoord[100] = { 0 };

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

void make_rook_attacked_table(int table[50][50])
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
				if (i == xcoord[l] && j == ycoord[l])
				{
					attacked_table[i][j] = 2;
				}
				else if (i == xcoord[l] && attacked_table[i][j] != 2)
				{
					attacked_table[i][j] = 1;
				}
				else if (j == ycoord[l] && attacked_table[i][j] != 2)
				{
					attacked_table[i][j] = 1;
				}
			}
		}
	}
}

void make_knight_attacked_table(int table[50][50])
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

	int x_add[9] = { -1,1,-2,-2, -1,1,2,2 };
	int y_add[9] = { -2,-2,-1,1, 2,2,-1,1 };

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			attacked_table[i][j] = 0;

			for (int l = 0; l < k; ++l)
			{
				for (int h = 0; h < 9; ++h)
				{
					if (attacked_table[xcoord[l] + x_add[h]][ycoord[l] + y_add[h]] != 2)
					{
						attacked_table[xcoord[l] + x_add[h]][ycoord[l] + y_add[h]] = 1;
					}
				}
				if (xcoord[l] == i && ycoord[l] == j)
				{
					attacked_table[i][j] = 2;
				}

			}
		}
	}
}

void make_bishop_attacked_table(int table[50][50])
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
				if (i == xcoord[l] && j == ycoord[l])
				{
					attacked_table[i][j] = 2;
				}
				else if (std::abs(i - xcoord[l]) == std::abs(j - ycoord[l]) && attacked_table[i][j] !=2)
				{
					attacked_table[i][j] = 1;
				}
			}
		}
	}

}

void queen_printer(int table[50][50]) // detailed chess table printer
{
	char abc = 'A';

	bool larger = false;
	int temp = 0;
	int number = 1;

	make_attacked_table(table);

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
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "| +++ ";
							else
								std::cout << "|+   +";
						}
						else
							std::cout << "|     ";
					}
					if (attacked_table[i][j] == 1)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "|#+++#";
							else
								std::cout << "|+   +";
						}
						else
							std::cout << "|#####";
					}
					if (attacked_table[i][j] == 2)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
							{
								std::cout << "| +++ ";
							}
							else
							{
								std::cout << "|+ Q +";
							}
						}
						else
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

void knight_printer(int table[50][50])
{
	char abc = 'A';

	make_knight_attacked_table(table);

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
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "| +++ ";
							else
								std::cout << "|+   +";
						}
						else std::cout << "|     ";
					}
					if (attacked_table[i][j] == 1)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "|#+++#";
							else
								std::cout << "|+   +";
						}
						else std::cout << "|#####";
					}
					if (attacked_table[i][j] == 2)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "| +++ ";
							else
								std::cout << "|+ H +";
						}
						else if (temp != 1)
						{
							std::cout << "|     ";
						}
						else
						{
							std::cout << "|  H  ";
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

void knight_tour_print(int table[50][50])
{
	char abc = 'A';

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
					if (table[i][j] == 0)
					{
						std::cout << "|     ";
					}
					if (table[i][j] >= 1)
					{
						if (temp != 1)
						{
							std::cout << "|     ";
						}
						else
						{
							if (table[i][j] / 10 == 0)
								std::cout << "|  " << table[i][j] << "  ";
							else if (table[i][j] / 10 < 10)
								std::cout << "| " << table[i][j] << "  ";
							else
								std::cout << "| " << table[i][j]  << " ";
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

void rook_printer(int table[50][50])
{
	char abc = 'A';

	bool larger = false;
	int temp = 0;
	int number = 1;

	make_rook_attacked_table(table);

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
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "| +++ ";
							else
								std::cout << "|+   +";
						}
						else std::cout << "|     ";
					}
					if (attacked_table[i][j] == 1)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "|#+++#";
							else
								std::cout << "|+   +";
						}
						else std::cout << "|#####";
					}
					if (attacked_table[i][j] == 2)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "| +++ ";
							else
								std::cout << "|+ T +";
						}
						else if (temp != 1)
						{
							std::cout << "|     ";
						}
						else
						{
							std::cout << "|  T  ";
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

void bishop_printer(int table[50][50])
{
	char abc = 'A';

	bool larger = false;
	int temp = 0;
	int number = 1;

	make_bishop_attacked_table(table);

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
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "| +++ ";
							else
								std::cout << "|+   +";
						}
						else std::cout << "|     ";
					}
					if (attacked_table[i][j] == 1)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "|#+++#";
							else
								std::cout << "|+   +";
						}
						else std::cout << "|#####";
					}
					if (attacked_table[i][j] == 2)
					{
						if (cursor_x == i && cursor_y == j)
						{
							if (temp != 1)
								std::cout << "|#+++#";
							else
								std::cout << "|+ B +";
						}
						else if (temp != 1)
						{
							std::cout << "|     ";
						}
						else
						{
							std::cout << "|  B  ";
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

///////////////////////
/////////////////////// Algorithms for the problems
///////////////////////

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

			char y_char = 'A' + i;

			if (lan)
			{
				std::cout << "The queen placed on " << y_char << " " << s + 1;
				Sleep(40);
				std::cout<< "dominates her row.\n";
			}
			else
			{
				std::cout << y_char << " " << s + 1  <<" kiralyno miatt";
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

			char y_char = 'A' + j;

			if (lan)
			{
				std::cout << "The queen placed on " << y_char << " " << i + 1;
				Sleep(40);
				std::cout << " attacks her lower right diagonal.\n";
				Sleep(40);
			}
			else
			{
				std::cout << y_char << " " << i + 1 << "-re helyezett kiralyno";
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
			char y_char = 'A' + j;

			if (lan)
			{
				std::cout << "The queen placed on " << y_char << " " << i + 1;
				Sleep(40);
				std::cout << " attacks her upper right diagonal.\n";
				Sleep(40);
			}
			else
			{
				std::cout << y_char << " " << i + 1 << "-re helyezett kiralyno";
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
		//basic_print(table);
		if(interval)
			system("cls");
		queen_printer(table);
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
				queen_printer(table);

				Sleep(interval);
			}

			if (bt_queen_auto(table, j + 1))
				return true;

			table[i][j] = 0;

			if (interval)
			{
				system("cls");

				//basic_print(table);
				queen_printer(table);

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
			queen_printer(table);

			char y_char = 'A' + j;

			if (lan)
			{
				Sleep(40);
				std::cout << "\nPlaced a queen on the " << y_char << " " << i+1 << " coordinates.\n";
			}
			else
			{
				Sleep(40);
				std::cout << "\nElhelyezett egy kiralynot a(z) " << y_char << " " << i+1 << " koordinatakra.\n";
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
			queen_printer(table);

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

			y_char = 'A' + j;

			if (lan)
			{
				Sleep(40);
				std::cout << "\nRemoved " << y_char << " " << i+1 << "\n";
				Sleep(40);
				std::cout << "Backtracking to a previous state.\n";
			}
			else
			{
				Sleep(40);
				std::cout << "\nTorolve lett " << y_char << " " << i+1 << "\n";
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
		queen_printer(table);
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

				queen_printer(table);

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

				queen_printer(table);

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

bool bt_dominating_queen_auto(int table[50][50],int nr) // Backtracking Dominating Independent Queen, automatic
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
			queen_printer(table);
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
					queen_printer(table);
				
					Sleep(interval);
				}

				if (bt_dominating_queen_auto(table, nr + 1))
					return true;

				table[i][j] = 0;

				if (interval)
				{
					system("cls");

					queen_printer(table);

					Sleep(interval);
				}
			}
		}
	}

	return false;
}

int attacked_nr(int table[50][50], int s, int o) // Hany nem lefedett pontot tamad minden pont egy tablan egy kiralyno
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

bool dominating_queens_auto_brute(int table[50][50],int count) // Brute-Force Queens dominating
{
	bool found = false;
	bool nul = false;

	if (count == n)
	{
		return false;
	}

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
			break;
		}

		system("cls");

		if (count == n / 2 + 1 || count == n / 2)
		{
			if (lan)
			{
				std::cout << "Found an optimal solution!\n";
			}
			else
			{
				std::cout << "Talalt egy optimalis megoldast!\n";
			}
		}

		return true;

	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (count > n / 2 + 1)
			{
				continue;
			}

			table[i][j] = 1;

			if (dominating_queens_auto_brute(table, count + 1))
				return true;

			table[i][j] = 0;
		}
	}
	
	return false;
}

void dominating_queens_man(int table[50][50],int count) // Greedy Queen Domintation, manual
{
	make_attacked_table(table);

	if (btn == 'a')
	{
		if (lan)
		{
			std::cout << "Program aborted.\n";
		}
		else
		{
			std::cout << "Program megallitva.\n";
		}
		return;
	}

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

		system("cls");

		queen_printer(table);

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

				//if (count > n / 2)
				//{
				//	continue;
				//}

				max = attacked_nr(attacked_table, i, j);
				xcoord = i;
				ycoord = j;
			}
		}
	}

	table[xcoord][ycoord] = 1;

	system("cls");

	queen_printer(table);

	char y_char = 'A' + ycoord;

	if (lan)
	{
		std::cout  << y_char << " " << xcoord+1 << " point has the most attacked spaces. Placing queen.\n";
	}
	else
	{
		std::cout << y_char  << " " << xcoord+1 << " pont tamadja a legtobb mezot. Kiralynot helyezunk erre.\n";
	}

	btn = _getch();


	if (btn == 'a')
	{
		if (lan)
		{
			std::cout << "Program aborted.\n";
		}
		else
		{
			std::cout << "Program megallitva.\n";
		}
		return;
	}

	dominating_queens_man(table,count + 1);
}

void dominating_queens_auto(int table[50][50],int count) // Greedy Queen Domintation, automatic
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
		if(interval)
			system("cls");
		
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
		
		queen_printer(table);
		
		Sleep(interval);
	}

	dominating_queens_auto(table, count + 1);
}

int knight_attacked_spots(int table[50][50], int x, int y) // Hany pontot tamad egy huszar
{

	// Az adatok amiket hozza adunk a koordinatakhoz, hogy a huszar lepeseit megtegyek.
	int x_add[9] = { -1,1,2,2,-1,1,-2,-2 };
	int y_add[9] = { 2,2,1,-1,-2,-2,-1,1 };  

	int count = 0;

	for (int k = 0; k < 8; ++k)
	{
		if (x + x_add[k] >= 0 && x + x_add[k] < n)
		{
			if (y + y_add[k] >= 0 && y + y_add[k] < n && table[x + x_add[k]][y + y_add[k]] == 0)
			{
				//table[x + x_add[k]][y + y_add[k]] = 1;
				//std::cout << x << " - " << x_add[k] << " = " << x + x_add[k] << '\n';
				//std::cout << y << " - " << y_add[k] << " = " << y + y_add[k] << '\n';
				count++;
			}
		}
	}

	return count;
}

int knight_attacked_spots_plus(int table[50][50], int x, int y) // Hany pontot tamad amikor a tabla le van fedve mar
{
	make_knight_attacked_table(table);

	int x_add[9] = { -1,1,2,2,-1,1,-2,-2 };
	int y_add[9] = { 2,2,1,-1,-2,-2,-1,1 };

	int count = 0;

	for (int k = 0; k < 8; ++k)
	{
		if (x + x_add[k] >= 0 && x + x_add[k] < n)
		{
			if (y + y_add[k] >= 0 && y + y_add[k] < n && attacked_table[x + x_add[k]][y + y_add[k]] == 0)
			{
				//table[x + x_add[k]][y + y_add[k]] = 1;
				//std::cout << x << " - " << x_add[k] << " = " << x + x_add[k] << '\n';
				//std::cout << y << " - " << y_add[k] << " = " << y + y_add[k] << '\n';
				count++;
			}
		}
	}

	return count;
}

/*
void knight_tour(int table[50][50], int x, int y) // Helytelen
{
	table[x][y] = 3;

	std::cout  << x << " , " << y << '\n';

	int min = 99;

	int x_new;
	int y_new;

	int x_add[9] = { -1,1,-2,-2, -1,1,2,2 };
	int y_add[9] = { -2,-2,-1,1, 2,2,-1,1 };

	//if (x % n == 0)
	//{
	//	int x_add[9] = { -1,1,-2,-2, -1,1,2,2 };
	//	int y_add[9] = { -2,-2,-1,1, 2,2,1,-1 };
	//}

	for (int k = 0; k < 8; ++k)
	{
		if (x + x_add[k] >= 0 && x + x_add[k] < n && table[x + x_add[k]][y + y_add[k]]!= 3)
		{
			if (y + y_add[k] >= 0 && y + y_add[k] < n && table[x + x_add[k]][y + y_add[k]] != 3)
			{
				table[x + x_add[k]][y + y_add[k]] = 1;
				int temp = knight_attacked_spots(table, x + x_add[k], y + y_add[k]);

				if (temp < min)
				{
					min = temp;
					x_new = x + x_add[k];
					y_new = y + y_add[k];
				}
			}
		}
	}

	//basic_print(table);

	btn = _getch();

	system("cls");

	knight_tour(table, x_new, y_new);
}
*/

bool improved_knights_tour_auto(int table[50][50], int x, int y, int count) // Knights tour, automatic
{
	bool found = false;

	if (count == n * n - 1)
	{
		system("cls");

		//table[x][y] = 1;

		knight_tour_print(table);

		if (lan)
		{
			std::cout << "\nEvery point has been visited.\n";
		}
		else
		{
			std::cout << "\nMinden pont meglatogatva.\n";
		}

		return true;
	}

	while (!found)
	{
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (table[i][j] == 0)
				{
					found = true;
				}

		if (!found)
		{
			return true;
		}
		else
			break;
	}

	int min = 99;


	int x_add[9] = { -1,1,-2,-2, -1,1,2,2 };
	int y_add[9] = { -2,-2,-1,1, 2,2,-1,1 };


	for (int l = 0; l < 8; ++l)
	{
		if (x + x_add[l] >= 0 && x + x_add[l] < n && table[x + x_add[l]][y + y_add[l]] == 0)
		{
			if (y + y_add[l] >= 0 && y + y_add[l] < n && table[x + x_add[l]][y + y_add[l]] == 0)
			{

				int temp = knight_attacked_spots(table, x + x_add[l], y + y_add[l]);

				if (temp < min)
				{
					min = temp;
				}
			}
		}
	}

	for (int k = 0; k < 8; ++k)
	{
		if (x + x_add[k] >= 0 && x + x_add[k] < n && table[x + x_add[k]][y + y_add[k]] == 0)
		{
			if (y + y_add[k] >= 0 && y + y_add[k] < n && table[x + x_add[k]][y + y_add[k]] == 0)
			{
				if (knight_attacked_spots(table, x + x_add[k], y + y_add[k]) == min)
				{

					count++;

					table[x + x_add[k]][y + y_add[k]] = count + 1;

					if (interval)
					{
						system("cls");

						knight_tour_print(table);

						Sleep(interval);
					}

					if (improved_knights_tour_auto(table, x + x_add[k], y + y_add[k], count))
						return true;

					count--;

					table[x + x_add[k]][y + y_add[k]] = 0;

					if (interval)
					{
						system("cls");

						knight_tour_print(table);

						Sleep(interval);
					}
				}
			}
		}
	}

	return false;

}

bool improved_knights_tour_man(int table[50][50], int x, int y, int count)
{
	bool found = false;

	if (btn == 'a')
	{
		if (lan)
		{
			std::cout << "Program aborted.\n";
		}
		else
		{
			std::cout << "Program megallitva.\n";
		}
		return false;
	}

	if (count == n * n - 1)
	{
		system("cls");

		//table[x][y] = 1;

		knight_tour_print(table);

		if (lan)
		{
			std::cout << "\nEvery point has been visited.\n";
		}
		else
		{
			std::cout << "\nMinden pont meglatogatva.\n";
		}

		return true;
	}

	while (!found)
	{
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				if (table[i][j] == 0)
				{
					found = true;
				}

		if (!found)
		{
			knight_tour_print(table);

			btn = _getch();

			return true;
		}
		else
			break;
	}
	
	int min = 99;


	int x_add[9] = { -1,1,-2,-2, -1,1,2,2 };
	int y_add[9] = { -2,-2,-1,1, 2,2,-1,1 };


	for (int l = 0; l < 8; ++l)
	{
		if (x + x_add[l] >= 0 && x + x_add[l] < n && table[x + x_add[l]][y + y_add[l]] == 0)
		{
			if (y + y_add[l] >= 0 && y + y_add[l] < n && table[x + x_add[l]][y + y_add[l]] == 0)
			{

				int temp = knight_attacked_spots(table, x + x_add[l], y + y_add[l]);

				///std::cout << "Minimum : " << temp << '\n';

				//table[x + x_add[l]][y + y_add[l]] = 1;

				///std::cout << x + x_add[l] << " , " << y + y_add[l] << '\n';

				//basic_print(table);

				//std::cout << temp << '\n';

				if (temp < min)
				{
					min = temp;
					//std::cout << min << '\n';
				}
			}
		}
	}

	//std::cout << min << '\n';
	//btn = _getch();

	for (int k = 0; k < 8; ++k)
	{
		if (x + x_add[k] >= 0 && x + x_add[k] < n && table[x + x_add[k]][y + y_add[k]] == 0)
		{
			if (y + y_add[k] >= 0 && y + y_add[k] < n && table[x + x_add[k]][y + y_add[k]] == 0)
			{
				if (knight_attacked_spots(table, x + x_add[k], y + y_add[k]) == min)
				{
					system("cls");
					//std::cout << min << '\n';

					table[x + x_add[k]][y + y_add[k]] = count+2;


					count++;

					//std::cout << x + x_add[k] << ' ' << y + y_add[k] << '\n';

					knight_tour_print(table);

					char y_char = 'A' + y;
					char new_y_char = 'A' + y + y_add[k];

					if (lan)
					{
						std::cout << "\nThe knight steps from " << y_char << " " << x+1 << " point to " << new_y_char << " " << x + x_add[k] + 1 << " point.\n";
					}
					else
					{
						std::cout << "\nA huszar " << y_char << " " << x+1 << " pontrol lep a(z) " << new_y_char << " " << x + x_add[k] +1 << " pontra.\n";
					}

					btn = _getch();

					if (btn == 'a')
					{
						if (lan)
						{
							std::cout << "Program aborted.\n";
						}
						else
						{
							std::cout << "Program megallitva.\n";
						}
						return false;
					}

					if (improved_knights_tour_man(table, x + x_add[k], y + y_add[k], count))
						return true;

					if (btn == 'a')
					{
						return false;
					}

					system("cls");

					count--;

					table[x+x_add[k]][y+y_add[k]] = 0;

					knight_tour_print(table);

					new_y_char = 'A' + y + y_add[k];

					if (lan)
					{
						std::cout << "\n" << new_y_char << " " << x + x_add[k] + 1 << " removed. Backtracking.\n";
					}
					else
					{
						std::cout << "\n" << new_y_char << " " << x + x_add[k] + 1 << " torolve. Backtrack-el.\n";
					}

					btn = _getch();

					if (btn == 'a')
					{
						if (lan)
						{
							std::cout << "Program aborted.\n";
						}
						else
						{
							std::cout << "Program megallitva.\n";
						}
						return false;
					}
				}
			}
		}
	}

	return false;

}

bool empty_row(int table[50][50],int row)
{
	for (int i = 0; i < n; ++i)
	{
		if (table[row][i] == 1)
		{
			return false;
		}
	}

	return true;
}

bool empty_column(int table[50][50], int col)
{
	for (int i = 0; i < n; ++i)
	{
		if (table[i][col] == 1)
		{
			return false;
		}
	}

	return true;
}

bool rook_domination_man(int table[50][50]) // Chaotic Rook domination, manual
{
	srand(time(NULL));

	int count = 0;

	while (count != n)
	{
		for (int i = 0; i < n; ++i)
		{
			if (empty_row(table, i))
			{
				int temp = rand() % n;

				if (empty_column(table, temp))
				{
					system("cls");
					table[i][temp] = 1;
					count++;
					rook_printer(table);
					std::cout << '\n';
					btn = _getch();

					if (btn == 'a')
					{
						if (lan)
						{
							std::cout << "Program aborted.\n";
						}
						else
						{
							std::cout << "Program megallitva.\n";
						}
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool rook_domination_auto(int table[50][50]) // Chaotic Rook domination, manual
{
	srand(time(NULL));

	int count = 0;

	while (count != n)
	{
		for (int i = 0; i < n; ++i)
		{
			if (empty_row(table, i))
			{
				int temp = rand() % n;

				if (empty_column(table, temp))
				{
					table[i][temp] = 1;
					count++;

					if(interval)
					{
						system("cls");
						rook_printer(table);
						std::cout << '\n';
						Sleep(interval);
					}
				}
			}
		}
	}
	return true;
}

bool bishop_domination_man(int table[50][50]) // Bishop domination, manual
{
	for (int i = 0; i < n; ++i)
	{
		if(n%2==0)
			table[i][n / 2-1] = 1;
		else
			table[i][n / 2] = 1;
		system("cls");
		bishop_printer(table);

		if (lan)
		{
			std::cout << "In every case, the most optimal solution is placing n bishops in the center column.\n";
		}
		else
		{
			std::cout << "Barmilyen esetben, a legoptimalisabb megoldas a kozepso oszlopba n darab futo helyezese.\n";
		}

		btn = _getch();

		if (btn == 'a')
		{
			if (lan)
			{
				std::cout << "Program aborted.\n";
			}
			else
			{
				std::cout << "Program megallitva.\n";
			}
			return false;
		}
	}

	return true;
}

bool bishop_domination_auto(int table[50][50]) // Bishop domination, automatic
{
	for (int i = 0; i < n; ++i)
	{
		if (n % 2 == 0)
			table[i][n / 2 - 1] = 1;
		else
			table[i][n / 2] = 1;
		if (interval)
		{
			system("cls");
			bishop_printer(table);
			Sleep(interval);
		}
	}

	return true;
}

bool knight_domination_man(int table[50][50])
{
	// 1  ( -2 , 1  )
	// 2  ( -1 , 2  )
	// 3  ( 1  , 2  )
	// 4  ( 2  , 1  )
	// 5  ( 2  , -1 )
	// 6  ( 1  , -2 )
	// 7  ( -1 , -2 )
	// 8  ( -2 , -1 )



	return true;
}

void guider()
{

	Guider_Begin:

	auto started = std::chrono::high_resolution_clock::now();
	auto done = std::chrono::high_resolution_clock::now();

	std::ofstream out("data.txt",std::ofstream::app);

	int a_int = 0;

	system("cls");

	if (lan)
	{
		//std::cout << "\n\t Numbers above 10 might take longer!";
		//Sleep(40);
		std::cout << "\n\t Please enter the chess tables dimension (NxN, N<38) : ";
		std::cin >> n;
	}
	else
	{
		//std::cout << "\n\t 10 folotti szamok tobb idot vehetnek igenybe!";
		//Sleep(40);
		std::cout << "\n\t Kerem adja meg a sakk tabla meretet (NxN, N<38) : ";
		std::cin >> n;
	}

	system("cls");

	if ((n < 0) || (n > 38))
	{
		if (lan)
			std::cout << "\n\tInvalid data!";
		else
			std::cout << "\n\tHelytelen adatok!";
		Sleep(1000);
		goto Guider_Begin;
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

		queen_printer(table);

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

		//system("cls");

		//queen_printer(table);

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

	case 3: // Dominating Queen (Greedy)
		started = std::chrono::high_resolution_clock::now();
		if (run_mode)
		{
			dominating_queens_man(table,0);
			out << 1 << ' ';
		}
		else
		{
			//dominating_queens_auto_brute(table,0);
			dominating_queens_auto(table, 0);
			queen_printer(table);
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
	case 4: // Knights tour

		Printing:

		char a;
		int b;

		system("cls");

		knight_tour_print(table);

		if (lan)
		{
			std::cout << "\nPlease give the starting position (For example A 1) : ";
		}
		else
		{
			std::cout << "\nAdja meg a kezdeti poziciot (Pld. A 1) : ";
		}

		std::cin >> a >> b;

		a_int = a - 65;

		if ((a_int < 0 || a_int > n))
		{
			if (lan)
			{
				std::cout << "Incorrect data.\n";
			}
			else
			{
				std::cout << "Helytelen adatok.\n";
			}
			btn = _getch();
			goto Printing;
		}

		if ((b-1 < 0 || b-1 > n))
		{
			if (lan)
			{
				std::cout << "Incorrect data.\n";
			}
			else
			{
				std::cout << "Helytelen adatok.\n";
			}
			btn = _getch();
			goto Printing;
		}

		//std::cout << a_int << '\n';

		table[b-1][a_int] = 1;

		//make_knight_attacked_table(table);

		//basic_print(attacked_table);

		//btn = _getch();

		started = std::chrono::high_resolution_clock::now();
		if (run_mode)
		{

			if (!improved_knights_tour_man(table, b-1, a_int, 0))
			{
				if (lan)
				{
					std::cout << "The board was not fully visited.\n";
				}
				else
				{
					std::cout << "A tablat nem jarta be teljesen.\n";
				}
			}

			done = std::chrono::high_resolution_clock::now();

			out << 1 << ' ';
		}
		else
		{
			
			if (!improved_knights_tour_auto(table, b-1, a_int, 0))
			{
				if (lan)
				{
					std::cout << "The board was not fully visited.\n";
				}
				else
				{
					std::cout << "A tablat nem jarta be teljesen.\n";
				}
			}

			done = std::chrono::high_resolution_clock::now();

			out << 1 << ' ';
		}

		if (lan)
		{
			std::cout << "\nTotal running time : ";
		}
		else
		{
			std::cout << "\nTeljes futasi ido : ";
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";

		out << 4 << ' ' << n << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';

		btn = _getch();

		break;
	case 5:  // Rook domination
		started = std::chrono::high_resolution_clock::now();
		if (run_mode)
		{
			out << 1 << ' ';
			rook_domination_man(table);
			done = std::chrono::high_resolution_clock::now();
		}
		else
		{
			out << 0 << ' ';
			rook_domination_auto(table);
			done = std::chrono::high_resolution_clock::now();
		}
		if (lan)
		{
			std::cout << "\nTotal running time : ";
		}
		else
		{
			std::cout << "\nTeljes futasi ido : ";
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";

		out << 5 << ' ' << n << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';

		btn = _getch();
		break;
	case 6:  // Bishop domination
		started = std::chrono::high_resolution_clock::now();
		if (run_mode)
		{
			out << 1 << ' ';
			bishop_domination_man(table);
			done = std::chrono::high_resolution_clock::now();
		}
		else
		{
			out << 0 << ' ';
			bishop_domination_auto(table);
			done = std::chrono::high_resolution_clock::now();
		}
		if (lan)
		{
			std::cout << "\nTotal running time : ";
		}
		else
		{
			std::cout << "\nTeljes futasi ido : ";
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << " ms\n";

		out << 6 << ' ' << n << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';

		btn = _getch();
		break;
	case 7:
		knight_domination_man(table);
		btn = _getch();
		break;
	default:
		break;
	}

	out.close();
		
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
		std::cout << "\n\t5. Rook dominating";
		Sleep(40);
		std::cout << "\n\t6. Bishop dominating";
		Sleep(40);
		std::cout << "\n\t7. Knight dominating";
		Sleep(40);
		std::cout << " \n\t8. Back to Main Menu";
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
		std::cout << "\n\t5. Bastya lefedes";
		Sleep(40);
		std::cout << "\n\t6. Futar lefedes";
		Sleep(40);
		std::cout << "\n\t7. Huszar lefedes";
		Sleep(40);
		std::cout << " \n\t8. Vissza a Fo Menube";
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
		task = 5;
		break;
	case '6':
		task = 6;
		break;
	case '7':
		task = 7;
		break;
	case '8':
		goto Chess_Menu_End;
		break;
	default :
		goto Chess_Menu;
		break;
	}

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

bool challenge[8] = { false };

bool is_dominated(int table[50][50])
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (table[i][j] == 0)
				return false;
		}
	}
	return true;
}

int goal;
int figure;

int solution_counter_queens(int table[50][50],int goal, int count)
{
	if (count == goal)
	{
		return count;
	}

	count=0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (dominating_safe_queen(table,i,j))
			{
				count++;
				table[i][j] = 1;
				solution_counter_queens(table, goal, count);
				table[i][j] = 0;
			}
		}
	}

	return count;
}

int solution_counter_rook(int table[50][50], int goal, int count)
{

}

void chess_challenges()
{
	Chess_Challenges:

	system("cls");

	srand(time(NULL));

	int temp = rand() % 8;

	figure = 1; // 1 = Queen, 2 = Rook, 3 = Bishop, 4 = Knight
	goal = 0; // The max amount allowed to be placed
	int count = 0;

	int table[50][50];

	cursor_x = 0;
	cursor_y = 0;

	if (!challenge[temp])
	{
		switch (temp)
		{
		case 0:
			n = 8;
			figure = 1;
			goal = 5;
			break;
		case 1:
			n = 5;
			figure = 4;
			goal = 5;
			break;
		case 2:
			n = 8;
			figure = 3;
			goal = 12;
			break;
		case 3:
			n = 4;
			figure = 4;
			goal = 4;
			break;
		case 4:
			n = 6;
			figure = 1;
			goal=3;
			break;
		case 5:
			n = 8;
			figure = 3;
			goal = 8;
			break;
		case 6:
			n = 8;
			figure = 2;
			goal = 8;
			break;
		case 7:
			n = 8;
			figure = 4;
			goal = 12;
			break;
		}
	}

	if (!goal)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (!challenge[i])
				goto Chess_Challenges;
		}
		if (lan)
		{
			std::cout << "\n\tSuccessfully completed all challenges! Congratulation!\n";
			Sleep(40);
			std::cout << "\tPress any button to return back.\n";
		}
		else
		{
			std::cout << "\n\tSikeresen megoldotta az osszes kihivast! Gratulalok!\n";
			Sleep(40);
			std::cout << "\tNyomjon meg barmilyen gombot a visszalepeshez.\n";
		}
		btn = _getch();
		return;
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			table[i][j] = 0;
		}
	}

Reprint:

	if (count > goal)
	{
		table[cursor_x][cursor_y] = 0;
	}

	if (figure == 1)
	{

		//int solutions = solution_counter_queens(table, goal, 0);

		queen_printer(table);
		if (lan)
		{
			std::cout << "\nDominate the table with " << goal << " queens!\n";
		}
		else
		{
			std::cout << "\nFedd le a tablat " << goal << " darab kiralynovel!\n";
		}

		//std::cout << "\nSolutions left : " << solutions << "\n";

		make_attacked_table(table);
		
		if(count==goal)
		if (is_dominated(attacked_table))
		{
			challenge[temp] = true;
			if (lan)
			{
				std::cout << "\nSuccessfully dominated!\n";
			}
			else
			{
				std::cout << "\nSikeresen lefedve!\n";
			}
			count = 0;
			goal = 0;
			btn = _getch();

			return;

		}

	}
	if (figure == 2)
	{
		//int solutions = solution_counter_rook(table, goal, 0);

		rook_printer(table);
		if (lan)
		{
			std::cout << "\nDominate the table with " << goal << " rooks!\n";
		}
		else
		{
			std::cout << "\nFedd le a tablat " << goal << " darab bastyaval!\n";
		}

		//std::cout << "\nSolutions left : " << solutions << "\n";

		make_rook_attacked_table(table);

		if (count == goal)
		if (is_dominated(attacked_table))
		{
			challenge[temp] = true;
			if (lan)
			{
				std::cout << "\nSuccessfully dominated!\n";
			}
			else
			{
				std::cout << "\nSikeresen lefedve!\n";
			}

			btn = _getch();

			return;

		}
	}
	if (figure == 3)
	{
		bishop_printer(table);
		if (lan)
		{
			std::cout << "\nDominate the table with " << goal << " bishops!\n";
		}
		else
		{
			std::cout << "\nFedd le a tablat " << goal << " darab futarral!\n";
		}

		make_bishop_attacked_table(table);

		if (count == goal)
		if (is_dominated(attacked_table))
		{
			challenge[temp] = true;
			if (lan)
			{
				std::cout << "\nSuccessfully dominated!\n";
			}
			else
			{
				std::cout << "\nSikeresen lefedve!\n";
			}

			btn = _getch();

			return;

		}
	}
	if (figure == 4)
	{
		knight_printer(table);


		if (lan)
		{
			std::cout << "\nDominate the table with " << goal << " knights!\n";
		}
		else
		{
			std::cout << "\nFedd le a tablat " << goal << " darab huszarral!\n";
		}

		make_knight_attacked_table(table);

		if (count == goal)
		if (is_dominated(attacked_table))
		{
			challenge[temp] = true;
			if (lan)
			{
				std::cout << "\nSuccessfully dominated!\n";
			}
			else
			{
				std::cout << "\nSikeresen lefedve!\n";
			}

			btn = _getch();

			return;

		}
	}

	if (count > goal)
	{
		count--;
		if (lan)
		{
			std::cout << "\nCannot place more pieces!\n";
		}
		else
		{
			std::cout << "\nNem helyezhet el tobb babut!\n";
		}
	}
	
	btn = _getch();

	if (btn == ' ')
	{
		if (!table[cursor_x][cursor_y])
		{
			count++;
			table[cursor_x][cursor_y] = 1;
		}
		else
		{
			count--;
			table[cursor_x][cursor_y] = 0;
		}
		system("cls");
		goto Reprint;
	}

	if (btn == 'w')
	{
		if (cursor_x - 1 == -1)
		{
			cursor_x = n - 1;
		}
		else
			cursor_x = cursor_x - 1;
		system("cls");
		goto Reprint;
	}
	else
		if (btn == 'a')
		{
			if (cursor_y - 1 == -1)
			{
				cursor_y = n - 1;
			}
			else
				cursor_y = cursor_y - 1;
			system("cls");
			goto Reprint;
		}
		else
			if (btn == 's')
			{
				cursor_x = cursor_x + 1;
				if (cursor_x + 1 > n)
				{
					cursor_x = 0;
				}
				system("cls");
				goto Reprint;
			}
			else
				if (btn == 'd')
				{
					cursor_y = cursor_y + 1;
					if (cursor_y + 1 > n)
					{
						cursor_y = 0;
					}
					system("cls");
					goto Reprint;
				}
				else
					if (btn == 'q')
					{
						cursor_x = -1;
						cursor_y = -1;
						count = 0;
						goal = 0;
						system("cls");
						return;
					}
					else
					{
						system("cls");
						goto Reprint;
					}
}

bool first_time = false;

void challenge_menu()
{
	system("cls");

	if (!first_time)
	{

		first_time = true;

		if (lan)
		{
			std::cout << "\n\t\t Chess Challenges\n";
			Sleep(40);
			std::cout << "\n\tTry to solve the given prompts, by moving the cursor with the WASD keys,\n\tand placing/removing pieces from the board with the Space bar!\n";
			Sleep(40);
			std::cout << "\n\tYou can quit any time by pressing the letter Q.\n";
			Sleep(40);
			std::cout << "\tGood luck! Press any button to proceed or Q to quit.\n";
		}
		else
		{
			std::cout << "\n\t\t Sakkos kihivasok\n";
			Sleep(40);
			std::cout << "\n\tProbald megoldani az adott feladatokat, a kurzort a WASD gombok segitsegevel mozgatva,\n\telhelyezve illetve leveve babukat a tablara Space gomb lenyomasaval!\n";
			Sleep(40);
			std::cout << "\n\tBarmikor kilephet a Q gomb segitsegevel.\n";
			Sleep(40);
			std::cout << "\tSok szerencset! Nyomjon meg barmilyen gombot a tovabblepeshez vagy Q-t a kilepeshez.\n";
		}

		btn = _getch();

		if (btn == 'q')
		{
			system("cls");
		}
		else
		{
			chess_challenges();
		}
	}
	else
	{
		chess_challenges();
	}
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
		std::cout << "\t2. Chess Challenges\n";
		Sleep(40);
		std::cout << "\t3. Settings\n";
		Sleep(40);
		std::cout << "\t4. Notes\n";
		Sleep(40);
		std::cout << "\t5. Recorded Times\n";
		Sleep(40);
		std::cout << "\t6. Exit\n";
	}
	else
	{
		std::cout << "\n\t\tFo Menu\n\n";
		Sleep(40);
		std::cout << "\t1. Sakk Problemak\n";
		Sleep(40);
		std::cout << "\t2. Sakk Kihivas\n";
		Sleep(40);
		std::cout << "\t3. Beallitasok\n";
		Sleep(40);
		std::cout << "\t4. Jegyzetek\n";
		Sleep(40);
		std::cout << "\t5. Mentett Idok\n";
		Sleep(40);
		std::cout << "\t6. Kilepes\n";
	}

	btn = _getch();

	switch (btn)
	{
	case '1':
		chess_menu();
		break;
	case '2':
		challenge_menu();
		break;
	case '3':
		settings_menu();
		break;
	case '4':
		notes_menu();
		break;
	case '5':
		record_menu();
		break;
	case '6':

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
