
#include <iostream>
/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Do not delete your previous main. you will be adding to it.

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<NumericType> value;' before
                you'd replace NumericType in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object 
    your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>. 
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 

#11) now that your class is templated, you'll need to adjust your logic in your division function to handle if your input is a zero or not, based on your templated type.  
        - look up how to use std::is_same<>::value on cppreference to determine the type of your template parameter.
        
        - look up how to use std::numeric_limits<>::epsilon() to determine if you're dividing by a floating point 0
        
        - read about Knuth's algorithm here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/

        - in plain-english, you'll need to implement logic like this:
        if your template type is an int
                if your parameter's type is also an int
                        if your parameter is 0
                                don't do the division
                else if it's less than epsilon
                        dont do the divison
        else if it's less than epsilon
                warn about doing the division

        - to make these checks work during compilation, your if() statements will need to be 'constexpr':  if constexpr (expression)

compile/link/run to make sure you don't have any errors

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
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

