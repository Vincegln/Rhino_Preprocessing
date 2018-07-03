#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <numeric>

#define DEBUG

#ifdef DEBUG
#define DEBUG_STDOUT(x) (std::cout << (x))
#else
#define DEBUG_STDOUT(x)
#endif

using namespace std;
namespace fs = std::filesystem;

void deleteLines(const std::string &, size_t, size_t);

size_t findLinePos(ifstream &, string &, string &);

int main() {
    ifstream nurb_file;
    string first_line_txt("dias_aorta");
    size_t first_line_pos;
    string last_line_txt("dias_inf_vc");
    size_t last_line_pos;
    string end_of_file_txt("EOF");
    size_t end_of_file_pos;

    size_t i = 1;
    string filename("both_out_" + to_string(i) + ".nrb");

    while (fs::exists(filename)) {
        nurb_file.open(filename);
        cout << "Processing of "<< filename << "...\r\n";

        first_line_pos = findLinePos(nurb_file, filename, first_line_txt);
        deleteLines(filename, 0, first_line_pos - 1);
        DEBUG_STDOUT(first_line_pos + "\r\n");
        last_line_pos = findLinePos(nurb_file, filename, last_line_txt);
        DEBUG_STDOUT(last_line_pos + "\r\n");
        end_of_file_pos = findLinePos(nurb_file, filename, end_of_file_txt);
        DEBUG_STDOUT(end_of_file_pos + "\r\n");
        if(last_line_pos != -1)
        {
            deleteLines(filename, last_line_pos, end_of_file_pos-last_line_pos);
        }



        cout << filename << " done\r\n";

        i++;
        filename = ("both_out_" + to_string(i) + ".nrb");
        nurb_file.close();
    }
    return 0;
}

void deleteLines(const std::string &filename, size_t start, size_t skip) {
    std::ifstream infile(filename.c_str(), std::ios::in);
    if (infile.is_open()) {
        std::string line;
        std::list<std::string> filelines;
        while (infile) {
            getline(infile, line);
            filelines.push_back(line);
        }
        infile.close();
        if (start > filelines.size()) {
            std::cerr << "Error! Starting to delete lines past the end of the file!\n";
            return;
        }
        if ((start + skip) > filelines.size()) {
            std::cerr << "Error! Trying to delete lines past the end of the file!\n";
            return;
        }
        std::list<std::string>::iterator deletebegin = filelines.begin(), deleteend;
        for (size_t i = 1; i < start; i++)
            deletebegin++;
        deleteend = deletebegin;
        for (size_t i = 0; i < skip; i++)
            deleteend++;
        filelines.erase(deletebegin, deleteend);

        std::ofstream outfile(filename.c_str(), std::ios::out | std::ios::trunc);
        if (outfile.is_open()) {
            copy(filelines.begin(), filelines.end(), ostream_iterator<string>(outfile, "\n"));
        }
        outfile.close();
    } else {
        std::cerr << "Error! Could not find file " << filename << " !\n";
        return;
    }
}

size_t findLinePos(ifstream &nurb_file, string &filename, string &wanted_line_txt) {
    size_t wanted_line_pos = -1, line_pos = 0;
    string stored_line;
    nurb_file.close();
    nurb_file.open(filename);
    while ((!nurb_file.eof()) && (wanted_line_pos == -1)) {
        getline(nurb_file, stored_line);
        if ((stored_line.find(wanted_line_txt) != string::npos) && (wanted_line_txt != "EOF")) {
            wanted_line_pos = line_pos;
        } else {
            line_pos++;
        };
    }
    if (wanted_line_txt == "EOF") {
        wanted_line_pos = line_pos;
    }

    return wanted_line_pos;
}