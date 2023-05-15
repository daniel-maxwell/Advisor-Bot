# Welcome!
> Advisorbot is a command-line Cryptocurrency simulation application which aims to provide the user with various functions analyse the trading activity of a Cryptocurrency exchange.
> The simulation works by parsing a .csv data set which is an excerpt of trading activity on a real cryptocurrency exchange over a period of 1 hour. Various commands enable the user to explore price fluctuations, compare currencies and much more.
>
> The table below details the commands available in this version of
> AdvisorBot:

![Command Table](https://github.com/daniel-maxwell/AdvisorBot/blob/master/Command%20Table.png)

> ## Command parsing code
>
> The first step to parsing the user's input was in creating a function 'getUserInput()' which returns the entire line the user typed in to the console before pressing the enter key, using 'std::getline(std::cin, line);'. This is continuously passed to another function, 'processUserInput()' in a 'while(true)' loop within the 'init()'function.
>
> 'processUserInput()' parses commands by using the delimiter character, in this case, ' ', to separate each individual word in the input and append it to a vector 'commands'. This is achieved using variables 'start' and 'end' to save the indices of the string at the start of a word and at the next occurrence of the delimiter using 'find()'. While 'end' does not equal 'std::string::npos'(value which equals the end of a std::string), each word is pushed to the 'commands' vector using 'commands.push_back(userInput.substr(start, end - start))'.
>
> Once the commands vector is populated with user input in the form of delimiter-separated commands, a series of if statements are used to check the first word the user input; ('commands\[0\]') against string commands that are familiar to the program. If a matching command is found at 'commands\[0\]', and the 'commands' vector matches the size (in terms of number of space-delimited words) of a valid command, then the variable 'option' is set to a number corresponding to that command. 'option' is passed to a 'switch' statement which runs the corresponding code block for that command, or prints an 'invalid choice' warning to the console, if the command was not recognized.
>
> Try-catch blocks are also implemented for the commands which are prone to errors resulting from the user passing a parsable but nonetheless invalid command such as an invalid product category or integer out of the available range of the function.
>
> 2
>
> ## Custom command: range
>
> The custom command I decided to implement for this project was a function that would compute the range between the highest ask or bid for a product in the current time-step. The reason I chose to add this functionality is because ranges are a very common metric tracked by traders due to it being viewed by many as a good indicator of the degree of 'risk' associated with a given product or security. High range suggests the price fluctuating to a greater degree at the current time and therefore may be prone to large fluctuations in the near future.
>
> The way in which I implemented the range command was to utilise the\
> functionality of the pre-existing 'min' and 'max' functions, using their return values when passed the product input by the user to subtract the 'min' value from 'max' leaving the difference between the values. The function returns a vector, which also stores the returned values from 'min' and 'max' so that a helpful return message can be printed to the console with the highest and lowest prices a long with their range.
>
>
> ## Optimising the exchange code
>
> The first way in which I set about optimising the exchange code was in
> modifying the 'CSVReader::tokenise' function. Instead of using
> 'find_first_of' and 'substr' to split the lines into tokens, you can
> use I found a faster method using 'strtok_s' which is a slight
> modification on a C function ('strtok') which a (for thread-safe
> tokenization). This is because 'strtok_s' operates directly on the
> input string, whilst 'std::getline' creates additional objects and
> perform additional operations, which can result in slower performance
> when used a large number of times.
>
> The second means by which I optimised the code to process the CSV data
> more efficiently was to modify the method by which tokens are
> converted to an\
> 'OrderBookEntry' object. Firstly, instead of initializing a series of
> individual strings
> to store each element of the input data, I operated directly on it.
> This saves the program from copying data in to string before it can be
> used and allows the program to proceed directly to the point at which
> it performs the necessary operations on the string. Additionally,
> instead of using the Standard Library's 'std::stod' I opted for the C
> functions 'strtod'. This is because
>
> Instead of using 'stod()' to convert the price and amount tokens to
> double values, I used 'strtod()' . This function is faster in most
> circumstances because it uses C-style string-to-number conversion
> operations which tend to have less overhead than their C++
> counterparts.
>
> Finally, using Visual Studio I optimized the code for release as
> opposed to debugging. This removes symbolic debugging information
> which can result in large overhead and thus results in performance
> improvements for the application.
>
