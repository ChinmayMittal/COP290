#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "matrixio.h"

#include "validators.h"

using namespace std;

vector<vector<float>> read(string filename)
{

    fstream myFile;
    int rows, columns;
    vector<vector<float>> ans; // will store the matrix to be returned

    myFile.open(filename, ios::in); // opens the input file in read mode

    if (myFile.is_open())
    {

        string line;
        int linenumber = 0;

        while (getline(myFile, line))
        {
            // reads entire line as a string

            stringstream buffer(line);
            string token;
            vector<string> tokens; // all tokens of the current line will be stored here
            while (getline(buffer, token, ' '))
            { // string tokenizer which splits the line (stored in a buffer ) about the empty space
                tokens.push_back(token);
            }

            // each line should have a unique token
            if (tokens.size() != 1)
            {
                throw("ERROR on linenumber " + to_string(linenumber + 1) + " of file " + filename + " one token expected, " + to_string(tokens.size()) + " found");
            }
            if (linenumber == 0)
            {
                // number of columns on the first line
                columns = string_to_int_validator(tokens[0], ("Error on linenumber " + to_string(linenumber + 1) + " of " + filename + ", Number of columns should be a positive integer"));
            }
            else if (linenumber == 1)
            {
                // number of rows on the second line
                rows = string_to_int_validator(tokens[0], ("Error on linenumber " + to_string(linenumber + 1) + " of " + filename + ", Number of rows should be a positive integer"));
                ans.resize(rows, vector<float>(columns, 0.0));
            }
            else
            {
                float inputFloat = string_to_float_validator(tokens[0], "Error on linenumber " + to_string(linenumber + 1) + " of " + filename + ", matrix elements should be  32 bit floats");
                // finds the correct index of the element in the current line according to rows major order
                ans[(linenumber - 2) % rows][(linenumber - 2) / rows] = inputFloat;
            }
            linenumber++;
        }
        myFile.close();
    }
    else
    {
        throw(filename + "  does not exists "); // throws error if file is not found
    }

    return ans;
}

void write(vector<vector<float>> &mat, string filename)
{

    fstream myFile;
    int rows = mat.size(), columns = mat[0].size();
    myFile.open(filename, ios::out); // files opened in write mode

    if (myFile.is_open())
    {

        myFile << columns << "\n"; // number of columns
        myFile << rows << "\n";    // number of rows

        // matrix printed in column major order
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                myFile << mat[row][col] << "\n";
            }
        }
        myFile.close();
    }
}