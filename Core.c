#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * Create the first part of minesweeper,
 * the part where it ask the user for x and y value,
 * and depending on the value of x, y, along with the choice of asserting,
 * the world would be either dead or alive
 *
 * @author Kevin Chen
 * @version 1.0
 * 
 * ICSI 333, Class Number: 6245, Section: 0001
 * 
 * Project One - MineSweeper part one
 * 
 */
 
int coordinate();

int width, length;
struct Game{
	int x,y,status;
} world;
typedef struct gameBoard{
	int bombs,numBomb;
	char fua;
} gameBoard;
struct gameBoard *board;

//Begin the game by setting up
int initialization() {
	//print a statement in terminal
	printf("Setting up the game\n");

	srand(time(0));
	//Allocate memory to board
	board = malloc(width * length * sizeof(struct gameBoard)); 
	//printf("Bombs\n");
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			//printf("length: %d\nwidth: %d\n", length, width);
			//Insert bomb with ratio of 4
			if((rand() % (4) == 0)){
				board[i*length + j].bombs = 1;
			}
			//Split the game board into 9 pieces and determine number of bomb around the square
			if(board[i*length + j].bombs == 1){
				if(j == 0 && i == 0) {
					board[i*length + j + 1].numBomb++;
					board[(i + 1)*length + j].numBomb++;
					board[(i + 1)*length + j + 1].numBomb++;
				} else if(j == width && i == 0){
					board[i*length + j - 1].numBomb++;
					board[(i + 1)*length + j].numBomb++;
					board[(i + 1)*length + j - 1].numBomb++;
				} else if(i == 0) {
					board[(i + 1)*length + j].numBomb++;
					board[i*length + j + 1].numBomb++;
					board[i*length + j - 1].numBomb++;
					board[(i + 1)*length + j + 1].numBomb++;
					board[(i + 1)*length + j - 1].numBomb++;
				} else if(j == 0 && i == length) {
					board[i*length + j + 1].numBomb++;
					board[(i - 1)*length + j].numBomb++;
					board[(i - 1)*length + j + 1].numBomb++;
				} else if(j == width && i == length) {
					board[i*length + j - 1].numBomb++;
					board[(i - 1)*length + j].numBomb++;
					board[(i - 1)*length + j - 1].numBomb++;
				} else if(i == length) {
					board[(i - 1)*length + j].numBomb++;
					board[i*length + j + 1].numBomb++;
					board[i*length + j - 1].numBomb++;
					board[(i - 1)*length + j + 1].numBomb++;
					board[(i - 1)*length + j - 1].numBomb++;
				} else if(j == 0) {
					board[i*length + j + 1].numBomb++;
					board[(i + 1)*length + j].numBomb++;
					board[(i - 1)*length + j].numBomb++;
					board[(i + 1)*length + j + 1].numBomb++;
					board[(i - 1)*length + j + 1].numBomb++;
				} else if(j == width) {
					board[i*length + j - 1].numBomb++;
					board[(i + 1)*length + j].numBomb++;
					board[(i - 1)*length + j].numBomb++;
					board[(i + 1)*length + j - 1].numBomb++;
					board[(i - 1)*length + j - 1].numBomb++;
				} else {
					board[i*length + j - 1].numBomb++;
					board[i*length + j + 1].numBomb++;
					board[(i + 1)*length + j].numBomb++;
					board[(i - 1)*length + j].numBomb++;
					board[(i + 1)*length + j + 1].numBomb++;
					board[(i + 1)*length + j - 1].numBomb++;
					board[(i - 1)*length + j + 1].numBomb++;
					board[(i - 1)*length + j - 1].numBomb++;
				}
			}
			//printf("%d ", board[i*length + j].bombs);
			//Set up the user's display board
			board[i*length + j].fua = '_';
		}
		//printf("\n");
	}
	/*
	printf("- - - - - -\n");
	printf("numBombs\n");
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			printf("%d ", board[i*length + j].numBomb);	
		}
		printf("\n");
	}
	*/
	//Show the game board
	printf("- - - - - -\n");
	printf("fua\n");
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			printf("%c ", board[i*length + j].fua);	
		}
		printf("\n");
	}
	
    return 0;
}
//Close the game
int tearDown(){
	//print a statement in terminal
	printf("Destroying the game\n");
	//Free the board when game is over
	free(board);	
	return 0;
}
//Return three values if user chooses f, u, or a
//Otherwise, return a single value for q and two value when user didn't chose correctly
int userChoice() {
	char userCommand;
	//Menu for user to follow
	printf("Choose a command from the list below:\nF for flag a square\nU for unflag a square\nA for assert that a spot is mine free\nQ for quiting the game\n");
	//Get user's input and store it in userCommand variable
	scanf(" %c", &userCommand);
	scanf("%*[^\n]");
	//Outcome depends on user's input
    switch (userCommand) {
		//When user chooses upper of lowercase f
        case 'F':
		case 'f':
			//A pointer assigned with values from function coordinate
			coordinate();
			//Determine if user chooses assert
			board[world.y*length + world.x].fua = 'F';
			//Determine if user chooses assert
			return 0;
            break;
		//When user chooses upper of lowercase u
        case 'U':
		case 'u':
			//A pointer assigned with values from function coordinate
			coordinate();
			//Determine if user chooses assert
			board[world.y*length + world.x].fua = '_';
			//Determine if user chooses assert
			return 0;
            break;
		//When user chooses upper of lowercase a
        case 'A':
		case 'a':
			//A pointer assigned with values from the function coordinate
			coordinate();
			//Determine if user chooses assert
			board[world.y*length + world.x].fua = '0' + board[world.y*length + world.x].numBomb;
			//Determine if user chooses assert
			return 1;
            break;
		//When user chooses upper of lowercase q
        case 'Q':
		case 'q':
			//The pointer value needed to get out the loop
			return -1;
            break;
		//When user chooses incorrectly
        default:
			//Tell user to try again
            printf("Please choose from these 4 letters: F, U, A, Q!\n");
			//Determine if user chooses assert
			return 0;
    }
}
//Obtain x and y values
int coordinate() {
	//Keep asking user until a correct x value was given
	do {
		//Ask user for a x value
		printf("Enter your horizontal coordinate (0 to %d) and press enter\n", length - 1);
		//Obtain userInput and store in x
		scanf(" %d", &world.x);	
		scanf("%*[^\n]");
	} while(world.x < 0 || world.x > length - 1);
	//Keep asking user until a correct y value was given
	do {
		//Ask user for a y value
		printf("Enter your vertical coordinate (0 to %d) and press enter\n", width - 1);
		//Obtain userInput and store in y
		scanf(" %d", &world.y);	
		scanf("%*[^\n]");
	//Stop the loop when condition are met
	} while(world.y < 0 || world.y > width - 1);
	return 0;
}
//Determine if the world is dead or alive
int updateWorld(int x, int y, int choosen) {
	//When x is 0, y is 0, and assert has been choosen
	if(board[y*length + x].bombs == 1 && choosen == 1)
		//Declare world is dead
		return 0;
	//Declare world is alive
	return 1;
}
//Tell the user if it explode or not
int displayStateOfWorld(int status) {
	//When world is dead
	if(status == 0) {
		//Print "BOOM"
		printf("BOOM\n");
	} else {
		//Otherwise say the world is fine
		printf("Ok\n");
	}
	//Print the game board
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			printf("%c ", board[i*length + j].fua);	
		}
		printf("\n");
	}
	
	/*
	for (int i = 0; i <  width; i++) {
		for (int j = 0; j < length; j++) {
			printf("%d ", *(world.gameBoard + i*length + j));	
			if(j==length-1){
				printf("\n");
			}
		}
	}
	*/
	return 0;
} 

int main(int numOfArg, char* args[]) {
	//printf("Number of Arguments: %d\n", numOfArg);
	if(numOfArg == 3 && atoi(args[1]) > 4 && atoi(args[2]) > 4) {
		//printf("Arguments: %s, %s\n", args[1],args[2]);
		width = atoi(args[1]);
		length = atoi(args[2]);
		//printf("Width: %d, Length: %d", width, length);
		int userChoiceOfAction;
		//Set up the game
		initialization();
		do {
			world.x = -1;
			world.y = -1;
			world.status = 1;
			//Obtain x, y, and the integer when assert is choosen
			userChoiceOfAction = userChoice();
			//When user didn't chooses q
			if(userChoiceOfAction != -1) {
				//Determine if the world is dead or alive
				world.status = updateWorld(world.x,world.y,userChoiceOfAction);
				//Show the vital status of the world
				displayStateOfWorld(world.status);
			}
		//Loop when world is alive and q is not choosen
		} while(world.status == 1 && userChoiceOfAction != -1);
		//Quit the game
		tearDown();
	} else {
		printf("Please enter in two numbers greater than 4 for width and length!\nTo call this program, enter:\n./Core [Arguments One no racket](WITH A SPACE BETWEEN 2 ARGUMENTS)[Arguments Two no racket]\n");
	}
	
	return 0;
}