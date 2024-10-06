#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// read_input_functions.h
#ifndef READ_INPUT_FUNCTIONS_H
#define FREAD_INPUT_UNCTIONS_H

// Function declarations
vector<string> readFile_as_vector(const string& filePath);
string readFile_as_string(const string& filePath);
void check_not_empty_vector(vector<string>& vector_of_lines);
void check_not_empty_single_string(string& file_as_string);

#endif // READ_INPUT_FUNCTIONS_H