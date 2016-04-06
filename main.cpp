#include <regex>
#include <fstream>
#include "RedBlackTree.h"

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

    RedBlackTree cityDictionary;

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
    std::string            input;
    std::vector<std::string> keyValues;

    bool exit_program;

    inputFile.open("/Users/dank/Dropbox/School/CS1D/2016_Spring/Extra-credit/red-black-tree-dictionary/inputFile.txt");
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

                    cityDictionary.remove(tempKey);
                }
            }
            else
            {
                // Inserting city into the dictionary
                if (std::regex_search(inputString, stringMatch, keyRegex))
                {
                    tempKey = std::stoi(stringMatch.str().c_str(), &sz);
                }
                if (std::regex_search(inputString, stringMatch, nameRegex))
                {
                    tempString = stringMatch.str().c_str();
                }
                cityDictionary.insert(tempKey, tempString);
            }

        }
        inputString = "";
        tempString  = "";
        tempKey     = 0;

    }

    do
    {
        exit_program = false;
        std::cout <<
        "1. Find key\n"
                "2. Get All Values\n"
                "3. Insert Key\n"
                "4. Remove Key\n"
                "5. Print Tree\n"
                "0. Exit\n";
        std::cout << "-------------\n";
        std::cout << "User Input >> ";
        std::cin >> input;
        switch (input[0])
        {
            case '1':
                std::cout << "Find value for the key : ";
                std::cin >> tempKey;

                tempString = cityDictionary.getValue(tempKey);
                if (tempString != "")
                {
                    std::cout << "The value : " << tempString << " was found!\n";
                }
                else
                {
                    std::cout << "No value was found for the key : " << tempKey << std::endl;
                }
                break;
            case '2':
                std::cout << "Find all values for the key : ";
                std::cin >> tempKey;

                keyValues = cityDictionary.getAllValues(tempKey);
                if (keyValues.size() > 0)
                {
                    std::cout << "For the key : " << tempKey << " the following values were found:\n";

                    for (int i = 0; i < keyValues.size(); i++)
                    {
                        std::cout << "Value [ " << std::setw(10) << keyValues[i] << "]" << std::endl;
                    }
                }
                else
                {
                    std::cout << "No value was found for the key : " << tempKey << std::endl;
                }
                break;
            case '3':
                std::cout << "Enter key to insert into tree : ";
                std::cin >> tempKey;
                std::cout << "Enter key to insert into tree : ";
                getline(cin, tempString);
                cityDictionary.insert(tempKey, tempString);
                std::cout << "The key [ " << tempKey << " ] with the value : " << tempString << " has been inserted into the red-black tree." << std::endl;
                break;
            case '4':
                std::cout << "Enter key to remove from tree : ";
                std::cin >> tempKey;
                tempString = cityDictionary.getValue(tempKey);
                cityDictionary.remove(tempKey);
                std::cout << "The key [ " << tempKey << " ] with the value : " << tempString << " has been removed from the red-black tree." << std::endl;
                break;
            case '5':
                cityDictionary.printTree();
                break;
            case '0':
                exit_program = true;
                break;
            default :
                std::cout << "Invalid input!\n\n";
        }

    } while (!exit_program);

    cityDictionary.printTree();
    inputFile.close();

    std::cout << std::endl << std::endl;

    RedBlackTree homeworkTree;

    homeworkTree.insert(33, "33");
    homeworkTree.insert(22, "22");
    homeworkTree.insert(50, "50");
    homeworkTree.insert(44, "44");
    homeworkTree.insert(55, "55");
    homeworkTree.insert(60, "60");

    homeworkTree.printTree();

    homeworkTree.remove(50);

    homeworkTree.printTree();

    homeworkTree.remove(55);

    homeworkTree.printTree();

    return 0;
}
