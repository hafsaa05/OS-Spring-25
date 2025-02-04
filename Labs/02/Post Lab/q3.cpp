#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int find_missing(vector<int>& arr) {
    int size = arr.size();
    int diff1 = arr[1] - arr[0];
    int diff2 = arr[2] - arr[1];

    int diff = (diff1 == diff2) ? diff1 : min(diff1, diff2);

    for (int i = 0; i < size - 1; ++i) {
        if (arr[i + 1] - arr[i] != diff) {
            return arr[i] + diff;
        }
    }
    return -1;
}

int main() {
    ifstream infile("input.txt");
    if (!infile.is_open()) {
        cout << "Error opening input.txt" << endl;
        return 1;
    }

    vector<int> numbers;
    int num;

    while (infile >> num) {
        numbers.push_back(num);
    }
    infile.close();

    if (numbers.size() < 3) {
        cout << "The series must have at least three numbers." << endl;
        return 1;
    }

    int missing = find_missing(numbers);

    ofstream outfile("missing.txt");
    if (outfile.is_open()) {
        outfile << missing << endl;
        outfile.close();
    } else {
        cout << "Error opening missing.txt" << endl;
        return 1;
    }

    cout << "Missing number saved in missing.txt" << endl;

    return 0;
}
