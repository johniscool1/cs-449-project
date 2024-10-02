#include "functions.hpp"
#include <iostream>

/* Add the members of a number class together
*/

int numbers::add() 
{
 return number1 + number2;
}

/* Subtract the members of a number class together
*/

int numbers::subtract() 
{
 /* oh no, it looks like the programmer coppied and pasted
    the add function and forgot to change the opertor to subtract!
    Hopefully the unit test will catch this. */ 
 return number1 + number2;
}