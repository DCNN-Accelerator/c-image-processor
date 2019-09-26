#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    ifstream csv;
    csv.open(argv[1]);
    stringstream str_strm((std::istreambuf_iterator<char>(csv) ),
                       (std::istreambuf_iterator<char>()    ));
    string tmp;
    vector<string> nums;
    char delim = ','; // Define the delimiter to split by

    while (getline(str_strm, tmp, delim)) {
        // Provide proper checks here for tmp like if empty
        // Also strip down symbols like !, ., ?, etc.
        // Finally push it.
        nums.push_back(tmp);
    }

    for(auto it = nums.begin(); it != nums.end(); it++) {
        cout << *it << endl;
    }
    
    csv.close();
    return 0;
}