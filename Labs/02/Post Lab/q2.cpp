#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int find_missing(int arr[], int size) {
    int diff1 = arr[1] - arr[0];
    int diff2 = arr[2] - arr[1];

    int diff = (diff1 == diff2) ? diff1 : min(diff1, diff2);

    for (int i = 0; i < size - 1; ++i) {
        if (arr[i + 1] - arr[i] != diff) {
            return arr[i] + diff;
        }
    }
    return -1;  // In case no missing element is found
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Enter at least three numbers in the series." << endl;
        return 1;
    }

    int size = argc - 1;
    int nums[size];

    for (int i = 1; i <= size; ++i) {
        nums[i - 1] = atoi(argv[i]);
    }

    int missing = find_missing(nums, size);

    ofstream file("missing.txt");
    if (file.is_open()) {
        file << missing << endl;
        file.close();
    } else {
        cout << "Error opening file." << endl;
        return 1;
    }

    cout << "Missing number saved in missing.txt" << endl;

    return 0;
}
