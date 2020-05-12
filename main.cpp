/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */

#include <iostream>
#include <cmath>
#include <functional>

struct IntType; struct FloatType; struct DoubleType;

struct Point
{
    Point( float x_, float y_ ) : x(x_), y(y_) {}
    Point( const IntType& );
    Point( const FloatType& );
    Point( const DoubleType& );

    Point& multiply( float m )
    {
        x *= m;
        y *= m;
        return *this;
    }

    Point& multiply( IntType& );
    Point& multiply( FloatType& );
    Point& multiply( DoubleType& );

    void toString();

private:
    float x{0}, y{0};

};

struct IntType
{

    IntType( int val )
    {
        value = new int(val);
    }

    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    void operator += (int x)
    {
        *value += x;
    }

    void operator -= (int x)
    {
        *value -= x;
    }

    void operator *= (int x)
    {
        *value *= x;
    }

    void operator /= (int x)
    {
        
        if( x == 0 )
        {
            std::cout << "Division by 0 is not allowed! Are you trying to open up a rift in space-time or something?\n";
        }

        else
        {
            *value /= x;
        }

    }

    IntType& pow( int );
    IntType& pow( const IntType& );
    IntType& pow( const FloatType& );
    IntType& pow( const DoubleType& );

    operator int() const { return *value; }

    IntType& apply( std::function<IntType&(int&)> func )
    {
        if( func ) return func(*value);

        std::cout << "Warning: Can't apply a nullptr function.\n";
        return *this;
    }

    IntType& apply( void(*func)(int&) )
    {
        if( func ) func(*value);
        return *this;
    }

private:
    int *value = nullptr;
    IntType& powInternal( const int );
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
        value = nullptr;
    }

    void operator += (float x)
    {
        *value += x;
    }

    void operator -= (float x)
    {
        *value -= x;
    }

    void operator *= (float x)
    {
        *value *= x;
    }

    void operator /= (float x)
    { 
        if( x == 0.f )
        {
            std::cout << "Dividing by 0 warning! Are you trying to open up a rift in space-time or something?\n";
        }
        *value /= x;
    }

    FloatType& pow( float );
    FloatType& pow( const IntType& );
    FloatType& pow( const FloatType& );
    FloatType& pow( const DoubleType& );

    operator float() const { return *value; }

    FloatType& apply( std::function<FloatType&(float&)> func )
    {
        if( func ) return func(*value);
        std::cout << "Warning: Can't apply a nullptr function.\n";
        return *this;
    }

    FloatType& apply( void(*func)(float&) )
    {
        if( func ) func(*value);
        return *this;
    }

private:
    float *value = nullptr;
    FloatType& powInternal( const float );

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
        value = nullptr;
    }

    void operator += (double x)
    {
        *value += x;
    }

    void operator -= (double x)
    {
        *value -= x;
    }

    void operator *= (double x)
    {
        *value *= x;
    }

    void operator /= (double x)
    { 
        if( x == 0.0 )
        {
            std::cout << "Dividing by 0 warning! Are you trying to open up a rift in space-time or something?\n";
        }
        *value /= x;
    }

    DoubleType& pow( double );
    DoubleType& pow( const IntType& );
    DoubleType& pow( const FloatType& );
    DoubleType& pow( const DoubleType& );

    operator double() const { return *value; }

    DoubleType& apply( std::function<DoubleType&(double&)> func )
    {
        if( func ) return func(*value);
        std::cout << "Warning: Can't apply a nullptr function.\n";
        return *this;
    }

    DoubleType& apply( void(*func)(double&) )
    {
        if( func ) func(*value);
        return *this;
    }

private:
    double *value = nullptr;
    DoubleType& powInternal( const double );
};


IntType& IntType::powInternal( const int y )
{   
    if( value ) *value = static_cast<int>( std::pow(*value, y) );
    return *this;
}

IntType& IntType::pow( int y )                { return powInternal( y ); }
IntType& IntType::pow( const IntType& it )    { return powInternal( static_cast<int>(it) ); }
IntType& IntType::pow( const FloatType& ft )  { return powInternal( static_cast<int>(ft) ); }
IntType& IntType::pow( const DoubleType& dt ) { return powInternal( static_cast<int>(dt) ); }


FloatType& FloatType::powInternal( const float y )
{   
    if( value ) { *value = static_cast<float>( std::pow(*value, y) ); }
    return *this;
}

FloatType& FloatType::pow( float y )              { return powInternal( y ); }
FloatType& FloatType::pow( const IntType& it )    { return powInternal( static_cast<float>(it) ); }
FloatType& FloatType::pow( const FloatType& ft )  { return powInternal( static_cast<float>(ft) ); }
FloatType& FloatType::pow( const DoubleType& dt ) { return powInternal( static_cast<float>(dt) ); }


DoubleType& DoubleType::powInternal( const double y )
{   
    if( value ) { *value = static_cast<double>( std::pow(*value, y) ); }
    return *this;
}

DoubleType& DoubleType::pow( double y )             { return powInternal( y ); }
DoubleType& DoubleType::pow( const IntType& it )    { return powInternal( static_cast<double>(it) ); }
DoubleType& DoubleType::pow( const FloatType& ft )  { return powInternal( static_cast<double>(ft) ); }
DoubleType& DoubleType::pow( const DoubleType& dt ) { return powInternal( static_cast<double>(dt) ); }

Point::Point( const FloatType& ft )  : Point( ft, ft ) {}
Point::Point( const IntType& it )    : Point( static_cast<float>(it), static_cast<float>(it) ) {}
Point::Point( const DoubleType& dt ) : Point( static_cast<float>(dt), static_cast<float>(dt) ) {}

Point& Point::multiply( IntType& it ) { return multiply( static_cast<float>(it) ); }
Point& Point::multiply( FloatType& ft ) { return multiply( static_cast<float>(ft) ); }
Point& Point::multiply( DoubleType& dt ) { return multiply( static_cast<float>(dt) ); }

void Point::toString() { std::cout << "\nPoint Coords:\nX: " << x << "\nY: " << y << "\n"; }

// Free Functions

void addInt(int& it)
{
    it += 1;
}

void funcloat(float& ft)
{
    ft *= 2.f;
}

void halfDouble(double& dt)
{
    dt /= 2.;
}

int main()
{
    // Operator Tests 

    IntType it(3);
    it += 2;
    std::cout << "\n3 + 2 is " << static_cast<int>( it );

    it -= 2;
    it += 1;
    std::cout << ", minus 2 add 1 is: " << static_cast<int>( it ) << "\n";

    it *= 2;
    it /= 3;
    it += 1;
    it -= 100;
    std::cout << "multiplied by 2, divided by 3, add 1, subtract 100 is:  " << static_cast<int>( it ) << "\n\n";

    
    IntType anotherInt(1);
    FloatType ft(2.5f);
    DoubleType dt(1.5);
    anotherInt -= static_cast<int>( ft );
    anotherInt /= static_cast<int>( dt );
    anotherInt /= static_cast<int>( 0.5 );
    std::cout << "1 minus 2.5f times 1.5 divide 0.5 is: " << static_cast<int>( anotherInt ) << "\n\n";

    
    DoubleType anotherDouble( 10.2 );
    anotherDouble /= 5.0;
    anotherDouble += 2;
    std::cout << "10.2 divide by 5.f plus 2 is: " << static_cast<double>( anotherDouble )  << "\n\n";

    // POW tests
    
    IntType powInt(2);
    powInt.pow(4);
    std::cout << "2 ^ 4 is " << static_cast<int>( powInt );
    powInt.pow( ft );
    std::cout << ", and that to the power of 2.5 is: " << static_cast<int>( powInt ) << "\n";

    
    FloatType powF(2.4f);
    powF.pow(2.f).pow(anotherDouble);
    std::cout << "and (2.4 ^ 2) ^ 4.04 is: " << static_cast<float>( powF ) << "\n";

    // Point tests
    
    Point p(2, 2);
    p.toString();
    p.multiply(powF);
    p.toString();
    p.multiply(3);
    p.toString();
    std::cout << "\n";

    // apply() tests

    IntType intFree(2), intLambda(2);
    intLambda.apply( [&intLambda](int& x) -> IntType&
        {
            intLambda += x;
            return intLambda;
        }
    );
    std::cout << "Int Lambda result: " << intLambda << "\n";

    intFree.apply(addInt);
    std::cout << "Int free func result: " << intFree << "\n\n";


    FloatType funcree(2.f), floatLambda(3.f);
    floatLambda.apply( [&floatLambda](float& x) -> FloatType&
        {
            floatLambda /= x;
            return floatLambda;
        }
    );
    std::cout << "Float Lambda result: " << floatLambda << "\n";

    funcree.apply(funcloat);
    std::cout << "Float free func result: " << funcree << "\n\n";

    
    DoubleType doubleFree(1.), doubleLambda(5.);
    doubleLambda.apply( [&doubleLambda](double& x) -> DoubleType&
        {
            doubleLambda *= x;
            return doubleLambda.apply(halfDouble);
        }
    );
    std::cout << "Double Lambda + free result: " << doubleLambda << "\n";

    doubleFree.apply(halfDouble).apply(halfDouble);
    std::cout << "Chained Double free func result: " << doubleFree << "\n\n";

}

