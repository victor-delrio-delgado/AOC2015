#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <utility>

#include "Core/read_input_functions.h"

using namespace std;

struct Command {
	string action;
	pair<int, int>  coordinate_1;
	pair<int, int>  coordinate_2;
};


class GridOfLights_100x100 {
	vector<vector<int>> grid_2d;

public:
	GridOfLights_100x100(); // Constructor
	void update_grid_lights_first_criteria(Command& command);
	void update_grid_lights_second_criteria(Command& command);
	void print_number_of_lit_lights();
	void print_intensity_of_light();
};

GridOfLights_100x100::GridOfLights_100x100() : grid_2d(1000, std::vector<int>(1000, 0)) {   // Question: why an array declaration caused stack overflow and this did not?
	// Initializes a 1000x1000 grid with all elements set to 0
}


void GridOfLights_100x100::update_grid_lights_first_criteria(Command& command)
{
	int start_x = command.coordinate_1.first;
	int start_y = command.coordinate_1.second;
	int end_x = command.coordinate_2.first;
	int end_y = command.coordinate_2.second;

	for (int i_start_x = start_x; i_start_x < end_x + 1; ++i_start_x)
	{
		for (int i_start_y = start_y; i_start_y < end_y + 1; ++i_start_y) // Fix here
		{
			if (command.action == "turn off ")
			{
				grid_2d[i_start_x][i_start_y] = 0;
			}
			else if (command.action == "turn on ")
			{
				grid_2d[i_start_x][i_start_y] = 1;
			}
			else if (command.action == "toggle ")
			{
				grid_2d[i_start_x][i_start_y] = 1 - grid_2d[i_start_x][i_start_y];
			}
		}
	}
}

void GridOfLights_100x100::update_grid_lights_second_criteria(Command& command)
{
	int start_x = command.coordinate_1.first;
	int start_y = command.coordinate_1.second;
	int end_x = command.coordinate_2.first;
	int end_y = command.coordinate_2.second;

	for (int i_start_x = start_x; i_start_x < end_x + 1; ++i_start_x)
	{
		for (int i_start_y = start_y; i_start_y < end_y + 1; ++i_start_y) // Fix here
		{
			if (command.action == "turn off ")
			{
				if (grid_2d[i_start_x][i_start_y] > 0) 
				{
					grid_2d[i_start_x][i_start_y] = grid_2d[i_start_x][i_start_y] - 1;
				}
			}
			else if (command.action == "turn on ")
			{
				++grid_2d[i_start_x][i_start_y];
			}
			else if (command.action == "toggle ")
			{
				grid_2d[i_start_x][i_start_y] = grid_2d[i_start_x][i_start_y] + 2;
			}
		}
	}
}

void GridOfLights_100x100::print_number_of_lit_lights()
{
	int lit_lights = 0;
	for (int i_start_x = 0; i_start_x < 1000; ++i_start_x) // Change 999 to 1000
	{
		for (int i_start_y = 0; i_start_y < 1000; ++i_start_y) // Change 999 to 1000
		{
			if (grid_2d[i_start_x][i_start_y] == 1) // Use '==' for comparison
			{
				++lit_lights;
			}
		}
	}
	cout << "Number of lit lights: " << lit_lights << endl;
}

void GridOfLights_100x100::print_intensity_of_light()
{
	int total_intensity = 0;
	for (int i_start_x = 0; i_start_x < 1000; ++i_start_x) // Change 999 to 1000
	{
		for (int i_start_y = 0; i_start_y < 1000; ++i_start_y) // Change 999 to 1000
		{
			total_intensity += grid_2d[i_start_x][i_start_y];
		}
	}
	cout << "Total intensity of lights: " << total_intensity << endl;
}


static void parse_string(string& instruction, Command& command){
	static const string str2 = " through ";
	static vector<string> strs1 = { "turn off " , "toggle ", "turn on "};   // Question: why did I need to remove the const. You cannot iterate over a const?
	static const string empty_string = "";
	static const string comma_separator = ",";

	size_t position_of_next_number_as_string;
	string action;
	for (string& str1 : strs1)
	{
		position_of_next_number_as_string = instruction.find(str1);
		if (position_of_next_number_as_string != string::npos) {
			instruction.replace(position_of_next_number_as_string, str1.length(), empty_string);
			action = str1;
		}
	}

	position_of_next_number_as_string = instruction.find(str2);
	instruction.replace(position_of_next_number_as_string, str2.length(), comma_separator); // Method to learn!

	string next_number_as_string;
	int next_number;
	vector<int> points;
	points.reserve(4);
	for (int i = 0; i < 4; ++i)
	{
		position_of_next_number_as_string = instruction.find(comma_separator);
		next_number_as_string = instruction.substr(0, position_of_next_number_as_string);
		instruction.replace(0, comma_separator.length() + next_number_as_string.length(), empty_string);
		next_number = stoi(next_number_as_string);   // Method to learn!
		points.push_back(next_number);
	}

	// Method!
	command.action = action;
	command.coordinate_1 = pair<int, int> (points[0], points[1]);
	command.coordinate_2 = pair<int, int> (points[2], points[3]);
}


int main()
{
	string filePath = "C:/Users/vikto/c_projects/AC2015/App/Source/input_day6.txt";
	vector<string> file_as_vector = readFile_as_vector(filePath);
	check_not_empty_vector(file_as_vector);

	GridOfLights_100x100 grid_first_criteria;
	GridOfLights_100x100 grid_second_criteria;

	for (string& s: file_as_vector){
		Command command;
		parse_string(s, command);
		grid_first_criteria.update_grid_lights_first_criteria(command);
		grid_second_criteria.update_grid_lights_second_criteria(command);
	}
	grid_first_criteria.print_number_of_lit_lights();
	grid_second_criteria.print_intensity_of_light();
}
