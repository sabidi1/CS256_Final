//
//  BigNumbers.cpp
//  
//

#include "BigNumbers.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class BigNumbers {
private:
    vector<int> numbers;
public:
    BigNumbers()
    {
               // default constructor
    }
    
    BigNumbers(string stringNumber)
    {
        for (int i = 0; i < stringNumber.length(); i++)
        {
            int converted = (int)stringNumber.at(i) - '0';
            numbers.push_back(converted);
            
            if (int(numbers.size()) > 10000)
            {
                cout << "Error, number is to big" << endl;
                return 0;
            }
        }
    }
    /*
     Adds two BigNumbers objects and returns the result as a BigNumbers object.
     */
    BigNumbers operator + (BigNumbers num)
    {
        BigNumbers tempValue;
        
        if (num.numbers.size() > numbers.size())        //if other number is bigger
        {
            tempValue.numbers.resize(int(num.numbers.size()));
        }
        else
        {
            tempValue.numbers.resize(int(numbers.size()));
        }
        
        int i = int(numbers.size()) - 1;
        int i2 = int(num.numbers.size()) - 1;
        int i3 = int(tempValue.numbers.size()) - 1;
        int addition;
        bool carry = false;
        bool finshAdding = false;
        
        // while-loop until each numbers have been added
        while (!finshAdding)
        {
            if (i < 0)
            {
                addition = num.numbers[i2--];
            }
            else if (i2 < 0)
            {
                addition = numbers[i--];
            } else
            {
                addition = numbers[i--] + num.numbers[i2--];
            }
            
            if (carry)
            {
                addition++;
                carry = false;
            }
            
            if (addition >= 10)
            {
                carry = true;
                addition -= 10;
            }
            
            tempValue.numbers[i3--] = addition;
            
            if (i < 0 && i2 < 0)
            {
                if (carry)
                {
                    //  if there is a carry
                    vector<int>::iterator it = tempValue.numbers.begin();
                    tempValue.numbers.insert(it, 1);
                }
                
                finshAdding = true;
            }
        }
        return tempValue;
    }
    
    /* subtraction(-) operator
     Subtracts two BigNumbers objects
     
     */
    BigNumbers operator - (BigNumbers num)
    {
        BigNumbers tempValue;
    
        if (num.numbers.size() >= numbers.size())
        {
            bool subtractValid = true;
            
            if (num.numbers.size() > numbers.size())        //if other number is smaller
            {
                subtractValid = false;
                
            }
            else            //other number is equal
            {
                for (int i = 0; i < int(numbers.size()); i++)
                {
                    if (num.numbers[i] > numbers[i])
                    {
                        subtractValid = false;
                        break;
                    }
                    else if (num.numbers[i] < numbers[i])
                    {
                        break;
                    }
                }
            }
        }
        }
        
        return tempValue;
    }
    
    /* multiplication(*) operator
     Multiplies two BigNumbers objects
     */
    BigNumbers operator * (BigNumbers num)
    {
        BigNumbers tempValue("0");
        int largerNum = 0;
        const int subtract = 1;

        if (numbers.size() < num.numbers.size())    //other number is bigger
        {
            largerNum = 0;
            
        }
        else if(numbers.size() > num.numbers.size())
        {
            largerNum = 1;
        }
        
        else    //same size
        {
            for (int i = 0; i < int(numbers.size()); i++)
            {
                if (num.numbers[i] > numbers[i])
                {
                    largerNum = 0;
                    break;
                    
                }
                else if (num.numbers[i] < numbers[i])
                {
                    largerNum = 1;
                    break;
                }
            }
        }
        
        if (largerNum == 0)
        {
            while (int(numbers.size()) != 0)
            {
                tempValue = tempValue + num;
                *this -= subtract;
            }
            
        }
        else
        {
            while (int(num.numbers.size()) != 0)
            {
                tempValue = tempValue + *this;
                num = num - subtract;
            }
        }
        
        return tempValue;
    }
    
    // division(/) operator
    BigNumbers operator / (BigNumbers num)
    {
        BigNumbers tempValue;
        
        if ( numbers.size() <= num.numbers.size())       //if other number is bigger
        {
            bool divideValid = true;
            
            if (num.numbers.size() > numbers.size())
            {
                divideValid = false;
            }
            else
            {
                for (int i = 0; i < int(numbers.size()); i++)
                {
                    if (num.numbers[i] > numbers[i])
                    {
                        divideValid = false;
                        break;
                    }
                    else if (num.numbers[i] < numbers[i])
                    {
                        break;
                    }
                }
            }
            
            if (!divideValid)       //cannot divide
            {
                result = 0;
                return result;
            }
        }
        
        BigNumbers addOne("1");
        
        while (numbers.size() != 0)
        {
                *this = *this - num;
                tempValue = tempValue + addOne;
        }
        return tempValue;
    }
    
    // modulus(%) operator
    BigNumbers operator % (BigNumbers num) {
        // cannot be 0
        while(int(numbers.size()) != 0) {
                *this = *this - num;
        }
        
        BigNumbers tempValue("0");
        return tempValue;
    }

};
