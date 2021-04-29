#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

char keys[10];	
int keyPos[10][2];	
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  											// เส้นขอบ
	for(int i=0; i <= SCREEN_WIDTH + 1; i++){ 
		gotoxy(i,SCREEN_HEIGHT); cout<<"=";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"||";
		gotoxy(SCREEN_WIDTH,i); cout<<"||";
	}
	for(int i=0; i < SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"||";
	}
}

void genAlphabet(int ind){
	keys[ind] = 65+rand()%25;
	keyPos[ind][0] = 2 + rand()%(WIN_WIDTH-2);   //random ตัวอักษร
	keyPos[ind][1] = 1;
}
void drawAlphabet(int ind){
	if( keyPos[ind][0] != 0 ){
		gotoxy(keyPos[ind][0], keyPos[ind][1]);   cout<<keys[ind];  
	} 
}
void eraseAlphabet(int ind){
	if( keyPos[ind][0] != 0 ){
		gotoxy(keyPos[ind][0], keyPos[ind][1]);   cout<<" ";  
	}
}
void resetAlphabet(int ind){
	eraseAlphabet(ind);
	genAlphabet(ind);
}

void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}
void timecount(){
	int time = 20;
	gotoxy(WIN_WIDTH + 7, 5);cout<<"time: "<<time<<endl;
}
void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n On Left side you will see falling characters ";
	cout<<"\n You have to keep them away from touching floor";
	cout<<"\n Press respective key from keyboard to keep playing";
	cout<<"\n\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void gameover(int score, int speed){
	system("cls");
	gotoxy(45,6); cout<<"--------------------------";
	gotoxy(45,7); cout<<"-------- Game Over -------";
	gotoxy(45,8); cout<<"--------------------------";
	gotoxy(45,10); cout<<"      SCORE: ";cout<< score;
	if(speed == 300){
		gotoxy(45,12);cout<<"      DIFFICULTY: Easy";
	}
	else if(speed == 240){
		gotoxy(45,12); cout<<"      DIFFICULTY: Normal";
	}
	else if(speed == 180){
		gotoxy(45,12); cout<<"      DIFFICULTY: Hard";
	}
	gotoxy(43,14); cout<<"Press any key to go back to menu.";
	getch();
}

void play(int speed){
	score = 0;
	for(int i=0; i<10; i++){
		keyPos[i][0] = keyPos[i][1] = 1;	
	}
	 
	system("cls"); 
	drawBorder(); 
	updateScore();
	
	for(int i=0; i<10; i++)
		genAlphabet(i); 
	
	gotoxy(WIN_WIDTH + 5, 2);cout<<"Typing Tutor";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			for(int i=0; i<10; i++){
				if( ch == keys[i] || ch-32 == keys[i] ){
					resetAlphabet(i);
					score++;
					updateScore();
				}
			}
			if(ch==27){
				break;
			}
		} 
		
		for(int i=0; i<10; i++)
			drawAlphabet(i);  
			
		Sleep(speed); 
		
		for(int i=0; i<10; i++){
			eraseAlphabet(i);  
			keyPos[i][1] += 1;
			if( keyPos[i][1] > SCREEN_HEIGHT ){
				gameover(score, speed);
				return;
			}
		}
	}
}
void difficult(){
	system("cls");
	gotoxy(45,5); cout<<" -------------------------- "; 
	gotoxy(45,6); cout<<" |       Difficulty       | "; 
	gotoxy(45,7); cout<<" --------------------------";
	gotoxy(45,9); cout<<"1. Easy";
	gotoxy(45,10); cout<<"2. Normal";
	gotoxy(45,11); cout<<"3. Hard";
	gotoxy(45,13); cout<<"select your difficulty: ";
	char diff = getche();

	if (diff == '1') play(300);
	else if (diff == '2') play(240);
	else if (diff == '3') play(180);
}


int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(45,5); cout<<" -------------------------- "; 
		gotoxy(45,6); cout<<" |     TYPING  TUTOR      | "; 
		gotoxy(45,7); cout<<" --------------------------";
		gotoxy(45,9); cout<<"1. Start Game";
		gotoxy(45,10); cout<<"2. Instructions";	 
		gotoxy(45,11); cout<<"3. Quit";
		gotoxy(45,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') {
			difficult();
		}
		else if( op=='2') {
			instructions();
		}
		else if( op=='3') {
			exit(0);
		} 
		
	}while(1);
	
	return 0;
}
