// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception> // for std::exception
#include <stdexcept> // for std::domain_error

// a custom exception class derived from std::exception
// It has an integer error code.
class MyException : public std::exception
{
private:
    int error_code; // some additional data about the error

public:
    explicit MyException(int code) // constructor
    {
        error_code = code;
    }

    [[nodiscard]] int get_code() const // getter
    {
        return error_code;
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    // throwing a standard std::out_of_range exception (which is derived from std::exception)
    throw std::out_of_range("Something Even More Custom is out of range");

    return true; // now this line is not reachable
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try // try wrap for the do_even_more_custom_application_logic() call
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
        else // some error but not an exception
            std::cout << "Even More Custom Application Logic Failed." << std::endl;
    }
    catch (std::exception& e) // catch anything derived from std::exception
    {
        std::cout << e.what() << std::endl;
    }

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main

    std::cout << "Leaving Custom Application Logic." << std::endl;

    throw MyException(1); // code 1 can be used to show where the exception occurred
}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception

    if (den == 0) // use std::domain_error here
        throw std::domain_error("Division By Zero in divide() function");
    else
        return (num / den); // simply return the result
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try
    {
        auto result = divide(numerator, denominator);
        // this line is printed only if no exception
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::domain_error& e) // ONLY the exception thrown by divide
    {
        std::cout << e.what() << std::endl; // report the exception
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception
    //  that wraps the whole main function, and displays a message to the console.
    try
    {
        do_division();
        do_custom_application_logic();
    }
    catch (MyException& e) // my custom exception
    {
        std::cout << "A custom MyException exception with error code " << e.get_code() << std::endl;
    }
    catch (std::exception& e) // any other std::exception-derived exception
    {
        std::cout << "A standard exception with message '" << e.what() << "'" << std::endl;
    }
    catch (...) // any non-std::exception-derived exception
    {
        std::cout << "An unknown exception!" << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
