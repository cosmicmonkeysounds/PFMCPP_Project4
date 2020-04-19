/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
     e) the pow() functions should be chainable.
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
         powInternal() should be chainable.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) Add to main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

struct Point
{
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
private:
    float x{0}, y{0};
};



 

#include <iostream>

struct IntType
{

    IntType( int val ) 
    {
        value = new int(val);
    }

    ~IntType()
    {
        delete value;
    }

    IntType& add( int y );
    IntType& subtract( int y );
    IntType& multiply( int y );
    IntType& divide( int y );

    operator int() { return *value; }

private:
    int *value = nullptr;

};

struct FloatType
{
    
    FloatType( float val )
    {
        value = new float(val);
    }

    ~FloatType()
    {
        delete value;
    }

    FloatType& add( float y );
    FloatType& subtract( float y );
    FloatType& multiply( float y );
    FloatType& divide( float y );

    operator float() { return *value; }

private:
    float *value = nullptr;

};

struct DoubleType
{

    DoubleType( double val )
    {
        value = new double(val);
    }

    ~DoubleType()
    {
        delete value;
    }

    DoubleType& add( double y );
    DoubleType& subtract( double y );
    DoubleType& multiply( double y );
    DoubleType& divide( double y );

    operator double() { return *value; }

private:
    double *value = nullptr;

};

IntType& IntType::add( int y )
{   
    *value += y;
    return *this;
}

IntType& IntType::subtract( int y )
{
    *value -= y;
    return *this;
}

IntType& IntType::multiply( int y )
{   
    *value *= y;
    return *this;
}

IntType& IntType::divide( int y )
{

    if( y == 0 )
    {
        std::cout << "Division by 0 is not allowed! Are you trying to open up a rift in space-time or something?" << "\n";
    }

    else
    {
        *value /= y;
    }
    
    return *this;
}

FloatType& FloatType::add( float y )
{
    *value += y;
    return *this;
}

FloatType& FloatType::subtract( float y )
{
    *value -= y;
    return *this;
}

FloatType& FloatType::multiply( float y )
{
    *value *= y;
    return *this;
}

FloatType& FloatType::divide( float y )
{
    if( y == 0.f )
    {
        std::cout << "Warning: You are dividing by zero, you heathen." << "\n";
    }
    *value /= y;
    return *this;
}

DoubleType& DoubleType::add( double y )
{
    *value += y;
    return *this;
}


DoubleType& DoubleType::subtract( double y )
{
    *value -= y;
    return *this;
}

DoubleType& DoubleType::multiply( double y )
{
    *value *= y;
    return *this;
}

DoubleType& DoubleType::divide( double y )
{
    if( y == 0. )
    {
        std::cout << "Warning: You are dividing by zero, you lunatic." << "\n";
    }
    *value /= y;
    return *this;
}

int main()
{

    IntType it( 3 );
    it.add( 2 );
    int i = it;
    std::cout << "\n3 + 2 is " << i;

    i = it.subtract( 2 ).add( 1 );
    std::cout << ", minus 2 add 1 is: " << i << "\n";

    i = it.multiply(2).divide(3).add(1).subtract(100);
    std::cout << "multiplied by 2, divided by 3, add 1, subtract 100 is:  " << i << "\n\n";


    IntType anotherInt(1);
    FloatType ft(2.5f);
    DoubleType dt(1.5);

    int ii = anotherInt.subtract( static_cast<int>(ft) ).divide( static_cast<int>(dt) ).divide( static_cast<int>(DoubleType(0.5)) );
    std::cout << "1 minus 2.5f times 1.5 divide 0.5 is: " << ii << "\n\n";

    DoubleType anotherDouble( 10.2 );
    double d = anotherDouble.divide( static_cast<double>( FloatType(5.f)) ).add( static_cast<double>(IntType(2)) );
    std::cout << "10.2 divide by 5.f plus 2 is: " << d << "\n";

}
