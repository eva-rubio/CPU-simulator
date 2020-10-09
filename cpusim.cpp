//============================================================================
// Name        : cpusim.cpp
// Author      : EVA RUBIO & MICHAEL OCEAN
// Version     : 1.2
// Copyright   : GPLv3
// Description : Fetch and Execute Simulator Skeleton for csc380.
//   based on the LMC, LC-3, and Pencil and Paper computer ISAs
//============================================================================

// 				>>>>>>> REFERENCE LINKS AT THE END OF FILE. 

#include "cpusim.h"
#include <sstream>
// look at the cpusim.h to see what methods are defined there
// and the definition for cpu_t

/**
* Returns true if char '-' not at the beguining of string, thus, all are digits. 
* 	False if the string has a preciding '-', thus the value will be treaded as negative.
**/

bool isInputPositive(string userString){
	for (int i = 0; i < userString.length(); i++){
		// "isDigit()" - Check if character is decimal digit.
		if (isdigit(userString[i]) == false){
			return false; 
		}
	}  
	return true;
}


/**
 ** the body of this function MUST BE CHANGED to do
 ** what fetch does -- modify the cpu as if a fetch happened
 **/
void fetch(cpu_t &cpu, WORD memory[])
{
	cpu.IR = memory[cpu.PC];
}

/**
 ** this function MUST BE CHANGED to do what execute does.
 ** Right now, It should look at the IR and figure out what
 ** to do.  Right now it only understands the HALT opcode.
 **
 ** this function should (and currently) returns:
 **  false if execution should stop (i.e., the opcode is HALT)
 **  true in all other circumstances
 **
 **/
bool execute(cpu_t &cpu, WORD memory[])
{

	WORD myOperand = cpu.getOperand();

	// do what execute should do
	if(cpu.getOpcode()==0x0) // this is the opcode for HALT
	{
		// do nothing, but return false
		// which tells the main loop that the program should stop
		return false;
	}
	else if(cpu.getOpcode()==0x1) // ADD
	{
		// TODO: do what ADD does
		// remember: for ADD/SUB, values are WORDs but WORDs don't have
		// signed values; be sure to test with negative user input!
/*		WORD valueToAdd = memory[myOperand];

		if((valueToAdd & 0x0800) != 0){
			// value stored is NEGATIVE
			int16_t signedValue = (int16_t)valueToAdd;
		}
		*/

		cpu.ACC = cpu.ACC + memory[myOperand];


	}
	else if(cpu.getOpcode()==0x2) // SUB
	{
		// TODO: do what ADD does
		// remember: for ADD/SUB, values are WORDs but WORDs don't have
		// signed values; be sure to test with negative user input!

		cpu.ACC = cpu.ACC - memory[myOperand];


	}
	else if(cpu.getOpcode()==0x3) // LDA
	{
		
		cpu.ACC = memory[myOperand];


	}
	else if(cpu.getOpcode()==0xb) // LD#
	{
		WORD valueForACC;
		WORD myMask = 0xf000;

		if((myOperand & 0x800) != 0){
			// operand is NEGATIVE
			valueForACC = myOperand | myMask;

			cout << "(negative) valueForACC: ";
			HexPrint(valueForACC, 4);
			cout << endl;

		} else {
			valueForACC = myOperand;
			cout << "(positive) valueForACC: ";
			HexPrint(valueForACC, 4);
			cout << endl;
		}
		cpu.ACC = valueForACC;
	}
	else if(cpu.getOpcode()==0xe) // LDp
	{

		WORD addresToFind = memory[myOperand];

		cpu.ACC = memory[addresToFind];

	}
	else if(cpu.getOpcode()==0x4) // STRA
	{
		
		memory[myOperand] = cpu.ACC;

	}
	else if(cpu.getOpcode()==0xc) // STRp
	{
		WORD addresToFind = memory[myOperand];
		
		memory[addresToFind] = cpu.ACC;

	}
	/*
		memory[n] = user input
		Prompt the user and take input.
		User will enter Decimal Values. 
	*/
	else if(cpu.getOpcode()==0x5) // INP
	{
		/*
stringstream class:
	- Stream class to operate on strings.
	- A 'stringstream', associates a string object with a stream allowing you to read from the string as if it were a stream (like cin).
	- stringstream class provides an interface to manipulate strings as if they were input/output streams.
	- (a convenient way to manipulate strings). Useful for parsing input. 

	* operator>>	Public member function to: Extract formatted input. (inherited from istream)
						 - read something from the stringstream object.
						 - Performs a formatted input operation (extraction).
						 - We are READING FROM THE STREAM (like reading from a file).
		*/

		string userInputString;

		cin >> userInputString;
		
		cout << "INPUT." << endl;
		cout << " - Decimal value to be introcued: ";
		cout << userInputString << endl;
		
		cout << " - Value will be stored at memory address: ";
		HexPrint(myOperand, 3);
		cout << endl;
		

		//Chech if value given should be treated as Pos or Neg.

		// A string is inserted into the stringstream and then (with >>) it is extracted as integer values.
		if (isInputPositive(userInputString)) {
			uint16_t posInput = 0;

			/* STRINGSTREAM CONSTRUCTOR.
				Using the initialization constructor. Where it:
					- Constructs a 'stringstream' object, with a copy of 'str' as content.

			* @param userInputString 	The String object to be copied to internal buffer. (A string object, whose content is copied).
			*/
			stringstream tochange(userInputString);


			/* tochange >> posInput;
				- Writing the contents of the 'stringstream' buffer, to the variable 'posInput'.
				- it is reading a value from 'tochange' and is assigning that value into the variable 'posInput'

				(After it, posInput contains the int value of the contents of the stringstream object). */
			tochange >> posInput;

			memory[myOperand] = posInput;

			cout << " - The (+) Value in Hex representation: ";
			HexPrint(posInput, 3);
			cout << endl;
		

		} else { 	//input value should be treated as NEGATIVE.

			/*
			string.begin() --> it references the first element of 'string'.
			
			string.erase(iterator-position) --> erases de chatacter at the position given.
				- Return the first character after the last character removed. 		*/

			// Deletes the first character of the string
			userInputString.erase(userInputString.begin());
			uint16_t absolValue = 0;

			stringstream tochange(userInputString);

			tochange >> absolValue;

			uint16_t negNum = -(uint16_t)absolValue;

			memory[myOperand] = negNum;

			cout << " - The (-) Value in Hex representation: ";
			HexPrint(negNum, 3);
			cout << endl;

		}
	}
	/*
		"cout << dec "
		C++ manipulator 'dec' function is used to set the basefield format flag for the str stream.
	*/
	else if(cpu.getOpcode()==0x6) // OUT
	{
		
		WORD valueToOutput = memory[myOperand];
		cout << "OUTPUT." << endl;
		cout << " - Value stored at memory address: ";
		HexPrint(myOperand, 3);
		cout << endl;
		cout << " - Contains the decimal number of: ";

		// If positive:
		if((valueToOutput & 0x8000) == 0){

			cout << dec << valueToOutput << '\n';

		} else {
			// casting it to signed integer to properly display value.
			cout << dec << (int16_t)valueToOutput << '\n';
		}

	}
	else if(cpu.getOpcode()==0x9) // BRA
	{
		
		cpu.PC = memory[myOperand];
	}
	else if(cpu.getOpcode()==0x7) // BRAgz
	{
		// if positive:
		if(((cpu.ACC & 0x8000) == 0) && (cpu.ACC > 0)){

			cpu.PC = memory[myOperand];
		}
	}
	else if(cpu.getOpcode()==0x8) // BR#
	{
		
		cpu.PC = myOperand;

	}
	else if(cpu.getOpcode()==0xa) // BRgz#
	{
		//If positive:
		if(((cpu.ACC & 0x8000) == 0) && (cpu.ACC > 0)){

			cpu.PC = myOperand;
		}
	}
	else if(cpu.getOpcode()==0xf) // NOP
	{

	}
	

	// all non-HALT branches wind up down here, where we return
	// true, because the program is still running
	return true;
}

/**
 ** this function MUST BE CHANGED to modify the CPU accordingly
 **/
void increment(cpu_t &cpu)
{
	cpu.PC++;
}

/**
 ** the main function -- this is where the magic happens
 ** you should NOT need to change this, but DO look at
 ** what it does!!
 **/
int main (int argc, char *argv[])
{
	// keep track of what cycle this is
	int loops=0;
	bool running = true;

	// CPU registers and memory
	// Essentially, these make up our virtual machine
	cpu_t cpu;
	WORD memory[MEMLENGTH];	// this is the system memory

	initMachine(cpu, memory); // clear out the virtual system

	readMemoryFromStdInput(memory);	// read memory from input/file

	debugMachineState(loops, cpu, memory); // print the state (for confirmation sake)

	while(running) // is the machine still running?
	{
		fetch(cpu, memory);

		increment(cpu);

		// (execute returns FALSE if it just ran a STOP instruction)
		running = execute(cpu, memory);

		// print the state of the machine after this pass
		// (and incriment the loops counter)
		debugMachineState(++loops, cpu, memory);
	}

	return 0; // tell the OS there was no error
}


/*		URL LINKS FOR SOURCES USED:

(Unsure of how many links to include. 
Here are the ones I believe to be the most important.
If I should include more, please let me know.)

http://users.ece.utexas.edu/~valvano/embed/chap3/chap3.htm
https://www.learncpp.com/cpp-tutorial/bitwise-operators/
https://en.cppreference.com/w/cpp/language/types
(... MANY others...)


For OpCode==0x5 - INP:
https://www.geeksforgeeks.org/stringstream-c-applications/
http://www.cplusplus.com/reference/sstream/stringstream/stringstream/
http://the.discspace.org/tech/cplusplus/iostream/stringstream/index.html
https://www.geeksforgeeks.org/stdstringerase-in-cpp/
http://www.cplusplus.com/reference/string/string/erase/


*/