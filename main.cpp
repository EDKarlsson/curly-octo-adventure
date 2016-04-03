#include <regex>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main()
{
    std::cout <<
    "/**************************************************************************\n"
            " * AUTHORS  : Dan Karlsson\n"
            " * CLASS    : CS1D\n"
            " * DATE     : 04-03-16\n"
            " * Extra Credit : Red-Black Tree Dictionary\n"
            " *************************************************************************/\n";

    Dictionary cityDictionary;
    Dictionary inputCity;

    // Regex Variables
    std::regex  keyRegex("[0-9][0-9]");
    std::regex  nameRegex("[A-Za-z]+( )?([A-Za-z]+)?");
    std::regex  deleteRegex("Delete");
    std::smatch stringMatch;

    // String variables and basic data types.
    std::string::size_type sz;
    std::ifstream          inputFile;
    std::string            inputString;
    std::string            tempString = "";
    int                    tempKey    = 0;

    inputFile.open(
            "/Users/dank/Dropbox/School/CS1D/2016_Spring/Assignments/cs1d-assignments/Assignment-09/inputFile.txt");
    while (!inputFile.eof())
    {
        std::getline(inputFile, inputString);

        if (inputString != "")
        {
            if (std::regex_search(inputString, deleteRegex))
            {
                // Delete values related to the specified the key
                if (std::regex_search(inputString, stringMatch, keyRegex))
                {
                    tempString = stringMatch.str().c_str();
                    tempKey    = std::stoi(tempString, &sz);

                    cityDictionary.remove(long(tempKey));
                }
            }
            else
            {
                // Inserting city into the dictionary
                if (std::regex_search(inputString, stringMatch, keyRegex))
                {
                    tempKey = std::stoi(stringMatch.str().c_str(), &sz);
                    inputCity.setKey(tempKey);
                }
                if (std::regex_search(inputString, stringMatch, nameRegex))
                {
                    tempString = stringMatch.str().c_str();
                    inputCity.setName(tempString);
                }
                cityDictionary.insert(tempKey, inputCity);
            }

            cityDictionary.outputList();

        }
        inputString = "";
        tempString  = "";
        tempKey     = 0;
    }

    inputFile.close();
    return 0;

}
