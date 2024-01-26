#include <stdio.h>
#include <stdlib.h>

/* Jordan Waite */
/* Lab 2 */
/* CS 1337 */
/* 1-24-24 */

// The purpose of this C program is to accept an arithmetic operation choice
// from the user, accept any number of integers, to perform that operation
// on said integers from left to right, and to output the final result.

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
			case '+':
				break;

			case '-':
				break;

			case '*':
				break;

			case '/':
				break;

			case 'q':
				exit(0);
				break;

			default:
				printf("Please enter a valid operation\n");
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
//each operand_count number of integers, ensure valid input of
//only integers, not produce a divide by zero error, and
//store the input integer values in a given array.
void operand_prompt(int operand_count, int operand_array[], char operator){

	//For loop to add each operand to an array
	//and reissue the prompt for the each operand
	for (int i = 0; i < operand_count; ++i) {
		int input;

		// Infinite while loop to prompt user
		// if input is invalid
		while (1) {
			printf("Enter integer %d: ", i+1);

			//Make sure the input is an integer
			if (scanf(" %d", &input) == 1) {
				//Ensure the first number input is not zero
				//if the operation is division
				if (i == 0 && input == 0 && operator == '/') {
					//No example or instruction regarding a
					//specific error message when the first
					//integer entered for division is 0, 
					//so I went with this
					printf("First number can't be zero\n");
				} else {
					operand_array[i] = input;
					break;
				}
			} else {
				printf("Please enter an integer\n");
				//Clear input buffer to avoid infinite
				//loop on invalid input
				while (getchar() != '\n');
			}
		}
	}
}


//The calculate function will take the operator character, the array of
//operands, and the size of the array as parameters. It should then
//iterate through the array and apply the chosen math operation on
//the numbers in the array from left to right. This function should
//then print back the entire expression computed, with division being
//computed as integer division.
void calculate(char operator, int operand_array[], int size) {
	//The result variable will initially hold the first integer in the array
	//to be operated upon, and will eventually develop into the final result
	int result = operand_array[0];
	printf("\nComputing: %d ", result);

	//We want to wrap a switch statement in a for loop to apply the operator
	//supplied to each element sequentially
	for (int i = 1; i < size; ++i){
		switch (operator) {
			case '+':
				printf("+ %d", operand_array[i]);
				result += operand_array[i]; 
				break;
			case '-':
				printf("- %d", operand_array[i]);
				result -= operand_array[i];
				break;
			case '*':
				printf("* %d", operand_array[i]);
				result *= operand_array[i];
				break;
			case '/':
				printf("/ %d", operand_array[i]);
				result /= operand_array[i];
				break;
		}
	}
	// Print the final result of the calculations
	printf(" = %d\n", result);
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
		int operand_array[operand_count];

		// Call the operand_prompt function to get
		// the operands from the user and store them
		// in the operand_array
		operand_prompt(operand_count, operand_array, operation);
	
		// Ensure we have the exact size of the array for
		// calculating purposes
		int size = sizeof(operand_array) / sizeof(operand_array[0]);

		// Call the calculate function
		calculate(operation, operand_array, size);
	}
}




