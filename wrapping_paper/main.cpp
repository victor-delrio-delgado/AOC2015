#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

#include "../read_input_lib/read_input_functions.h"

vector<int> split_each_input_in_several_dimensions(string & raw_string_with_dimensions_and_exes);


class Present{

public:

    // int shape_multiplicator;
    // string shape;

    // Initialize as 0 so every time that I call the class there is no stacking
    vector<int> side_areas;
    vector<int> perimeters;
    int volume = 1;
    int wrapping_gift_area = 0;
    int ribbon_length = 0;
    int number_of_used_different_areas = 0;

    // void determine_shape_multiplicator(string& shape_in)
    // {
    //     cout << "Shape of the gift: " << shape_in << endl;
    //     shape = shape_in;
    //     if (shape == "rectangular"){
    //         shape_multiplicator = 2;
    //         number_of_used_different_areas = 3;
    //     }
    // }
    int calculate_wrapping_gift_area(vector<int> side_lengths, bool test_mode)
    {
        
        number_of_used_different_areas = side_lengths.size();
        for (int i = 0; i < number_of_used_different_areas; i++) {
            for (int j = 0; j < number_of_used_different_areas; j++) {
                if (i != j) { // Ensure we do not multiply an element by itself
                    perimeters.push_back(side_lengths[i]*2 + side_lengths[j]*2);
                    side_areas.push_back(side_lengths[i] * side_lengths[j]);
                }
            }
            volume = volume * side_lengths[i];
        }

        int smallest_area = side_areas[0];
        int sum_areas = 0;
        for (const int& area : side_areas) {
            // cout << "Area of one side: " << area << endl;
            if (area < smallest_area){
                smallest_area = area;
            }
            sum_areas += area;
        }

        int smallest_perimeter = perimeters[0];
        for (const int& perimeter : perimeters) {
            //cout << "Perimeter of one side: " << area << endl;
            if (perimeter < smallest_perimeter){
                smallest_perimeter = perimeter;
            }
        }

        wrapping_gift_area = smallest_area + sum_areas + smallest_perimeter + volume;
        ribbon_length = smallest_perimeter + volume;

        if (test_mode){
            cout << "Sum of areas: " << sum_areas << endl;
            cout << "Smallest area: " << smallest_area << endl;
            cout << "Ribbon - wrap around: " << smallest_perimeter << endl;
            cout << "Ribbon - bow: " << volume << endl;

            cout << "Final wrapping area: " << wrapping_gift_area << endl;
            cout << "Final ribbon_length: " << ribbon_length << endl;
        }
    }
};


vector<vector<int>> process_input_and_split_in_dimension_vector(vector<string> & file_as_vector_of_lines){

    vector<int> vector_of_dimensions;
    vector<vector<int>> vector_with_dimensions_of_all_gifts;
    vector_with_dimensions_of_all_gifts.reserve(file_as_vector_of_lines.size());

    //for (const auto & line: file_as_vector_of_lines){
    for (string & line: file_as_vector_of_lines){
        vector_of_dimensions = split_each_input_in_several_dimensions(line);
        vector_with_dimensions_of_all_gifts.emplace_back(vector_of_dimensions);
    }

    return vector_with_dimensions_of_all_gifts;
};


vector<int> split_each_input_in_several_dimensions(string & raw_string_with_dimensions_and_exes){
    char separator = 'x';
    string temp_captured;
    int temp_captured_int;
    stringstream ss(raw_string_with_dimensions_and_exes);
    vector<int> vector_of_dimensions;
    vector_of_dimensions.reserve(raw_string_with_dimensions_and_exes.length());

    while (getline(ss, temp_captured, separator)){
        temp_captured_int = std::stoi(temp_captured);
        vector_of_dimensions.emplace_back(temp_captured_int);
        //cout << "Dimension: " <<temp_captured << endl;
    }

    return vector_of_dimensions;
};


vector<Present> initialize_all_presents(vector<string>& file_as_vector_of_lines){
    int number_of_presents = file_as_vector_of_lines.size();
    Present vector_of_presents[2];
    Present iterable_present;
    vector<int> iterable_dimension;

    for (string & line: file_as_vector_of_lines){

        iterable_dimension.clear();
    }

};


int main(){
    /* =====================
     Read wrapping items
     =======================*/
    string filePath = "wrapping_paper/input.txt";
    vector<string> file_as_vector_of_lines = readFile_as_vector(filePath);
    check_not_empty_vector(file_as_vector_of_lines);

    /* =====================
     Pre process input instruction
     =======================*/
    vector<vector<int>> vector_with_dimensions_of_all_gifts;
    vector_with_dimensions_of_all_gifts = process_input_and_split_in_dimension_vector(file_as_vector_of_lines);
    cout << "Size vector_with_dimensions_of_all_gifts: " << vector_with_dimensions_of_all_gifts.size() << endl;

    /* =====================
     Calculate wrapping gift areas
     =======================*/
    
    int total_wrapping_area = 0;
    int total_ribbon_length = 0;
    /*Unit test - Proposed inputs*/
    for (vector<int> & dimensions : vector<vector<int>> {{2, 3, 4}, {1, 1, 10}}){
        cout << "_____ Unit test _____ " << endl;
        Present object_iterator_unit_test;
        object_iterator_unit_test.calculate_wrapping_gift_area(dimensions, true);
        cout << "wrapping area present: " << object_iterator_unit_test.wrapping_gift_area << endl;
        total_wrapping_area += object_iterator_unit_test.wrapping_gift_area;

    }
    cout << "Total wrapping area sum: " << total_wrapping_area << endl;
    cout << "__________ " << endl;
    total_wrapping_area = 0;
    total_ribbon_length = 0;
    /**/
    /*Unit test - Dimensions of first gift*/
    cout << "_____ Unit test _____ " << endl;
    vector<int> unit_test_first_dimension = vector_with_dimensions_of_all_gifts[0];
    for (int & dimension: unit_test_first_dimension){
        cout << "dimension_unit_test: " << dimension << endl;
    }
    cout << "__________ " << endl;
    /**/


    // With this approach, I will create X objects of present, rather than use present object as a present-calculator object.
    for (vector<int> & dimensions : vector_with_dimensions_of_all_gifts){
        Present object_iterator;
        object_iterator.calculate_wrapping_gift_area(dimensions, false);
        total_wrapping_area += object_iterator.wrapping_gift_area;
        total_ribbon_length += object_iterator.ribbon_length;
    }
    cout << "Total wrapping area: " << total_wrapping_area << endl;
    cout << "Total ribbon length: " << total_ribbon_length << endl;
    return 0;
}

