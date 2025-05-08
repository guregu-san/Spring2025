/***************************************************************
Assignment 2
Description: A bare bones shell interface program that allows the user
to terminate it by entering the "exit" command. If the user tries
any other commands, they are informed of their non-existence.
Input Parameters: None - No command line arguments are accepted.
Output Parameters: 0 is returned if the program runs and terminates successfully.
Date: 10/3/25
****************************************************************/
#include <stdio.h> //Library needed for input and output.
#include <string.h> //Library needed for string manipulation.
#define BUFFER_SIZE 100 //Max size of the accepted user input.

//Start of the main function.
int main(){
  //Variable declarations.
	char input[BUFFER_SIZE];
	char *command; //Pointer to the command section of the input.

  //Infite loop so that the shell program terminates only when explicitly instructed.
	while (1)
	{
        //Print the command prompt.
		printf("CSOS>");

        //Read in the user's input.
		fgets(input, sizeof(input), stdin);

        //Remove the leftover new-line character from the input.
        input[strcspn(input, "\n")] = '\0';

        //Set the command pointer to the input string's start.
        command = input;
        
        //Remove any leading spaces from the command by moving its pointer forward.
        while (command[0] == ' ')
            command++;

        //Point the command pointer to the 1st token that is returned from parsing the
        //string it's currently pointing to, using the "space" character as the delimeter.
        //(strtok has a side effect on the "input" variable because it manipulates the original
        //values by replacing the ones equal to the given delimeter with termination characters)
        command = strtok(command, " ");

        //Terminate the shell if the command part of the initial input is "exit".
		if (!strcmpi(command, "exit"))
			return 0;

        //Inform the user that the command they tried doesn't exist. 
        printf("No command found!\n");
	}
}
//End of the main function.
