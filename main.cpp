/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */


struct A {};

struct HeapA
{
    A* a = new A();

    ~HeapA()
    {
        delete a;
    }
};


 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
        These functions should return the result of calling the function that takes the primitive.
     
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << "\n";  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
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
