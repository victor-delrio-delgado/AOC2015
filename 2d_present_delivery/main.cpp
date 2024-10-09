#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <utility>
using namespace std;

#include "../read_input_lib/read_input_functions.h"

#define UP '^'
#define DOWN 'v'
#define RIGHT '>'
#define LEFT '<'


int check_if_pair_already_exists(pair<int, int> & coordinate, vector<pair<int, int>> & combination_vector_unique){
    int i = 0;
    for (pair<int, int> & unique_coordinate: combination_vector_unique){
        if (unique_coordinate == coordinate){
            return i;
        }
        ++i;
    }
    return -1;
}


int analyze_trayectory(vector<pair<int, int>> & combination_vector_raw, vector<pair<int, int>> & combination_vector_unique, vector<int> & count){

    size_t number_of_total_destinations = combination_vector_raw.size();
    combination_vector_unique.reserve(number_of_total_destinations); // Reserve space estimation (max possible) for efficiency
    count.reserve(number_of_total_destinations);                     // Reserve space estimation (max possible) for efficiency

    int i;
    for (pair<int, int> & coordinate: combination_vector_raw){
        i = check_if_pair_already_exists(coordinate, combination_vector_unique);
        if (i == -1){                                                           // Pair does not exist in vector of uniques
            combination_vector_unique.push_back(coordinate);
            count.push_back(1);
        }
        else{                                                                   // Pair exists and we increase counter in the same index where it was found
            count[i] = count[i] + 1;
        }
    }

    cout <<  "Number of coordinates: "        << combination_vector_raw.size() <<endl;
    cout <<  "Number of unique coordinates: " << combination_vector_unique.size() <<endl;
    cout <<  "Number of elements in count: "  << count.size() <<endl;
    return combination_vector_unique.size();
}


vector<pair<int, int>> merge_trayectories(vector<vector<pair<int, int>>> & several_trayectories){
    cout << "number of trayectories to merge: " << several_trayectories.size() << endl;
    vector<pair<int, int>> merged_trayectories;

    int expected_size = 0;
    for (int i; i<several_trayectories.size(); i++){
        expected_size += several_trayectories[i].size();
    }
    cout << "sum of raw positions in all trayectories: " << expected_size << endl;
    merged_trayectories.reserve(expected_size);

    int i;
    for (vector<pair<int, int>> & individual_trayectory: several_trayectories){
        if (i==0){
            merged_trayectories = individual_trayectory;
        }
        else{
            merged_trayectories.insert(merged_trayectories.end(), individual_trayectory.begin(), individual_trayectory.end());
        }
    }
    cout << "final number of positions in the merged trayectory: " << merged_trayectories.size() << endl;
    return merged_trayectories;
}


class Deliverer{
private:
    int x = 0, y = 0;
    vector<pair<int, int>> combination_vector_raw;
    vector<pair<int, int>> combination_vector_unique;
    vector<int> count;
    string name_of_the_deliverer;

    void move_two_d(const char instruction){
        if (instruction == UP){
            ++y;
        }
        else if (instruction == DOWN){
            --y;
        }
        else if (instruction== RIGHT){
            ++x;
        }
        else if (instruction == LEFT){
            --x;
        }
        else{
        }
    }

    void store_coordinates(){
        combination_vector_raw.push_back({x, y});
    }


public:

    void process_new_instruction(const char c){
        move_two_d(c);
        store_coordinates();
    }

    void analyze_results(){
        cout << "\n" << name_of_the_deliverer << ": " << endl;
        int res = analyze_trayectory(combination_vector_raw, combination_vector_unique, count);
    }

    vector<pair<int, int>> get_raw_trayectory(){
        return combination_vector_raw;
    }

    Deliverer(string& move_instructions, string name_of_the_deliverer){
        combination_vector_raw.reserve(move_instructions.size());
        combination_vector_raw.push_back({x, y});
        this->name_of_the_deliverer = name_of_the_deliverer;
    }
};



int simulate_delivery(string & instructions){

    Deliverer Santa  = Deliverer(instructions, "Santa");
    Deliverer Pinche = Deliverer(instructions, "Pinche");
    int alternator = 0;
    for (const char & c: instructions){
        if (alternator % 2 == 0){
            Santa.process_new_instruction(c);
        }
        else{
            Pinche.process_new_instruction(c);
        }
        ++alternator;
    }
    Santa.analyze_results();
    Pinche.analyze_results();
    vector<vector<pair<int, int>>> several_trayectories;
    several_trayectories.reserve(2);
    several_trayectories.push_back(Santa.get_raw_trayectory());
    several_trayectories.push_back(Pinche.get_raw_trayectory());

    cout << "\n" << "SANTA Y SUS PINCHES" << ": " << endl;
    vector<pair<int, int>> merged_trayectories = merge_trayectories(several_trayectories);
    vector<pair<int, int>> trayectories_unique;
    vector<int> count_of_presents_in_each_coordinate;
    int res = analyze_trayectory(merged_trayectories, trayectories_unique, count_of_presents_in_each_coordinate);
    return res;
}


int main(){

    /* =====================
     Read floor instructions
     =======================*/
    string filePath = "2d_present_delivery/input.txt";
    string file_as_string = readFile_as_string(filePath);
    check_not_empty_single_string(file_as_string);

    /* =====================
     Calculate 2D movement
     =======================*/
    
    vector<int> expected_results = {3, 3, 11};
    vector<string> sanity_checks = {"^v", "^>v<", "^v^v^v^v^v"};
    for (int i = 0; i<expected_results.size(); i++){
        cout << "\n\n" << "___ "  << "Test " << i << "___ " << endl;
        string instructions = sanity_checks[i];
        int result = simulate_delivery(instructions);
        if (result == expected_results[i]){
            cout << "Test " << i << " passes" << endl;
        }
        else{
            cout << "Test " << i << " fails" << endl;
        }
    }

    cout << "\n""\n""\n" << "____ACTUAL REAL DEAL_____" << endl;

    string instructions = file_as_string;
    int result = simulate_delivery(instructions);

    return 0;
}

