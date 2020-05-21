
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

        - in plain-english, you'll need to implement this logic:
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
        }
    );
    std::cout << "Int Lambda result: " << intLambda << "\n";

    intFree.apply(freeFuncDouble<IntType::Primitive>);
    std::cout << "Int free func result: " << intFree << "\n\n";


    Numeric<float> floatFuncFree(2.f), floatLambda(3.f);
    using FloatType = decltype(floatLambda);

    floatLambda.apply( [&floatLambda](std::unique_ptr<FloatType::Primitive> &x) -> Numeric<float>&
        {
            floatLambda /= *x;
            return floatLambda;
        }
    );
    std::cout << "Float Lambda result: " << floatLambda << "\n";

    floatFuncFree.apply(freeFuncDouble<FloatType::Primitive>);
    std::cout << "Float free func result: " << floatFuncFree << "\n\n";

    
    Numeric<double> doubleFree(1.), doubleLambda(5.);
    using DoubleType = decltype(doubleLambda);

    doubleLambda.apply( [&doubleLambda](std::unique_ptr<DoubleType::Primitive> &x) -> void
        {
            doubleLambda *= *x;
        }
    );
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
        }
    );

}

