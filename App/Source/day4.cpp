#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <utility>

//#include "Core/read_input_functions.h"
#include "Core/md5_functions.h"

using namespace std;

int main()
{

	const unsigned int number_of_positions_that_have_to_be_0 = 6;
	unsigned int sumatory_of_passes = 0;

	string input = "yzbqklnj";
	string input_iterable;
	string output;
	unsigned int i = 0;
	string i_str;
	while (true) {

		i_str = to_string(i);
		input_iterable = input + i_str;
		output = md5Hash(input_iterable);

		if (output.size() < number_of_positions_that_have_to_be_0) {
			continue;
		}
		for (int j=0; j < number_of_positions_that_have_to_be_0; ++j) {

			if (output[j] == '0') {
				++sumatory_of_passes;
			}
		}
		if (sumatory_of_passes == number_of_positions_that_have_to_be_0) {
			cout << "puzzle_output: " << output << endl;
			cout << "puzzle_result: " << i << endl;
			break;
		}
		sumatory_of_passes = 0;
		i = i + 1;
	}

	


	
}