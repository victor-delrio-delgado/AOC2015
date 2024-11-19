#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <utility>

#include "Core/read_input_functions.h"

enum class RequiredOperation {uninitialized, one, two, two_shift};
//Color myColor = Color::Red;

struct ParsedInformation{
	string command;
	vector<string> inputs;
	string output;
};

class WireBaseFunctionality{
private:
	void print_error_message(){
		std::cout << "The number of inputs is not the expected for operation" << endl;
	}
public:
	RequiredOperation variables_required = RequiredOperation::uninitialized;
	const string ivariable1;
	const string ivariable2;
	const string ovariable;

	WireBaseFunctionality(const string& iv1 = "",const string& iv2 = "",const string& ov = ""): ivariable1(iv1), ivariable2(iv2), ovariable(ov){}
	bool determine_if_enough_input_variables();
	RequiredOperation return_number_of_variables(){return variables_required;}
	virtual void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {}
};

bool WireBaseFunctionality:: determine_if_enough_input_variables(){
	bool not_enough_variables = true;
	switch (variables_required){
		case RequiredOperation::one:
			not_enough_variables = (ivariable1 == "" || ovariable == "");
		case RequiredOperation::two:
			not_enough_variables = (ivariable1 == "" || ivariable2 == "" || ovariable == "");
		case RequiredOperation::two_shift:
			not_enough_variables = (ivariable1 == "" || ovariable == "");
	}

	if (not_enough_variables)
	{
		print_error_message();
		return false;
	}
	else{
		return true;
	}
};


class AndOperation : public WireBaseFunctionality{
	public:
		using WireBaseFunctionality::WireBaseFunctionality;
		AndOperation(){variables_required = RequiredOperation::two;}
		void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {ovariable_value = ivariable1_value & ivariable2_value;}
};

class OrOperation : public WireBaseFunctionality{
	public:
		using WireBaseFunctionality::WireBaseFunctionality;
		OrOperation(){variables_required = RequiredOperation::two;}
		void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {ovariable_value = ivariable1_value | ivariable2_value;}
};

class LShift : public WireBaseFunctionality{
	public:
		using WireBaseFunctionality::WireBaseFunctionality;
		LShift(){variables_required = RequiredOperation::two_shift;}
		void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {ovariable_value = ivariable1_value << ivariable2_value;}
};

class RShift : public WireBaseFunctionality{
	public:
		using WireBaseFunctionality::WireBaseFunctionality;
		RShift(){variables_required = RequiredOperation::two_shift;}
		void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {ovariable_value = ivariable1_value >> ivariable2_value;}
};

class NOT : public WireBaseFunctionality{
	public:
		using WireBaseFunctionality::WireBaseFunctionality;
		NOT(){variables_required = RequiredOperation::one;}
		void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {ovariable_value = ivariable1_value >> ivariable2_value;}
};

class SET : public WireBaseFunctionality{
	public:
		using WireBaseFunctionality::WireBaseFunctionality;
		SET(){variables_required = RequiredOperation::one;}
		void calculation(int& ovariable_value, int ivariable1_value, int ivariable2_value) {ovariable_value = !ivariable1_value;}
};



static ParsedInformation parse_string(string& instruction, vector<string>& possible_operations){
	ParsedInformation ParsedInfo;


	static const string separator_inputs_outputs = " -> ";
	static const string separator = " ";

	size_t length_of_input_output_separator = separator_inputs_outputs.length();
	size_t length_of_instruction_string = instruction.length();
	size_t position_of_output_substring = instruction.find(separator_inputs_outputs);

	ParsedInfo.output = instruction.substr(position_of_output_substring + length_of_input_output_separator, length_of_instruction_string);
	string input = instruction.substr(0, position_of_output_substring);

	vector<string> input_information;
	size_t position_of_next_input;
	while (true){
		position_of_next_input = input.find(separator);
		if (position_of_next_input == string::npos) {
			input_information.push_back(input);
			break;
		}
		else{
			input_information.push_back(input.substr(0, position_of_next_input));
			input.replace(0, position_of_next_input + 1, "");
		}
	}

	vector<string> input_variables;
	ParsedInfo.command = "";
	for (string& input: input_information){
		for (string& possible_operation: possible_operations){
			if (input == possible_operation){
				ParsedInfo.command = possible_operation;
			}
		}
	}
	for (string& input : input_information) {
		if (input != ParsedInfo.command) {
			input_variables.push_back(input);
		}
	}

	if (input_variables.size() == 1){
		input_variables.push_back("");
	}

	ParsedInfo.inputs = input_variables;

	return ParsedInfo;
}

int stored_value_for_variable(string variable_use_case, vector<string>& known_variables,  vector<int>& known_values){
	int i = 0;
	for (string& v: known_variables){
		if (v == variable_use_case){
			break;
		}
		++i;
	}
	if (i == known_variables.size()){
		return -1;
	}
	else{
		return known_values[i];
	}
}

int all_needed_variables_are_initialized(int v1, int v2, RequiredOperation number_of_inputs){
	bool enough_variables;
	switch (number_of_inputs){
		case RequiredOperation::one:
			enough_variables = (v1 != -1);
		case RequiredOperation::two:
			enough_variables = (v1 != -1 && v2 != -1);
		case RequiredOperation::two_shift:
			enough_variables = (v1 != -1);
	}
	return enough_variables;
}


int main()
{
	string filePath = "C:/Users/vikto/c_projects/AC2015/App/Source/input_day7.txt";
	vector<string> file_as_vector = readFile_as_vector(filePath);
	check_not_empty_vector(file_as_vector);

	vector<string> possible_operations = {"AND", "OR", "LSHIFT", "RSHIFT", "NOT", "SET"};

	vector<string> known_variables;
	known_variables.push_back("");
	vector<int> known_values;
	known_values.push_back(-1);

	while(true)
	{
		size_t known_variables_at_the_beggining_of_this_iteration = known_variables.size();
		for (string& s: file_as_vector){
			ParsedInformation ParsedInfo = parse_string(s, possible_operations);

			int output_value  = stored_value_for_variable(ParsedInfo.output, known_variables,  known_values);
			bool output_unknown = output_value == -1;
			if (output_unknown) 													
			{
				WireBaseFunctionality* base_class = nullptr;

				if (ParsedInfo.command == "AND"){
					AndOperation initialized_derived(ParsedInfo.inputs[0], 
													ParsedInfo.inputs[1], 
													ParsedInfo.output);
					base_class = &initialized_derived;
				}
				else if (ParsedInfo.command == "OR"){
					OrOperation initialized_derived(ParsedInfo.inputs[0], 
													ParsedInfo.inputs[1], 
													ParsedInfo.output);
					base_class = &initialized_derived;
				}
				else if (ParsedInfo.command == "LSHIFT"){
					LShift initialized_derived(ParsedInfo.inputs[0], 
													ParsedInfo.inputs[1], 
													ParsedInfo.output);
					base_class = &initialized_derived;
				}
				else if (ParsedInfo.command == "RSHIFT"){
					RShift initialized_derived(ParsedInfo.inputs[0], 
													ParsedInfo.inputs[1], 
													ParsedInfo.output);
					base_class = &initialized_derived;
				}
				else if (ParsedInfo.command == "NOT"){
					NOT initialized_derived(ParsedInfo.inputs[0], 
													ParsedInfo.inputs[1], 
													ParsedInfo.output);
					base_class = &initialized_derived;					
				}
				else if (ParsedInfo.command == "SET"){
					SET initialized_derived(ParsedInfo.inputs[0], 
													ParsedInfo.inputs[1], 
													ParsedInfo.output);
					base_class = &initialized_derived;					
				}

				bool enough_input_variables 			= base_class-> determine_if_enough_input_variables();
				if (enough_input_variables) 													
				{

					int input_value_1 = stored_value_for_variable(ParsedInfo.inputs[0], known_variables,  known_values);
					int input_value_2 = stored_value_for_variable(ParsedInfo.inputs[1], known_variables,  known_values);
					bool enough_initialized_input_variables = all_needed_variables_are_initialized(input_value_1,
																					input_value_2,
																					base_class-> return_number_of_variables());
					if (enough_initialized_input_variables)	
					{
						base_class-> calculation(output_value, input_value_1, input_value_2);
						known_variables.push_back(ParsedInfo.output);
						known_values.push_back(output_value);
					}															
				}
			}
		}
		size_t known_variables_at_the_end_of_this_iteration = known_variables.size();

		if(known_variables_at_the_end_of_this_iteration == known_variables_at_the_beggining_of_this_iteration){break;};
	}
	cout << "done" << endl;
}
