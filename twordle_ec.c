//Bay Pevehouse
// Project 10 ( final project b4 final )
// 05/01/2026

#include <stdio.h>
//also wasn't here if we were allowed to use the bool library ( which would have been cleaned up more here and I apologize ) but did just use 1 and 0.


#define SIZE 5 //per exc can only have 5 letters "sound"
#define TRIES 6 // technically 6 tries
#define INPUT 10

// need atleast 6 func
int readSecret(char answer[]);
int getSize(char word[]);
char smallLetter(char ch);
void fixCaps(char word[]); // in her executable, you can put CAPS or lowercase or even SOunD and it still comes out to see sound, keeping this to allow program to see one guess.
int isGood(char entry[]);
int isSame(char entry[], char answer[]);
int hasChar(char word[], char ch);
void saveEntry(char tries[][SIZE + 1], char entry[], int row); // this is our reader to find our null character
void printGame(char tries[][SIZE + 1], char answer[], int count);
void printEntry(char entry[], char answer[]);
void printWinner(char answer[], int numTries);

int main(){

	char answer[SIZE + 1];
	char entry[INPUT];
	char tries[TRIES][SIZE + 1];

	int numTries = 0;
	int didWin = 0;
	int opened = 1;
	int result;

	if(!readSecret(answer)){
		printf("Could not open mystery.txt, goodbye!\n");
		opened = 0;
	}

	fixCaps(answer);

	while(numTries < TRIES && didWin == 0 && opened == 1){

		if(numTries == TRIES - 1){
			printf("FINAL GUESS : ");
		}else{
			printf("GUESS %d! Enter your guess: ", numTries + 1);
		}

		scanf("%9s", entry);
		fixCaps(entry);

		while(!isGood(entry)){

			if(getSize(entry) != SIZE){
				printf("Your guess must be 5 letters long.");
			}else{
				printf("Your guess must contain only letters.");
			}

			printf("\nPlease try again: ");
			scanf("%9s", entry);
			fixCaps(entry);

		}

		numTries++;

		printf("================================\n");

		if(isSame(entry, answer)){
			result = 1;
		}else{
			result = 2;
		}

		switch(result){

			case 1:
				didWin = 1;
				printWinner(answer, numTries);
			break;

			case 2:
				saveEntry(tries, entry, numTries - 1);
				printGame(tries, answer, numTries);
			break;
		}

	}

	if(opened == 1 && didWin == 0){
		printf("You lost, better luck next time!\n");
	}
	return 0;
}

int readSecret(char answer[]){

	FILE *wordFile;
	wordFile = fopen("mystery.txt", "r");

	if(wordFile == NULL){
		return 0;
	}

	fscanf(wordFile, "%s", answer);

	fclose(wordFile);
	return 1;
}

int getSize(char word[]){

	int i = 0;
	while(word[i] != '\0'){
		i++;
	}
	return i;
}

char smallLetter(char ch){

	if(ch >= 'A' && ch <= 'Z'){
		ch = ch + 32;
	}
	return ch;
}

void fixCaps(char word[]){

	int i;
	for(i = 0; word[i] != '\0'; i++){
		word[i] = smallLetter(word[i]);
	}
}

int isGood(char entry[]){

	int i;
	if(getSize(entry) != SIZE){
		return 0;
	}

	for(i = 0; i < SIZE; i++){
		if(!((entry[i] >= 'a' && entry[i] <= 'z') || (entry[i] >= 'A' && entry[i] <= 'Z'))){
			return 0;
		}
	}
	return 1;
}

int isSame(char entry[], char answer[]){

	int i;
	for(i = 0; i < SIZE; i++){
		if(entry[i] != answer[i]){
			return 0;
		}
	}
	return 1;
}

int hasChar(char word[], char ch){

	int i;
	for(i = 0; i < SIZE; i++){
		if(word[i] == ch){
			return 1;
		}
	}
	return 0;
}

void saveEntry(char tries[][SIZE + 1], char entry[], int row){

	int i;

	for(i = 0; i < SIZE; i++){
		tries[row][i] = entry[i];
	}
	tries[row][SIZE] = '\0';
}

void printGame(char tries[][SIZE + 1], char answer[], int count){

	int i;
	for(i = 0; i < count; i++){
		printEntry(tries[i], answer);
	}
}

void printEntry(char entry[], char answer[]){

	int i;
	for(i = 0; i < SIZE; i++){
		if(entry[i] == answer[i]){
			printf("%c", entry[i] - 32);
		}else{
			printf("%c", entry[i]);
		}
	}

	printf("\n");

	for(i = 0; i < SIZE; i++){
		if(entry[i] != answer[i] && hasChar(answer, entry[i])){
			printf("^");
		}else{
			printf(" ");
		}
	}

	printf("\n"); 
}

void printWinner(char answer[], int numTries){

	int i;
	printf("\t\t");

	for(i = 0; i < SIZE; i++){
		printf("%c", answer[i] - 32);
	}

	printf("\n");

	if(numTries == 1){
		printf("\tYou won in 1 guess!\n");
	}else{
		printf("\tYou won in %d guesses!\n", numTries);
	}

	switch(numTries){ //i tried to " " here but it ended up not being the best, I know I brought up before the 
	//spaces here in project 1 and another project but, I used \t instead

		case 1:
			printf("\t\tGOATED!\n");
		break;

		case 2:
		case 3:
			printf("\t\tAmazing!\n");
		break;

		case 4:
		case 5:
			printf("\t\tNice!\n");
		break;

		case 6:
		break;

	}
}


