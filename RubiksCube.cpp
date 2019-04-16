#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <fstream>
#include "Cube.h"
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std::chrono;

//colored numbers
constexpr auto RED2 = "\033[31m";
constexpr auto GREEN2 = "\033[32m";
constexpr auto YELLOW2 = "\033[33m";
constexpr auto BLUE2 = "\033[34m";
constexpr auto WHITE2 = "\033[37m";
constexpr auto ORANGE2 = "\033[91m";




//only colors
constexpr auto RESET = "\033[0m";
constexpr auto RED = "\033[41m";
constexpr auto GREEN = "\033[42m";
constexpr auto YELLOW = "\033[43m";
constexpr auto BLUE = "\033[44m";
constexpr auto WHITE = "\033[47m";
constexpr auto ORANGE = "\033[101m";

/*
#define RESET "\033[0m"
#define RED "\033[31m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define ORANGE = "\033[91m";
*/


int num_solves = 100000;
bool cfop_delay = true;
bool turn_delay = false;
bool print_cube = true;
bool show_moves = true;
bool show_colors = true;



int main(int argc, char** argv)
{
	if (argc > 6)
	{
		std::cout << "Incorrect syntax: Usage = ./RubiksCube.exe [--debug] (--debug is optional)\n";
		return -1;
	}
	if (argc == 5 && strcmp(argv[5], "--debug") != 0)
	{
		std::cout << "Incorrect syntax: Usage = ./RubiksCube.exe [--debug] (--debug is optional)\n";
		return -1;
	}
	//to run from VS uncomment the multi-line comment around the if
	bool debug = true;
	///*
	if (argc == 5 && strcmp(argv[4], "--debug") != 0)
		debug = false;
	else if (argc == 1)
		debug = false;
	//*/
	int cube[6][3][3];
	std::pair<std::string, int> p;
	int count = 0, choice = 0;
	std::ifstream is;
	std::ofstream os;
	std::string reverse_scramble = "";
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			for (int k = 0; k <= 2; k++)
			{
				cube[i][j][k] = count;
				count++;
			}
		}
	}
	if (debug)
	{
		int result;
		result = debug_selector(num_solves, cfop_delay, turn_delay, print_cube, show_moves);
		if (result != -1 && result != 0)
			solver_debug(cube);
		else
			std::cout << "IDK you did something wrong " << std::endl;
	}
	else
	{
		do
		{
			choice = menu(choice);
			int turns;
			if (choice == 1)
			{
				std::cout << "How many turns in the scramble?: ";
				std::cin >> turns;
				reverse_scramble = random_scramble(cube, turns, os);
				print(cube);
			}
			else if (choice == 2)
			{
				//play game yourself
				print(cube);
				auto start = high_resolution_clock::now();
				play(cube);
				auto end = high_resolution_clock::now();
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			//load custom scramble
			else if (choice == 3)
			{
				auto start = high_resolution_clock::now();
				load_scramble(cube, is);
				print(cube);
				if (is_solved(cube))
				{
					auto end = high_resolution_clock::now();
					std::cout << "The Cube has been Solved" << std::endl;
					if (duration_cast<milliseconds>(end - start).count() < 1.0)
						std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
					else if (duration_cast<seconds>(end - start).count() < 1)
						std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
					else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
						std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
					else if (duration_cast<seconds>(end - start).count() >= 60)
						std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
				}
			}
			//load custom solution
			else if (choice == 4)
			{
				load_scramble(cube, is);
				print(cube);
			}
			//ai solver
			else if (choice == 5)
			{
				solver(cube);
			}
			else if (choice == 6)
			{
				auto start = high_resolution_clock::now();
				cheeky_ai(cube, reverse_scramble, os, is);
				if (is_solved(cube))
				{
					auto end = high_resolution_clock::now();
					if (duration_cast<milliseconds>(end - start).count() < 1.0)
						std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
					else if (duration_cast<seconds>(end - start).count() < 1)
						std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
					else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
						std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
					else if (duration_cast<seconds>(end - start).count() >= 60)
						std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
				}
			}
            else if (choice == 7)
            {
                int result;
                result = debug_selector(num_solves, cfop_delay, turn_delay, print_cube, show_moves);
                if (result != -1 && result != 0)
                    solver_debug(cube);
                else
                    std::cout << "IDK you did something wrong " << std::endl;
            }
			else if (choice == 8)
			{
				std::cout << "Goodbye" << std::endl;
				return 0;
			}
		} while (choice != 8);
	}
}

int debug_selector(int& num, bool& a, bool& b, bool& c, bool& d)
{
	int g;
	std::cout << "----------------------------------------------------";
	std::cout << "Debugging" << std::endl;
	std::cout << "How many solves?: ";
	std::cin >> g;
	num = g;
	std::cout << "1. CFOP DELAY: cfop_delay = true, turn_delay = false, print_cube = true, show_moves = true\n";
	std::cout << "2. TURN DELAY: cfop_delay = false, turn_delay = true, print_cube = true, show_moves = true\n";
	std::cout << "3. NO DELAY: cfop_delay = false, turn_delay = false, print_cube = false, show_moves = false\n";
	std::cout << "4. Quit\n";
	std::cin >> g;
	if (g == 1) { a = true; b = false; c = true; d = true; return 1; }
	else if (g == 2) { a = false; b = true; c = true; d = true; return 1; }
	else if (g == 3) { a = false; b = false; c = false; d = false; return 1; }
	else if (g == 4) { return -1; }
	return 0;
}

void cube_with_pair(int cube[6][3][3])
{
	//good idea but don't know if this is any better/worse
	std::pair<std::string, std::pair<int, int>> cube2[6][3][3];
	for (int a = 0; a < 6; a++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::pair<std::string, std::pair<int, int>> temp;
				if(a == 0) temp.first = "yellow";
				else if (a == 1) temp.first = "blue";
				else if (a == 2) temp.first = "red";
				else if (a == 3) temp.first = "green";
				else if (a == 4) temp.first = "orange";
				else if (a == 5) temp.first = "white";
				temp.second.first = i;
				temp.second.second = j;
				cube2[a][i][j] = temp;
			}
		}
	}
}

void cheeky_ai(int cube[6][3][3], std::string r_scramble, std::ofstream& os, std::ifstream& is)
{
	std::string temp = "";
	std::istringstream iss(r_scramble);
	while (iss >> temp)
	{
		turn_cube(cube, temp, true);
	}
}

std::string check_color(int cube[6][3][3], int x, int y, int z)
{
	if (cube[x][y][z] >= 0 && cube[x][y][z] <= 8) return "yellow";
	else if (cube[x][y][z] >= 9 && cube[x][y][z] <= 17) return "blue";
	else if (cube[x][y][z] >= 18 && cube[x][y][z] <= 26) return "red";
	else if (cube[x][y][z] >= 27 && cube[x][y][z] <= 35) return "green";
	else if (cube[x][y][z] >= 36 && cube[x][y][z] <= 44) return "orange";
	else if (cube[x][y][z] >= 45 && cube[x][y][z] <= 53) return "white";
	return " ";
}

std::string check_color(int * ptr)
{
	if (*ptr >= 0 && *ptr <= 8) return "yellow";
	else if (*ptr >= 9 && *ptr <= 17) return "blue";
	else if (*ptr >= 18 && *ptr <= 26) return "red";
	else if (*ptr >= 27 && *ptr <= 35) return "green";
	else if (*ptr >= 36 && *ptr <= 44) return "orange";
	else if (*ptr >= 45 && *ptr <= 53) return "white";
	return " ";
}

static bool top_layer_right(int cube[6][3][3])
{
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][1]) && check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) &&
		check_color(&cube[2][0][0]) == check_color(&cube[2][0][1]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) &&
		check_color(&cube[3][0][0]) == check_color(&cube[3][0][1]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][1]) && check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
		return true;
	return false;
}

static void auf(int cube[6][3][3])
{
	for (int i = 0; i < 4; i++)
	{
		if (is_solved(cube)) return;
		turn_cube(cube, "U", true);
	}
}

void solver_debug(int cube[6][3][3])
{
	//cross
	//need to implement while loop to keep running function till the cross is made
	//implement a thing that writes the moves the ai does to solve the cube to a file with sstream (ofstream)
	int numRight = 0, numWrong = 0;
	int literallyWhat = 0;
	std::ofstream oss;
	std::ofstream os;
	os.open("Stats.txt");
	if (!os.is_open())
	{
		std::cout << "Failed to open the file \n";
		return;
	}
	auto start2 = high_resolution_clock::now();
	for (int e = 0; e < num_solves; e++)
	{
        //put the ofstream inside the scramble function cuz don't need to pass from debug
		random_scramble(cube, 25, oss);
		auto start = high_resolution_clock::now();
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		do {
			cross(cube);
		} while (!(check_color(cube, 5, 0, 1) == "white" && check_color(cube, 5, 1, 0) == "white" && check_color(cube, 5, 1, 2) == "white" && check_color(cube, 5, 2, 1) == "white"));
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		if (cfop_delay)
			delay();
		corners(cube);
		//it's bound to happen in 1 million runs
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		if (cfop_delay)
			delay();
		do { second_layer(cube); } while (!second_layer_correct(cube));
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		if (cfop_delay)
			delay();
		top_cross(cube);
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		if (cfop_delay)
			delay();
		do { oll(cube); } while (!top_correct(cube));
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		else if (!is_solved(cube) && !top_layer_right(cube))
		{
			if (cfop_delay)
				delay();
			//pll skip
			if ((top_layer_right(cube) && !is_solved(cube)) || is_solved(cube))
			{
				auf(cube);
				if (is_solved(cube)) {
					auto end = high_resolution_clock::now();
					std::cout << "The Cube has been Solved" << std::endl;
					if (turn_delay || cfop_delay)
					{
						if (duration_cast<milliseconds>(end - start).count() < 1.0)
							std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
						else if (duration_cast<seconds>(end - start).count() < 1)
							std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
						else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
							std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
						else if (duration_cast<seconds>(end - start).count() >= 60)
							std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
					}
					++numRight;
					if (cfop_delay)
						delay();
					continue;
				}
				else
				{
					std::cout << "Literally no idea... this option should never output" << std::endl;
					literallyWhat++;
					if (cfop_delay)
						delay();
					continue;
				}
			}
			//split into two parts
			//part one get headlights on f l && r faces && full bar on the b face
			//part two doing the U alg either once || twice as needed
			//also need to account for if there is an H perm situation
			pll(cube);
		}
		if (top_layer_right(cube) && !is_solved(cube)) auf(cube);
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numRight;
			if (cfop_delay)
				delay();
			continue;
		}
		else
		{
			auto end = high_resolution_clock::now();
			std::cout << "Not solved && idk what to do to solve it" << std::endl;
			if (turn_delay || cfop_delay)
			{
				if (duration_cast<milliseconds>(end - start).count() < 1.0)
					std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() < 1)
					std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
					std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
				else if (duration_cast<seconds>(end - start).count() >= 60)
					std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			}
			++numWrong;
			if (cfop_delay)
				delay();
		}
	}
	auto end2 = high_resolution_clock::now();
	os << "Total number of solves: " << num_solves << ", # correct solves: " << numRight << std::endl; 
	os << "# of incorrect solves: " << numWrong << " " << std::endl;
	os << numRight << " / " << numWrong << " = " << (double)numRight / (double)numWrong << "%" << std::endl;
	std::cout << "\n";
	std::cout << "Testing complete: " << num_solves << " solves" << std::endl;
	if (literallyWhat > 0)
	{
		std::cout << "--------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Number of errors that defy the laws of physics && Rubik's Cubes: " << literallyWhat << "\n";
		std::cout << "--------------------------------------------------------------------------------------" << std::endl;
	}
	std::cout << "Number of correct solves: " << numRight << std::endl;
	std::cout << "Number of incorrect solves: " << numWrong << std::endl;
	if (numRight == num_solves)
		std::cout << "Percent correct = " << numRight << " / " << num_solves << " = " << "100%" << std::endl;
	else
		std::cout << "Percent corect = " << numRight << " / " << num_solves << " = " << (double)numRight / (double)num_solves << "%\n";
	if (duration_cast<milliseconds>(end2 - start2).count() < 1)
		std::cout << "Total runtime = " << duration_cast<microseconds>(end2 - start2).count() << " microseconds" << std::endl;
	else if (duration_cast<seconds>(end2 - start2).count() < 1)
		std::cout << "Total runtime = " << duration_cast<milliseconds>(end2 - start2).count() << " milliseconds" << std::endl;
	else if(duration_cast<minutes>(end2-start2).count() < 1)
		std::cout << "Total runtime = " << duration_cast<seconds>(end2 - start2).count() << " seconds" << std::endl;
	else if (duration_cast<minutes>(end2 - start2).count() >= 1 && duration_cast<minutes>(end2-start2).count() <= 60)
		std::cout << "Total runtime = " << duration_cast<minutes>(end2 - start2).count() << " minutes && " << (duration_cast<seconds>(end2-start2).count() - (duration_cast<minutes>(end2 - start2).count() * 60)) << " seconds" << std::endl;
	else if (duration_cast<minutes>(end2 - start2).count() > 60)
		std::cout << "Total runtime = " << duration_cast<hours>(end2 - start2).count() << " hours" << " && " << (duration_cast<minutes>(end2-start2).count() - (duration_cast<hours>(end2 - start2).count() * 60)) << " minutes" << std::endl;
}

void solver(int cube[6][3][3])
{
	//cross
	//need to implement while loop to keep running function till the cross is made
	//implement a thing that writes the moves the ai does to solve the cube to a file with sstream (ofstream)
	int numRight = 0, numWrong = 0;
	int literallyWhat = 0;
	std::ofstream os;
	random_scramble(cube, 25, os);
	auto start = high_resolution_clock::now();
	do {
		cross(cube);
	} while (!(check_color(cube, 5, 0, 1) == "white" && check_color(cube, 5, 1, 0) == "white" && check_color(cube, 5, 1, 2) == "white" && check_color(cube, 5, 2, 1) == "white"));
	if(cfop_delay)
		delay();
	corners(cube);
	if(cfop_delay)
		delay();
	do { second_layer(cube); } while (!second_layer_correct(cube));
	if (is_solved(cube)) {
		auto end = high_resolution_clock::now();
		std::cout << "The Cube has been Solved" << std::endl;
		std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds" << std::endl;
		++numRight;
		if (cfop_delay)
			delay();
		return;
	}
	if(cfop_delay)
		delay();
	top_cross(cube);
	if (is_solved(cube)) {
		auto end = high_resolution_clock::now();
		std::cout << "The Cube has been Solved" << std::endl;
		std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds" << std::endl;
		++numRight;
		if (cfop_delay)
			delay();
		return;
	}
	if (cfop_delay)
	delay();
	do { oll(cube); } while (!top_correct(cube));
	if (is_solved(cube)) {
		auto end = high_resolution_clock::now();
		std::cout << "The Cube has been Solved" << std::endl;
		std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds" << std::endl;
		++numRight;
		if (cfop_delay)
			delay();
		return;
	}
	if (cfop_delay)
		delay();
	//check pll skip
	if (!is_solved(cube) && !top_layer_right(cube))
	{
		if ((top_layer_right(cube) && !is_solved(cube)) || is_solved(cube))
		{
			auf(cube);
			if (is_solved(cube)) {
				auto end = high_resolution_clock::now();
				std::cout << "The Cube has been Solved" << std::endl;
				std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds" << std::endl;
				++numRight;
				if (cfop_delay)
					delay();
				return;
			}
			else
			{
				std::cout << "Literally no idea... this option should never output" << std::endl;
				literallyWhat++;
				if (cfop_delay)
					delay();
				return;
			}
		}
		//split into two parts
		//part one get headlights on f l && r faces && full bar on the b face
		//part two doing the U alg either once || twice as needed
		//also need to account for if there is an H perm situation
		pll(cube);
		if (top_layer_right(cube) && !is_solved(cube)) auf(cube);
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			std::cout << "The Cube has been Solved" << std::endl;
			if (duration_cast<milliseconds>(end - start).count() < 1.0)
				std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
			else if (duration_cast<seconds>(end - start).count() < 1)
				std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
			else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
				std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
			else if (duration_cast<seconds>(end - start).count() >= 60)
				std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			++numRight;
			if (cfop_delay)
				delay();
		}
		else
		{
			auto end = high_resolution_clock::now();
			std::cout << "Not solved && idk what to do to solve it" << std::endl;
			if (duration_cast<milliseconds>(end - start).count() < 1.0)
				std::cout << "Elapsed time = " << duration_cast<microseconds>(end - start).count() << " microseconds" << std::endl;
			else if (duration_cast<seconds>(end - start).count() < 1)
				std::cout << "Elapsed time = " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << std::endl;
			else if (duration_cast<seconds>(end - start).count() >= 1 && duration_cast<seconds>(end - start).count() < 60)
				std::cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << std::endl;
			else if (duration_cast<seconds>(end - start).count() >= 60)
				std::cout << "Elapsed time = " << duration_cast<minutes>(end - start).count() << " minutes (" << duration_cast<seconds>(end - start).count() << " seconds)" << std::endl;
			++numWrong;
			if (cfop_delay)
				delay();
		}
	}
}

bool top_correct(int cube[6][3][3])
{
	if (check_color(&cube[0][0][0]) == check_color(&cube[0][0][1]) && check_color(&cube[0][0][0]) == check_color(&cube[0][0][2]) &&
		check_color(&cube[0][1][0]) == check_color(&cube[0][0][0]) && check_color(&cube[0][1][2]) == check_color(&cube[0][0][0]) &&
		check_color(&cube[0][0][0]) == check_color(&cube[0][2][0]) && check_color(&cube[0][0][0]) == check_color(&cube[0][2][2]) && check_color(&cube[0][0][0]) == "yellow")
		return true;
	return false;
}

void oll(int cube[6][3][3])
{
	//23 HEADLIGHTS
	if (check_color(&cube[0][0][0]) == "yellow" && check_color(&cube[0][0][1]) == "yellow" && check_color(&cube[0][0][2]) == "yellow" &&
		check_color(&cube[0][1][0]) == "yellow" && check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][1][2]) == "yellow" &&
		check_color(&cube[0][2][1]) == "yellow" && check_color(&cube[0][2][0]) != "yellow" && check_color(&cube[0][2][2]) != "yellow" &&
		check_color(&cube[2][0][0]) == "yellow" && check_color(&cube[2][0][2]) == "yellow")
	{
		//R R d rp u u r dp rp u u rp
		turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "D", true); turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Dp", true); turn_cube(cube, "Rp", true);
		turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true);
	}
	//T oll
	else if (check_color(&cube[0][2][0]) != "yellow" && check_color(&cube[0][0][0]) != "yellow" && check_color(&cube[0][0][2]) == "yellow" &&
		check_color(&cube[0][2][2]) == "yellow" && check_color(&cube[2][0][0]) == "yellow" && check_color(&cube[4][0][2]) == "yellow")
	{
		//l f rp fp lp f r fp
		turn_cube(cube, "L", true); turn_cube(cube, "F", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true); turn_cube(cube, "Lp", true); turn_cube(cube, "F", true);
		turn_cube(cube, "R", true); turn_cube(cube, "Fp", true);
	}
	//BOWTIE
	else if (check_color(&cube[0][2][0]) == "yellow" && check_color(&cube[0][0][2]) == "yellow" && check_color(&cube[0][0][0]) != "yellow" &&
		check_color(&cube[0][2][2]) != "yellow" && check_color(&cube[2][0][2]) == "yellow" && check_color(&cube[1][0][0]) == "yellow")
	{
		//Fp l f rp fp lp f r
		turn_cube(cube, "Fp", true); turn_cube(cube, "L", true); turn_cube(cube, "F", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true); turn_cube(cube, "Lp", true);
		turn_cube(cube, "F", true); turn_cube(cube, "R", true);
	}
	//pi
	else if (check_color(&cube[2][0][2]) == "yellow" && check_color(&cube[4][0][0]) == "yellow" && check_color(&cube[1][0][0]) == "yellow" &&
		check_color(&cube[1][0][2]) == "yellow")
	{
		//R u u r r up r r up r r u u r
		turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true);
	}
	//H
	else if (check_color(&cube[2][0][0]) == "yellow" && check_color(&cube[2][0][2]) == "yellow" && check_color(&cube[4][0][0]) == "yellow" &&
		check_color(&cube[4][0][2]) == "yellow")
	{
		//f r u rp up r u rp up r u rp up fp
		turn_cube(cube, "F", true);
		for (int i = 0; i < 3; i++)
		{
			turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true);
		}
		turn_cube(cube, "Fp", true);
	}
	//sune
	else if (check_color(&cube[0][2][0]) == "yellow" && check_color(&cube[2][0][2]) == "yellow" && check_color(&cube[3][0][2]) == "yellow" &&
		check_color(&cube[4][0][2]) == "yellow")
	{
		//r u rp u r u u rp
		turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true);
	}
	//anti sune
	else if (check_color(&cube[0][2][2]) == "yellow" && check_color(&cube[2][0][0]) == "yellow" && check_color(&cube[1][0][0]) == "yellow" &&
		check_color(&cube[4][0][0]) == "yellow")
	{
		//lp up l up lp u u l
		turn_cube(cube, "Lp", true); turn_cube(cube, "Up", true); turn_cube(cube, "L", true); turn_cube(cube, "Up", true); turn_cube(cube, "Lp", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "L", true);
	}
	else
		turn_cube(cube, "U", true);
}

static bool has_bar(int cube[6][3][3])
{
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][1]) && check_color(&cube[1][0][0]) == check_color(&cube[1][0][2])) return true;
	else if (check_color(&cube[2][0][0]) == check_color(&cube[2][0][1]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2])) return true;
	else if (check_color(&cube[3][0][0]) == check_color(&cube[3][0][1]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2])) return true;
	else if (check_color(&cube[4][0][0]) == check_color(&cube[4][0][1]) && check_color(&cube[4][0][0]) == check_color(&cube[4][0][2])) return true;
	else return false;
}

static void Ua_perm(int cube[6][3][3])
{
	turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
	turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
}

static void Ub_perm(int cube[6][3][3])
{
	turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true);
	turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true);
}

static void M(int cube[6][3][3])
{
	int temp[3] = { cube[0][2][1], cube[0][1][1], cube[0][0][1] };
	int temp2[3] = { cube[2][0][1], cube[2][1][1], cube[2][2][1] };
	int temp3[3] = { cube[5][0][1], cube[5][1][1], cube[5][2][1] };
	int temp4[3] = { cube[4][2][1], cube[4][1][1], cube[4][0][1] };
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		cube[4][i][1] = temp[count];
		cube[0][i][1] = temp2[count];
		cube[2][i][1] = temp3[count];
		cube[5][i][1] = temp4[count];
		count++;
	}
}

static void Mp(int cube[6][3][3])
{
	M(cube); M(cube); M(cube);
}

static void M2(int cube[6][3][3])
{
	M(cube); M(cube);
}

static void H_perm(int cube[6][3][3])
{
	//m2 u m2 u2 m2 u m2
	turn_cube(cube, "M2", true); turn_cube(cube, "U", true); turn_cube(cube, "M2", true);
	turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "M2", true);
	turn_cube(cube, "U", true); turn_cube(cube, "M2", true);
}

static void Z_perm(int cube[6][3][3])
{
	//m2 u m2 u mp u2 m2 u2 mp u2
	turn_cube(cube, "M2", true); turn_cube(cube, "U", true); turn_cube(cube, "M2", true);
	turn_cube(cube, "U", true); turn_cube(cube, "Mp", true); turn_cube(cube, "U", true);
	turn_cube(cube, "U", true); turn_cube(cube, "M2", true); turn_cube(cube, "U", true);
	turn_cube(cube, "U", true); turn_cube(cube, "Mp", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true);
}

static void T_perm(int cube[6][3][3])
{
	turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true);
	turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true);
}

void pll(int cube[6][3][3])
{
	if (is_solved(cube))
		return;
	else if (!is_solved(cube))
	{
		for (int g = 0; g < 3; g++)
		{
			if (is_solved(cube))
			{
				return;
			}
			if (has_bar(cube) && check_color(&cube[2][0][0]) != check_color(&cube[2][0][1]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) && check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[3][0][0]) != check_color(&cube[3][0][1]) && check_color(&cube[4][0][0]) == check_color(&cube[4][0][1])
				&& check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
			{
				if (check_color(&cube[3][0][1]) == check_color(&cube[1][0][0]) && check_color(&cube[1][0][1]) ==
					check_color(&cube[2][0][0]))
				{
					if (cfop_delay)
						delay();
					Ua_perm(cube);
				}
				else
				{
					if (cfop_delay)
						delay();
					Ub_perm(cube);
				}
				return;
			}
			turn_cube(cube, "U", true);
		}
	}
	//need to account for if alredy solved && ohly need u perm || ua perm
	//if top is h perm.  do u perm u u perm up && auf
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) && check_color(&cube[2][0][1]) == check_color(&cube[4][0][0]) && check_color(&cube[4][0][1]) == check_color(&cube[2][0][0]) && !has_bar(cube))
	{
		H_perm(cube);
	}
	else if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) && check_color(&cube[2][0][1]) != check_color(&cube[4][0][0]) && check_color(&cube[4][0][1]) != check_color(&cube[2][0][0]) && !has_bar(cube))
	{
		Z_perm(cube);
		if (!is_solved(cube) && !top_layer_right(cube))
		{
			H_perm(cube);
		}
		if (!is_solved(cube) && top_layer_right(cube))
		{
			auf(cube);
			if (is_solved(cube)) return;
		}
	}
	//if top is z perm.  green || blue needs to be on [0][1] position on red face
	//then u perm.  turn so block is on orange side uperm .  if not solved another u perm && auf.


	//if no headlights just do t perm from any orientation
	if (check_color(&cube[2][0][0]) != check_color(&cube[2][0][2]) &&
		check_color(&cube[3][0][0]) != check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) != check_color(&cube[4][0][2]) &&
		check_color(&cube[1][0][0]) != check_color(&cube[1][0][2]))
	{
		T_perm(cube);
	}
	//check if solved, if needs u perm, if needs h || z perm after initial t perm
	if (is_solved(cube))
		return;
	for (int g = 0; g < 3; g++)
	{
		if (is_solved(cube))
		{
			return;
		}
		if (has_bar(cube) && check_color(&cube[2][0][0]) != check_color(&cube[2][0][1]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) && check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[3][0][0]) != check_color(&cube[3][0][1]) && check_color(&cube[4][0][0]) == check_color(&cube[4][0][1])
			&& check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
		{
			if (check_color(&cube[3][0][1]) == check_color(&cube[1][0][0]) && check_color(&cube[1][0][1]) ==
				check_color(&cube[2][0][0]))
			{
				if (cfop_delay)
					delay();
				Ua_perm(cube);
			}
			else
			{
				if (cfop_delay)
					delay();
				Ub_perm(cube);
			}
			return;
		}
		turn_cube(cube, "U", true);
	}
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) && check_color(&cube[2][0][1]) == check_color(&cube[4][0][0]) && check_color(&cube[4][0][1]) == check_color(&cube[2][0][0]) && !has_bar(cube))
	{
		H_perm(cube);
	}
	else if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) && check_color(&cube[2][0][1]) != check_color(&cube[4][0][0]) && check_color(&cube[4][0][1]) != check_color(&cube[2][0][0]) && !has_bar(cube))
	{
		Z_perm(cube);
		if (!is_solved(cube) && !top_layer_right(cube))
		{
			H_perm(cube);
		}
		if (!is_solved(cube) && top_layer_right(cube))
		{
			auf(cube);
			if (is_solved(cube)) return;
		}
	}
	//if top is z perm.  green || blue needs to be on [0][1] position on red face
	//then u perm.  turn so block is on orange side uperm .  if not solved another u perm && auf.
	if (check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]))
	{
		turn_cube(cube, "U", true);
	}
	else if (check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]))
	{
		turn_cube(cube, "U", true); turn_cube(cube, "U", true);
	}
	else if (check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
	{
		turn_cube(cube, "Up", true);
	}
	//r u rp up rp f r r up rp up r u rp fp
	T_perm(cube);
	if (cfop_delay)
		delay();
	if (is_solved(cube))
	{
		return;
	}
	else if (!is_solved(cube) && top_layer_right(cube))
	{
		auf(cube); if (is_solved(cube)) return;
	}
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) && check_color(&cube[2][0][1]) == check_color(&cube[4][0][0]) && check_color(&cube[4][0][1]) == check_color(&cube[2][0][0]) && !has_bar(cube))
	{
		H_perm(cube);
	}
	else if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) &&
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) && check_color(&cube[2][0][1]) != check_color(&cube[4][0][0]) && check_color(&cube[4][0][1]) != check_color(&cube[2][0][0]) && !has_bar(cube))
	{
		Z_perm(cube);
		if (!is_solved(cube) && !top_layer_right(cube))
		{
			H_perm(cube);
		}
		if (!is_solved(cube) && top_layer_right(cube))
		{
			auf(cube);
			if (is_solved(cube)) return;
		}
	}
	if (check_color(&cube[2][0][0]) == check_color(&cube[2][0][1]) && check_color(&cube[2][0][2]) == check_color(&cube[2][0][0])) {
		turn_cube(cube, "U", true); turn_cube(cube, "U", true);
	}
	else if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][1]) && check_color(&cube[1][0][0]) == check_color(&cube[1][0][2])) { turn_cube(cube, "U", true); }
	else if (check_color(&cube[3][0][0]) == check_color(&cube[3][0][1]) && check_color(&cube[3][0][0]) == check_color(&cube[3][0][2])) { turn_cube(cube, "Up", true); }
	if (has_bar(cube) && check_color(&cube[2][0][0]) != check_color(&cube[2][0][1]) && check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) && check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) && check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) && check_color(&cube[3][0][0]) != check_color(&cube[3][0][1]) && check_color(&cube[4][0][0]) == check_color(&cube[4][0][1])
		&& check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
	{
		if (check_color(&cube[3][0][1]) == check_color(&cube[1][0][0]) && check_color(&cube[1][0][1]) ==
			check_color(&cube[2][0][0]))
		{
			if (cfop_delay)
				delay();
			Ua_perm(cube);
		}
		else
		{
			if (cfop_delay)
				delay();
			Ub_perm(cube);
		}
		return;
	}
}

void top_cross(int cube[6][3][3])
{
	//top dot shape
	if (check_color(&cube[0][0][1]) != "yellow" && check_color(&cube[0][1][0]) != "yellow" && check_color(&cube[0][1][2]) != "yellow" && check_color(&cube[0][2][1]) != "yellow")
	{
		turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
	}
	//top l shape
	if (check_color(&cube[0][1][0]) == "yellow" && check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][2][1]) == "yellow" &&
		check_color(&cube[0][0][1]) != "yellow" && check_color(&cube[0][1][2]) != "yellow") turn_cube(cube, "U", true);
	else if(check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][1][2]) == "yellow" && check_color(&cube[0][2][1]) == "yellow" && 
		check_color(&cube[0][0][1]) != "yellow" && check_color(&cube[0][1][0]) != "yellow") {
		turn_cube(cube, "U", true); turn_cube(cube, "U", true);
	}
	else if(check_color(&cube[0][0][1]) == "yellow" && check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][1][2]) == "yellow" &&
		check_color(&cube[0][1][0]) != "yellow" && check_color(&cube[0][2][1]) != "yellow") {
		turn_cube(cube, "Up", true);
	}
	if (check_color(&cube[0][1][0]) == "yellow" && check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][0][1]) == "yellow" &&
	check_color(&cube[0][2][1]) != "yellow" && check_color(&cube[0][1][2]) != "yellow")
	{
		turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
	}
	//top bar
	if (check_color(&cube[0][0][1]) == "yellow" && check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][2][1]) == "yellow" &&
		check_color(&cube[00][1][0]) != "yellow" && check_color(&cube[0][1][2]) != "yellow")
	{
		turn_cube(cube, "U", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
		//f u r u rp up fp
	}
	else if (check_color(&cube[0][1][0]) == "yellow" && check_color(&cube[0][1][1]) == "yellow" && check_color(&cube[0][1][2]) == "yellow" &&
		check_color(&cube[0][0][1]) != "yellow" && check_color(&cube[0][2][1]) != "yellow")
	{
		turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
		//f r u rp up fp
	}
}

bool second_layer_correct(int cube[6][3][3])
{
	if (check_color(&cube[1][1][0]) == "blue" && check_color(&cube[1][1][2]) == "blue" &&
		check_color(&cube[2][1][0]) == "red" && check_color(&cube[2][1][2]) == "red" &&
		check_color(&cube[3][1][0]) == "green" && check_color(&cube[3][1][2]) == "green" &&
		check_color(&cube[4][1][0]) == "orange" && check_color(&cube[4][1][2]) == "orange") 
		return true;
	return false;
}

void second_layer(int cube[6][3][3])
{
	bool g = true;
	int* ptr = &cube[0][0][1]; // top
	int* ptr2 = &cube[0][1][0]; //left
	int* ptr3 = &cube[0][1][2];
	int* ptr4 = &cube[0][2][1]; //right && bottom

	int* red = &cube[2][0][1]; int* blue = &cube[1][0][1]; int* orange = &cube[4][0][1]; int* green = &cube[3][0][1];
	if(check_color(cube, 0, 2, 1) == "green" && check_color(cube, 2, 0, 1) == "red") { turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g); 
	turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g);}
	if(check_color(cube, 0, 2, 1) == "blue" && check_color(cube, 2,0,1) == "red") { turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g);}
	if (check_color(cube, 0, 1, 0) == "red" && check_color(cube, 1, 0, 1) == "blue") {
		turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g);
	}
	if (check_color(cube, 0, 1, 2) == "red" && check_color(cube, 3, 0, 1) == "green") {
		turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g);
	}
	if(check_color(cube, 0, 1, 0) == "orange" && check_color(cube, 1, 0, 1) == "blue") {
		turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "U", g);
		turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g);
	}
	if(check_color(&cube[0][1][2]) == "orange" && check_color(&cube[3][0][1]) == "green") {
		turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); turn_cube(cube, "Up", g);
		turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g);
	}
	if(check_color(cube, 0, 0, 1) == "blue" && check_color(cube, 4, 0, 1) == "orange") {
		turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "Up", g);
		turn_cube(cube, "Bp", g); turn_cube(cube, "U", g); turn_cube(cube, "B", g);
	}
	if(check_color(&cube[0][0][1]) == "green" && check_color(&cube[4][0][1]) == "orange") {
		turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "U", g);
		turn_cube(cube, "B", g); turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g);
	}
	turn_cube(cube, "U", true);
	int count = 0;
	if (check_color(ptr) == "yellow") count++;
	if (check_color(ptr2) == "yellow") count++;
	if (check_color(ptr3) == "yellow") count++;
	if (check_color(ptr4) == "yellow") count++;
	if (check_color(red) == "yellow") count++;
	if (check_color(blue) == "yellow") count++;
	if (check_color(orange) == "yellow") count++;
	if (check_color(green) == "yellow") count++;
	//this is the problem rn  goes into infinite loop //fixed
	if (count >= 4 && !second_layer_correct(cube)){
		if (check_color(&cube[2][1][2]) != "red" || check_color(&cube[3][1][0]) != "green") {
			turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g);
			turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g);
		}
		else if (check_color(&cube[1][1][2]) != "blue" || check_color(&cube[2][1][0]) != "red") {
			turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g);
		}
		else if (check_color(&cube[3][1][2]) != "green" || check_color(&cube[4][1][0]) != "orange") {
			turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); turn_cube(cube, "Up", g);
			turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g);
		}
		else {
			turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "U", g);
			turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g);
		}
	}
	count = 0;
	/*
	if(check_color(cube, 2, 1, 2) != "red" && check_color(cube, 3, 1, 0) != "green") {
		turn_cube(cube, "U", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g);
		turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g);
	}
	else if(check_color(cube, 2, 1, 0) != "red" && check_color(cube, 1, 1, 2) != "blue") { turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); }
	else if(check_color(cube, 3, 1, 2) != )
	*/
}

static bool white_on_top(int cube[6][3][3])
{
	if (check_color(&cube[1][0][0]) == "white" || check_color(&cube[1][0][2]) == "white" || check_color(&cube[2][0][0]) == "white" || check_color(&cube[2][0][2]) == "white" || check_color(&cube[3][0][0]) == "white" ||
		check_color(&cube[3][0][2]) == "white" || check_color(&cube[4][0][0]) == "white" || check_color(&cube[4][0][2]) == "white" || check_color(&cube[0][0][0]) == "white" ||
		check_color(&cube[0][0][2]) == "white" || check_color(&cube[0][2][0]) == "white" || check_color(&cube[0][2][2]) == "white")
		return true;
	return false;
}

void corners(int cube[6][3][3])
{
	bool g = true;

	//check if white is in bottom layer if it is being to top


	do {

		//white red green corner piece
		if (check_color(cube, 2, 0, 2) == "green" && check_color(cube, 0, 2, 2) == "white" && check_color(cube, 3, 0, 0) == "red") { turn_cube(cube, "R", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g); }
		if (check_color(cube, 2, 0, 2) == "white" && check_color(cube, 0, 2, 2) == "red" && check_color(cube, 3, 0, 0) == "green") { turn_cube(cube, "U", true); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); }
		if (check_color(cube, 2, 0, 2) == "red" && check_color(cube, 0, 2, 2) == "green" && check_color(cube, 3, 0, 0) == "white") { turn_cube(cube, "R", g); turn_cube(cube, "U", g); turn_cube(cube, "Rp", g); }

		//white red blue corner
		if (check_color(cube, 0, 2, 0) == "white" && check_color(cube, 1, 0, 2) == "red" && check_color(cube, 2, 0, 0) == "blue") { turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); }
		if (check_color(cube, 0, 2, 0) == "red" && check_color(cube, 1, 0, 2) == "blue" && check_color(cube, 2, 0, 0) == "white") { turn_cube(cube, "F", g); turn_cube(cube, "U", g); turn_cube(cube, "Fp", g); }
		if (check_color(cube, 0, 2, 0) == "blue" && check_color(cube, 1, 0, 2) == "white" && check_color(cube, 2, 0, 0) == "red") { turn_cube(cube, "Lp", g); turn_cube(cube, "Up", g); turn_cube(cube, "L", g); }

		//white blue orange corner
		if (check_color(cube, 0, 0, 0) == "white" && check_color(cube, 1, 0, 0) == "orange" && check_color(cube, 4, 0, 2) == "blue") { turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); turn_cube(cube, "Lp", g); turn_cube(cube, "Up", g); }
		if (check_color(cube, 0, 0, 0) == "blue" && check_color(cube, 1, 0, 0) == "white" && check_color(cube, 4, 0, 2) == "orange") { turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "Lp", g); }
		if (check_color(cube, 0, 0, 0) == "orange" && check_color(cube, 1, 0, 0) == "blue" && check_color(cube, 4, 0, 2) == "white") { turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); }

		//white green orange corner 0 3 4
		if (check_color(cube, 0, 0, 2) == "white" && check_color(cube, 3, 0, 2) == "orange" && check_color(cube, 4, 0, 0) == "green") { turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "U", g); }
		if (check_color(cube, 0, 0, 2) == "green" && check_color(cube, 3, 0, 2) == "white" && check_color(cube, 4, 0, 0) == "orange") { turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); } //check
		if (check_color(cube, 0, 0, 2) == "orange" && check_color(cube, 3, 0, 2) == "green" && check_color(cube, 4, 0, 0) == "white") { turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); }
		//if there is a white piece in botom layer but is not oriented correctly, bring back into top layer to be inserted
		if (!white_on_top(cube))
		{
			if (check_color(cube, 5, 0, 0) == "white" || check_color(cube, 5, 0, 2) == "white" || check_color(cube, 5, 2, 0) == "white" || check_color(cube, 5, 2, 2) == "white" ||
				check_color(&cube[1][2][0]) == "white" || check_color(&cube[1][2][2]) == "white" || check_color(&cube[2][2][0]) == "white" || check_color(&cube[2][2][2]) == "white" ||
				check_color(&cube[3][2][0]) == "white" || check_color(&cube[3][2][2]) == "white" || check_color(&cube[4][2][0]) == "white" || check_color(&cube[4][2][2]) == "white") {
				if ((check_color(cube, 2, 2, 2) == "white" || check_color(cube, 3, 2, 0) == "white" || check_color(cube, 5, 0, 2) == "white") && (check_color(cube, 2, 2, 2) != "red" || check_color(cube, 3, 2, 0) != "green" || check_color(&cube[5][0][2]) != "white")) {
					turn_cube(cube, "R", g); turn_cube(cube, "U", g); turn_cube(cube, "Rp", g);
				}
				else if ((check_color(cube, 2, 2, 0) == "white" || check_color(cube, 1, 2, 2) == "white" || check_color(cube, 5, 0, 0) == "white") && (check_color(cube, 2, 2, 0) != "red" || check_color(cube, 1, 2, 2) != "blue" || check_color(&cube[5][0][0]) != "white")) {
					turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g);
				}
				else if ((check_color(cube, 1, 2, 0) == "white" || check_color(cube, 4, 2, 2) == "white" || check_color(cube, 5, 2, 0) == "white") && (check_color(cube, 1, 2, 0) != "blue" || check_color(cube, 4, 2, 2) != "orange" || check_color(&cube[5][2][0]) != "white")) {
					turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "Lp", g);
				}
				else if ((check_color(cube, 3, 2, 2) == "white" || check_color(cube, 4, 2, 0) == "white" || check_color(cube, 5, 2, 2) == "white") && (check_color(cube, 3, 2, 2) != "green" || check_color(cube, 4, 2, 0) != "orange" || check_color(&cube[5][2][2]) != "white")) {
					turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g);
				}
			}
		}
		turn_cube(cube, "U", true);
	} while (!(check_color(cube, 5, 0, 0) == "white" && check_color(cube, 5, 0, 2) == "white" && check_color(cube, 5, 2, 0) == "white" && check_color(cube, 5, 2, 2) == "white" && check_color(&cube[2][2][0]) == "red" && check_color(&cube[2][2][2]) == "red" &&
			   check_color(&cube[1][2][0]) == "blue" && check_color(&cube[1][2][2]) == "blue" && check_color(&cube[3][2][0]) == "green" && check_color(&cube[3][2][2]) == "green" && check_color(&cube[4][2][0]) == "orange" && check_color(&cube[4][2][2]) == "orange"));
}

void cross(int cube[6][3][3])
{
	//2 1 2 4 1 0
	//change all but yellow face to move white piece to to layer
	//move white to top then use the yellow checker to move cross pieces
	bool t = true;


	//red face
	if (check_color(cube, 2, 0, 1) == "white")
	{
		if (check_color(cube, 0, 2, 1) == "red") { turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true); }
		else if (check_color(cube, 0, 2, 1) == "blue") { turn_cube(cube, "Fp", true); turn_cube(cube, "L", true); turn_cube(cube, "F", true); }
		else if (check_color(cube, 0, 2, 1) == "orange") { turn_cube(cube, "U", true); turn_cube(cube, "Lp", true); turn_cube(cube, "B", true); turn_cube(cube, "L", true); }
		else if (check_color(cube, 0, 2, 1) == "green") { turn_cube(cube, "F", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true); }
	}
	else if (check_color(cube, 2, 1, 0) == "white"){ turn_cube(cube, "Lp", true); turn_cube(cube, "Up", true); turn_cube(cube, "L", true);}
	else if (check_color(cube, 2, 1, 2) == "white") { turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); }
	else if (check_color(cube, 2, 2, 1) == "white") { turn_cube(cube, "Fp", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); }

	//green face
	if (check_color(cube, 3, 0, 1) == "white") { turn_cube(cube, "U", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);}
	else if (check_color(cube, 3, 1, 0) == "white") { turn_cube(cube, "Fp", true); turn_cube(cube, "Up", true); turn_cube(cube, "F", true); }
	else if (check_color(cube, 3, 1, 2) == "white") { turn_cube(cube, "B", true); turn_cube(cube, "U", true); turn_cube(cube, "Bp", true); }
	else if (check_color(cube, 3, 2, 1) == "white") { turn_cube(cube, "R", true); turn_cube(cube, "Fp", true); turn_cube(cube, "Up", true); turn_cube(cube, "F", true); turn_cube(cube, "U", true); }
	
	//orange face
	if (check_color(cube, 4, 0, 1) == "white") { turn_cube(cube, "B", true); turn_cube(cube, "L", true); turn_cube(cube, "Up", true); turn_cube(cube, "Lp", true); turn_cube(cube, "Bp", true); }
	else if (check_color(cube, 4, 1, 0) == "white") { turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); }
	else if (check_color(cube, 4, 1, 2) == "white") { turn_cube(cube, "L", true); turn_cube(cube, "Up", true); turn_cube(cube, "Lp", true); }
	else if (check_color(cube, 4, 2, 1) == "white") { turn_cube(cube, "B", true); turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); }

	//blue face
	if (check_color(cube, 1, 0, 1) == "white") { turn_cube(cube, "L", true); turn_cube(cube, "F", t); turn_cube(cube, "Up", t); turn_cube(cube, "Fp", t); turn_cube(cube, "Lp", t); }
	else if (check_color(cube, 1, 1, 0) == "white") { turn_cube(cube, "L", t); turn_cube(cube, "Up", t); turn_cube(cube, "Lp", t); }
	else if (check_color(cube, 1, 1, 2) == "white") { turn_cube(cube, "F", t); turn_cube(cube, "Up", t); turn_cube(cube, "Fp", t); turn_cube(cube, "U", true); }
	else if (check_color(cube, 1, 2, 1) == "white") { turn_cube(cube, "Lp", t); turn_cube(cube, "F", t); turn_cube(cube, "U", t); turn_cube(cube, "Fp", t); turn_cube(cube, "Up", true); }

	//yellow face
	if(check_color(cube, 0, 0, 1) == "white")
	{
		if (check_color(cube, 4, 0, 1) == "orange") { turn_cube(cube, "B", true); turn_cube(cube, "B", true);}
		else if (check_color(cube, 4, 0, 1) == "blue") { turn_cube(cube, "Up", true); turn_cube(cube, "L", true); turn_cube(cube, "L", true); }
		else if (check_color(cube, 4, 0, 1) == "red") { turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "F", true); turn_cube(cube, "F", true); }
		else if (check_color(cube, 4, 0, 1) == "green") { turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); }
	}
	if (check_color(cube, 0, 1, 0) == "white")
	{
		if (check_color(cube, 1, 0, 1) == "blue") { turn_cube(cube, "L", true); turn_cube(cube, "L", true);}
		else if (check_color(cube, 1, 0, 1) == "red") { turn_cube(cube, "Up", true); turn_cube(cube, "F", true); turn_cube(cube, "F", true); }
		else if (check_color(cube, 1, 0, 1) == "green") { turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); }
		else if (check_color(cube, 1, 0, 1) == "orange") { turn_cube(cube, "U", true); turn_cube(cube, "B", true); turn_cube(cube, "B", true); }
	}
	if (check_color(cube, 0, 1, 2) == "white")
	{
		if (check_color(cube, 3, 0, 1) == "red") { turn_cube(cube, "U", true); turn_cube(cube, "F", true); turn_cube(cube, "F", true); }
		else if (check_color(cube, 3, 0, 1) == "green") { turn_cube(cube, "R", true); turn_cube(cube, "R", true); }
		else if (check_color(cube, 3, 0, 1) == "orange") { turn_cube(cube, "Up", true); turn_cube(cube, "B", true); turn_cube(cube, "B", true); }
		else if (check_color(cube, 3, 0, 1) == "blue") { turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "L", true); turn_cube(cube, "L", true); }
	}
	if (check_color(cube, 0, 2, 1) == "white")
	{
		if (check_color(cube, 2, 0, 1) == "red") { turn_cube(cube, "F", true); turn_cube(cube, "F", true);}
		else if (check_color(cube, 2, 0, 1) == "green") { turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); }
		else if (check_color(cube, 2, 0, 1) == "orange") { turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "B", true); turn_cube(cube, "B", true); }
		else if (check_color(cube, 2, 0, 1) == "blue") { turn_cube(cube, "U", true); turn_cube(cube, "L", true); turn_cube(cube, "L", true); }
	}
	//white face
	if (check_color(cube, 5, 0, 1) == "white" && check_color(cube, 2, 2, 1) != "red") { turn_cube(cube, "F", t); turn_cube(cube, "F", t); }
	else if (check_color(cube, 5, 1, 0) == "white" && check_color(cube, 1, 2, 1) != "blue") { turn_cube(cube, "L", t); turn_cube(cube, "L", t); }
	else if (check_color(cube, 5, 1, 2) == "white" && check_color(cube, 3, 2, 1) != "green") { turn_cube(cube, "R", t); turn_cube(cube, "R", t); }
	else if (check_color(cube, 5, 2, 1) == "white" && check_color(cube, 4, 2, 1) != "orange") { turn_cube(cube, "B", t); turn_cube(cube, "B", t); }
}

void delay()
{
	for (int i = 0; i < 100000000; i++)
		for (int j = 0; j < 20; j += 2);
	return;
}

void play(int cube[6][3][3])
{
	std::string move;
	do 
	{
		std::cout << "Enter in your move || 'q' to quit: ";
		std::cin >> move;
		while (move != "q" && move != "Q" && !valid_move(move))
		{
			std::cout << "Invalid move... try again" << std::endl;
			std::cin >> move;
		}
		turn_cube(cube, move, true);
		if (is_solved(cube)) {
			std::cout << "CONGRATS! NICE! AWESOME! 11/10 " << std::endl;
			return;
		}
	} while (move != "Q" && move != "q");

}

bool valid_move(std::string move)
{
	if (move != "R" && move != "Rp" && move != "L" && move != "Lp" &&
		move != "U" && move != "Up" && move != "D" && move != "Dp" &&
		move != "B" && move != "Bp" && move != "F" && move != "Fp")
		return false;
	return true;
}

bool is_solved(int cube[6][3][3])
{
	int correct[6][3][3];
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				correct[i][j][k] = count;
				count++;
				if (correct[i][j][k] != cube[i][j][k])
					return false;
			}
		}
	}
	return true;
}

int menu(int choice)
{
	//add a debug menu
	std::cout << std::endl;
	std::cout << "Rubik's Cube Solver" << std::endl;
	std::cout << "1. Randomly Scramble the Cube" << std::endl;
	std::cout << "2. Solve the cube yourself" << std::endl;
	std::cout << "3. Upload a custom scramble" << std::endl;
	std::cout << "4. Load a custom solution " << std::endl;
	std::cout << "5. Ai cube solve" << std::endl;
	std::cout << "6. Cheeky Ai cube solve" << std::endl;
    std::cout << "7. Debug" << std::endl;
	std::cout << "8. Quit" << std::endl;
	std::cout << "Enter in a choice: "; std::cin >> choice;
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8) {
		std::cout << "Invalid menu choice, try again" << std::endl;
		std::cout << "Enter in a choice: ";
		std::cin >> choice;
	}
	return choice;
}

//delay for turn_delay
static void delay2()
{
	for (int i = 0; i < 100000; i++)
		for (int j = 0; j < 800; j++);
}


void turn_cube(int cube[6][3][3], std::string temp, bool yea)
{
	if (temp == "R") R(cube);
	else if (temp == "Rp") Rp(cube);
	else if (temp == "U") U(cube);
	else if (temp == "Up") Up(cube);
	else if (temp == "L") L(cube);
	else if (temp == "Lp") Lp(cube);
	else if (temp == "F") F(cube);
	else if (temp == "Fp") Fp(cube);
	else if (temp == "D") D(cube);
	else if (temp == "Dp") Dp(cube);
	else if (temp == "B") B(cube);
	else if (temp == "Bp") Bp(cube);
	else if (temp == "M") M(cube);
	else if (temp == "Mp") Mp(cube);
	else if (temp == "M2") M2(cube);
	if(show_moves)
		std::cout << "One " << temp << " rotation" << std::endl;
	if(turn_delay)
		delay2();
	if (yea && print_cube)
	{
		print(cube);
		std::cout << std::endl;
	}
}

void load_scramble(int cube[6][3][3], std::ifstream& is)
{
	std::string filename = "", temp = "";
	std::cout << "Enter in the filename: ";
	std::cin >> filename;
	is.open(filename);
	if (is.is_open()) 
		is.clear();
	if (is.fail()) {
		std::cout << "Error loading file..." << std::endl;
		return;
	}
	while (is >> temp)
	{
		turn_cube(cube, temp, false);
	}
	is.close();
}

static std::string opp(std::string a)
{
	if (a == "R") return "Rp";
	else if (a == "Rp") return "R";
	else if (a == "U") return "Up";
	else if (a == "Up") return "U";
	else if (a == "L") return "Lp";
	else if (a == "Lp") return "L";
	else if (a == "F") return "Fp";
	else if (a == "Fp") return "F";
	else if (a == "D") return "Dp";
	else if (a == "Dp") return "D";
	else if (a == "B") return "Bp";
	else if (a == "Bp") return "B";
	else return "~";
}

std::string random_scramble(int cube[6][3][3], int scramble_size, std::ofstream& os)
{
	std::string scramble = "", temp = "";
	std::string reverse_scramble = "";
	std::vector<std::string> vect2;
	//will make fillle explorer use 90% of cpu without
	if (turn_delay || cfop_delay)
	{
		os.open("test.txt");
		if (os.is_open()) {
			os.clear();
		}
		else {
			std::cout << "Error opening file... test.txt" << std::endl;
			return "~";
		}
	}
	std::vector<std::string> vect = { "R", "Rp", "U", "Up", "L", "Lp", "F", "Fp", "D", "Dp", "B", "Bp" };
	int random = 0;
	srand(time(NULL));
	for (int i = 0; i < scramble_size; i++)
	{
		random = rand() % 12;
		scramble += vect.at(random);
		scramble += " ";
		vect2.insert(vect2.begin(), opp(vect.at(random)));
	}
	if (turn_delay || cfop_delay)
	{
		std::istringstream iss(scramble);
		while (iss >> temp)
		{
			turn_cube(cube, temp, false);
			os << temp << " ";
		}
		os << "\n# of turns in scramble: " << scramble_size << "\n";
		os.close();
	}
	std::vector<std::string>::iterator begin = vect2.begin();
	std::vector<std::string>::iterator end = vect2.end();
	if (turn_delay || cfop_delay)
	{
		os.open("reverse_scramble.txt");
		int counter = 0;
		if (os.is_open())
			os.clear();
		while (begin != end)
		{
			reverse_scramble += *begin;
			reverse_scramble += " ";
			os << *begin << " ";
			counter++;
			++begin;
		}
		os.close();
		std::cout << "# of turns in scramble: " << scramble_size << std::endl;
	}
	return reverse_scramble;
}

void B(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			foo[c] = cube[4][j][i];
			c++;
		}
	}
	c = 0;
	for (int a = 0; a < 3; a++)
	{
		for (int k = 0; k < 3; k++)
		{
			cube[4][a][k] = foo[c];
			c++; //lol
		}
	}
	c = 0;
	//rotate edges
	//yellow
	int temp[3] = { cube[0][0][2], cube[0][0][1], cube[0][0][0] };
	//green
	int temp2[3] = { cube[3][0][2], cube[3][1][2], cube[3][2][2] };
	//white
	int temp3[3] = { cube[5][2][2], cube[5][2][1], cube[5][2][0] };
	//blue
	int temp4[3] = { cube[1][0][0], cube[1][1][0], cube[1][2][0] };
	for(int v = 0; v < 3; v++)
	{
		cube[1][v][0] = temp[c];
		cube[0][0][v] = temp2[c];
		cube[3][v][2] = temp3[c];
		cube[5][2][v] = temp4[c];
		c++;
	}
}

void Bp(int cube[6][3][3])
{
	for (int i = 0; i < 3; i++) B(cube);
}

void D(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	//roate face
	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			foo[c] = cube[5][j][i];
			c++; //hah
		}
	}
	c = 0;
	for (int a = 0; a < 3; a++)
	{
		for (int k = 0; k < 3; k++)
		{
			cube[5][a][k] = foo[c];
			c++;
		}
	}
	c = 0;
	//rotate edges
	//blue
	int temp[3] = { cube[1][2][0], cube[1][2][1], cube[1][2][2] };
	//red
	int temp2[3] = { cube[2][2][0], cube[2][2][1], cube[2][2][2] };
	//green
	int temp3[3] = { cube[3][2][0], cube[3][2][1], cube[3][2][2] };
	//orange
	int temp4[3] = { cube[4][2][0], cube[4][2][1], cube[4][2][2] };
	for(int v = 0; v < 3; v++)
	{
		cube[2][2][v] = temp[c];
		cube[3][2][v] = temp2[c];
		cube[4][2][v] = temp3[c];
		cube[1][2][v] = temp4[c];
		c++; //hahah
	}
}

void Dp(int cube[6][3][3])
{
	for (int i = 0; i < 3; i++) D(cube);
}

void Up(int cube[6][3][3])
{
	for (int i = 0; i < 3; i++) U(cube);
}

void U(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	//rotate face
	for (int i = 0; i < 3; i++) 
	{
		for (int j = 2; j >= 0; j--) 
		{
			foo[c] = cube[0][j][i];
			c++; //haha
		} 
	}
	c = 0;
	for (int a = 0; a < 3; a++) 
	{
		for (int k = 0; k < 3; k++)
		{
			cube[0][a][k] = foo[c];
			c++;
		}
	}
	//ROTATE EDGES
	//orange
	int temp[3] = { cube[4][0][0], cube[4][0][1], cube[4][0][2] };
	//green
	int temp2[3] = { cube[3][0][0], cube[3][0][1],cube[3][0][2] };
	//red
	int temp3[3] = { cube[2][0][0], cube[2][0][1], cube[2][0][2] };
	//blue
	int temp4[4] = { cube[1][0][0], cube[1][0][1], cube[1][0][2] };
	c = 0;
	for (int v = 0; v < 3; v++)
	{
		cube[3][0][v] = temp[c];
		cube[2][0][v] = temp2[c];
		cube[1][0][v] = temp3[c];
		cube[4][0][v] = temp4[c];
		c++;
	}
}

void Rp(int cube[6][3][3])
{
	R(cube); R(cube); R(cube);
}

void R(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	//rotate face
	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			foo[c] = cube[3][j][i];
			c++;
		}
	}
	c = 0;
	for (int a = 0; a < 3; a++) {
		for (int k = 0; k < 3; k++) {
			cube[3][a][k] = foo[c]; c++;
		}
	}
	//ROTATE EDGES
	//red
	int temp[3] = { cube[2][0][2], cube[2][1][2], cube[2][2][2] };
	//white
	int temp2[3] = { cube[5][0][2], cube[5][1][2], cube[5][2][2] };
	//orange
	int temp3[3] = { cube[4][2][0], cube[4][1][0], cube[4][0][0] };
	//yellow
	int temp4[3] = { cube[0][2][2], cube[0][1][2], cube[0][0][2] };
	c = 0;
	for (int v = 0; v < 3; v++) {
		cube[0][v][2] = temp[c];
		cube[2][v][2] = temp2[c];
		cube[5][v][2] = temp3[c];
		cube[4][v][0] = temp4[c];
		c++;
	}
}

void Lp(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	//rotate face
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j <= 2; j++)
		{
			foo[c] = cube[1][j][i];
			c++;
		}
	}
	c = 0;
	for (int a = 0; a < 3; a++)
	{
		for (int k = 0; k < 3; k++)
		{
			cube[1][a][k] = foo[c];
			c++;
		}
	}
	//ROTATE EDGES
	int temp[3] = { cube[5][0][0], cube[5][1][0], cube[5][2][0] };
	int temp2[3] = { cube[2][0][0], cube[2][1][0], cube[2][2][0] };
	int temp3[3] = { cube[0][2][0], cube[0][1][0], cube[0][0][0] };
	int temp4[3] = { cube[4][2][2], cube[4][1][2], cube[4][0][2] };
	c = 0;
	for (int v = 0; v < 3; v++)
	{
		cube[2][v][0] = temp[c];
		cube[0][v][0] = temp2[c];
		cube[4][v][2] = temp3[c];
		cube[5][v][0] = temp4[c];
		c++;
	}
}

void L(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	//rotate face only
	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			foo[c] = cube[1][j][i];
			c++; //haha
		}
	}
	c = 0;
	for (int a = 0; a < 3; a++)
	{
		for (int k = 0; k < 3; k++)
		{
			cube[1][a][k] = foo[c];
			c++;//hehe
		}
	}
	//ROTATE EDGES
	int temp[3] = { cube[5][2][0], cube[5][1][0], cube[5][0][0] };
	int temp2[3] = { cube[4][2][2], cube[4][1][2], cube[4][0][2] };
	int temp3[3] = { cube[0][0][0], cube[0][1][0], cube[0][2][0] };
	int temp4[3] = { cube[2][0][0], cube[2][1][0], cube[2][2][0] };
	c = 0;
	for (int v = 0; v < 3; v++)
	{
		cube[4][v][2] = temp[c];
		cube[0][v][0] = temp2[c];
		cube[2][v][0] = temp3[c];
		cube[5][v][0] = temp4[c];
		c++;
	}
}

void Fp(int cube[6][3][3])
{
	F(cube); F(cube); F(cube);
}

void F(int cube[6][3][3])
{
	int foo[9];
	int c = 0;
	//ROTATES RED FACE ONLY
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			foo[c] = cube[2][j][i];
			c++; //hehe
		}
	}
	c = 0;
	for (int a = 0; a < 3; a++)
	{
		for (int k = 0; k < 3; k++)
		{
			cube[2][a][k] = foo[c];
			c++; //hah
		}
	}
	//ROTATE EDGES
	int temp[3] = { cube[0][2][0], cube[0][2][1], cube[0][2][2] };
	int temp2[3] = { cube[3][2][0], cube[3][1][0], cube[3][0][0] };
	int temp3[3] = { cube[1][2][2], cube[1][1][2], cube[1][0][2] };
	int temp4[3] = { cube[5][0][0], cube[5][0][1], cube[5][0][2] };
	c = 0;
	for (int v = 0; v < 3; v++)
	{
		cube[3][v][0] = temp[c];
		cube[5][0][v] = temp2[c];
		cube[0][2][v] = temp3[c];
		cube[1][v][2] = temp4[c];
		c++;
	}
}

//fuck this shit!
void print(int cube[6][3][3])
{
	const char* colors[7] = { RESET, RED, GREEN, YELLOW, BLUE, WHITE, ORANGE };
	const char* colors2[7] = { RESET, RED2, GREEN2, YELLOW2, BLUE2, WHITE2, ORANGE2 };
	int color = 0;
	//YELLOW FACE
	for (int i = 0; i <= 2; i++)
	{
		std::cout << "         ";
		for (int e = 0; e <= 2; e++)
		{
			//asigns each number to its respective color
			if (cube[0][i][e] >= 0 && cube[0][i][e] <= 8) color = 3;
			else if (cube[0][i][e] >= 9 && cube[0][i][e] <= 17) color = 4;
			else if (cube[0][i][e] >= 18 && cube[0][i][e] <= 26) color = 1;
			else if (cube[0][i][e] >= 27 && cube[0][i][e] <= 35) color = 2;
			else if (cube[0][i][e] >= 36 && cube[0][i][e] <= 44) color = 6;
			else if (cube[0][i][e] >= 45 && cube[0][i][e] <= 53) color = 5;
			if (cube[0][i][e] < 9) std::cout << colors[3] << colors2[3] << "0";
			if (cube[0][i][e] == 9) std::cout << colors[4] << colors2[4] << "0";
			std::cout << colors[color] << colors2[color] << cube[0][i][e] << " " << RESET;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int j = 0; j <= 2; j++)
	{
		for (int q = 1; q <= 4; q++)
		{
			/*
			if (q == 1) color = 4;
			else if (q == 2) color = 1;
			else if (q == 3) color = 2;
			else if (q == 4) color = 7;
			*/
			for (int p = 0; p < 3; p++)
			{
				if (cube[q][j][p] >= 0 && cube[q][j][p] <= 8) color = 3;
				else if (cube[q][j][p] >= 9 && cube[q][j][p] <= 17) color = 4;
				else if (cube[q][j][p] >= 18 && cube[q][j][p] <= 26) color = 1;
				else if (cube[q][j][p] >= 27 && cube[q][j][p] <= 35) color = 2;
				else if (cube[q][j][p] >= 36 && cube[q][j][p] <= 44) color = 6;
				else if (cube[q][j][p] >= 45 && cube[q][j][p] <= 53) color = 5;
				if (cube[q][j][p] < 10) std::cout << colors[color] << colors2[color] << "0";
				std::cout << colors[color] << colors2[color] << cube[q][j][p] << " " << RESET;

			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int k = 0; k <= 2; k++)
	{
		std::cout << "         ";
		for (int a = 0; a <= 2; a++)
		{
			if (cube[5][k][a] >= 0 && cube[5][k][a] <= 8) color = 3;
			else if (cube[5][k][a] >= 9 && cube[5][k][a] <= 17) color = 4;
			else if (cube[5][k][a] >= 18 && cube[5][k][a] <= 26) color = 1;
			else if (cube[5][k][a] >= 27 && cube[5][k][a] <= 35) color = 2;
			else if (cube[5][k][a] >= 36 && cube[5][k][a] <= 44) color = 6;
			else if (cube[5][k][a] >= 45 && cube[5][k][a] <= 53) color = 5;
			if (cube[5][k][a] < 10) std::cout << colors[color] << colors2[color] << "0";
			std::cout << colors[color] << colors2[color] << cube[5][k][a] << " " << RESET;
		}
		std::cout << std::endl;
	}
}