#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Author: Eva Rubio

using namespace std;

#define MAIN_MEMLENGTH 32
#define MEMLENGTH 0xFFF
#define OPCODE 0xF000	// the opcode is the first 4 bits
#define OPERAND 0x0FFF	// the operand is the last 12 bits


// UNSIGNED int. DECIMAL NUMBER. 
// 16 bits long (2 Bytes)

//		- largest number it can hold: 65,535
//		- smallest number: 0.
typedef uint16_t WORD; // word is an (unsigned) int, 16 bits

void HexPrint(WORD val, int width);


struct cpu_t{
	int PC;				// this is the CPU's program counter
	WORD ACC;			// this is the CPU's accumulator
	WORD IR;			// this is the CPU's instruction register

	// a few helpful methods.  NOTHING in this struct should change.
	WORD getOpcode(){
		

		return (IR & OPCODE) >> 12;
	}

	WORD getOperand(){
		return IR & OPERAND;
	}

	void init(){
		PC=0;
		ACC=0;
		IR=0x0000;
	}
};
/**
 ** initMachine() initializes the state of the virtual machine state.
 ** (1) zeros out the CPU registers
 ** (2) sets the program counter to the start of memory
 ** (3) fills memory with zeros
 **/
void initMachine(cpu_t &cpu, WORD memory[])
{
	cpu.init();
	for(int i=0;i<MEMLENGTH;i++){
		memory[i] = 0x0000;
	}
}
/** this function will print a hex version of the value you give (an UNsigned 16bit int)
 ** it, front padded with as many zeros as needed to fit a width
 ** of 'width' --- for example HexPrint(23,2) prints 17
 ** and HexPrint(32,3) prints 020
 ** it does NOT print a newline
 **/
void HexPrint(WORD val, int width)
{
	/*

	C++ defines some format flags for standard input and output, 
	which can be manipulated with the flags() function.

	- ios::hex	Numeric values are displayed in hexidecimal.

	- ios::dec	Numeric values are displayed in decimal.
	*/


	cout << "0x" ;
	 // switch to hex
	cout.flags(ios::hex);

	// set zero paddnig
	cout.fill('0');
	cout.width(width);

	// print the val
	cout << val ;

	// switch back to decimal
	cout.flags(ios::dec);
}
int main (int argc, char *argv[])
{
	cpu_t cpu;
	WORD memory[MEMLENGTH];	// this is the system memory

	initMachine(cpu, memory); // clear out the virtual system

	cpu.IR = 0x3008;


	cout << "PC: " << cpu.PC <<endl;
	cout << " PURE RAW - IR : " << cpu.IR  << endl;
	cout << " hex IR: (4)";
	HexPrint(cpu.IR, 4);
	cout << endl;

	

	

	cout << " PURE RAW - OPCODE : " <<  OPCODE << endl;

	cout << " getOpcode(): " << endl;
	cout << " Yes shift -(IR & OPCODE) >> 12 : " << ((cpu.IR & OPCODE) >> 12) << endl;

	cout << "-----------------" << endl;
	cout << "\t (HexPrint(1) - Opcode:";
	HexPrint(cpu.getOpcode(), 1);
	cout << ")" << endl;
	cout << "\t (HexPrint(2) - Opcode:";
	HexPrint(cpu.getOpcode(), 2);
	cout << ")" << endl;
	cout << "\t (HexPrint(0) - Opcode:";
	HexPrint(cpu.getOpcode(), 0);
	cout << ")" << endl;


/*

	0x23

	(0X22)

	cout << "PC: " << cpu.PC <<endl;
	cout << "IR: (4)";
	HexPrint(cpu.IR, 4);
	cout << endl;
	cout << "IR: (3)";
	HexPrint(cpu.IR, 3);
	cout << endl;
	cout << "IR: (5)";
	HexPrint(cpu.IR, 5);
	cout << endl;
*/
}