/***************************************************************
Assignment 3
Description: A simulation of the linux "diff" command, that displays
the differences between 2 text files line-by-line.
Input Parameters: 2 text files.
Output Parameters:
    - 0 is returned if the program runs and terminates successfully.
    - 1 is returned if the program is not given 2 CLAs.
    - 2 is returned if the program can't open both files.
Date: 1/5/25
****************************************************************/
#include <stdio.h> //Library needed for input and output.
#include <string.h> //Library needed for string manipulation.
#define BUFFER_SIZE 100 //Max length of each text file line.

//Start of the main function.
int main(int argc, char *argv[]){
    //Check if 2 arguments have been given.
    if (argc != 3)
	{
        printf("ERROR: Please give 2 text files as the arguments");
		return 1;
	}

    //File pointer declarations.
    FILE *file1;
    FILE *file2;

    //Open both files in read mode.
    file1 = fopen(argv[1],"r");
    file2 = fopen(argv[2],"r");

    //Check if the files opened successfully.
    if (file1 == NULL || file2 == NULL)
    {
        printf("ERROR: Files couldn't be opened");   
        return 2;            
    }
	
    //Variables for tracking the current line in each file.
    char line1[BUFFER_SIZE];
    char line2[BUFFER_SIZE];
    int currentLine = 0;

    //Read and compare lines until we reach the end of the 1st file. 
    //If the end of the 2nd file is reached first, print the remaining lines from the 1st.
    while (fgets(line1, BUFFER_SIZE, file1))
    {
        //If the 2nd file reached its end, its line should be empty
        //when we print the remaining lines from the 1st.
        if (!fgets(line2, BUFFER_SIZE, file2))
            line2[0] = '\n';

        //Remove the leftover new-line characters from each line.
        line1[strcspn(line1, "\n")] = '\0';
        line2[strcspn(line2, "\n")] = '\0';

        //Compare the current lines from both text files.
        if (strcmp(line1, line2))
            printf("%d %s > %s\n", currentLine, line1, line2);

        currentLine++;
    }

    //Close both files.
    fclose(file1);
    fclose(file2);

    //Return 0 if the program run successfully.
    return 0;
}
//End of the main function.
