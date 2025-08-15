#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

string compressString(const string& s) {
    string result;
    int count = 1;
    for (size_t i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && s[i] == s[i + 1]) {
            count++;
        } else {
            result += s[i];
            result += to_string(count);
            count = 1;
        }
    }
    return result;
}

void compressChunk(const string& input, string& output) {
    output = compressString(input);
}

int main() {
    string filename;
    cout << "Enter filename to compress: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file!" << endl;
        return 0;
    }

    string content((istreambuf_iterator<char>(infile)), (istreambuf_iterator<char>()));
    infile.close();

    // Split content into 4 chunks
    int n = content.size();
    vector<string> chunks(4);
    chunks[0] = content.substr(0, n/4);
    chunks[1] = content.substr(n/4, n/4);
    chunks[2] = content.substr(n/2, n/4);
    chunks[3] = content.substr(3*n/4);

    vector<string> compressed(4);
    vector<thread> threads;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 4; i++) {
        threads.push_back(thread(compressChunk, chunks[i], ref(compressed[i])));
    }

    for (auto &t : threads) t.join();

    string finalCompressed = compressed[0] + compressed[1] + compressed[2] + compressed[3];

    ofstream outfile("compressed.txt");
    outfile << finalCompressed;
    outfile.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "File compressed successfully in " << duration.count() << " seconds.\n";
    cout << "Compressed data saved as compressed.txt\n";

    return 0;
}
