/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Edit your Chapter 5 Part 4 Task and replace its instructions with these instructions
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */

#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator ___() { /* read-only function */ }
    operator ___() { /* read/write function */ }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
namespace example
{
template<typename NumericType>
struct Numeric
{
    //snip
    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }
    //snip
};
}

/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}

#include <iostream>
#include <cmath>
#include <functional>
#include <memory>
#include <limits>
#include <typeinfo>

struct Point
{
    Point( float x_, float y_ ) : x(x_), y(y_) {}

    template<typename T>
    Point( T& a, T& b ) : Point(static_cast<float>(a), static_cast<float>(b) ) { }

    Point& multiply( float m )
    {
        x *= m;
        y *= m;
        return *this;
    }

    template<typename T>
    Point& multiply( T& val )
    {
        return multiply( static_cast<float>(val) );
    }

    void toString() 
    { 
        std::cout << "\nPoint Coords:\nX: " << x << "\nY: " << y << "\n"; 
    }

private:
    float x{0}, y{0};

};

template<typename T>
class Numeric
{
public:

    using Primitive = T;

    Numeric( Primitive val ) : value( new Primitive(val) ) {}

    Numeric& operator += ( const Primitive val )
    {
        *value += val;
        return *this;
    }

    Numeric& operator -= ( const Primitive val )
    {
        *value -= val;
        return *this;
    }

    Numeric& operator *= ( const Primitive val )
    {
        *value *= val;
        return *this;
    }

    Numeric& operator /= ( const Primitive val )
    {   
        if constexpr ( std::is_same< Primitive, int >::value )
        { 
            if constexpr ( std::is_same< decltype(val), const int >::value )
            {
                if( val == 0 )
                {
                    std::cout << "Division by 0 is not allowed with integers! Are you trying to open up a rift in space-time or something?\n";
                    return *this;
                } 
            }
            else if ( val < std::numeric_limits<Primitive>::epsilon() )
            {
                std::cout << "Division by 0 is not allowed with integers! Are you trying to open up a rift in space-time or something?\n";
                return *this;            
            }
        }
        else if ( val < std::numeric_limits<Primitive>::epsilon() )
        {
            std::cout << "Warning, dividing by 0.\n";
        }

        *value /= val;
        return *this;
    } 

    operator Primitive() const { return *value; }

    Numeric& apply( std::function< Numeric&(std::unique_ptr<Primitive>&) > func )
    {
        if ( func ) 
            return func( value );
        std::cout << "Warning: Can't apply a null pointer function.\n";
        return *this;
    }

    Numeric& apply( void(*func)(std::unique_ptr<Primitive>&) )
    {
        if ( func ) 
            func( value );
        return *this;
    }

    Numeric& pow( const Primitive val )
    {
        return powInternal( val );
    }

    template<typename AnotherType>
    Numeric& pow( const AnotherType& val )
    {
        return powInternal( static_cast<Primitive>(val) );
    }

private:

    std::unique_ptr<Primitive> value; 

    Numeric& powInternal( const Primitive val )
    {
        if( value ) *value = static_cast<Primitive>( std::pow(*value, val) );
        return *this;
    }
    
};

template<>
class Numeric<double>
{
public:

    using Primitive = double;

    Numeric( Primitive val ) : value( new Primitive(val) ) {}

    Numeric& operator += ( const Primitive val )
    {
        *value += val;
        return *this;
    }

    Numeric& operator -= ( const Primitive val )
    {
        *value -= val;
        return *this;
    }

    Numeric& operator *= ( const Primitive val )
    {
        *value *= val;
        return *this;
    }

    Numeric& operator /= ( const Primitive val )
    {   
        if ( val < std::numeric_limits<Primitive>::epsilon() )
        {
            std::cout << "Warning, dividing by 0.\n";
        }

        *value /= val;
        return *this;
    } 

    operator Primitive() const { return *value; }

    template<typename Callable>
    auto apply( Callable func ) -> Numeric&
    {
        func( value );
        return *this;
    }

    Numeric& pow( const Primitive val )
    {
        return powInternal( val );
    }

    template<typename AnotherType>
    Numeric& pow( const AnotherType& val )
    {
        return powInternal( static_cast<Primitive>(val) );
    }

private:

    std::unique_ptr<Primitive> value; 

    Numeric& powInternal( const Primitive val )
    {
        if( value ) 
            *value = static_cast<Primitive>( std::pow(*value, val) );

        return *this;
    }

};

// Free Functions

template<typename T>
void freeFuncDouble(std::unique_ptr<T>& val)
{
    *val = static_cast<T>( *val * 2 );
}

void addInt(int& it)
{
    it += 1;
}

void funcFloat(float& ft)
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

    Numeric<int> it(3);
    it += 2;
    std::cout << "\n3 + 2 is " << it;

    it -= 2;
    it += 1;
    std::cout << ", minus 2 add 1 is: " << it << "\n";

    it *= 2;
    it /= 3;
    it += 1;
    it -= 100;
    std::cout << "multiplied by 2, divided by 3, add 1, subtract 100 is:  " << it << "\n\n";

    
    Numeric<int> anotherInt(1);
    Numeric<float> ft(2.5f);
    Numeric<double> dt(1.5);
    anotherInt -= static_cast<int>( ft );
    anotherInt /= static_cast<int>( dt );
    anotherInt /= static_cast<int>( 0.5 );
    std::cout << "1 minus 2.5f times 1.5 divide 0.5 is: " << anotherInt << "\n\n";

    
    Numeric<double> anotherDouble( 10.2 );
    anotherDouble /= 5.0;
    anotherDouble += 2;
    std::cout << "10.2 divide by 5.f plus 2 is: " << anotherDouble << "\n\n";

    // POW tests
    
    Numeric<int> powInt(2);
    powInt.pow(4);
    std::cout << "2 ^ 4 is " << powInt;
    powInt.pow( static_cast<int>(ft) );
    std::cout << ", and that to the power of 2.5 is: " << powInt << "\n";

    
    Numeric<float> powF(2.4f);
    powF.pow(2.f).pow(anotherDouble);
    std::cout << "and (2.4 ^ 2) ^ 4.04 is: " << powF << "\n";

    // Point tests
    
    Point p(2, 2);
    p.toString();
    p.multiply(powF);
    p.toString();
    p.multiply(3);
    p.toString();
    std::cout << "\n";

    // apply() tests

    Numeric<int> intFree(2), intLambda(2);
    using IntType = decltype(intLambda);

    intLambda.apply( [&intLambda](std::unique_ptr<IntType::Primitive> &x) -> Numeric<int>&
    {
        intLambda += *x;
        return intLambda;
    });
    std::cout << "Int Lambda result: " << intLambda << "\n";

    intFree.apply(freeFuncDouble<IntType::Primitive>);
    std::cout << "Int free func result: " << intFree << "\n\n";


    Numeric<float> floatFuncFree(2.f), floatLambda(3.f);
    using FloatType = decltype(floatLambda);

    floatLambda.apply( [&floatLambda](std::unique_ptr<FloatType::Primitive> &x) -> Numeric<float>&
    {
        floatLambda /= *x;
        return floatLambda;
    });
    std::cout << "Float Lambda result: " << floatLambda << "\n";

    floatFuncFree.apply(freeFuncDouble<FloatType::Primitive>);
    std::cout << "Float free func result: " << floatFuncFree << "\n\n";

    
    Numeric<double> doubleFree(1.), doubleLambda(5.);
    using DoubleType = decltype(doubleLambda);

    doubleLambda.apply( [&doubleLambda](std::unique_ptr<DoubleType::Primitive> &x) -> void
    {
        doubleLambda *= *x;
    });
    std::cout << "Double Lambda + free result: " << doubleLambda << "\n";

    doubleFree.apply(freeFuncDouble<DoubleType::Primitive>).apply(freeFuncDouble<DoubleType::Primitive>);
    std::cout << "Chained Double free func result: " << doubleFree << "\n\n";

    Numeric<double> doubleNumeric{2.4};
    using dtNumeric = decltype(doubleNumeric);

    doubleNumeric += Numeric<int>{2};
    std::cout << "2.4 + 2 is: " << doubleNumeric << "\n";

    doubleNumeric.apply( []( std::unique_ptr<dtNumeric::Primitive> &x ) -> void
    { 
        *x = (*x + *x * 0.0001) / *x; 
    });

}

