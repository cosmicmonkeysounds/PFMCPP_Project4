/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1

 Purpose:  This project will take you through the process of writing a class that wraps a numeric type, beginning with writing simple member functions and ending with a fully templated class with lots of functionality. 
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.
 
 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 3) implement the appropriate action in the member function. 
         a) Be aware that floating point division by 0 is legal, but integer division by 0 will crash your program.  
         b) Handle this possible input when you write your divide() functions.
         c) you should warn the user if they're doing floating-point-division-by-zero but not prevent the division from happening
         d) you should warn AND prevent the division from happening if it is an integer-division-by-zero.
 
 4) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 5) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 6) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 7) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>

struct IntType
{
    int add( int lhs, int rhs);
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

int IntType::add( int lhs, int rhs )
{
    return lhs + rhs;
}

int IntType::subtract( int lhs, int rhs )
{
    return lhs - rhs;
}

int IntType::multiply( int lhs, int rhs )
{
    return lhs * rhs;
}

int IntType::divide( int lhs, int rhs)
{
    if( lhs == 0 || rhs == 0)
    {
        std::cout << "Division by 0 is not allowed! Are you trying to open up a rift in space-time or something?" << std::endl;
        return 0;
    }
    return lhs / rhs;
}

struct FloatType
{
    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

float FloatType::add( float lhs, float rhs)
{
    return lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs)
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs)
{
    return lhs * rhs;
}

float FloatType::divide( float lhs, float rhs)
{
    if(lhs == 0.f || rhs == 0.f)
    {
        std::cout << "Warning: You are dividing by zero, you heathen." << std::endl;
    }

    return lhs / rhs;
}

struct DoubleType
{
    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

double DoubleType::add( double lhs, double rhs)
{
    return lhs + rhs;
}

double DoubleType::subtract( double lhs, double rhs)
{
    return lhs - rhs;
}

double DoubleType::multiply( double lhs, double rhs)
{
    return lhs * rhs;
}

double DoubleType::divide( double lhs, double rhs)
{
    if(lhs == 0. || rhs == 0.)
    {
        std::cout << "Warning: You are dividing by zero, you lunatic." << std::endl;
    }

    return lhs / rhs;
}

int main()
{
    std::cout << "good to go!" << std::endl;

    IntType it;
    auto intResult = it.add(1, 2);
    std::cout << "1 + 2 is: " << intResult << std::endl;
    std::cout << "1 - 2 is: " << it.subtract(1, 2) << std::endl;
    std::cout << "1 * 2 is: " << it.multiply(1, 2) << std::endl;
    std::cout << "1 / 2 is: " << it.divide(1, 2) << std::endl;
    std::cout << "0 / 2 is: " << it.divide(0, 2) << std::endl;

    FloatType ft;
    auto floatResult = ft.add(2.5f, 4.5f);
    std::cout << "2.5 + 4.5 is: " << floatResult << std::endl;
    std::cout << "4.6 - 2.1 is: " << ft.subtract(4.6f, 2.1f) << std::endl;
    std::cout << "3.2 * 2.1 is: " << ft.multiply(3.2f, 2.1f) << std::endl;
    std::cout << "1.2 / 100.23 is: " << ft.divide(1.2f, 100.23f) << std::endl;
    std::cout << "20.1 / 0 is: " << ft.divide(20.1f, 0.f) << std::endl;

    DoubleType dt;
    auto doubleResult = dt.add(2.5, 4.5);
    std::cout << "2.5 + 4.5 is: " << doubleResult << std::endl;
    std::cout << "1.2 - 2.1 is: " << dt.subtract(1.2, 2.1) << std::endl;
    std::cout << "3.2 * 2.1 is: " << dt.multiply(3.2, 2.1) << std::endl;
    std::cout << "1.2 / 100.23 is: " << dt.divide(1.2, 100.23) << std::endl;
    std::cout << "20.1 / 0 is: " << dt.divide(20.1, 0.) << std::endl;
}
