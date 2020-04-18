/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
 do not remove anything from main().  you'll be revising your main() to work with these new code changes.
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
         use the proper casting technique to invoke this conversion function
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

 

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
    // void* n = &y
    // *value += *( static_cast< int* >(n) );
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

    IntType it(3);
    it.add(2);

    int i = it;
    std::cout << "\n3 + 2 is " << i;
    i = it.subtract(2).add(1);
    std::cout << ", minus 2 add 1 is: " << i << "\n";
    i = it.multiply(2).divide(3).add(1).subtract(100);
    std::cout << "multiplied by 2, divided by 3, add 1, subtract 100 is:  " << i << "\n\n";

    IntType anotherInt(1);
    FloatType ft(2.5f);
    DoubleType dt(1.5);

    int ii = anotherInt.subtract(ft).divide(dt).divide(DoubleType(0.5));
    std::cout << "1 minus 2.5f times 1.5 divide 0.5 is: " << ii << "\n\n";

    DoubleType anotherDouble(10.2);
    double d = anotherDouble.divide(FloatType(5.f)).add(IntType(2));
    std::cout << "10.2 divide by 5.f plus 2 is: " << d << "\n";

}
