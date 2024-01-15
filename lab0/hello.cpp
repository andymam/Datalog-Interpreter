#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>


using namespace std;

int main(int argc, char* argv[] ) {

    // cout << "Hello" << endl;
    // cout << "argc: " << argc << endl;
    // cout << "argv[0]: " << argv[0] << endl;
    // cout << "argv[1]: " << argv[1] << endl;

    string filename;
    filename = argv[1];

    ifstream in;
    in.open(filename);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    in.close();

    // cout << "*** Start of Input ***" << endl;
    // cout << input << endl;
    // cout << "*** End of Input ***" << endl;

    int lines = 0;
    int spaces = 0;
    int digits = 0;
    int letters = 0;


    for (char c : input) {   
        if (c == '\n') {
            lines++;
        }
        if (isspace(c)) {
            spaces++;
        }
        if (isdigit(c)) {
            digits++;
        }
        if (isalpha(c)) {
            letters++;
        }
    }

    cout << "chars: " << input.size() << endl;
    cout << "lines: " << lines << endl;
    cout << "spaces: " << spaces << endl;
    cout << "digits: " << digits << endl;
    cout << "letters: " << letters << endl; 

}