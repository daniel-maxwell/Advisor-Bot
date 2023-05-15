#include "AdvisorMain.h"

AdvisorMain::AdvisorMain()
{
}

void AdvisorMain::init()
{
    std::string input;
    currentTime = orderBook.getEarliestTime();
    previousTime = "";
    welcome();
    while(true)
    {
        input = getUserInput();
        processUserInput(input);
    }
}

void AdvisorMain::welcome()
{
    std::cout << "Welcome to AdvisorBot!" << std::endl;
    std::cout << "Hint: Enter 'help' for a list of available commands, or 'help [cmd]' for more information on a specific command." << std::endl;
}

void AdvisorMain::helpMenu(std::string menuItem = "main")
{
    int selection = 0; // convert user input to int to be used in switch statement
    if (menuItem == "main") selection = 1;
    if (menuItem == "prod")  selection = 2;
    if (menuItem == "min")  selection = 3;
    if (menuItem == "max")  selection = 4;
    if (menuItem == "avg")  selection = 5;
    if (menuItem == "predict")  selection = 6;
    if (menuItem == "time")  selection = 7;
    if (menuItem == "step")  selection = 8;
    if (menuItem == "range")  selection = 9; // custom function

    switch(selection)
    {
        case 1: // main help menu
            std::cout << "\nAvailable commands are: \n" << std::endl;
            std::cout << "'prod' - Lists the available products on the exchange" << std::endl;
            std::cout << "'min' - find minimum bid or ask for product in current time step" << std::endl;
            std::cout << "'max' - find maximum bid or ask for product in current time step" << std::endl;
            std::cout << "'avg' - compute average ask or bid for the sent product over the sent number of time steps" << std::endl;
            std::cout << "'predict' - predicts max or min ask or bid for the sent product for the next time step" << std::endl;
            std::cout << "'time' - states current time in dataset" << std::endl;
            std::cout << "'step' - move to next time step" << std::endl;
            std::cout << "'range' - computes the difference between minimum and maximum prices for the current time step\n" << std::endl;
            std::cout << "For more information on a specific command, enter 'help [cmd]' \n" << std::endl;
            break;

        case 2: // help prod
            std::cout << "cmd: prod | Lists the available products on the exchange" << std::endl;
            break;

        case 3: // help min
            std::cout << "'min' - find minimum bid or ask for product in current time step" << std::endl;
            break;

        case 4: // help max
            std::cout << "'max' - find maximum bid or ask for product in current time step" << std::endl;
            break;

        case 5: // help avg
            std::cout << "'avg' - compute average ask or bid for the sent product over the sent number of time steps" << std::endl;
            break;

        case 6: // help predict
            std::cout << "'predict' - predicts max or min ask or bid for the sent product for the next time step" << std::endl;
            break;

        case 7: // help time
            std::cout << "'time' - states current time in dataset" << std::endl;
            break;

        case 8: // help step
            std::cout << "'step' - move to next time step" << std::endl;
            break;

        case 9: // range
            std::cout << "'range' - computes the difference between minimum and maximum prices for the current time step\n\n" << std::endl;
            break;

        default: std::cout << "Invalid help menu selection. Please enter 'help [cmd]' for help on a specific command " << std::endl;
    }
}
 
std::string AdvisorMain::getUserInput() // needs to check the user input for help, help cmd...etc
{
    std::string line;
    std::cout << "Enter your command: " << std::endl;
    std::getline(std::cin, line);
    return line;
}

void AdvisorMain::processUserInput(std::string userInput)
{
    const std::string delimiter = " "; // space character is the delimiter
    std::vector<std::string> commands; // vector to store user input
    auto start = 0U; // unsigned int iterating variable
    auto end = userInput.find(delimiter); // variable set to the index of the first occurence of the delimiter
    int option = 0;

    while (end != std::string::npos) // stores each command in the commands vector
    {
        commands.push_back(userInput.substr(start, end - start));
        start = end + delimiter.length();
        end = userInput.find(delimiter, start);
    }
    commands.push_back(userInput.substr(start, end)); // pushes final token to the commands vector

    // Use the first element in commands to select an option to be passed in to the switch statement
    if (commands[0] == "help" && commands.size() == 1) option = 1; // main help
    if (commands[0] == "help" && commands.size() > 1) option = 2; // help [cmd]
    if (commands[0] == "prod" && commands.size() == 1) option = 3;
    if (commands[0] == "min" && commands.size() == 3) option = 4;
    if (commands[0] == "max" && commands.size() == 3) option = 5;
    if (commands[0] == "avg" && commands.size() == 4) option = 6;
    if (commands[0] == "predict" && commands.size() == 4) option = 7;
    if (commands[0] == "time" && commands.size() == 1) option = 8;
    if (commands[0] == "step" && commands.size() == 1) option = 9;
    if (commands[0] == "range" && commands.size() == 3) option = 10;

    // use the value of option to call the appropriate function or flag input as invalid
    switch (option)
    {
        case 1: // Main help menu
            helpMenu();
            break;

        case 2: 
            helpMenu(commands[1]);
            break;

        case 3:
            listProducts();
            break;

        case 4:
            try { std::cout << "Min " << commands[2] << " for product " << commands[1] << " is: " << findMin(commands[1], commands[2], currentTime) << std::endl; }
            catch (const std::exception& e) { std::cout << "Invalid product or type. Please enter a valid product and specify ask or bid." << std::endl; }
            break;

        case 5:
            try { std::cout << "Max " << commands[2] << " for product " << commands[1] << " is: " << findMax(commands[1], commands[2], currentTime) << std::endl; }
            catch (const std::exception& e) { std::cout << "Invalid product or type. Please enter a valid product and specify ask or bid." << std::endl; }
            break;

        case 6:
            try { std::cout << "Average " << commands[1] << " " << commands[2] << " price over " << std::stoi(commands[3]) << " time steps was: " << findAvg(commands[1], commands[2], std::stoi(commands[3])) << std::endl; }
            catch (const std::exception& e) { std::cout << "Invalid product, type or number of timesteps." << std::endl; }
            break;

        case 7:
        {
            try
            {
                const std::tuple<double, double, int> prediction = predict(commands[1], commands[2], commands[3]);
                std::cout << "Product: " << commands[2] << "\n" << "Type: " << commands[1] << " " << commands[3] << " price" << std::endl;
                std::cout << "Simple Moving Average price prediction over " << std::get<2>(prediction) << " timesteps: " << std::get<0>(prediction) << std::endl;
                std::cout << "Weighted Moving Average price prediction over " << std::get<2>(prediction) << " timesteps: " << std::get<1>(prediction) << std::endl;
            }
            catch (const std::exception& e) { std::cout << "Predict cannot be used on the first timestep and must be of format [min/max] [product] [ask/bid]." << std::endl; }
            break;
        }

        case 8:
            getCurrentTime();
            break;

        case 9:
            gotoNextTimeframe();
            break;

        case 10:
        {
            try {
                const std::vector<double> calculateRange = range(commands[1], commands[2]);
                std::cout << "Min " << commands[2] << ": " << calculateRange[0] << "\nMax " << commands[2] << ": " << calculateRange[1] << "\nRange: " << calculateRange[2] << std::endl;
                }
            catch (const std::exception& e) { std::cout << "Invalid product or type. Please enter a valid product and specify ask or bid." << std::endl; }
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again or enter 'help' for a list of valid commands." << std::endl;
    }
}

void AdvisorMain::listProducts()
{
    // loop through the products in the current time step and display a list of them
    std::cout << "Products available are as follows: \n" << std::endl;
    for (const std::string& p : orderBook.getKnownProducts())
    {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;
}   

double AdvisorMain::findMin(const std::string product, const std::string type, const std::string timestamp)
{
    const OrderBookType orderType = OrderBookEntry::stringToOrderBookType(type);
    if (orderType == OrderBookType::unknown) throw std::exception{};
    std::vector<OrderBookEntry> matchingOrders;
    std::vector<std::string> availableProducts = orderBook.getKnownProducts();

    /** will store the location of the requested product in the availableProducts vector. will be set to availableProducts.end() if not found **/
    std::vector<std::string>::iterator productQuery = find(availableProducts.begin(), availableProducts.end(), product);

    if (productQuery != availableProducts.end()) // checks if the user entered a valid product
    {
        matchingOrders = orderBook.getOrders(orderType, product, timestamp);
        if (matchingOrders.size() == 0)
        {
            std::cout << "Alert: no matching orders found in timestep " << timestamp << std::endl;
            return 0;
        }
        else return OrderBook::getLowPrice(matchingOrders);
    }
    else throw std::exception{};
}

double AdvisorMain::findMax(const std::string product, const std::string type, const std::string timestamp)
{
    const OrderBookType orderType = OrderBookEntry::stringToOrderBookType(type);
    if (orderType == OrderBookType::unknown) throw std::exception{};
    std::vector<OrderBookEntry> matchingOrders;
    std::vector<std::string> availableProducts = orderBook.getKnownProducts();

    /** stores a referece to the requested product in the availableProducts vector or set to availableProducts.end() if not found **/
    const std::vector<std::string>::iterator productQuery = find(availableProducts.begin(), availableProducts.end(), product);

    if (productQuery != availableProducts.end()) // checks if the user entered a valid product
    {
        matchingOrders = orderBook.getOrders(orderType, product, timestamp);
        if (matchingOrders.size() == 0)
        {
            std::cout << "Alert: no matching orders found in timestep " << timestamp << std::endl;
            return 0;
        }
        else return OrderBook::getHighPrice(matchingOrders);
    }
    else throw std::exception{};
}

double AdvisorMain::findAvg(const std::string product, const std::string type, const int timesteps)
{
    const OrderBookType orderType = OrderBookEntry::stringToOrderBookType(type);
    if (orderType == OrderBookType::unknown) throw std::exception{};
    if (timesteps < 1) throw std::exception{};
    if (orderBook.timestepsPassed - timesteps < 0) // too early in the simulation to satisfy
    {
        std::cout << "Insufficient number of timesteps have passed since the earliest available timestep to satisfy the request." << std::endl;
        throw std::exception{};
    }

    // after checks, declare variables.
    double sum = 0; // will store the sum of prices that match the criteria
    double result;
    std::string time = orderBook.fetchTimestep(orderBook.timestepsPassed - timesteps) ; // stores reference to the number of timesteps as we iterate.
    std::vector<OrderBookEntry> matchingOrders;

    for (int i = 0; i < timesteps; i++)
    {
        matchingOrders = orderBook.getOrders(orderType,
            product, time);

        for (OrderBookEntry& e : matchingOrders)
        {
            sum += e.price;
        }
        time = orderBook.getNextTime(time);
    }

    result = sum / timesteps;

    if (result == 0) throw std::exception{};
    else
    {
        return result;
    }
}

std::tuple<double, double, int> AdvisorMain::predict(std::string maxOrMin, std::string product, std::string type) // Predicts price using both simple moving average and weighted moving average.
{
    if (OrderBookEntry::stringToOrderBookType(type) == OrderBookType::unknown) throw std::exception{}; // checks for valid order type
    if (currentTime == orderBook.getEarliestTime()) throw std::exception{}; // checks that we are on a valid time step

    // after checks, initialise variables
    std::string time = orderBook.getEarliestTime(); // stores time as we iterate through time steps
    int saveCurrentTimestep = orderBook.timestepsPassed; // to reset time step counter back later
    int iterations = 0; // counts how many timesteps were used to make the prediction
    double sma = 0; // simple moving average
    double wma = 0; // weighted moving average

    if (orderBook.timestepsPassed - 10 < 0) // Early in the simulation. Warn user of lower prediction accuracy
    {
        std::cout << "WARNING: less than 10 timesteps have passed since the earliest available timestep. This may lower prediction accuracy." << std::endl;
        time = orderBook.getEarliestTime();
    }
    else time = orderBook.fetchTimestep(orderBook.timestepsPassed - 10);

    if (maxOrMin == "max")
    {
        for (int i = 0; i < 10; i++)
        {
            const double maxValue = findMax(product, type, time);
            sma += maxValue;
            wma += maxValue * i;
            iterations += 1;
            if (time == currentTime)
            {
                break;
            }
            time = orderBook.getNextTime(time);
        }
    }
    if (maxOrMin == "min")
    {
        for (int i = 0; i < 10; i++)
        {
            const double minValue = findMin(product, type, time);
            sma += minValue;
            wma += minValue * i;
            iterations += 1;
            if (time == currentTime)
            {
                break;
            }
            time = orderBook.getNextTime(time);
        }
    }
    sma = sma / iterations;
    wma = wma / (iterations * (iterations + 1) / 2);
    std::tuple<double, double, int> result (sma, wma, iterations); // tuple with our sma/wma values and the number of time steps the function used to calculate
    return result;
}

std::vector<double> AdvisorMain::range(const std::string product, const std::string type)
{
    std::vector<double> result;
    const double min = findMin(product, type, currentTime);
    const double max = findMax(product, type, currentTime);
    result.push_back(min);
    result.push_back(max);
    result.push_back(max - min);
    return result;
}

void AdvisorMain::getCurrentTime()
{
    std::cout << "Current time is: " << currentTime << std::endl;
}

void AdvisorMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    previousTime = currentTime;
    currentTime = orderBook.getNextTime(currentTime);
}