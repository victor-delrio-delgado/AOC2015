#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "read_input_functions.h"


void floor_movement(string& floor_instructions, int& final_floor, int& first_basement_instruction, int first_instruction_n, int basement_location){
    
    char up_direction = '(';
    char down_direcion= ')';
    bool basement_already_reached = false;
    int correction_indexes = 1;

    for (int n = first_instruction_n - correction_indexes; n < floor_instructions.length(); n++){

        if (floor_instructions[n] == up_direction){
            ++final_floor;
        }
        else if (floor_instructions[n] == down_direcion)
        {
            --final_floor;
        }

        if (final_floor == basement_location & !basement_already_reached){
            first_basement_instruction = n + correction_indexes;
            basement_already_reached = true;
        }
    }
}


int main(){

    /* =====================
     Read floor instructions
     =======================*/
    string filePath = "input.txt";
    vector<string> file_as_vector_of_lines = readFile_as_vector(filePath);
    //check_not_empty_vector(file_as_vector_of_lines);
    string file_as_string = readFile_as_string(filePath);
    check_not_empty_single_string(file_as_string);

    /* =====================
     Calculate floor instructions
     =======================*/
    int initial_floor = 0;
    int basement_location = -1;
    int first_instruction_n = 1;

    int final_floor = initial_floor;
    int first_basement_instruction = first_instruction_n;
    floor_movement(file_as_string, final_floor, first_basement_instruction, first_instruction_n, basement_location);
    cout << "Target floor: " << final_floor << endl;
    cout << "Firt basement instruction: " << first_basement_instruction << endl;
    
    return 0;
}

