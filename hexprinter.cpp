#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Eva Rubio

using namespace std;

/*

' #define ' - A type of Preprocessor Directive: MACRO. 
	Preprocessors are programs that process our source code before compilation.

Macros are a piece of code in a program which is given some name.
	Whenever this name is encountered by the compiler, 
	 the compiler REPLACES the name with the actual piece of code.

*/


#define MAIN_MEMLENGTH 32
#define MEMLENGTH 0xFFF
#define OPCODE 0xF000	// the opcode is the first 4 bits
#define OPERAND 0x0FFF	// the operand is the last 12 bits

//OPCODE - 11110000 00000000 - 0xF000 -  61,440 - 16 bits

//00110000 00001000 - 0x3008 - 12,296 - IR

// UNSIGNED int. DECIMAL NUMBER. 
// 16 bits long (2 Bytes)

//		- largest number it can hold: 65,535
//		- smallest number: 0.

/*
typedef : Used to give data type a new name
*/

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

ADDS 0s IN FRONT UNTIL THERE ARE 'width' NUMBER AFTER 0x
	ex. (3)0x3008
		(4)0x3008
		(5)0x03008


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



	cpu.IR = 0x3a08;

		cout << "PC: " << cpu.PC <<endl;

		cout << "IR: ";
		cout << cpu.IR << endl;
		HexPrint(cpu.IR, 4);
		cout << endl;

		cout << "\t (Opcode:";
		HexPrint(cpu.getOpcode(), 1);
		cout << ")" << endl;

		cout << "\t (Operand:";
		HexPrint(cpu.getOperand(), 7);
		cout << ")" << endl;

		

		cout << "ACC: ";
		HexPrint(cpu.ACC,4);
		cout << endl;	

		WORD valueForACC;
		WORD myMask = 0xf000;

		WORD myOperand = cpu.getOperand();
		if((myOperand & 0x800) != 0){
			// operand is NEGATIVE
			valueForACC = myOperand | myMask;

			cout << "valueForACC: ";
			HexPrint(valueForACC, 4);
			cout << endl;

		} else {
			valueForACC = myOperand;
			cout << "(positive) valueForACC: ";
			HexPrint(valueForACC, 4);
			cout << endl;
		}

		cpu.ACC = valueForACC;
		cout << " NEW - - ACC: ";
		HexPrint(cpu.ACC,4);
		cout << endl;	

		cout << " ---------------------------------------- " << endl;

		WORD address = 0xfff;
		cpu.PC = address;
		cout << " NEW - - PC: " << endl;
		cout << cpu.PC << endl;
		cout << "now in hex: " << endl;
		HexPrint(cpu.PC,4);
		cout << endl;

//----------------------
		memory[12] = 0xfff;

		cpu.ACC = cpu.ACC + memory[12];

		
		cout << " ADDITION VALUE OF  - - ACC: ";
		HexPrint(cpu.ACC,4);
		cout << endl;


/**
	memory[0] = 0x0000;
	memory[1] = 0x0001;
	memory[2] = 1;
	memory[3] = 0xf;
	memory[4] = -10;		//Hex signed 2's comple 0xFFF6
	memory[5] = memory[4] + memory[2];
	memory[6] = (-10 - (-5));  //Hex signed 2's compl 0xFFFB
**/

/*

	cout << "memory contents:" << endl;
	for(int i=0;i<MAIN_MEMLENGTH;i++){
		cout << "mem[";
		HexPrint(i,3);
		cout << "] == ";
		HexPrint(memory[i],4);
		cout << endl;
	}
	for(int i=MAIN_MEMLENGTH;i<MEMLENGTH;i++){
		if(memory[i]!=0){
			cout << "mem[";
			HexPrint(i,3);
			cout << "] == ";
			HexPrint(memory[i],4);
			cout << endl;
		}
	}





	
	int width1 = 10;
	int width2 = 2;
	int width3 = 3;

	WORD unsigInt1 = 23;
	cout << "HexPrint : unsigInt1 (23), width2 (2) " << endl;
	HexPrint(unsigInt1, width2);
	cout << endl;
	cout << endl;
	

	WORD unsigInt2 = 60000;
	cout << "HexPrint : unsigInt2 (60000), width1 (10) " << endl;
	HexPrint(unsigInt2, width1);
	cout << endl;
	cout << endl;


	WORD unsigInt3 = 2;
	cout << "HexPrint : unsigInt3 (2), width3 (3) " << endl;
	HexPrint(unsigInt3, width3);
	cout << endl;


	uint16_t x;
	uint16_t y;
	uint16_t z;
	cout << endl;
    cout << "ints Byte size: " << sizeof(int) << endl;
    cout << "unsigned ints Byte size: " << sizeof(unsigned int) << endl;
    cout << "uint16_t Byte size: " << sizeof(uint16_t) << endl;
    cout << "int16_t Byte size: " << sizeof(int16_t) << endl;
   	cout << endl;
   	cout << endl;


    cout << "x? > ";
    cin >> x;
    cout << endl;
    cout << "y? > ";
    cin >> y;
    cout << endl;
    cout << " -  x: " << x << endl;
    cout << " - (int)x: " << (int)x << endl;
    cout << " - (int16_t)x: " << (int16_t)x << endl;
    cout << " - (uint16_t)x: " << (uint16_t)x << endl;
    cout << " - x in hex: ";
    HexPrint(x,4);

    z = x + y;
	
	cout << endl;

    cout << endl;
    cout << " -  z: " << z << endl;
    cout << " - (int)z: " << (int)z << endl;
    cout << " - (int16_t)z: " << (int16_t)z << endl;
    cout << " - (uint16_t)z: " << (uint16_t)z << endl;
    cout << " - z in hex: ";
    HexPrint(z,4);
*/
	return 0;
}