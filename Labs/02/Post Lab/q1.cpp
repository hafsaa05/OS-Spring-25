#include <iostream>
#include <cstdlib>  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: Please provide at least one integer as a command-line argument." << endl;
        return 1;
    }

    int sum = 0;

    for (int i = 1; i < argc; ++i) {
        bool isValid = true;
        for (int j = 0; argv[i][j] != '\0'; ++j) {
            if (!isdigit(argv[i][j]) && !(j == 0 && argv[i][j] == '-')) {
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            cerr << "Error: Invalid input '" << argv[i] << "'. Please enter only integers." << endl;
            return 1;
        }

        int num = atoi(argv[i]);
        sum += num;
    }

    double average = static_cast<double>(sum) / (argc - 1);

    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
