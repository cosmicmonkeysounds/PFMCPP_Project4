
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

Do not delete your previous main. 

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7.  
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */
#if false
namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

        /* 
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 

        it should become:
        */
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif
 /*
 6) compile/link/run to make sure you don't have any errors
 
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

int main()
{
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

    IntType powInt(2);
    powInt.pow(4);
    std::cout << "2 ^ 4 is " << static_cast<int>( powInt );
    powInt.pow( ft );
    std::cout << ", and that to the power of 2.5 is: " << static_cast<int>( powInt ) << "\n";

    FloatType powF(2.4f);
    powF.pow(2.f).pow(anotherDouble);
    std::cout << "and (2.4 ^ 2) ^ 4.04 is: " << static_cast<float>( powF ) << "\n";

    Point p(2, 2);
    p.toString();
    p.multiply(powF);
    p.toString();
    p.multiply(3);
    p.toString();
    std::cout << "\n";
}
