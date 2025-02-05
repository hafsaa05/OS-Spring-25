#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    const size_t buffer_size = 1024;
    char buffer[buffer_size];

    while (file.read(buffer, buffer_size) || file.gcount() > 0) {
        cout.write(buffer, file.gcount());
    }

    file.close();
    return 0;
}
