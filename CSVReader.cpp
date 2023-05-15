#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>


CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    //std::cout << "Called readCSV" << std::endl;
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        //std::cout << "Opened CSV file" << std::endl;
        while (std::getline(csvFile, line))
        {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception& e)
            {
                //std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }// end of while
    }    

    //std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator) // Optimised version
{
    std::vector<std::string> tokens;
    char* str = const_cast<char*>(csvLine.c_str()); // initialize char* pointer to the string to be split:
    char* token = nullptr;
    char* context = nullptr;
    token = strtok_s(str, &separator, &context);
    while (token != nullptr) // Iterate through the tokens calling strtok_s with a null pointer until it returns null pointer
    {
        tokens.push_back(token);
        token = strtok_s(nullptr, &separator, &context);
    }
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    if (tokens.size() != 5) // bad
    {
        //std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    price = strtod(tokens[3].c_str(), nullptr);
    amount = atof(tokens[4].c_str());

    OrderBookEntry obe{ price,
                        amount,
                        tokens[0],
                        tokens[1],
                        OrderBookEntry::stringToOrderBookType(tokens[2]) };

    return obe;
}

/*
OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
    std::string amountString,
    std::string timestamp,
    std::string product,
    OrderBookType orderType)
{
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception& e) {
        //std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        //std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl; 
        throw;
    }
    OrderBookEntry obe{ price,
                    amount,
                    timestamp,
                    product,
                    orderType };

    return obe;
}
*/


OrderBookEntry CSVReader::stringsToOBE(std::string priceString, 
                                    std::string amountString, 
                                    std::string timestamp, 
                                    std::string product, 
                                    OrderBookType orderType)
{
    double price, amount;
    try {
         price = std::stod(priceString);
         amount = std::stod(amountString);
    }catch(const std::exception& e){
        //std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        //std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl; 
        throw;        
    }
    OrderBookEntry obe{price, 
                    amount, 
                    timestamp,
                    product, 
                    orderType};
                
    return obe;
}
     