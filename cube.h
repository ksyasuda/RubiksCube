#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


void print(int cube[6][3][3]);

void F(int cube[6][3][3]);

void Fp(int cube[6][3][3]);

void L(int cube[6][3][3]);

void Lp(int cube[6][3][3]);

void R(int cube[6][3][3]);

void Rp(int cube[6][3][3]);

void U(int cube[6][3][3]);

void Up(int cube[6][3][3]);

void D(int cube[6][3][3]);

void Dp(int cube[6][3][3]);

void B(int cube[6][3][3]);

void Bp(int cube[6][3][3]);

std::string random_scramble(int cube[6][3][3], int scramble_size, std::ofstream& os);

void load_scramble(int cube[6][3][3], std::ifstream& ins);

void turn_cube(int cube[6][3][3], std::string temp, bool yeah);

int menu(int choice);

bool is_solved(int cube[6][3][3]);

void play(int cube[6][3][3]);

bool valid_move(std::string move);

void solver(int cube[6][3][3]);

void cross(int cube[6][3][3]);

void second_layer(int cube[6][3][3]);

void corners(int cube[6][3][3]);

void delay();

bool second_layer_correct(int cube[6][3][3]);

void top_cross(int cube[6][3][3]);

std::string check_color(int * ptr);

void pll(int cube[6][3][3]);

void oll(int cube[6][3][3]);

bool top_correct(int cube[6][3][3]);

void cheeky_ai(int cube[6][3][3], std::string rs);

void cube_with_pair();

void solver_debug(int cube[6][3][3]);

int debug_selector(int& num, bool& a, bool& b, bool& c, bool& d);


#endif
