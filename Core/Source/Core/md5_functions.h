#include <openssl/md5.h>
#include <string>
#include <sstream>  // for std::stringstream
#include <iomanip>  // for std::setw, std::setfill
using namespace std;

// read_input_functions.h
#ifndef MD5_FUNCTIONS_H
#define MD5_FUNCTIONS_H

// Function declarations
string md5Hash(const string& data);
#endif // READ_INPUT_FUNCTIONS_H