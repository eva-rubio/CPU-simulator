// Eva Rubio

//(The number of bits in a type is sizeof(T) * CHAR_BIT.)


//std::bitset supports the full set of bitwise operators.
#include <bitset>
...


//to create an std::bitset representing the value, then stream that to cout.
char a = -58;    
std::bitset<8> x(a);
std::cout << x << '\n';

short c = -315;
std::bitset<16> y(c);
std::cout << y << '\n';



//Use on-the-fly conversion to std::bitset. No temporary variables, no loops, no functions, no macros.
#include <iostream>
#include <bitset>

int main() {

/*
C++ manipulator hex function is used to set the basefield format flag for the str stream.

When we set basefield to hex, then integer values inserted into the stream are 
expressed in hexadecimal base (i.e. radix 16). For input streams, when this flag is set, 
then extracted values are also expected to be expressed in hexadecimal base.
*/
	int n = 24;  
  cout << dec << n << '\n';  
  cout << hex << n << '\n';  
  cout << oct << n << '\n';  
  return 0;  


    int a = -58, b = a>>3, c = -315;

    std::cout << "a = " << std::bitset<8>(a)  << std::endl;
    std::cout << "b = " << std::bitset<8>(b)  << std::endl;
    std::cout << "c = " << std::bitset<16>(c) << std::endl;

    int x=5;
  	std::cout<<std::bitset<32>(x)<<std::endl;

  	int v = 0x12345678;
std::cout << std::bitset<32>(v);
}

/*
So a simple C statement such as “a = b * 123;” turns into machine instructions which:

fetch the value of variable “b”
multiply it by the constant “123”
store the result in variable “a”.
Each of those variables are nothing but aliases for specific addresses in RAM, as defined during the transformation to machine code.

*/