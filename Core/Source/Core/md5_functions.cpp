#include <openssl/md5.h>
#include <string>
#include <sstream>  // for std::stringstream
#include <iomanip>  // for std::setw, std::setfill
using namespace std;

string md5Hash(const string& data) {
    // Buffer to hold the result
    unsigned char hash[MD5_DIGEST_LENGTH];

    // Perform the MD5 hash operation
    MD5(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    // Convert the result to a readable hexadecimal string
    stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}