#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

// Function to count lines of code in a file
int countLoc(const string &file_path)
{

    ifstream file(file_path);
    if (!file.is_open())
    {
        throw runtime_error("Error opening file");
    }

    string line;
    int loc = 0; // Lines of code counter
    bool inside_multi_line_comment = false;

    while (getline(file, line))
    {
        // Remove leading and trailing whitespaces
        line.erase(line.find_last_not_of(" \t") + 1);
        line.erase(0, line.find_first_not_of(" \t"));

        // Check if the line is not empty
        if (!line.empty())
        {
            // Check if inside a multi-line comment
            if (inside_multi_line_comment)
            {

                size_t comment_end_pos = line.find("*/");
                if (comment_end_pos != string::npos)
                {
                    // Trim the line after the end of the multi-line comment
                    line.erase(0, comment_end_pos + 2);
                    inside_multi_line_comment = false;
                }
                else
                {
                    // Skip the entire line
                    continue;
                }
            }

            // Check if the line is not a comment

            line.erase(0, line.find_first_not_of(" \t"));
            if (!line.empty() && line.find("//") != 0 && line.find("/*") != 0)
            {
                loc++;
            }

            // Check if the line contains the start of a multi-line comment
            size_t comment_start_pos = line.find("/*");
            if (comment_start_pos != string::npos)
            {
                // Trim the line before the start of the multi-line comment
                line.erase(comment_start_pos);
                inside_multi_line_comment = true;
            }
        }
    }

    return loc;
}

int main()
{
    string file_path = "test.cpp";

    try
    {
        int loc = countLoc(file_path);
        cout << "Lines of code: " << loc << endl;
    }
    catch (const exception &e)
    {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
