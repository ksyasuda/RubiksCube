#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <glfw-3.2.1/include/GLFW/glfw3.h>


#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define GREEN "\033[32m"
#define ORANGE "\033[91m"

using namespace std;
using namespace std::chrono;

void print(int cube[6][3][3]);

void F(int cube[6][3][3]);

void Fp(int cube [6][3][3]);

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

string random_scramble(int cube[6][3][3], int scramble_size, ofstream& os);

void load_scramble(int cube[6][3][3], ifstream& ins);

void turn_cube(int cube[6][3][3], string temp, bool yeah);

int menu(int choice);

bool is_solved(int cube[6][3][3]);

void play(int cube[6][3][3]);

bool valid_move(string move);

void solver(int cube[6][3][3]);

void cross(int cube[6][3][3]);

void second_layer(int cube[6][3][3]);

void corners(int cube[6][3][3]);

void delay();

bool second_layer_correct(int cube[6][3][3]);

void top_cross(int cube[6][3][3]);

string check_color(int * ptr);

void pll(int cube[6][3][3]);

void oll(int cube[6][3][3]);

bool top_correct(int cube[6][3][3]);

void cheeky_ai(int cube[6][3][3], string r_scramble, ofstream& os, ifstream& is);

void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	/*
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		3, 1, 0,  // first Triangle
		1, 2, 3   // second Triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0); // no need to unbind it every time 

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	*/
	int cube[6][3][3];
	int count = 0, choice = 0;
	ifstream is;
	ofstream os;
	string reverse_scramble = "";
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
	solver(cube);
	do 
	{
		choice = menu(choice);
		int turns;
		if (choice == 1)
		{
			cout << "How many turns in the scramble?: ";
			cin >> turns;
			reverse_scramble = random_scramble(cube, turns, os);
			print(cube);
		}
		else if (choice == 2)
		{
			//play game yourself
			print(cube);
			play(cube);
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
				cout << "The Cube has been Solved" << endl;
				cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << endl;
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
		else if(choice == 6)
		{
			auto start = high_resolution_clock::now();
			cheeky_ai(cube, reverse_scramble, os, is);
			if (is_solved(cube))
			{
				auto end = high_resolution_clock::now();
				cout << "The Cube has been Solved" << endl;
				cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end-start).count() << " milliseconds)" << endl;
			}
		}
		else if (choice == 7)
		{
			cout << "Goodbye" << endl;
			return 0;
		}
	} while (choice != 7);
	//glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void cheeky_ai(int cube[6][3][3], string r_scramble, ofstream& os, ifstream& is)
{
	string temp = "";
	istringstream iss(r_scramble);
	while (iss >> temp)
	{
		turn_cube(cube, temp, true);
	}
}

string check_color(int cube[6][3][3], int x, int y, int z)
{
	if (cube[x][y][z] >= 0 and cube[x][y][z] <= 8) return "yellow";
	else if (cube[x][y][z] >= 9 and cube[x][y][z] <= 17) return "blue";
	else if (cube[x][y][z] >= 18 and cube[x][y][z] <= 26) return "red";
	else if (cube[x][y][z] >= 27 and cube[x][y][z] <= 35) return "green";
	else if (cube[x][y][z] >= 36 and cube[x][y][z] <= 44) return "orange";
	else if (cube[x][y][z] >= 45 and cube[x][y][z] <= 53) return "white";
	return " ";
}

string check_color(int * ptr)
{
	if (*ptr >= 0 and *ptr <= 8) return "yellow";
	else if (*ptr >= 9 and *ptr <= 17) return "blue";
	else if (*ptr >= 18 and *ptr <= 26) return "red";
	else if (*ptr >= 27 and *ptr <= 35) return "green";
	else if (*ptr >= 36 and *ptr <= 44) return "orange";
	else if (*ptr >= 45 and *ptr <= 53) return "white";
	return " ";
}

static bool top_layer_right(int cube[6][3][3])
{
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][1]) and check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) and
		check_color(&cube[2][0][0]) == check_color(&cube[2][0][1]) and check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) and
		check_color(&cube[3][0][0]) == check_color(&cube[3][0][1]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) and
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][1]) and check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
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

void solver(int cube[6][3][3])
{
	//cross
	//need to implement while loop to keep running function till the cross is made
	//implement a thing that writes the moves the ai does to solve the cube to a file with sstream (ofstream)
	int numRight = 0, numWrong = 0;
	int num_solves = 200;
	ofstream os;
	for (int e = 0; e < num_solves; e++)
	{
		random_scramble(cube, 25, os);
		auto start = high_resolution_clock::now();
		do {
			cross(cube);
		} while (!(check_color(cube, 5, 0, 1) == "white" and check_color(cube, 5, 1, 0) == "white" and check_color(cube, 5, 1, 2) == "white" and check_color(cube, 5, 2, 1) == "white"));
		delay();
		corners(cube);
		delay();
		do { second_layer(cube); } while (!second_layer_correct(cube));
		delay();
		top_cross(cube);
		delay();
		do { oll(cube); } while (!top_correct(cube));
		delay();
		//pll skip
		if ((top_layer_right(cube) and !is_solved(cube)) or is_solved(cube)) 
		{
			auf(cube); 
			if (is_solved(cube)) {
				auto end = high_resolution_clock::now();
				cout << "The Cube has been Solved" << endl;
				cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds" << endl;
				++numRight;
				delay();
				continue;
			}
			else
				cout << "Literally no idea... this option should never output" << endl;
		}
		//split into two parts
		//part one get headlights on f l and r faces and full bar on the b face
		//part two doing the U alg either once or twice as needed
		//also need to account for if there is an H perm situation
		pll(cube);
		if (top_layer_right(cube) and !is_solved(cube)) auf(cube);
		if (is_solved(cube)) {
			auto end = high_resolution_clock::now();
			cout << "The Cube has been Solved" << endl;
			cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end-start).count() << " milliseconds)" << endl;
			++numRight;
			delay();
		}
		else
		{
			auto end = high_resolution_clock::now();
			cout << "Not solved and idk what to do to solve it" << endl;
			cout << "Elapsed time = " << duration_cast<seconds>(end - start).count() << " seconds (" << duration_cast<milliseconds>(end - start).count() << " milliseconds)" << endl;
			++numWrong;
			delay();
		}
	}
	cout << "Testing complete: " << num_solves << " solves" << endl;
	cout << "Number of correct solves: " << numRight << endl;
	cout << "Number of incorrect solves: " << numWrong << endl;
	cout << "Percent corect = " << numRight << " / " << num_solves << " = " << (double)numRight / (double)num_solves;
}

bool top_correct(int cube[6][3][3])
{
	if (check_color(&cube[0][0][0]) == check_color(&cube[0][0][1]) and check_color(&cube[0][0][0]) == check_color(&cube[0][0][2]) and
		check_color(&cube[0][1][0]) == check_color(&cube[0][0][0]) and check_color(&cube[0][1][2]) == check_color(&cube[0][0][0]) and
		check_color(&cube[0][0][0]) == check_color(&cube[0][2][0]) and check_color(&cube[0][0][0]) == check_color(&cube[0][2][2]) and check_color(&cube[0][0][0]) == "yellow")
		return true;
	return false;
}

void oll(int cube[6][3][3])
{
	//23 HEADLIGHTS
	if (check_color(&cube[0][0][0]) == "yellow" and check_color(&cube[0][0][1]) == "yellow" and check_color(&cube[0][0][2]) == "yellow" and
		check_color(&cube[0][1][0]) == "yellow" and check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][1][2]) == "yellow" and
		check_color(&cube[0][2][1]) == "yellow" and check_color(&cube[0][2][0]) != "yellow" and check_color(&cube[0][2][2]) != "yellow" and
		check_color(&cube[2][0][0]) == "yellow" and check_color(&cube[2][0][2]) == "yellow")
	{
		//R R d rp u u r dp rp u u rp
		turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "D", true); turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Dp", true); turn_cube(cube, "Rp", true);
		turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true);
	}
	//T oll
	else if (check_color(&cube[0][2][0]) != "yellow" and check_color(&cube[0][0][0]) != "yellow" and check_color(&cube[0][0][2]) == "yellow" and
		check_color(&cube[0][2][2]) == "yellow" and check_color(&cube[2][0][0]) == "yellow" and check_color(&cube[4][0][2]) == "yellow")
	{
		//l f rp fp lp f r fp
		turn_cube(cube, "L", true); turn_cube(cube, "F", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true); turn_cube(cube, "Lp", true); turn_cube(cube, "F", true);
		turn_cube(cube, "R", true); turn_cube(cube, "Fp", true);
	}
	//BOWTIE
	else if (check_color(&cube[0][2][0]) == "yellow" and check_color(&cube[0][0][2]) == "yellow" and check_color(&cube[0][0][0]) != "yellow" and
		check_color(&cube[0][2][2]) != "yellow" and check_color(&cube[2][0][2]) == "yellow" and check_color(&cube[1][0][0]) == "yellow")
	{
		//Fp l f rp fp lp f r
		turn_cube(cube, "Fp", true); turn_cube(cube, "L", true); turn_cube(cube, "F", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true); turn_cube(cube, "Lp", true);
		turn_cube(cube, "F", true); turn_cube(cube, "R", true);
	}
	//pi
	else if (check_color(&cube[2][0][2]) == "yellow" and check_color(&cube[4][0][0]) == "yellow" and check_color(&cube[1][0][0]) == "yellow" and
		check_color(&cube[1][0][2]) == "yellow")
	{
		//R u u r r up r r up r r u u r
		turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true);
	}
	//H
	else if (check_color(&cube[2][0][0]) == "yellow" and check_color(&cube[2][0][2]) == "yellow" and check_color(&cube[4][0][0]) == "yellow" and
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
	else if (check_color(&cube[0][2][0]) == "yellow" and check_color(&cube[2][0][2]) == "yellow" and check_color(&cube[3][0][2]) == "yellow" and
		check_color(&cube[4][0][2]) == "yellow")
	{
		//r u rp u r u u rp
		turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true);
	}
	//anti sune
	else if (check_color(&cube[0][2][2]) == "yellow" and check_color(&cube[2][0][0]) == "yellow" and check_color(&cube[1][0][0]) == "yellow" and
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
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][1]) and check_color(&cube[1][0][0]) == check_color(&cube[1][0][2])) return true;
	else if (check_color(&cube[2][0][0]) == check_color(&cube[2][0][1]) and check_color(&cube[2][0][0]) == check_color(&cube[2][0][2])) return true;
	else if (check_color(&cube[3][0][0]) == check_color(&cube[3][0][1]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2])) return true;
	else if (check_color(&cube[4][0][0]) == check_color(&cube[4][0][1]) and check_color(&cube[4][0][0]) == check_color(&cube[4][0][2])) return true;
	else return false;
}

void pll(int cube[6][3][3])
{
	if (is_solved(cube))
		return;
	else if (!is_solved(cube))
	{
		for (int g = 0; g < 3; g++)
		{
			if (is_solved(cube)) { return; }
			else if (has_bar(cube) and check_color(&cube[2][0][0]) != check_color(&cube[2][0][1]) and check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) and check_color(&cube[3][0][0]) != check_color(&cube[3][0][1]) and check_color(&cube[4][0][0]) == check_color(&cube[4][0][1])) 
			{
				turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
				turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
				if (check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) and
					check_color(&cube[3][0][0]) != check_color(&cube[3][0][1])) {
					turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
					turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
				}
				delay();
				return;
			}
			turn_cube(cube, "U", true);
		}
	}
	//need to account for if alredy solved and ohly need u perm or ua perm
	//if top is h perm.  do u perm u u perm up and auf
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) and check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) and
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) and check_color(&cube[2][0][1]) == check_color(&cube[4][0][0]) and check_color(&cube[4][0][1]) == check_color(&cube[2][0][0]) and !has_bar(cube))
	{
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		turn_cube(cube, "U", true);
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		do { turn_cube(cube, "U", true); } while (!is_solved(cube));
		return;
	}
	else if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) and check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) and
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) and check_color(&cube[2][0][1]) != check_color(&cube[4][0][0]) and check_color(&cube[4][0][1]) != check_color(&cube[2][0][0]) and !has_bar(cube))
	{
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		do { turn_cube(cube, "U", true); } while (check_color(&cube[4][0][0]) != check_color(&cube[4][0][1]) and check_color(&cube[4][0][2]) != check_color(&cube[4][0][1]));
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		if (!is_solved(cube)) 
		{
			turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
			turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		}
		if (!is_solved(cube) and top_layer_right(cube))
		{
			auf(cube);
			if (is_solved(cube)) return;
		}
		/*
		for (int i = 0; i < 3; i++)
		{
			turn_cube(cube, "U", true);
			if (is_solved(cube)) {
				return;
			}
		}
		*/
	}
	//if top is z perm.  green or blue needs to be on [0][1] position on red face
	//then u perm.  turn so block is on orange side uperm .  if not solved another u perm and auf.
	//if no headlights just do t perm from any orientation
	if (check_color(&cube[2][0][0]) != check_color(&cube[2][0][2]) and
		check_color(&cube[3][0][0]) != check_color(&cube[3][0][2]) and
		check_color(&cube[4][0][0]) != check_color(&cube[4][0][2]) and
		check_color(&cube[1][0][0]) != check_color(&cube[1][0][2]))
	{
		turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true);
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true);
	}
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
	turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true);
	turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Fp", true);
	delay();
	if (is_solved(cube)) 
	{
		return;
	}
	else if (!is_solved(cube) and top_layer_right(cube))
	{
		auf(cube); if (is_solved(cube)) return;
	}
	if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) and check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) and
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) and check_color(&cube[2][0][1]) == check_color(&cube[4][0][0]) and check_color(&cube[4][0][1]) == check_color(&cube[2][0][0]) and !has_bar(cube))
	{
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		turn_cube(cube, "U", true);
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		if(!is_solved(cube) and top_layer_right(cube)) auf(cube);
		return;
	}
	else if (check_color(&cube[1][0][0]) == check_color(&cube[1][0][2]) and check_color(&cube[2][0][0]) == check_color(&cube[2][0][2]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2]) and
		check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]) and check_color(&cube[2][0][1]) != check_color(&cube[4][0][0]) and check_color(&cube[4][0][1]) != check_color(&cube[2][0][0]) and !has_bar(cube))
	{
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		do { turn_cube(cube, "U", true); } while (check_color(&cube[4][0][0]) != check_color(&cube[4][0][1]) and check_color(&cube[4][0][2]) != check_color(&cube[4][0][1]));
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		if (check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) and
			check_color(&cube[2][0][0]) != check_color(&cube[2][0][1]))
		{
			turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
			turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		}
		if(!is_solved(cube) and top_layer_right(cube)) auf(cube);
		return;
	}
	if (check_color(&cube[2][0][0]) == check_color(&cube[2][0][1]) and check_color(&cube[2][0][2]) == check_color(&cube[2][0][0])) {
		turn_cube(cube, "U", true); turn_cube(cube, "U", true);
	}
	else if(check_color(&cube[1][0][0]) == check_color(&cube[1][0][1]) and check_color(&cube[1][0][0]) == check_color(&cube[1][0][2])) { turn_cube(cube, "U", true); }
	else if (check_color(&cube[3][0][0]) == check_color(&cube[3][0][1]) and check_color(&cube[3][0][0]) == check_color(&cube[3][0][2])) { turn_cube(cube, "Up", true); }
	if (check_color(&cube[4][0][0]) == check_color(&cube[4][0][1]) and check_color(&cube[4][0][0]) == check_color(&cube[4][0][2]))
	{
		delay();
		//r up r u r u r up rp up r r
		turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
		turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		if (check_color(&cube[1][0][0]) != check_color(&cube[1][0][1]) and
			check_color(&cube[3][0][0]) != check_color(&cube[3][0][1])) {
			turn_cube(cube, "R", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "R", true); turn_cube(cube, "Up", true);
			turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "R", true); turn_cube(cube, "R", true);
		}
	}
}

void top_cross(int cube[6][3][3])
{
	//top dot shape
	if (check_color(&cube[0][0][1]) != "yellow" and check_color(&cube[0][1][0]) != "yellow" and check_color(&cube[0][1][2]) != "yellow" and check_color(&cube[0][2][1]) != "yellow")
	{
		turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
	}
	//top l shape
	if (check_color(&cube[0][1][0]) == "yellow" and check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][2][1]) == "yellow" and
		check_color(&cube[0][0][1]) != "yellow" and check_color(&cube[0][1][2]) != "yellow") turn_cube(cube, "U", true);
	else if(check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][1][2]) == "yellow" and check_color(&cube[0][2][1]) == "yellow" and 
		check_color(&cube[0][0][1]) != "yellow" and check_color(&cube[0][1][0]) != "yellow") {
		turn_cube(cube, "U", true); turn_cube(cube, "U", true);
	}
	else if(check_color(&cube[0][0][1]) == "yellow" and check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][1][2]) == "yellow" and
		check_color(&cube[0][1][0]) != "yellow" and check_color(&cube[0][2][1]) != "yellow") {
		turn_cube(cube, "Up", true);
	}
	if (check_color(&cube[0][1][0]) == "yellow" and check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][0][1]) == "yellow" and
	check_color(&cube[0][2][1]) != "yellow" and check_color(&cube[0][1][2]) != "yellow")
	{
		turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
	}
	//top bar
	if (check_color(&cube[0][0][1]) == "yellow" and check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][2][1]) == "yellow" and
		check_color(&cube[00][1][0]) != "yellow" and check_color(&cube[0][1][2]) != "yellow")
	{
		turn_cube(cube, "U", true); turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
		//f u r u rp up fp
	}
	else if (check_color(&cube[0][1][0]) == "yellow" and check_color(&cube[0][1][1]) == "yellow" and check_color(&cube[0][1][2]) == "yellow" and
		check_color(&cube[0][0][1]) != "yellow" and check_color(&cube[0][2][1]) != "yellow")
	{
		turn_cube(cube, "F", true); turn_cube(cube, "R", true); turn_cube(cube, "U", true); turn_cube(cube, "Rp", true); turn_cube(cube, "Up", true); turn_cube(cube, "Fp", true);
		//f r u rp up fp
	}
	
}

bool second_layer_correct(int cube[6][3][3])
{
	if (check_color(&cube[1][1][0]) == "blue" and check_color(&cube[1][1][2]) == "blue" and
		check_color(&cube[2][1][0]) == "red" and check_color(&cube[2][1][2]) == "red" and
		check_color(&cube[3][1][0]) == "green" and check_color(&cube[3][1][2]) == "green" and
		check_color(&cube[4][1][0]) == "orange" and check_color(&cube[4][1][2]) == "orange") 
		return true;
	return false;
}

void second_layer(int cube[6][3][3])
{
	bool g = true;
	int* ptr = &cube[0][0][1]; // top
	int* ptr2 = &cube[0][1][0]; //left
	int* ptr3 = &cube[0][1][2];
	int* ptr4 = &cube[0][2][1]; //right and bottom

	int* red = &cube[2][0][1]; int* blue = &cube[1][0][1]; int* orange = &cube[4][0][1]; int* green = &cube[3][0][1];
	if(check_color(cube, 0, 2, 1) == "green" and check_color(cube, 2, 0, 1) == "red") { turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g); 
	turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g);}
	if(check_color(cube, 0, 2, 1) == "blue" and check_color(cube, 2,0,1) == "red") { turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g);}
	if (check_color(cube, 0, 1, 0) == "red" and check_color(cube, 1, 0, 1) == "blue") {
		turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g);
	}
	if (check_color(cube, 0, 1, 2) == "red" and check_color(cube, 3, 0, 1) == "green") {
		turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g);
	}
	if(check_color(cube, 0, 1, 0) == "orange" and check_color(cube, 1, 0, 1) == "blue") {
		turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "U", g);
		turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g);
	}
	if(check_color(&cube[0][1][2]) == "orange" and check_color(&cube[3][0][1]) == "green") {
		turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); turn_cube(cube, "Up", g);
		turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g);
	}
	if(check_color(cube, 0, 0, 1) == "blue" and check_color(cube, 4, 0, 1) == "orange") {
		turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "Up", g);
		turn_cube(cube, "Bp", g); turn_cube(cube, "U", g); turn_cube(cube, "B", g);
	}
	if(check_color(&cube[0][0][1]) == "green" and check_color(&cube[4][0][1]) == "orange") {
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
	if (count >= 4 and !second_layer_correct(cube)){
		if (check_color(&cube[2][1][2]) != "red" or check_color(&cube[3][1][0]) != "green") {
			turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g);
			turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g);
		}
		else if (check_color(&cube[1][1][2]) != "blue" or check_color(&cube[2][1][0]) != "red") {
			turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g);
		}
		else if (check_color(&cube[3][1][2]) != "green" or check_color(&cube[4][1][0]) != "orange") {
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
	if(check_color(cube, 2, 1, 2) != "red" and check_color(cube, 3, 1, 0) != "green") {
		turn_cube(cube, "U", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g);
		turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g);
	}
	else if(check_color(cube, 2, 1, 0) != "red" and check_color(cube, 1, 1, 2) != "blue") { turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); }
	else if(check_color(cube, 3, 1, 2) != )
	*/
}

static bool white_on_top(int cube[6][3][3])
{
	if (check_color(&cube[1][0][0]) == "white" or check_color(&cube[1][0][2]) == "white" or check_color(&cube[2][0][0]) == "white" or check_color(&cube[2][0][2]) == "white" or check_color(&cube[3][0][0]) == "white" or
		check_color(&cube[3][0][2]) == "white" or check_color(&cube[4][0][0]) == "white" or check_color(&cube[4][0][2]) == "white" or check_color(&cube[0][0][0]) == "white" or
		check_color(&cube[0][0][2]) == "white" or check_color(&cube[0][2][0]) == "white" or check_color(&cube[0][2][2]) == "white")
		return true;
	return false;
}

void corners(int cube[6][3][3])
{
	bool g = true;

	//check if white is in bottom layer if it is being to top


	do {

		//white red green corner piece
		if (check_color(cube, 2, 0, 2) == "green" and check_color(cube, 0, 2, 2) == "white" and check_color(cube, 3, 0, 0) == "red") { turn_cube(cube, "R", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); turn_cube(cube, "Rp", g); turn_cube(cube, "Up", g); }
		if (check_color(cube, 2, 0, 2) == "white" and check_color(cube, 0, 2, 2) == "red" and check_color(cube, 3, 0, 0) == "green") { turn_cube(cube, "U", true); turn_cube(cube, "R", g); turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); }
		if (check_color(cube, 2, 0, 2) == "red" and check_color(cube, 0, 2, 2) == "green" and check_color(cube, 3, 0, 0) == "white") { turn_cube(cube, "R", g); turn_cube(cube, "U", g); turn_cube(cube, "Rp", g); }

		//white red blue corner
		if (check_color(cube, 0, 2, 0) == "white" and check_color(cube, 1, 0, 2) == "red" and check_color(cube, 2, 0, 0) == "blue") { turn_cube(cube, "F", g); turn_cube(cube, "Up", g); turn_cube(cube, "Fp", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); }
		if (check_color(cube, 0, 2, 0) == "red" and check_color(cube, 1, 0, 2) == "blue" and check_color(cube, 2, 0, 0) == "white") { turn_cube(cube, "F", g); turn_cube(cube, "U", g); turn_cube(cube, "Fp", g); }
		if (check_color(cube, 0, 2, 0) == "blue" and check_color(cube, 1, 0, 2) == "white" and check_color(cube, 2, 0, 0) == "red") { turn_cube(cube, "Lp", g); turn_cube(cube, "Up", g); turn_cube(cube, "L", g); }

		//white blue orange corner
		if (check_color(cube, 0, 0, 0) == "white" and check_color(cube, 1, 0, 0) == "orange" and check_color(cube, 4, 0, 2) == "blue") { turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); turn_cube(cube, "Lp", g); turn_cube(cube, "Up", g); }
		if (check_color(cube, 0, 0, 0) == "blue" and check_color(cube, 1, 0, 0) == "white" and check_color(cube, 4, 0, 2) == "orange") { turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "Lp", g); }
		if (check_color(cube, 0, 0, 0) == "orange" and check_color(cube, 1, 0, 0) == "blue" and check_color(cube, 4, 0, 2) == "white") { turn_cube(cube, "U", g); turn_cube(cube, "L", g); turn_cube(cube, "Up", g); turn_cube(cube, "Lp", g); }

		//white green orange corner 0 3 4
		if (check_color(cube, 0, 0, 2) == "white" and check_color(cube, 3, 0, 2) == "orange" and check_color(cube, 4, 0, 0) == "green") { turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); turn_cube(cube, "U", g); }
		if (check_color(cube, 0, 0, 2) == "green" and check_color(cube, 3, 0, 2) == "white" and check_color(cube, 4, 0, 0) == "orange") { turn_cube(cube, "U", g); turn_cube(cube, "B", g); turn_cube(cube, "Up", g); turn_cube(cube, "Bp", g); } //check
		if (check_color(cube, 0, 0, 2) == "orange" and check_color(cube, 3, 0, 2) == "green" and check_color(cube, 4, 0, 0) == "white") { turn_cube(cube, "Up", g); turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g); }
		//if there is a white piece in botom layer but is not oriented correctly, bring back into top layer to be inserted
		if (!white_on_top(cube))
		{
			if (check_color(cube, 5, 0, 0) == "white" or check_color(cube, 5, 0, 2) == "white" or check_color(cube, 5, 2, 0) == "white" or check_color(cube, 5, 2, 2) == "white" or
				check_color(&cube[1][2][0]) == "white" or check_color(&cube[1][2][2]) == "white" or check_color(&cube[2][2][0]) == "white" or check_color(&cube[2][2][2]) == "white" or
				check_color(&cube[3][2][0]) == "white" or check_color(&cube[3][2][2]) == "white" or check_color(&cube[4][2][0]) == "white" or check_color(&cube[4][2][2]) == "white") {
				if ((check_color(cube, 2, 2, 2) == "white" or check_color(cube, 3, 2, 0) == "white" or check_color(cube, 5, 0, 2) == "white") and (check_color(cube, 2, 2, 2) != "red" or check_color(cube, 3, 2, 0) != "green" or check_color(&cube[5][0][2]) != "white")) {
					turn_cube(cube, "R", g); turn_cube(cube, "U", g); turn_cube(cube, "Rp", g);
				}
				else if ((check_color(cube, 2, 2, 0) == "white" or check_color(cube, 1, 2, 2) == "white" or check_color(cube, 5, 0, 0) == "white") and (check_color(cube, 2, 2, 0) != "red" or check_color(cube, 1, 2, 2) != "blue" or check_color(&cube[5][0][0]) != "white")) {
					turn_cube(cube, "Lp", g); turn_cube(cube, "U", g); turn_cube(cube, "L", g);
				}
				else if ((check_color(cube, 1, 2, 0) == "white" or check_color(cube, 4, 2, 2) == "white" or check_color(cube, 5, 2, 0) == "white") and (check_color(cube, 1, 2, 0) != "blue" or check_color(cube, 4, 2, 2) != "orange" or check_color(&cube[5][2][0]) != "white")) {
					turn_cube(cube, "L", g); turn_cube(cube, "U", g); turn_cube(cube, "Lp", g);
				}
				else if ((check_color(cube, 3, 2, 2) == "white" or check_color(cube, 4, 2, 0) == "white" or check_color(cube, 5, 2, 2) == "white") and (check_color(cube, 3, 2, 2) != "green" or check_color(cube, 4, 2, 0) != "orange" or check_color(&cube[5][2][2]) != "white")) {
					turn_cube(cube, "Rp", g); turn_cube(cube, "U", g); turn_cube(cube, "R", g);
				}
			}
		}
		turn_cube(cube, "U", true);
	} while (!(check_color(cube, 5, 0, 0) == "white" and check_color(cube, 5, 0, 2) == "white" and check_color(cube, 5, 2, 0) == "white" and check_color(cube, 5, 2, 2) == "white" and check_color(&cube[2][2][0]) == "red" and check_color(&cube[2][2][2]) == "red" and
			   check_color(&cube[1][2][0]) == "blue" and check_color(&cube[1][2][2]) == "blue" and check_color(&cube[3][2][0]) == "green" and check_color(&cube[3][2][2]) == "green" and check_color(&cube[4][2][0]) == "orange" and check_color(&cube[4][2][2]) == "orange"));
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
	if (check_color(cube, 5, 0, 1) == "white" and check_color(cube, 2, 2, 1) != "red") { turn_cube(cube, "F", t); turn_cube(cube, "F", t); }
	else if (check_color(cube, 5, 1, 0) == "white" and check_color(cube, 1, 2, 1) != "blue") { turn_cube(cube, "L", t); turn_cube(cube, "L", t); }
	else if (check_color(cube, 5, 1, 2) == "white" and check_color(cube, 3, 2, 1) != "green") { turn_cube(cube, "R", t); turn_cube(cube, "R", t); }
	else if (check_color(cube, 5, 2, 1) == "white" and check_color(cube, 4, 2, 1) != "orange") { turn_cube(cube, "B", t); turn_cube(cube, "B", t); }
}

void delay()
{
	for (int i = 0; i < 100000000; i++)
		for (int j = 0; j < 20; j += 2);
	return;
}

void play(int cube[6][3][3])
{
	string move;
	do 
	{
		cout << "Enter in your move or 'q' to quit: ";
		cin >> move;
		while (move != "q" and move != "Q" and !valid_move(move))
		{
			cout << "Invalid move... try again" << endl;
			cin >> move;
		}
		turn_cube(cube, move, true);
		if (is_solved(cube)) {
			cout << "CONGRATS! NICE! AWESOME! 11/10 " << endl;
			return;
		}
	} while (move != "Q" and move != "q");

}

bool valid_move(string move)
{
	if (move != "R" and move != "Rp" and move != "L" and move != "Lp" and
		move != "U" and move != "Up" and move != "D" and move != "Dp" and
		move != "B" and move != "Bp" and move != "F" and move != "Fp")
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
	cout << "1. Randomly Scramble the Cube" << endl;
	cout << "2. Solve the cube yourself" << endl;
	cout << "3. Upload a custom scramble" << endl;
	cout << "4. Load a custom solution " << endl;
	cout << "5. Ai cube solve" << endl;
	cout << "6. cheecky Ai cube solve" << endl;
	cout << "7. Quit" << endl;
	cout << "Enter in a choice: "; cin >> choice;
	while (choice != 1 and choice != 2 and choice != 3 and choice != 4 and choice != 5 and choice != 6 and choice != 7) {
		cout << "Invalid menu choice, try again" << endl;  
		cout << "Enter in a choice: "; 
		cin >> choice;
	}
	return choice;
}


void turn_cube(int cube[6][3][3], string temp, bool yea)
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
	cout << "One " << temp << " rotation" << endl;
	if(yea) print(cube);
	cout << endl;
}

void load_scramble(int cube[6][3][3], ifstream& is)
{
	string filename = "", temp = "";
	cout << "Enter in the filename: ";
	cin >> filename;
	is.open(filename);
	if (is.is_open()) 
		is.clear();
	if (is.fail()) {
		cout << "Error loading file..." << endl;
		return;
	}
	while (is >> temp)
	{
		turn_cube(cube, temp, false);
	}
	is.close();
}

static string opp(string a)
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

string random_scramble(int cube[6][3][3], int scramble_size, ofstream& os)
{
	string scramble = "", temp = "";
	string reverse_scramble = "";
	vector<string> vect2;
	os.open("test.txt");
	if (os.is_open()) {
		os.clear();
	}
	else {
		cout << "Error opening file... test.txt" << endl;
		return "~";
	}
	vector<string> vect = { "R", "Rp", "U", "Up", "L", "Lp", "F", "Fp", "D", "Dp", "B", "Bp" };
	int random = 0;
	srand(time(NULL));
	for (int i = 0; i < scramble_size; i++)
	{
		random = rand() % 12;
		scramble += vect.at(random);
		scramble += " ";
		vect2.insert(vect2.begin(), opp(vect.at(random)));
	}
	istringstream iss(scramble);
	while (iss >> temp)
	{
		turn_cube(cube, temp, false);
		os << temp << " ";
	}
	os << "\n# of turns in scramble: " << scramble_size << "\n";
	os.close();
	vector<string>::iterator begin = vect2.begin();
	vector<string>::iterator end = vect2.end();
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
	cout << "# of turns in scramble: " << scramble_size << endl;
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
	const char* colors[8] = { RESET, RED, GREEN, YELLOW, BLUE, WHITE, GREEN, ORANGE };
	int color = 0;
	//YELLOW FACE
	for (int i = 0; i <= 2; i++)
	{
		cout << "         ";
		for (int e = 0; e <= 2; e++)
		{
			//asigns each number to its respective color
			if (cube[0][i][e] >= 0 and cube[0][i][e] <= 8) color = 3;
			else if (cube[0][i][e] >= 9 and cube[0][i][e] <= 17) color = 4;
			else if (cube[0][i][e] >= 18 and cube[0][i][e] <= 26) color = 1;
			else if (cube[0][i][e] >= 27 and cube[0][i][e] <= 35) color = 6;
			else if (cube[0][i][e] >= 36 and cube[0][i][e] <= 44) color = 7;
			else if (cube[0][i][e] >= 45 and cube[0][i][e] <= 53) color = 5;
			if (cube[0][i][e] < 9) cout << colors[3] << "0";
			else if (cube[0][i][e] == 9) cout << colors[4] << "0";
			cout << colors[color] << cube[0][i][e] << " " << RESET;
		}
		cout << endl;
	}
	cout << endl;
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
				if (cube[q][j][p] >= 0 and cube[q][j][p] <= 8) color = 3;
				else if (cube[q][j][p] >= 9 and cube[q][j][p] <= 17) color = 4;
				else if (cube[q][j][p] >= 18 and cube[q][j][p] <= 26) color = 1;
				else if (cube[q][j][p] >= 27 and cube[q][j][p] <= 35) color = 6;
				else if (cube[q][j][p] >= 36 and cube[q][j][p] <= 44) color = 7;
				else if (cube[q][j][p] >= 45 and cube[q][j][p] <= 53) color = 5;
				if (cube[q][j][p] < 10) cout << colors[color] << "0";
				cout << colors[color] << cube[q][j][p] << " " << RESET;
			}
		}
		cout << endl;
	}
	cout << endl;
	for (int k = 0; k <= 2; k++)
	{
		cout << "         ";
		for (int a = 0; a <= 2; a++)
		{
			if (cube[5][k][a] >= 0 and cube[5][k][a] <= 8) color = 3;
			else if (cube[5][k][a] >= 9 and cube[5][k][a] <= 17) color = 4;
			else if (cube[5][k][a] >= 18 and cube[5][k][a] <= 26) color = 1;
			else if (cube[5][k][a] >= 27 and cube[5][k][a] <= 35) color = 6;
			else if (cube[5][k][a] >= 36 and cube[5][k][a] <= 44) color = 7;
			else if (cube[5][k][a] >= 45 and cube[5][k][a] <= 53) color = 5;
			if (cube[5][k][a] < 10) cout << colors[color] << "0";
			cout << colors[color] << cube[5][k][a] << " " << RESET;
		}
		cout << endl;
	}
}