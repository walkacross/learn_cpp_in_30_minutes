#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

// function prototypes
//https://github.com/shyney7/libtorch_dataloader
std::vector<std::vector<double>> csv2Dvector(const std::string& inputFileName);
std::vector<double> onelinevector(const std::vector<std::vector<double>>& invector);
void print2dvec(std::vector<std::vector<double>>& vec2print);
void print1dvector(std::vector<double>& vec2print);

int main() {
    int a = 100;
    std::cout << "Hello, World!" << std::endl;

    std::vector<std::vector<double>> data_vector_list;

    const std::string input_loc = "../nohdr.csv";
    data_vector_list = csv2Dvector(input_loc);
    std::cout << "Data Vector: \n"; // debug reasons remove later
    print2dvec(data_vector_list); // debug remove later
    std::vector<double> flat_vector;

    std::vector<double> flattend_vector = onelinevector(data_vector_list);
    std::cout << "Flat Vector: \n"; //debug
    print1dvector(flattend_vector); //debug



    std::cout << "Hello, end" << std::endl;
    return 0;
}

std::vector<std::vector<double>> csv2Dvector(const std::string& inputFileName) {
    using namespace std;

    vector<vector<double>> data;
    ifstream inputFile(inputFileName);
    int l = 0;

    while (inputFile) {
        l++;
        string s;
        if (!getline(inputFile, s))
            break;
        if (s[0] != '#') {
            istringstream ss(s);
            vector<double> record;

            while (ss) {
                string line;
                if (!getline(ss, line, ','))
                    break;
                try {
                    record.push_back(stof(line));
                } catch (const std::invalid_argument e) {
                    cout << "NaN found in file " << inputFileName << " line " << l
                         << '\n';
                    e.what();
                }
            }

            data.push_back(record);
        }
    }

    if (!inputFile.eof()) {
        cerr << "Could not read file " << inputFileName << '\n';
        throw invalid_argument("File not found.");
    }

    return data;
}

std::vector<double> onelinevector(const std::vector<std::vector<double>>& invector) {

    std::vector<double> v1d;
    if (invector.size() == 0)
        return v1d;
    v1d.reserve(invector.size() * invector.front().size());

    for (auto &innervector : invector) {
        v1d.insert(v1d.end(), innervector.begin(), innervector.end());
    }

    return v1d;
}

void print2dvec(std::vector<std::vector<double>> &vec2print) {
    for (const auto& i:vec2print) {
        for (const auto& j: i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
}

void print1dvector(std::vector<double>& vec2print) {
    for (const auto& i:vec2print) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}