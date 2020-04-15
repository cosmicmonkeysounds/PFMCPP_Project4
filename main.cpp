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

struct FloatType; 
struct DoubleType;

struct IntType
{
    int *value = nullptr;

    IntType( int val ) 
    {
        value = new int(val);
    }

    ~IntType()
    {
        delete value;
    }

    IntType& add( int y );
    IntType& add( const IntType& it );
    IntType& add( const FloatType& ft );
    IntType& add( const DoubleType& dt );

    IntType& subtract( int y );
    IntType& subtract( const IntType& it );
    IntType& subtract( const FloatType& ft );
    IntType& subtract( const DoubleType& dt );

    IntType& multiply( int y );
    IntType& multiply( const IntType& it );
    IntType& multiply( const FloatType& ft );
    IntType& multiply( const DoubleType& dt );

    IntType& divide( int y );
    IntType& divide( const IntType& it );
    IntType& divide( const FloatType& ft );
    IntType& divide( const DoubleType& dt );
};

struct FloatType
{
    float *value = nullptr;

    FloatType( float val )
    {
        value = new float(val);
    }

    ~FloatType()
    {
        delete value;
    }

    FloatType& add( float y );
    FloatType& add( const IntType& it );
    FloatType& add( const FloatType& ft );
    FloatType& add( const DoubleType& dt );

    FloatType& subtract( float y );
    FloatType& subtract( const IntType& it );
    FloatType& subtract( const FloatType& ft );
    FloatType& subtract( const DoubleType& dt );

    FloatType& multiply( float y );
    FloatType& multiply( const IntType& it );
    FloatType& mulitply( const FloatType& ft );
    FloatType& multiply( const DoubleType& dt );

    FloatType& divide( float y );
    FloatType& divide( const IntType& it );
    FloatType& divide( const FloatType& ft );
    FloatType& divide( const DoubleType& dt );
};

struct DoubleType
{
    double *value = nullptr;

    DoubleType( double val )
    {
        value = new double(val);
    }

    ~DoubleType()
    {
        delete value;
    }

    DoubleType& add( double y );
    DoubleType& add( const IntType& it );
    DoubleType& add( const FloatType& ft );
    DoubleType& add( const DoubleType& dt );

    DoubleType& subtract( double y );
    DoubleType& subtract( const IntType& it );
    DoubleType& subtract( const FloatType& ft );
    DoubleType& subtract( const DoubleType& dt );
    
    DoubleType& multiply( double y );
    DoubleType& multiply( const IntType& it );
    DoubleType& multiply( const FloatType& ft );
    DoubleType& multiply( const DoubleType& dt );

    DoubleType& divide( double y );
    DoubleType& divide( const IntType& it );
    DoubleType& divide( const FloatType& ft );
    DoubleType& divide( const DoubleType& dt );
};

IntType& IntType::add( int y )
{
    *value += y;
    return *this;
}

IntType& IntType::add( const IntType& it )
{
    return add( *it.value );
}

IntType& IntType::add( const FloatType& ft )
{
    return add( static_cast<int>( *ft.value ) );
}

IntType& IntType::add( const DoubleType& dt )
{
    return add( static_cast<int>( *dt.value ) );
}

IntType& IntType::subtract( int y )
{
    *value -= y;
    return *this;
}

IntType& IntType::subtract( const IntType& it )
{
    return subtract( *it.value );
}

IntType& IntType::subtract( const FloatType& ft )
{
    return subtract( static_cast<int>( *ft.value ) );
}

IntType& IntType::subtract( const DoubleType& dt )
{
    return subtract( static_cast<int>( *dt.value ) );
}

IntType& IntType::multiply( int y )
{   
    *value *= y;
    return *this;
}

IntType& IntType::multiply( const IntType& it )
{
    return multiply( *it.value );
}

IntType& IntType::multiply( const FloatType& ft )
{
    return multiply( static_cast<int>( *ft.value ) );
}

IntType& IntType::multiply( const DoubleType& dt )
{
    return multiply( static_cast<int>( *dt.value ) );
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

IntType& IntType::divide( const IntType& it )
{
    return divide( *it.value );
}

IntType& IntType::divide( const FloatType& ft )
{
    return divide( static_cast<int>( *ft.value ) );
}

IntType& IntType::divide( const DoubleType& dt )
{
    return divide( static_cast<int>( *dt.value ) );
}

FloatType& FloatType::add( float y )
{
    *value += y;
    return *this;
}

FloatType& FloatType::add( const IntType& it )
{
    return add( static_cast<float>( *it.value ) );
}

FloatType& FloatType::add( const FloatType& ft )
{
    return add( *ft.value );
}

FloatType& FloatType::add( const DoubleType& dt )
{
    return add( static_cast<float>( *dt.value ) );
}

FloatType& FloatType::subtract( float y )
{
    *value -= y;
    return *this;
}

FloatType& FloatType::subtract( const IntType& it )
{
    return subtract( static_cast<float>( *it.value ) );
}

FloatType& FloatType::subtract( const FloatType& ft )
{
    return subtract( *ft.value );
}

FloatType& FloatType::subtract( const DoubleType& dt )
{
    return subtract( static_cast<float>( *dt.value ) );
}

FloatType& FloatType::multiply( float y )
{
    *value *= y;
    return *this;
}

FloatType& FloatType::multiply( const IntType& it )
{
    return multiply( static_cast<float>( *it.value ) );
}

FloatType& FloatType::mulitply( const FloatType& ft )
{
    return multiply( *ft.value );
}

FloatType& FloatType::multiply( const DoubleType& dt )
{
    return multiply( static_cast<float>( *dt.value ) );
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

FloatType& FloatType::divide( const IntType& it )
{
    return divide( static_cast<float>( *it.value ) );
}

FloatType& FloatType::divide( const FloatType& ft )
{
    return divide( *ft.value );
}

FloatType& FloatType::divide( const DoubleType& dt )
{
    return divide( static_cast<float>( *dt.value ) );
}

DoubleType& DoubleType::add( double y )
{
    *value += y;
    return *this;
}

DoubleType& DoubleType::add( const IntType& it )
{
    return add( static_cast<double>( *it.value ) );
}

DoubleType& DoubleType::add( const FloatType& ft )
{
    return add( static_cast<double>( *ft.value ) );
}

DoubleType& DoubleType::add( const DoubleType& dt )
{
    return add( *dt.value );
}

DoubleType& DoubleType::subtract( double y )
{
    *value -= y;
    return *this;
}

DoubleType& DoubleType::subtract( const IntType& it )
{
    return subtract( static_cast<double>( *it.value ) );
}

DoubleType& DoubleType::subtract( const FloatType& ft )
{
    return subtract( static_cast<double>( *ft.value ) );
}

DoubleType& DoubleType::subtract( const DoubleType& dt )
{
    return subtract( *dt.value );
}

DoubleType& DoubleType::multiply( double y )
{
    *value *= y;
    return *this;
}

DoubleType& DoubleType::multiply( const IntType& it )
{
    return multiply( static_cast<double>( *it.value ) );
}

DoubleType& DoubleType::multiply( const FloatType& ft )
{
    return multiply( static_cast<double>( *ft.value ) );
}

DoubleType& DoubleType::multiply( const DoubleType& dt )
{
    return multiply( *dt.value );
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

DoubleType& DoubleType::divide( const IntType& it )
{
    return divide( static_cast<double>( *it.value ) );
}

DoubleType& DoubleType::divide( const FloatType& ft )
{
    return divide( static_cast<double>( *ft.value ) );
}

DoubleType& DoubleType::divide( const DoubleType& dt )
{
    return divide( *dt.value );
}

int main()
{

    IntType it(3);
    it.add(2);
    std::cout << "\n3 + 2 is: " << *it.value << "\n";
    it.subtract(2).add(1);
    std::cout << "minus 2 add 1 is: " << *it.value << "\n";
    std::cout << "multiplied by 2, divided by 3, add 1, subtract 100 is:  " << 
    *it.multiply(2).divide(3).add(1).subtract(100).value << "\n\n";

    IntType anotherInt(1);
    FloatType ft(2.5f);
    DoubleType dt(1.5);
    std::cout << "1 minus 2.5f times 1.5 divide 0.5 is: " << *anotherInt.subtract(ft).divide(dt).divide(DoubleType(0.5)).value << "\n\n";

    DoubleType anotherDouble(10.2);
    std::cout << "10.2 divide by 5.f plus 2 is: " << *anotherDouble.divide(FloatType(5.f)).add(IntType(2)).value << "\n";

}
