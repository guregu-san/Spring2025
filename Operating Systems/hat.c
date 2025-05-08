/******************************************************************************
Assignment 4
Description: A combination of the head and tail UNIX commands. Depending on 
the arguments given by the user it will print the first or last N number
of lines from a given text file.
Input Parameters: A character representing the option(H/T), an integer
indicating how many lines should be printed, and a text file.
Output Parameters:
    - 0 is returned if the program runs and terminates successfully.
    - 1 is returned if the program is not given 3 CLAs.
    - 2 is returned if the program is not given a valid option.
    - 3 is returned if the program is not given a valid number of lines to print.
    - 4 is returned if the program can't open the file.
Date: 7/5/25
*******************************************************************************/
#include <stdio.h> //Library needed for input and output.
#include <stdlib.h> //Library that includes type conversion and memory allocation/deallocation functions.
#include <ctype.h> //Library that includes toupper().
#include <string.h> //Library needed for string manipulation.
#define BUFFER_SIZE 100 //Max length of each text file line.

//Start of the main function.
int main(int argc, char *argv[]){
    //Check if 3 arguments have been given.
    if (argc != 4)
	{
        printf("ERROR: Please enter the option(H/T), the number of lines you want printed, and a text file");
		return 1;
	}

    //Initialize the variable for the option(case doesn't matter).
    char flag = toupper(*argv[1]);

    //Check if a valid option has been given.
    if (flag != 'H' && flag != 'T')
    {
        printf("ERROR: Invalid option entered. Try again(h/t)");
		return 2;
    }
    
    //Initialize the variable for the number of lines to be printed(conversion to int needed).
    int printNumber = atoi(argv[2]);

    //Check if an integer has been given.
    if (printNumber == 0)
    {
        printf("ERROR: Entered invalid input as a number. Try again");
		return 3;
    }

    //File pointer declaration.
    FILE *file;

    //Open file in read mode.
    file = fopen(argv[3],"r");

    //Check if the file opened successfully.
    if (file == NULL)
    {
        printf("ERROR: File couldn't be opened");   
        return 4;
    }
	
    //Initialize the variables for holding a read line, and keeping track of which line we're at.
    char line[BUFFER_SIZE];
    int currentLine = 0;

    //If the option is H print the first N lines, otherwise the last N lines.
    if (flag == 'H')
    {
        //Print the first N lines, or all of them if the file is shorter than expected.
        while (currentLine < printNumber && fgets(line, BUFFER_SIZE, file))
        {
            printf("%s", line);
            currentLine++;
        }

        //Close file.
        fclose(file);

        //Return 0 if the program run successfully.
        return 0;
    }

    //Initialize the pointer to, or array of, the last N lines read, by allocating heap memory to it.
    //(needs to be deallocated when not needed anymore)
    char **lines = malloc(printNumber * sizeof(char*));

    //Read the first N lines and populate the array.
    while (currentLine < printNumber && fgets(line, BUFFER_SIZE, file))
    {
        //Duplicate the line read so that it gets a unique address and assign it to the
        //appropriate pointer. If it's not duplicated each time, all the pointers in the
        //array will end up pointing to the same address, i.e., line.
        //(also need to be deallocated when not needed anymore)
        lines[currentLine] = strdup(line);

        currentLine++;
    }

    //Check if the file had less lines than expected.
    if (currentLine < printNumber)
    {
        //Print the lines it has.
        for (int i = 0; i < currentLine; i++)
            printf("%s", lines[i]);
    }
    else
    {
        //Keep reading lines until the EOF is reached, and update the line array each time.
        while (fgets(line, BUFFER_SIZE, file))
        {
            //Shift the existing lines in the array backwards.
            for (currentLine = 0; currentLine < printNumber - 1; currentLine++)
                lines[currentLine] = lines[currentLine + 1];

            //Add the most recently read line as the last.
            lines[printNumber - 1] = strdup(line);
        }

        for (currentLine = 0; currentLine < printNumber; currentLine++)
            printf("%s", lines[currentLine]);
    }

    //Deallocate the memory used by the lines.
    for (int i = 0; i < printNumber; i++)
        free(lines[i]);

    //Deallocate the memory used by the pointer to the lines.
    free(lines);

    //Close file.
    fclose(file);

    //Return 0 if the program run successfully.
    return 0;
}
//End of the main function.
