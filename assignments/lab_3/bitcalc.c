#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Jordan Waite */
/* Lab 3 */
/* CS 1337 */
/* 2-15-24 */

// Author: Jordan Waite

// The purpose of this program is to utilize binary representation of
// hexadecimal integers and to apply logical binary operations. The program
// will prompt the user for an operator (|, &, and ^ (or, and, and xor)), the
// number of operands, and the hexadecimal operands. The program should then
// perform the operation on the numbers in the form firstnum operator secondnum
// operator etc. The result should then be returned in both hexadecimal and
// binary.

// Function to prompt the user to enter an appropriate operator or "q" to quit
char operator_prompt() {
	char operator;

	// Wrap the prompt in infinite do-while loop so 
	// that invalid input reiterates the loop
	do{ 
		printf ("Enter operation: ");	
		scanf (" %c", &operator);	
		// Use a switch to determine the operator 
		// input, quit, or retry if input invalid
		switch(operator) {
			case '|':
				break;

			case '&':
				break;

			case '^':
				break;

			case 'q':
				exit(0);
				break;

			default:
				printf("Please enter |, &, ^, or q\n");
				continue;
		}
		return operator;		
	} while (1);
}


//Function to prompt the user for the number of operands
int operand_count_prompt(){
	int integer_count;
	//Ininite do-while loop to reiterate prompt if invalid input
	while(1) {
		printf("Enter number of integers: ");
		//Make sure the result of scanf is an integer
		if(scanf(" %d", &integer_count) != 1) {
			//Clear input buffer to avoid
			//an infinite loop on char input
			while (getchar() != '\n');
			printf("Please enter an integer greater than 1\n");
			continue;
		}
		//Ensure that the input is greater than 1 and
		//is not equal to 1
		if(integer_count < 1 || integer_count ==1){
			//Clear the input buffer
			while (getchar() != '\n');
			printf("Please enter an integer greater than 1\n");
			continue;
		}
		else {
			return integer_count;
		}
	}
}

//The operand_prompt function should prompt the user once for
//each operand_count number of hexadecimal integers, ensure valid input of
//only hexadecimal values, and have a maximum of 8 hexadecimal digits.
//Inputs with less than 8 digits should be assumed to have leading zeros.
//These values should be stored in arrays.
void operand_prompt(int operand_count, unsigned int operand_array[]) {
    // For loop to add each operand to an array and reissue the prompt for each operand
    for (int i = 0; i < operand_count; ++i) {
	//Declare empty unsigned int to hold hex values
	unsigned int hex_val;

        // Infinite while loop to prompt user if input is invalid
        while (1) {
            printf("Enter integer %d: ", i + 1);

            // Make sure the input is at maximum a 8-digit hex character
            if (scanf(" %08X", &hex_val) == 1) {
		    if (hex_val > 0xFFFFFFFF) {
	                    printf("Please enter an 8-digit hexadecimal integer\n");
			    //Clear buffer
			    while (getchar() != '\n');
			    continue;
		    }
		    //If valid input, read current hexVal into operand array
		    operand_array[i] = hex_val;
		    while (getchar() != '\n');
		    break;

	    } else {
		    //If input is not properly read as a hex value, throw error
	            printf("Please enter an 8-digit hexadecimal integer\n");
		    while (getchar() != '\n');
		}
        }
    }
}


//Using a bit mask, and formatting the hex value at hand, we
//can get the binary representation of the hex integers
void print_bytes(int hex) {
	// Create a bit mask
	int mask = 0x80000000;

	//Loop through each position
	for(int i = 0; i < 32; i++) {
		//Print current bit
		printf("%d", (hex & mask) != 0);

		//Include a space after every 8 bits
		if ((i + 1) % 8 == 0)
			printf(" ");

		//Shift right by 1 position
		mask >>=1;
	}
}

//Make a function specifically for returning a single conversion
//of hex to binary for the result
char* print_binary_result(int hex) {
	//Variable to store binary result
	//Use malloc to avoid seg fault
	char* binary_result = (char*)malloc(33);

	//Create bit mask
    	int mask = 0x80000000;
	//Index for binary result array
	int j = 0;	
	//Print = sign
	printf("\t= ");
    	// Loop through each position
    	for (int i = 0; i < 32; i++) {
		//Set current bit to binary representation
		binary_result[j++] = ((hex & mask) !=0) ? '1' : '0';

        	// Include a space after every 8 bits including spaces
        	if ((i + 1) % 8 == 0)
            		binary_result[j++] = ' ';

        	// Shift right by 1 position
        	mask >>= 1;
    	}
	//Store result and end array with null terminator
	binary_result[j] = '\0';
	return binary_result;
}

//The calculate function will take the operator character, the array of
//operands, and the size of the array as parameters. It should then
//perform the operation on the numbers 'firstnum operator secondnum operator
//thirdnum etc' from left to right. The function should then print back the
//entire expression being computed in hexadecimal and binary
void calculate(char operator, int operand_array[], int size) {

	//The result variable will initially hold the first hex integer in the array
	//to be operated upon, and will eventually develop into the final result
	unsigned int result = operand_array[0];
	
        //We want to wrap a switch statement in a for loop to apply the operator
        //supplied to each element sequentially to calculate the result of the expression
        for (int i = 1; i < size; ++i){
                switch (operator) {
                        case '&':
                                result &= operand_array[i];
                                break;
                        case '|':
                                result |= operand_array[i];
                                break;
                        case '^':
                                result ^= operand_array[i];
                                break;
                }
        }

	//Print out the header
	printf("\n");
	printf("Hexadecimal operation:\n");

	//Print first operand seperately with a tab
	printf("\t  %08X\n", operand_array[0]);

	//Iterate through the array
	for (int i = 1; i < size; i++) {
		//Print the operator followed by the subsequent operand 
		if (i <= size - 1) {
			printf("\t%c %08X\n", operator, operand_array[i]);
		}
	}

	// Print the final result of the calculations
	printf("\t= %08X\n", result);
	printf("\n");

	//Print the binary operation
	//Print header
	printf("Binary operation:\n");
	//Print the binary representation of the array of hex values
	for (int i = 0; i < size; i++) {
		printf("\t");
		if (i == 0) {
			printf("  ");
		}
		if (i > 0) {
			//Print the operator
			printf("%c ", operator);
		}
	//Call our print bytes function to print binary of that index hex value
	print_bytes(operand_array[i]);
	printf("\n");	
	}
	
	//Print result of binary expression
	char* binary_result = print_binary_result(result);
	printf("%s\n", binary_result);	
	printf("\n");
}


int main() {
	//Wrap the main in infinite loop to repeat after calculation
	while(1) {
		// Get the operator from the user
		char operation = operator_prompt();

		// Call the operand_count_prompt function to get the number of
		// operands from the user
		int operand_count = operand_count_prompt();

		// Declare a fixed array of the size of the
		// operand_count
		unsigned int operand_array[operand_count];

		// Call the operand_prompt function to get
		// the operands from the user and store them
		// in the operand_array
		operand_prompt(operand_count, operand_array);
	
		// Ensure we have the exact size of the array for
		// calculating purposes
		int size = sizeof(operand_array) / sizeof(operand_array[0]); 

		// Call the calculate function
		calculate(operation, operand_array, size);
		
	}
}


