#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <utility>

#include "Core/read_input_functions.h"

using namespace std;

/*
char*: This part indicates a pointer to a char. In the context of strings, char* is used to represent a C-style string 
(a null-terminated array of characters).

(&arr): This indicates that the parameter is a reference to the array arr. 
By using a reference, the function can work directly with the original array, not a copy of it. 
This is important because passing large arrays by value can be inefficient, as it involves copying the entire array.

[3]: This part indicates that arr is an array of exactly 3 elements. 
The compiler needs to know the size of the array at compile time when you pass arrays by reference. 
Here, the array contains 3 pointers to char.
*/

/*
bool vowel_analyzer(string& row, char* arr[], int size) {  // Passing array as a pointer and size separately
	Arr has been decayed from array of pointers to char** (pointer to first element) 
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << endl;
    }
}
*/

bool vowel_analyzer(string& row, const char* (&vowels_array)[5]) {  // Passing array as a pointer and size separately
	int size_of_possible_vowels = sizeof(vowels_array)/sizeof(vowels_array[0]);   // Esta operacion de memoria se hace frente a pointers, con lo que aseguramos constancia con strings de diferente longitud
	vector<int> vector_of_counters(size_of_possible_vowels, 0);

	for (int i = 0; i < size_of_possible_vowels; ++i) {
		for (char& c: row){
			if (c == *vowels_array[i]){
				vector_of_counters.at(i) = vector_of_counters[i] + 1;
			}
		}
    }

	int total_counter = 0;
	for (int& counter: vector_of_counters){
		total_counter += counter;
		if (total_counter >= 3) {
			return true;
		}
	}
	return false;
}


static bool bad_substring_analyzer(string& row, const char* bad_strings_array[], int size_of_possible_bad_words){
	// bad_strings_array is a degraded const char* []  --> *bad_strings_array  --> pointer to first memory location
	for (int i = 0; i < size_of_possible_bad_words; ++i)
	{
		if (row.find(*(bad_strings_array + i)) != string::npos) 
		{
			return false;
		}	
    }
	return true;
}


bool two_characters_in_a_row(string& row)
{
	char previous_character = '\0';
	for (char& c: row){
		if (c == previous_character){
			return true;
		}
		previous_character = c;
	}
	return false;
}


bool pair_appears_twice(string& row)
{
	vector<string> couples_even_numbers;
	couples_even_numbers.reserve(row.size() / 2 + 1);
	vector<string> couples_odd_numbers;
	couples_odd_numbers.reserve(row.size() / 2 + 1);

	// Get each set of 2
	int counter = 0;
	char character_buffer;  // Individual characters, not strings, so I can modify them
	string new_pair_temp;
	for (char& c: row)
	{
		if (counter > 0)
		{
			new_pair_temp = string(1, character_buffer) + c;
			if (counter % 2 == 0)
			{
				couples_even_numbers.push_back(new_pair_temp);
			}
			else 
			{
				couples_odd_numbers.push_back(new_pair_temp);
			}
		}
		character_buffer = c;
		++counter;
	}

	// We will create a full list of pairs but deleting concatenations
	vector<string> all_valid_couples;
	counter = 0;
	for (string s: couples_odd_numbers)
	{
		if (counter <= couples_even_numbers.size() - 1)
		{
			if (s != couples_even_numbers[counter])
			{
				all_valid_couples.push_back(s);
				all_valid_couples.push_back(couples_even_numbers[counter]);
			}
		}
		++counter;
	}

	// Identify if there are repetitions
	int i = 0;
	int j = 0;
	for (string s1: all_valid_couples)
	{
		for (string s2: all_valid_couples)
		{
			if (i != j)
			{
				if (s1 == s2)
				{
					return true;
				}
			}
			++j;
		}
		j = 0;
		++i;
	}
	return false;
}


bool letters_repeated_with_one_in_the_middle(string& row)
{
	char character_buffer[2];
	string new_pair_temp;
	int counter = 0;
	for (char& c: row)
	{
		if (counter > 1)
		{
			if (character_buffer[1] == c)
			{
				return true;
			}
		}
		if (counter > 0)
		{
			character_buffer[1] = character_buffer[0];			
		}
		character_buffer[0] = c;
		++counter;
	}	
	return false;
}


int main()
{
	string filePath = "C:/Users/vikto/c_projects/AC2015/App/Source/input_day6.txt";
	vector<string> file_as_vector = readFile_as_vector(filePath);
	check_not_empty_vector(file_as_vector);

	/*char *strings[] creates an array of pointers, where each element points to a string literal. 
	This method is more flexible, as each string can have different lengths.*/
    const char *bad_strings_array[] = {
        "ab",
        "cd",
        "pq",
		"xy"
    };
	int bad_string_array_size = sizeof(bad_strings_array)/sizeof(bad_strings_array[0]);

    const char *vowels_array[] = {
        "a",
        "e",
        "i",
		"o",
		"u"
    };

	unsigned int nice_strings_part1 = 0;
	bool vowel_condition;
	bool two_consecutive_characters_condition;
	bool bad_substring_condition;

	unsigned int nice_strings_part2 = 0;
	bool repeated_pairs;
	bool letters_repeated_with_on_letter_between_them;

	for (string& s: file_as_vector){
		vowel_condition 					 = vowel_analyzer        (s, vowels_array);
		bad_substring_condition 			 = bad_substring_analyzer(s, bad_strings_array, bad_string_array_size);
		two_consecutive_characters_condition = two_characters_in_a_row(s);

		if (vowel_condition * two_consecutive_characters_condition * bad_substring_condition == true){
			++nice_strings_part1;
		}

		repeated_pairs								 = pair_appears_twice(s);
		letters_repeated_with_on_letter_between_them = letters_repeated_with_one_in_the_middle(s);

		if (repeated_pairs * letters_repeated_with_on_letter_between_them == true){
			++nice_strings_part2;
		}

	}

	cout << "Nice strings part 1: " << nice_strings_part1 << endl;
	cout << "Nice strings part 2: " << nice_strings_part2 << endl;
}
