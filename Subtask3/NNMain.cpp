#include <iostream>
#include <string>
#include <fstream>

#include "interfaceNN.h"
#include "matarr.h"
#include "predHelper.h"
#include "vectorio.h"

// sample usage of program 
const std::string USAGE = "USAGE: ./yourcode.out mfcc_file_name outputfile";

void writeToFile(std::string inpFileName, std::string outFileName, pred_t *results)
{   
    /*
        This function appends the output ( top 3 predictions of the AUDIO API ) to the output file 
    */
    std::ofstream outFile;
    outFile.open(outFileName, std::ofstream::out | std::ofstream::app);

    if (!outFile.is_open())
    {
        // error handling for file io errors 
        throw std::invalid_argument("The file " + outFileName + " can't be created/opened.");
    }

    outFile << inpFileName << " ";

    for (size_t i = 0; i < 3; i++)
    {
        outFile << numToLabel[results[i].label] << " ";
    }

    for (size_t i = 0; i < 3; i++)
    {
        outFile << results[i].prob << " ";
    }

    outFile << std::endl;
    outFile.close();
}

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        // error handling for unexpected number of arguments
        std::cout << "ERROR: PROGRAM TERMINATING....\n" ; 
        std::cout << USAGE << std::endl;
        return 0;
    }

    std::string featuresFile(argv[1]);
    std::string outputFile(argv[2]);

    pred_t results[12];
    try{
        // call to audio library created 
        libaudioAPI(argv[1], results);
        // append in text file 
        writeToFile(featuresFile, outputFile, results);
    }catch (string exp)
    {
        // ERROR HANDLING
        cout << "ERROR:  PROGRAM TERMINATING....\n";
        cout << exp << "\n";
    }
    catch (char const *exp)
    {
        // ERROR HANDLING
        cout << "ERROR:  PROGRAM TERMINATING....\n";
        cout << exp << "\n";
        
    }


    return 0;
}