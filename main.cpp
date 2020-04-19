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

#include <iostream>
#include <cmath>

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

    IntType& add     ( int );
    IntType& subtract( int );
    IntType& multiply( int );
    IntType& divide  ( int );
    IntType& pow( int );
    IntType& pow( const IntType& );
    IntType& pow( const FloatType& );
    IntType& pow( const DoubleType& );

    operator int() const { return *value; }

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

    FloatType& add     ( float );
    FloatType& subtract( float );
    FloatType& multiply( float );
    FloatType& divide  ( float );

    FloatType& pow( float );
    FloatType& pow( const IntType& );
    FloatType& pow( const FloatType& );
    FloatType& pow( const DoubleType& );

    operator float() const { return *value; }

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

    DoubleType& add     ( double );
    DoubleType& subtract( double );
    DoubleType& multiply( double );
    DoubleType& divide  ( double );
    DoubleType& pow( double );
    DoubleType& pow( const IntType& );
    DoubleType& pow( const FloatType& );
    DoubleType& pow( const DoubleType& );

    operator double() const { return *value; }

private:
    double *value = nullptr;
    DoubleType& powInternal( const double );
};

IntType& IntType::add     ( int y ) { *value += y; return *this; }
IntType& IntType::subtract( int y ) { *value -= y; return *this; }
IntType& IntType::multiply( int y ) { *value *= y; return *this; }

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

IntType& IntType::powInternal( const int y )
{   
    if( value ) { *value = static_cast<int>( std::pow(*value, y) ); }
    return *this;
}

IntType& IntType::pow( int y )                { return powInternal( y ); }
IntType& IntType::pow( const IntType& it )    { return powInternal( static_cast<int>(it) ); }
IntType& IntType::pow( const FloatType& ft )  { return powInternal( static_cast<int>(ft) ); }
IntType& IntType::pow( const DoubleType& dt ) { return powInternal( static_cast<int>(dt) ); }

FloatType& FloatType::add     ( float y ) { *value += y; return *this; }
FloatType& FloatType::subtract( float y ) { *value -= y; return *this; }
FloatType& FloatType::multiply( float y ) { *value *= y; return *this; }

FloatType& FloatType::divide( float y )
{
    if( y == 0.f )
    {
        std::cout << "Warning: You are dividing by zero, you heathen." << "\n";
    }
    *value /= y;
    return *this;
}

FloatType& FloatType::powInternal( const float y )
{   
    if( value ) { *value = static_cast<float>( std::pow(*value, y) ); }
    return *this;
}

FloatType& FloatType::pow( float y )              { return powInternal( y ); }
FloatType& FloatType::pow( const IntType& it )    { return powInternal( static_cast<float>(it) ); }
FloatType& FloatType::pow( const FloatType& ft )  { return powInternal( static_cast<float>(ft) ); }
FloatType& FloatType::pow( const DoubleType& dt ) { return powInternal( static_cast<float>(dt) ); }

DoubleType& DoubleType::add     ( double y ) { *value += y; return *this; }
DoubleType& DoubleType::subtract( double y ) { *value -= y; return *this; }
DoubleType& DoubleType::multiply( double y ) { *value *= y; return *this; }

DoubleType& DoubleType::divide( double y )
{
    if( y == 0. )
    {
        std::cout << "Warning: You are dividing by zero, you lunatic." << "\n";
    }
    *value /= y;
    return *this;
}

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
    std::cout << "10.2 divide by 5.f plus 2 is: " << d << "\n\n";

    IntType powInt(2);
    int pit = powInt.pow(4);
    std::cout << "2 ^ 4 is " << pit;
    pit = powInt.pow( ft );
    std::cout << ", and that to the power of 2.5 is: " << pit << "\n";

    FloatType powF(2.4f);
    float fit = powF.pow(2.f).pow(anotherDouble);
    std::cout << "and (2.4 ^ 2) ^ 4.04 is: " << fit << "\n";

    Point p(2, 2);
    p.toString();
    p.multiply(powF);
    p.toString();
    p.multiply(3);
    p.toString();
    std::cout << "\n";
}
