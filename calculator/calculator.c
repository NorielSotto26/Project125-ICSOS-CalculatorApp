/*	SOTTO, NORIEL E.			*/
/*  ARIOLA, JONAH 				*/
/*	CMSC 125 T-6L				*/
/*	CALCULATOR! App for ICS-OS	*/


#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

int print_menu();	//prints the menu frame
void print_aboutUs();	//prints the about us frame
void pointer_menu(int y);	//prints the pointer in the menu
void print_help();	//prints the help frame
void innerSquare(int r, int c, int x, int y, int color); //prints a button innerSquare
void outerSquare(int x, int y, int color);	//prints the buttons border
void print_display(int x, int y, int color);	//prints display area
void display_button(int x);	//fxn for clicking buttons
int factorial(int n);	
int evaluate();	//evaluates expressions
void setup_buttonArray();	//setup buttons array
void print_button(int r, int c, int x, int y, int color); //print a button
void print_calculator(int x, int y); //set up initial calculator
void erase(); //basically covers an area with a black rectangle

/* constants */
#define maxrow 4
#define maxcol 7

#define up_key 'w'
#define down_key 's'
#define left_key 'a'
#define right_key 'd'
#define enter '\n'
#define quit 'x'
#define help 'h'
#define start '1'

#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63
#define BLACK 100
#define RED 32

#define X_coord 23
#define Y_coord 68	

/* global variables */
int row, col, oldrow=0, oldcol=0;
int flips=0, remaining_bulb;
int level, count=0, hour=0, min=0;
char board[maxrow][maxcol];
int buttons[maxrow][maxcol];
int bulbs_x[maxrow][maxcol];
int bulbs_y[maxrow][maxcol];
char exp[20] = "";
char print[20] = "";

int main()
{
	char keypress;
	int i,j;

	set_graphics(VGA_320X200X256);
   	setup_buttonArray();

	do{
		erase(1,1,400,220);
		
		keypress=start;
		if(print_menu()==2) break;	//prints the menu, break if exit chosen
		erase(1,1,400,220);	//else clears the frame

		print_calculator(X_coord, Y_coord);	//prints the calculator UI
		row=0;
		col=0;
		do{	
			//ACTION LISTENER
			if (keypress=(char)getch()){
				//if 'D' is pressed, move to the right
				if(keypress==right_key){
					oldrow = row;
					oldcol = col;
					col = (col + 1) % maxcol;
				}
				//if 'A' is pressed, move to the left
				else if(keypress==left_key){
					oldrow = row;
					oldcol = col;
					if(col <= 0)
						col = maxcol - 1;
					else
						col--;
				}
				//if 'W' is pressed, move to the top
				else if(keypress==up_key){
					oldrow = row;
					oldcol = col;
					if(row <= 0)
						row = maxrow - 1;
					else
						row--;
				}
				//if 'S' is pressed, move to the bottom
				else if(keypress==down_key){
					oldrow = row;
					oldcol = col;
					row = (row + 1) % maxrow;
				}
				//if 'Enter' is pressed, display the pressed button to the display area
				else if(keypress == enter){				
					display_button(buttons[row][col]);
					if(strcmp(exp,"Exiting...") == 0){	//if the button is the EXIT button, move to the menu
						erase(1,1,400,220);
						keypress=start;
						if(print_menu()==2) keypress = quit;
						else {
							erase(1,1,400,220);
							print_calculator(X_coord, Y_coord);
							row=0;
							col=0;
						}
						strcpy(exp,"");
					}
				}
				//if 'H' is pressed, display the help frame
				else if(keypress==help){
					print_help();
					print_calculator(X_coord, Y_coord);
					row=0;
					col=0;
					write_text(exp,35,35,WHITE,0);
				}
				// update the display of the selected and previously selected
				if(keypress==right_key || keypress==left_key || keypress==up_key || keypress==down_key){
					if(oldcol == 0 && oldrow == 3) {
						outerSquare(X_coord+(oldcol*40),Y_coord+(oldrow*32),RED);
					}
					else {
						outerSquare(X_coord+(oldcol*40),Y_coord+(oldrow*32),GRAY);
					}
					outerSquare(X_coord+(col*40),Y_coord+(row*32),WHITE);
					
				}
			}			
	      		
		} while (keypress != quit);
	} while (keypress != quit);
	
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}
//function for printing the menu
int print_menu(){
	char keypress = start;
	int i,j,choice=0;;

	do{
  	 	write_text(" ",5,5,GRAY,0); 
		write_text(" 0 X 1 / 5 % 8 - 3 + 9 ! 2 ^ 7 4 X",2,15,RED,0);
		write_text(" /                               -",2,35,RED,0);
		write_text(" 7                               9",2,55,RED,0);
		write_text(" +                               X",2,75,RED,0);
		write_text(" 3                               4",2,95,RED,0);
		write_text(" -                               ^",2,115,RED,0);
		write_text(" 6                               5",2,135,RED,0);
		write_text(" !                               %",2,155,RED,0);
		write_text(" 5 % 8 - 3 + 9 ! 2 ^ 7 4 X 1 0 X 1",2,175,RED,0);
		write_text("       [PRESS 'H' FOR HELP]       ",2,188,GRAY,0);
		write_text("ICS OS",135,35,WHITE,0);
		write_text("CALCULATOR",120,55,WHITE,0);
		write_text("1   CONTINUE",110,95,WHITE,0);
		write_text("2   ABOUT",110,115,WHITE,0);
		write_text("3   EXIT",110,135,WHITE,0);
		//switch case for printing the pointer
		switch(choice){
			case 0:
				pointer_menu(95);	//moves the pointer to '1   CONTINUE'
				break;
			case 1:
				pointer_menu(115);	//moves the pointer to '2   ABOUT'
				break;
			case 2:
				pointer_menu(135);	//moves the pointer to '3   EXIT'
				break;
		}
		//ACTION LISTENER
		if (keypress=(char)getch()){	
			if(keypress==down_key){			//if 'S' is pressed, move the pointer to the bottom
				choice = (choice + 1) % 3;
			}else if(keypress==up_key){		//if 'W' is pressed, move the pointer to the top
				choice = choice - 1;
				if(choice < 0) choice = 2;
			}else if(keypress==help){		//if 'H' is pressed, print the help frame
				print_help();
			}else if(keypress==enter){		//if 'ENTER' is pressed, execute the chosen choice
				if(choice == 0) return 0;		//1 - EXIT
				else if(choice == 1){			//2 - ABOUT US
					erase(1,1,400,220);
					print_aboutUs();		
					erase(1,1,400,220);
				}
				else if(choice == 2) return 2;	//3 - EXIT
			}
		}
	}while(1);
}
//prints the about us frame
void print_aboutUs(){
	char keypress = start;

	write_text("DATE CREATED: MAY 17,2017",30,25,WHITE,0);
	write_text("PROJECT NAME: ICS CALCULATOR",30,45,WHITE,0);
	write_text("DESCRIPTION: AN APPLICATION THAT",30,65,WHITE,0);
	write_text("     HAS THE BASIC FUNCTIONS OF",30,85,WHITE,0);
	write_text("     A CALCULATOR",30,105,WHITE,0);
	write_text("CONTRIBUTORS: NORIEL SOTTO",30,125,WHITE,0);
	write_text("              JONAH ARIOLA",30,145,WHITE,0);
	write_text("PRESS ANY KEY TO GO BACK",55,185,ROYAL_BLUE,0);
	
	do{
		if (keypress=(char)getch()) return;
	}while(1);
}
//positions the pointer in the menu
void pointer_menu(int y){
	int i,j;
	for(i=0;i!=7;i++) for(j=0;j!=7;j++) write_pixel(85+i,95+j,BLACK);
	for(i=0;i!=7;i++) for(j=0;j!=7;j++) write_pixel(85+i,115+j,BLACK);
	for(i=0;i!=7;i++) for(j=0;j!=7;j++) write_pixel(85+i,135+j,BLACK);
	for(i=0;i!=7;i++) for(j=0;j!=7;j++) write_pixel(85+i,y+j,RED);
}
//prints the help frame
void print_help(){
	char keypress = start;
	int i,j;
	//prints the display in the middle
	for(i=0;i!=180;i++) for(j=0;j!=130;j++){
		if(i<3 || i>176 || j<3 || j>126) write_pixel(70+i,35+j,ROYAL_BLUE);	//prints border
		else write_pixel(70+i,35+j,BLACK);									//prints main
	}
	write_text("CONTROLS",80,45,WHITE,0);
	write_text("W - UP KEY",80,60,WHITE,0);
	write_text("S - DOWN KEY",80,75,WHITE,0);
	write_text("A - LEFT KEY",80,90,WHITE,0);
	write_text("D - RIGHT KEY",80,105,WHITE,0);	
	write_text("ENTER - ENTER KEY",80,120,WHITE,0);
	write_text("press any key",100,135,GRAY,0);
	write_text("to continue",110,150,GRAY,0);

	do{
		if (keypress=(char)getch()){
			for(i=0;i!=180;i++) for(j=0;j!=130;j++) write_pixel(70+i,35+j,BLACK);
			return;
		}
	}while(1);
}
//setup int array for buttons
//used as identification for the buttons
void setup_buttonArray(){
	int i,j,k=0;
	for (i = 0; i < maxrow; i++){
		for (j = 0; j < maxcol; j++){
			buttons[i][j] = ++k;
		}
	}
}
//function for displaying the entered button in the display area
void display_button(int x){
	erase(35,35,250,10);
	switch(x){
		case 1:
			strcat(exp,"1");
			write_text(exp,35,35,WHITE,0);
			break;
		case 2:
			strcat(exp,"2");
			write_text(exp,35,35,WHITE,0);
			break;
		case 3:
			strcat(exp,"3");
			write_text(exp,35,35,WHITE,0);
			break;
		case 4:
			strcat(exp,"(");
			write_text(exp,35,35,WHITE,0);
			break;
		case 5:
			strcat(exp,")");
			write_text(exp,35,35,WHITE,0);
			break;
		case 6:
			strcpy(exp,"");
			write_text(exp,35,35,WHITE,0);
			break;
		case 7:
			exp[strlen(exp)-1] = '\0';
			write_text(exp,35,35,WHITE,0);
			break;
		case 8:
			strcat(exp,"4");
			write_text(exp,35,35,WHITE,0);
			break;
		case 9:
			strcat(exp,"5");
			write_text(exp,35,35,WHITE,0);
			break;
		case 10:
			strcat(exp,"6");
			write_text(exp,35,35,WHITE,0);
			break;
		case 11:
			strcat(exp,"/");
			write_text(exp,35,35,WHITE,0);
			break;
		case 12:
			strcat(exp,"x");
			write_text(exp,35,35,WHITE,0);
			break;
		case 13:
			strcat(exp,"^2");
			write_text(exp,35,35,WHITE,0);
			break;
		case 14:
			strcat(exp,"^");
			write_text(exp,35,35,WHITE,0);
			break;
		case 15:
			strcat(exp,"7");
			write_text(exp,35,35,WHITE,0);
			break;
		case 16:
			strcat(exp,"8");
			write_text(exp,35,35,WHITE,0);
			break;
		case 17:
			strcat(exp,"9");
			write_text(exp,35,35,WHITE,0);
			break;
		case 18:
			strcat(exp,"-");
			write_text(exp,35,35,WHITE,0);
			break;
		case 19:
			strcat(exp,"+");
			write_text(exp,35,35,WHITE,0);
			break;
		case 20:
			strcat(exp,"P");
			write_text(exp,35,35,WHITE,0);
			break;
		case 21:
			strcat(exp,"e");
			write_text(exp,35,35,WHITE,0);
			break;
		case 22:
			strcpy(exp,"Exiting...");
			write_text(exp,35,35,WHITE,0);
			break;
		case 23:
			strcat(exp,"0");
			write_text(exp,35,35,WHITE,0);
			break;
		case 24:
			strcat(exp,".");
			write_text(exp,35,35,WHITE,0);
			break;
		case 25:
			strcat(exp,"!");
			write_text(exp,35,35,WHITE,0);
			break;
		case 26:
			strcat(exp,"%");
			write_text(exp,35,35,WHITE,0);
			break;
		case 27:
			strcat(exp,"Sq(");
			write_text(exp,35,35,WHITE,0);
			break;
		case 28:
			if(checkValidity(exp) == 0){
				write_text("invalid expression...",35,35,WHITE,0);
				break;
			}
			sprintf(print, "%d", evaluate());
			strcat(exp, " = ");
			strcat(exp, print);
			write_text(exp,35,35,WHITE,0);
			strcpy(exp,print);
			break;
	}
}

int isOperation(char op){
	if(op == 'x' || op == '/' || op == '+' || op == '-' || op == '^' || op == '%' || op == '!' || op == 'S' || op == '.' || op == 'P' || op == 'e'){
		return 1;
	}
	return 0;
}

int checkValidity(char exp[20]){
	int i;
	if(isOperation(exp[0])) return 0;
	for (i=0;i<strlen(exp)-1;i++){
		if(isOperation(exp[i]) == 1 && isOperation(exp[i+1]) == 1) return 0;
	}
	return 1;
}
//function for evaluating the expression
int evaluate(){
	int answer[20];
	int operand[20];
	char operator[20];
	int answer_TOS = 0;
	int operand_idx = 0;
	int operator_TOS = 0;
	int i = 0, j = 0;
	int isSquare = 0,counter = 0;
	while(exp[i] != '\0'){
		if(exp[i] == '1'){
			operand[operand_idx] = 1;
			operand_idx++;
		}else if(exp[i] == '2'){
			operand[operand_idx] = 2;
			operand_idx++;
		}else if(exp[i] == '3'){
			operand[operand_idx] = 3;
			operand_idx++;
		}else if(exp[i] == '4'){
			operand[operand_idx] = 4;
			operand_idx++;
		}else if(exp[i] == '5'){
			operand[operand_idx] = 5;
			operand_idx++;
		}else if(exp[i] == '6'){
			operand[operand_idx] = 6;
			operand_idx++;
		}else if(exp[i] == '7'){
			operand[operand_idx] = 7;
			operand_idx++;
		}else if(exp[i] == '8'){
			operand[operand_idx] = 8;
			operand_idx++;
		}else if(exp[i] == '9'){
			operand[operand_idx] = 9;
			operand_idx++;
		}else if(exp[i] == '0'){
			operand[operand_idx] = 0;
			operand_idx++;
		}else if(exp[i] == 'P'){
			operand[operand_idx] = 3;
			operand_idx++;
		}else if(exp[i] == 'e'){
			operand[operand_idx] = 2;
			operand_idx++;
		}else if(operand_idx != 0){
			for(j = 0; j < operand_idx - 1; j++){
				operand[0] = (operand[0]*10)+operand[j+1];
			}
			answer[answer_TOS] = operand[0];
			answer_TOS++;
			operand_idx = 0;
		}
		//OPERATION: ADDTION
		if(exp[i] == '+'){
			if(operator_TOS == 0){
				operator[operator_TOS] = '+';
				operator_TOS++;
			}else{
				if(operator[operator_TOS - 1] == '^'){
					int x = answer[answer_TOS - 2];
					while( (answer[answer_TOS - 1]--) != 1 ) {
						answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
					}
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '-'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] - answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == 'x'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] * answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '/'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] / answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '%'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] % answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}
				operator[operator_TOS] = '+';
				operator_TOS++;
			}
		}
		//OPERATION: SUBTRACTIION
		else if(exp[i] == '-'){
			if(operator_TOS == 0){
				operator[operator_TOS] = '-';
				operator_TOS++;
			}else{
				if(operator[operator_TOS - 1] == '^'){
					int x = answer[answer_TOS - 2];
					while( (answer[answer_TOS - 1]--) != 1 ) {
						answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
					}
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '+'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] + answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == 'x'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] * answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '/'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] / answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '%'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] % answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}
				operator[operator_TOS] = '-';
				operator_TOS++;
			}
		}
		//OPERATION: MULTIPLICATION
		else if(exp[i] == 'x'){
			if(operator_TOS == 0){
				operator[operator_TOS] = 'x';
				operator_TOS++;
			}else{
				if(operator[operator_TOS - 1] == '^'){
					int x = answer[answer_TOS - 2];
					while( (answer[answer_TOS - 1]--) != 1 ) {
						answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
					}
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '/'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] / answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '%'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] % answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}
				operator[operator_TOS] = 'x';
				operator_TOS++;
			}
		}
		//OPERATION: DIVISION
		else if(exp[i] == '/'){
			if(operator_TOS == 0){
				operator[operator_TOS] = '/';
				operator_TOS++;
			}else{
				if(operator[operator_TOS - 1] == '^'){
					int x = answer[answer_TOS - 2];
					while( (answer[answer_TOS - 1]--) != 1 ) {
						answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
					}
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == 'x'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] * answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '%'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] % answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}
				operator[operator_TOS] = '/';
				operator_TOS++;
			}
		}
		//OPERATION: MODULO
		else if(exp[i] == '%'){
			if(operator_TOS == 0){
				operator[operator_TOS] = '%';
				operator_TOS++;
			}else{
				if(operator[operator_TOS - 1] == '^'){
					int x = answer[answer_TOS - 2];
					while( (answer[answer_TOS - 1]--) != 1 ) {
						answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
					}
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == 'x'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] * answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '/'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] / answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}
				operator[operator_TOS] = '%';
				operator_TOS++;
			}
		}
		//OPERATION: EXPONENT
		else if(exp[i] == '^'){
			operator[operator_TOS] = '^';
			operator_TOS++;
		}
		//OPERATION: OPEN PARENTHESIS
		else if(exp[i] == '('){
			operator[operator_TOS] = '(';
			operator_TOS++;
			if(isSquare) counter++;
		}
		//OPERATION: CLOSING PARENTHESIS
		else if(exp[i] == ')'){
			while(operator[operator_TOS - 1] != '('){
				if(operator[operator_TOS - 1] == '^'){
					int x = answer[answer_TOS - 2];
					while( (answer[answer_TOS - 1]--) != 1 ) {
						answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
					}
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '%'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] % answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '+'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] + answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '-'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] - answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == 'x'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] * answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}else if(operator[operator_TOS - 1] == '/'){
					answer[answer_TOS - 2] = answer[answer_TOS - 2] / answer[answer_TOS - 1];
					answer_TOS--;
					operator[operator_TOS - 1] = '\0';
					operator_TOS--;
				}
			}
			operator[operator_TOS - 1] = '\0';
			operator_TOS--;

			if(isSquare){
				counter--;
				if(counter==0){
					isSquare = 0;
					answer[answer_TOS-1] = squareRoot(answer[answer_TOS-1]);
				}
			}
		}
		//OPERATION: FACTORIAL
		else if(exp[i] == '!'){
			answer[answer_TOS - 1] = factorial(answer[answer_TOS - 1]);
		}
		else if(exp[i] == 'S'){
			i++;
			isSquare = 1;
		}
		i++;
	}
	if(operand_idx != 0){
		for(j = 0; j < operand_idx - 1; j++){
			operand[0] = (operand[0]*10)+operand[j+1];
		}
		answer[answer_TOS] = operand[0];
		answer_TOS++;
		operand_idx = 0;
	}
	for(j = operator_TOS - 1; j > -1; j--){
		if(operator[j] == '+'){
			answer[answer_TOS - 2] = answer[answer_TOS - 2] + answer[answer_TOS - 1];
			answer_TOS--;
			operator[j] = '\0';
		}else if(operator[j] == '-'){
			answer[answer_TOS - 2] = answer[answer_TOS - 2] - answer[answer_TOS - 1];
			answer_TOS--;
			operator[j] = '\0';
		}else if(operator[j] == 'x'){
			answer[answer_TOS - 2] = answer[answer_TOS - 2] * answer[answer_TOS - 1];
			answer_TOS--;
			operator[j] = '\0';
		}else if(operator[j] == '/'){
			answer[answer_TOS - 2] = answer[answer_TOS - 2] / answer[answer_TOS - 1];
			answer_TOS--;
			operator[j] = '\0';
		}else if(operator[j] == '%'){
			answer[answer_TOS - 2] = answer[answer_TOS - 2] % answer[answer_TOS - 1];
			answer_TOS--;
			operator[j] = '\0';
		}else if(operator[j] == '^'){
			int x = answer[answer_TOS - 2];
			while( (answer[answer_TOS - 1]--) != 1 ) {
				answer[answer_TOS - 2] = answer[answer_TOS - 2] * x;
			}
			answer_TOS--;
			operator[j] = '\0';
		}
	}
	return answer[answer_TOS - 1];
}

int factorial(int n){
	if(n >= 1){
		return n * factorial(n - 1);
	}else{
		return 1;
	}
}
int squareRoot(int n){
	int x = n/2;
	while((x)!=0){
		if(x*x == n) return x;
		x--;
	}
	return 0;
}
//prints the button with the outer and inner function
void print_button(int r, int c, int x, int y, int color){
	outerSquare(x, y, color);
	innerSquare(r, c, x, y, color);
}
//prints outer portion of the button
void outerSquare(int x, int y, int color){
	int i,j;
	for (i=0;i<32;i++)write_pixel(i+x,0+y,color);
	for (i=0;i<32;i++)write_pixel(i+x,1+y,color);

	for (j=2;j<24;j++){
		for (i=0;i<2;i++)write_pixel(i+x,j+y,color);
		for (i=30;i<32;i++)write_pixel(i+x,j+y,color);
	}

	for (i=0;i<32;i++)write_pixel(i+x,24+y,color);
	for (i=0;i<32;i++)write_pixel(i+x,25+y,color);

}
//prints inner portion of the button
void innerSquare(int r, int c, int x, int y, int color){
	int i,j;
	for (i=4;i<28;i++) for (j=4;j<22;j++) write_pixel(i+x,j+y,color);
}
 //set up initial board 
void print_calculator(int x, int y){

	int i, j, a, b;
 	a=x;
 	b=y;
 	//prints help message at the upper left
   	write_text(" PRESS 'H' FOR HELP   CALCULATOR",15,5,WHITE,0); 
   	//prints the display area
   	print_display(a,25,GRAY);
	//prints the buttons
	for(i=0; i<maxrow; i++, b+=32){
		for(j=0; j<maxcol; j++, a+=40)
			print_button(i, j, a, b, GRAY);
		a=x;
	}

	outerSquare(X_coord,Y_coord,WHITE);
	print_button(0, 0, X_coord, Y_coord+96, RED);

	//ROW 1
	write_text("1",36,78,BLACK,0);
	write_text("2",76,78,BLACK,0);
	write_text("3",116,78,BLACK,0);
	write_text("(",156,78,BLACK,0);
	write_text(")",196,78,BLACK,0);
	write_text("AC",230,78,BLACK,0);
	write_text("CE",270,78,BLACK,0);

	//ROW 2
	write_text("4",36,110,BLACK,0);
	write_text("5",	76,110,BLACK,0);
	write_text("6",116,110,BLACK,0);
	write_text("/",156,110,BLACK,0);
	write_text("x",196,110,BLACK,0);
	write_text("^2",230,110,BLACK,0);
	write_text("^",276,110,BLACK,0);

	//ROW 3
	write_text("7",36,142,BLACK,0);
	write_text("8",76,142,BLACK,0);
	write_text("9",116,142,BLACK,0);
	write_text("-",156,142,BLACK,0);
	write_text("+",196,142,BLACK,0);
	write_text("P",236,142,BLACK,0);
	write_text("e",276,142,BLACK,0);

	//ROW 4
	write_text("Ex",30,174,WHITE,0);
	write_text("0",76,174,BLACK,0);
	write_text(".",116,174,BLACK,0);
	write_text("!",156,174,BLACK,0);
	write_text("%",196,174,BLACK,0);
	write_text("Sq",230,174,BLACK,0);
	write_text("=",276,174,BLACK,0);
	
}
//prints the display area 
void print_display(int x, int y, int color){
	int i,j;
	for (i=0;i<272;i++)write_pixel(i+x,0+y,color);
	for (i=0;i<272;i++)write_pixel(i+x,1+y,color);

	for (j = 2; j < 35; j++){
		for (i=0;i<2;i++)write_pixel(i+x,j+y,color);
		for (i=270;i<272;i++)write_pixel(i+x,j+y,color);
	}
	

	for (i=0;i<272;i++)write_pixel(i+x,35+y,color);
	for (i=0;i<272;i++)write_pixel(i+x,36+y,color);
}
 //covers an area with black
void erase(int x, int y, int w, int h){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}

