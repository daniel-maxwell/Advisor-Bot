#pragma once
#include <vector>
#include <tuple>
#include <iostream>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "CSVReader.h"


class AdvisorMain
{
    public:
        AdvisorMain();
        /** Call this to start the sim */
        void init();
    private:
        void welcome();
        void helpMenu(std::string menuItem);
        std::string getUserInput();
        void processUserInput(std::string userInput);
        void listProducts();
        double findMin(std::string product, std::string type, std::string timestamp);
        double findMax(std::string product, std::string type, std::string timestamp);
        double findAvg(std::string product, std::string type, int timesteps);
        std::tuple<double, double, int> predict(std::string maxOrMin, std::string product, std::string type);
        std::vector<double> range(std::string product, std::string type);
        void getCurrentTime();
        void gotoNextTimeframe();


        std::string currentTime;
        std::string previousTime;

        OrderBook orderBook{"20200601.csv"}; // main data set
        Wallet wallet;

};