#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "read_input_functions.h"

vector<string> readFile_as_vector(const string& filePath){
    string line;
    vector<string> lines;

    ifstream file(filePath);
    if (!file){
        cout << "Could not open file: " << filePath << endl;
        return lines;
    }
    while (getline(file, line)){
        lines.push_back(line);
    }
    return lines;
}

string readFile_as_string(const string& filePath) {
    ifstream file(filePath);
    if (!file) {
        cerr << "File could not be opened!: " << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}


void check_not_empty_vector(vector<string>& vector_of_lines){
    if (!vector_of_lines.empty()){
        cout << "Number of string rows in input file: " << vector_of_lines.size() << endl;
        // for (auto& line:vector_of_lines){
        //     cout << line << endl;
        // }
    }
    else {
        cerr << "Empty file" << endl;
    }
}

void check_not_empty_single_string(string& file_as_string){
    int file_size = 0;
    if (!file_as_string.empty()){
        cout << "Size_of_string uing sizeof (prints size of memory, as this is a pointer): " << sizeof(file_as_string) << endl;
        cout << "Size_of_string first position (we access via [0], so we are entering the actual pointer): " << sizeof(file_as_string[0]) << endl;
        for (char c : file_as_string){  //Null terminator not included
            ++file_size;
        }
        cout << "Size_of_string first as a whole (.length()) (without null terminator): " << file_as_string.length() << endl;
        cout << "Size_of_string first as a whole (using for loop and a counter) (without null terminator): " << file_size << endl;
    }
    else {
        cerr << "Empty file" << endl;
    }
}
