// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_order
    //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

    const std::string account_number = "CharlieBrown42";
    char user_input[20];
    std::cout << "Enter a value: ";
    std::cin.getline(user_input, 20, '\n');// getline standard library function that reads input
    // from a an input stream. The function extracts characters
    // from the input stream and appends it to the char array until
    // the delimiting character is found (\n) or user presses enter key.
    // Code prevents buffer overflow because it truncates the first 20 characters from the input string.

    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;
}
