/*	SOTTO, NORIEL E.			*/
/*  ARIOLA, JONAH 				*/
/*	CMSC 125 T-6L				*/
/*	CALCULATOR! App for ICS-OS	*/


#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

void set_coordinates(int x, int y); //initialize panel coordinates
void innerSquare(int r, int c, int x, int y, int color); //prints a button innerSquare
void outerSquare(int x, int y, int color);
void print_display(int x, int y, int color);
void display_button(int x);
int evaluate();
void setup_buttonArray();
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
#define reset 'r'
#define yes 'y'
#define no 'n'
#define start '1'
#define quit_game '2'

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
  
	char keypress = start;
	int i,j;
	char str[15];
	int champion = 0;

	set_graphics(VGA_320X200X256);
  	set_coordinates(X_coord, Y_coord); //initialize board coordinates
   	setup_buttonArray();

	do{
		erase(1,1,400,220);
		
		keypress=start;
		erase(1,1,400,220);

		print_calculator(X_coord, Y_coord);
		row=0;
		col=0;
		do{

			if (keypress=(char)getch()){
			
				if(keypress==right_key){
					oldrow = row;
					oldcol = col;
					col = (col + 1) % maxcol;
				}
				
				else if(keypress==left_key){
					oldrow = row;
					oldcol = col;
					if(col <= 0)
						col = maxcol - 1;
					else
						col--;
				}
				
				else if(keypress==up_key){
					oldrow = row;
					oldcol = col;
					if(row <= 0)
						row = maxrow - 1;
					else
						row--;
				}
				
				else if(keypress==down_key){
					oldrow = row;
					oldcol = col;
					row = (row + 1) % maxrow;
				}
				
				else if(keypress == enter){				
					display_button(buttons[row][col]);
					// write_text("Some expression here..",35,35,WHITE,0);
					if(strcmp(exp,"Exiting...") == 0){
						keypress = quit;
					}
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

void set_coordinates(int x, int y){
	int i, j, a, b;
	
	a = x;
	b = y;
	
	for(i=0; i<maxrow; i++, b+=24){
		for(j=0; j<maxcol; j++, a+=31){
			bulbs_x[i][j] = a;
			bulbs_y[i][j] = b;
		}
		a=x;
	}
}

void setup_buttonArray(){
	int i,j,k=0;
	for (i = 0; i < maxrow; i++){
		for (j = 0; j < maxcol; j++){
			buttons[i][j] = ++k;
		}
	}
	
}

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
			strcat(exp,"S");
			write_text(exp,35,35,WHITE,0);
			break;
		case 28:
			sprintf(print, "%d", evaluate());
			strcat(exp, " = ");
			strcat(exp, print);
			write_text(exp,35,35,WHITE,0);
			strcpy(exp,print);
			break;
	}
}

int evaluate(){
	int answer[20];
	int operand[20];
	char operator[20];
	int answer_TOS = 0;
	int operand_idx = 0;
	int operator_TOS = 0;
	int i = 0, j = 0;
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
		}else{
			for(j = 0; j < operand_idx - 1; j++){
				operand[0] = (operand[0]*10)+operand[j+1];
			}
			answer[answer_TOS] = operand[0];
			answer_TOS++;
			operand_idx = 0;
		}
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
		}else if(exp[i] == '-'){
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
		}else if(exp[i] == 'x'){
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
		}else if(exp[i] == '/'){
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
		}else if(exp[i] == '%'){
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
		}else if(exp[i] == '^'){
			operator[operator_TOS] = '^';
			operator_TOS++;
		}
		i++;
	}
	for(j = 0; j < operand_idx - 1; j++){
		operand[0] = (operand[0]*10)+operand[j+1];
	}
	answer[answer_TOS] = operand[0];
	answer_TOS++;
	operand_idx = 0;
	for(j = operator_TOS - 1; j > -1; j--){
		printf("%c\n", operator[j]);
			write_text(exp,35,35,WHITE,0);
			write_text(exp,35,35,WHITE,0);
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


void outerSquare(int x, int y, int color){
	int i;
	for (i=0;i<32;i++)write_pixel(i+x,0+y,color);
	for (i=0;i<32;i++)write_pixel(i+x,1+y,color);

	for (i=0;i<2;i++)write_pixel(i+x,2+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,2+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,3+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,3+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,4+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,4+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,5+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,5+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,6+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,6+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,7+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,7+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,8+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,8+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,9+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,9+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,10+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,10+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,11+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,11+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,12+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,12+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,13+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,13+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,14+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,14+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,15+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,15+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,16+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,16+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,17+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,17+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,18+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,18+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,19+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,19+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,20+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,20+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,21+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,21+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,22+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,22+y,color);
	for (i=0;i<2;i++)write_pixel(i+x,23+y,color);
	for (i=30;i<32;i++)write_pixel(i+x,23+y,color);

	for (i=0;i<32;i++)write_pixel(i+x,24+y,color);
	for (i=0;i<32;i++)write_pixel(i+x,25+y,color);

}

void innerSquare(int r, int c, int x, int y, int color){
	int i;
	
	for (i=4;i<28;i++)write_pixel(i+x,4+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,5+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,6+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,7+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,8+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,9+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,10+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,11+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,12+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,13+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,14+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,15+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,16+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,17+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,18+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,19+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,20+y,color);
	for (i=4;i<28;i++)write_pixel(i+x,21+y,color);
}

void print_button(int r, int c, int x, int y, int color){

	outerSquare(x, y, color);
	innerSquare(r, c, x, y, color);
	
}


void print_calculator(int x, int y){ //set up initial board 

	int i, j, a, b;
 	a=x;
 	b=y;
 	char str[15];

   	write_text("CALCULATOR",120,5,WHITE,0); 

   	print_display(a,25,GRAY);
	
	for(i=0; i<maxrow; i++, b+=32){
		for(j=0; j<maxcol; j++, a+=40)
			print_button(i, j, a, b, GRAY);
		a=x;
	}


	outerSquare(X_coord,Y_coord,WHITE);
	print_button(0, 0, X_coord, Y_coord+96, RED);
	//display legend

	//ROW 1
	write_text("1",36,78,BLACK,0);
	write_text("2",76,78,BLACK,0);
	write_text("3",116,78,BLACK,0);
	write_text("(",156,78,BLACK,0);
	write_text(")",196,78,BLACK,0);
	write_text("CE",230,78,BLACK,0);
	write_text("AC",270,78,BLACK,0);

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
	write_text("S",236,174,BLACK,0);
	write_text("=",276,174,BLACK,0);

	/*write_text("Up: W",26,205,WHITE,0);
	write_text("Down: W",76,205,WHITE,0);
	write_text("Left: W",126,205,WHITE,0);
	write_text("Right: W",176,205,WHITE,0);*/
	
}

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

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}

