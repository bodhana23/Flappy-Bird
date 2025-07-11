//Group number 13
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WINDOW_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//Determines where each pipe is drawn on the horizontal axis.
int pipePos[3]; 
//store the positions of the gaps in the pipes.
int gapPossition[3];
//Ensures that pipes are only drawn when they should be visible to the player and reset when they go off-screen.
int pipeFlag[3];
//ASCII art of a bird
char bird[2][6] = { {'/','-','-','o','\\',' ',},
					{'|','_','_','_',' ','>'} };
//x coordinate of bird position					
int birdPos = 6;

int score = 0;

//function to move the cursor to a specific position on the console screen.
void gotoxy(int x, int y)//in <windows.h>
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
//function to control how the cursor appears in a console application. 
void setcursor(bool visible, DWORD size) // DWORD is in <windows.h>
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor); //This is a Windows API function that sets the cursor's size and visibility in the console
}
//function to draw the border
void drawBorder(){ 
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); //draw the upper horizontal border start from LHS
		cout<<"±";
		gotoxy(i,SCREEN_HEIGHT); //draw the bottem horizontal border
		cout<<"±";
	}
	
	for(int i=0; i<SCREEN_HEIGHT+1; i++){
		gotoxy(0,i); //draw the left vertical border
		cout<<"±";
		gotoxy(SCREEN_WIDTH,i); //draw the rignt vertical border
		cout<<"±";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WINDOW_WIDTH,i); //draw a window to play the game
		cout<<"±";
	}
}
//function that generates a random position for a gap in a pipe
void generatePipe(int ind){
	gapPossition[ind] = 3 + rand()%14; 
}

void drawPipe(int ind){
	if( pipeFlag[ind] == true ){ //This flag indicates whether the pipe at index ind should be drawn or not.
		//draw the upper part of the pipe
		for(int i=0; i<gapPossition[ind]; i++){ 
		//allows pipe to move horizontaly
			gotoxy(WINDOW_WIDTH-pipePos[ind],i+1);
			cout<<"±±±"; 
		}
		//draw the bottem part of the pipe
		for(int i=gapPossition[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WINDOW_WIDTH-pipePos[ind],i+1); 
			cout<<"±±±"; 
		}
	} 
}
//clears the characters from the console where the pipe was previously drawn
void erasePipe(int ind){
	
	if( pipeFlag[ind] == true ){
		//Erase the upper part of the pipe
		for(int i=0; i<gapPossition[ind]; i++){ 
			gotoxy(WINDOW_WIDTH-pipePos[ind],i+1);
			cout<<"   "; //clear the pipe overwriting it with spaces.
		}
		//Erase the Lower Part of the Pipe
		for(int i=gapPossition[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WINDOW_WIDTH-pipePos[ind],i+1);
			cout<<"   "; 
		}
	}
}
//function to draw the bird
void drawBird(){
	
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); // allows the bird to move up or down
			cout<<bird[i][j];
		}
	}
}
//function to erase the bird from the console where previously drawn
void eraseBird(){
	
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); 
			cout<<" "; // replacing each character of the bird with a space
		}
	}
}

// function to detect a collosion
int collision(){
	
	//assumes that the bird is at or near the same horizontal position where a collision could potentially occur
	if( pipePos[0] >= 61  ){
		//The condition checks if the bird's y-coordinate (birdPos) is either above the gap or below the gap
		if( birdPos < gapPossition[0] || birdPos > gapPossition[0]+GAP_SIZE ){
			return true;
		}
	}
	return 0;
}

// function to update the score
void updateScore(){
	gotoxy(WINDOW_WIDTH + 7, 5);
	cout<<"Score: "<<score<<endl;
}

// function to print the best score
int bestScore = 0;
void updateBestScore(int currentScore) {
    if (currentScore > bestScore) {
        bestScore = currentScore;
    }
}
//post game window
void gameover() {
	
    int consoleWidth = 90;
    int startX = (consoleWidth - 58) / 2; // Adjusting to center the message
    // clear the console screen
    system("cls");
    
    cout << endl;
    gotoxy(5, 4); cout << "\t\t==========================================================================================" << endl;
    gotoxy(startX, 5); cout << "\t\t                                                     " << endl;
    gotoxy(startX, 6); cout << " $$$$$$\\   $$$$$$\\  $$\\      $$\\ $$$$$$$$\\        $$$$$$\\  $$\\    $$\\ $$$$$$$$\\ $$$$$$$\\  \n";
    gotoxy(startX, 7); cout << "$$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  _____|      $$  __$$\\ $$ |   $$ |$$  _____|$$  __$$\\ \n";
    gotoxy(startX, 8); cout << "$$ /  \\__|$$ /  $$ |$$$$\\  $$$$ |$$ |            $$ /  $$ |$$ |   $$ |$$ |      $$ |  $$ |\n";
    gotoxy(startX, 9); cout << "$$ |$$$$\\ $$$$$$$$ |$$\\$$\\$$ $$ |$$$$$\\          $$ |  $$ |\\$$\\  $$  |$$$$$\\    $$$$$$$  |\n";
    gotoxy(startX, 10); cout << "$$ |\\_$$ |$$  __$$ |$$ \\$$$  $$ |$$  __|         $$ |  $$ | \\$$$  /  $$  __|   $$  __$$< \n";
    gotoxy(startX, 11); cout << "$$ |  $$ |$$ |  $$ |$$ |\\$  /$$ |$$ |            $$ |  $$ |  \\$$  /   $$ |      $$ |  $$ |\n";
    gotoxy(startX, 12); cout << "\\$$$$$$  |$$ |  $$ |$$ | \\_/ $$ |$$$$$$$$\\        $$$$$$  |   \\$/    $$$$$$$$\\ $$ |  $$ |\n";
    gotoxy(startX, 13); cout << "\\______/ \\__|  \\__|\\__|     \\__|\\________|       \\______/     \\_/    \\________|\\__|  \\__|\n";
    gotoxy(5, 14); cout << "\t\t==========================================================================================" << endl;
    gotoxy(startX, 16); cout << "\t\t------------------ Your score: " << score << " --------------------" << endl;
    gotoxy(startX, 17); cout << endl;
    gotoxy(startX, 18); cout << "\t\t         Press any key to go back to the menu.";
    updateBestScore(score);
    //reads a single character from the keyboard
	getch(); //<conio.h>
}

// function to display the instructions
void instructions(){
	
	// clear the console 
	system("cls");
	
	gotoxy(7,1); cout<<" ========================================================================================================== "; 
	gotoxy(8,3); cout << "$$$$$$$$\\ $$\\        $$$$$$\\  $$$$$$$\\  $$$$$$$\\ $$\\     $$\\       $$$$$$$\\  $$$$$$\\ $$$$$$$\\  $$$$$$$\\  \n";
    gotoxy(8,4); cout << "$$  _____|$$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\\\$$\\   $$  |      $$  __$$\\ \\_$$  _|$$  __$$\\ $$  __$$\\ \n";
    gotoxy(8,5); cout << "$$ |      $$ |      $$ /  $$ |$$ |  $$ |$$ |  $$ |\\$$\\ $$  /       $$ |  $$ |  $$ |  $$ |  $$ |$$ |  $$ |\n";
    gotoxy(8,6); cout << "$$$$$\\    $$ |      $$$$$$$$ |$$$$$$$  |$$$$$$$  | \\$$$$  /        $$$$$$$\\ |  $$ |  $$$$$$$  |$$ |  $$ |\n";
    gotoxy(8,7); cout << "$$  __|   $$ |      $$  __$$ |$$  ____/ $$  ____/   \\$$  /         $$  __$$\\   $$ |  $$  __$$< $$ |  $$ |\n";
    gotoxy(8,8); cout << "$$ |      $$ |      $$ |  $$ |$$ |      $$ |         $$ |          $$ |  $$ |  $$ |  $$ |  $$ |$$ |  $$ |\n";
    gotoxy(8,9); cout << "$$ |      $$$$$$$$\\ $$ |  $$ |$$ |      $$ |         $$ |          $$$$$$$  |$$$$$$\\ $$ |  $$ |$$$$$$$  |\n";
    gotoxy(8,10); cout << "\\__|      \\________|\\__|  \\__|\\__|      \\__|         \\__|          \\_______/ \\______|\\__|  \\__|\\_______/ \n";
	gotoxy(7,13); cout<<"==========================================================================================================";
	gotoxy(50,14);cout<<"INSTRUCTIONS";
	gotoxy(10,16);cout<<"* Press spacebar to make bird fly";
	gotoxy(10,17);cout<<"* You can change the diffculty level in the game by pressing 3 in the main menu";
	gotoxy(10,18);cout<<"* Press any key to go back to menu";
	//reads a single character from the keyboard
	getch();
}

void play(int level){
	
	// Birds initial vertical position
	birdPos = 6;
	score = 0;
	// Activating the first pipe
	pipeFlag[0] = true; 
	// Second pipe is inactive
	pipeFlag[1] = false;
	//pipe horizontal position initialize to 4
	pipePos[0] = pipePos[1] = 4;
	
	system("cls"); 
	drawBorder();
	generatePipe(0);
	updateScore();
	
	//Display Initial Game Info
	gotoxy(WINDOW_WIDTH + 5, 2);
	cout<<"FLAPPY BIRD";
	gotoxy(WINDOW_WIDTH + 6, 4);
	cout<<"----------";
	gotoxy(WINDOW_WIDTH + 6, 6);
	cout<<"----------";
	gotoxy(WINDOW_WIDTH + 5,8);
	cout<<"Best Score:"<<bestScore;
	gotoxy(WINDOW_WIDTH + 7, 12);
	cout<<"Control ";
	gotoxy(WINDOW_WIDTH + 7, 13);
	cout<<"-------- ";
	gotoxy(WINDOW_WIDTH + 2, 14);
	cout<<" Spacebar = jump";
	
	gotoxy(10, 5);
	cout<<"Press any key to start";
	getch();
	gotoxy(10, 5);
	cout<<"                      ";
	
	while(true){
		 //kbhit = key board hit (<conio.h>)
		if(kbhit()){
			//The getch() function returns the ASCII code of the key pressed
			char ch = getch();
			//if the input is spacebar = ASCII 32
			if(ch==32){
				// to make sure bird is at the top edge and should not move up further.
				if( birdPos > 3 )
				// make bird moves upwards by 3 rows on the console screen
					birdPos-=3;
			}
			//if the input is escape = ASCII 27 
			if(ch==27){
				break;
			}
		}
		// draw the bird on the console
		drawBird();
		// Draw the pipes on the screen
		drawPipe(0);
		drawPipe(1);
	
	// if a collition is dected call game over function
		if( collision() == 1 ){
			gameover();
			return;
		}
		// used to control the game's speed
		Sleep(level); //<windows.h>
		// Erase the current drawings of birds and pipes
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		//The bird automatically falls by incrementing birdPos by 1 simulating gravity
		birdPos += 1;
		
		//If the bird falls below the screen the game ends with a game-over screen.
		if( birdPos > SCREEN_HEIGHT - 2 ){
			gameover();
			return;
		}
		// If the first pipe is active it moves to the right by 2 units
		if( pipeFlag[0] == 1 )
			pipePos[0] += 2;
		
		// The second pipe is moved if it is active.
		if( pipeFlag[1] == 1 )
			pipePos[1] += 2;
		
		/* When the first pipe reaches a certain position on the screen (near the right edge), 
		the second pipe is activated (pipeFlag[1] = 1), and its position is reset (pipePos[1] = 4).
		 A new pipe is generated using generatePipe(1);.*/
		if( pipePos[0] >= 40 && pipePos[0] < 42 ){
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			generatePipe(1);
		}
		// when the pipe is ath this possition update the score and the second pipe take the first npossition  
		if( pipePos[0] > 68 ){
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPossition[0] = gapPossition[1];
		}
		
	}
	 
}

int main()
{
	/*Ensure that rand() is properly seeded using srand(time(0)) (or another seed) to get different sequences of random numbers
	each time the program runs. Otherwise, rand() will generate the same sequence of numbers on each execution.*/
	setcursor(0,0); 
	srand( (unsigned)time(NULL));
	 
    int level = 100;
	
	do{
		// Manin menu to choose the options 	
		system("cls");
		gotoxy(7,1); cout<<" ========================================================================================================== "; 
		gotoxy(8,3); cout << "$$$$$$$$\\ $$\\        $$$$$$\\  $$$$$$$\\  $$$$$$$\\ $$\\     $$\\       $$$$$$$\\  $$$$$$\\ $$$$$$$\\  $$$$$$$\\  \n";
        gotoxy(8,4); cout << "$$  _____|$$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\\\$$\\   $$  |      $$  __$$\\ \\_$$  _|$$  __$$\\ $$  __$$\\ \n";
        gotoxy(8,5); cout << "$$ |      $$ |      $$ /  $$ |$$ |  $$ |$$ |  $$ |\\$$\\ $$  /       $$ |  $$ |  $$ |  $$ |  $$ |$$ |  $$ |\n";
        gotoxy(8,6); cout << "$$$$$\\    $$ |      $$$$$$$$ |$$$$$$$  |$$$$$$$  | \\$$$$  /        $$$$$$$\\ |  $$ |  $$$$$$$  |$$ |  $$ |\n";
        gotoxy(8,7); cout << "$$  __|   $$ |      $$  __$$ |$$  ____/ $$  ____/   \\$$  /         $$  __$$\\   $$ |  $$  __$$< $$ |  $$ |\n";
        gotoxy(8,8); cout << "$$ |      $$ |      $$ |  $$ |$$ |      $$ |         $$ |          $$ |  $$ |  $$ |  $$ |  $$ |$$ |  $$ |\n";
        gotoxy(8,9); cout << "$$ |      $$$$$$$$\\ $$ |  $$ |$$ |      $$ |         $$ |          $$$$$$$  |$$$$$$\\ $$ |  $$ |$$$$$$$  |\n";
        gotoxy(8,10); cout << "\\__|      \\________|\\__|  \\__|\\__|      \\__|         \\__|          \\_______/ \\______|\\__|  \\__|\\_______/ \n";
        gotoxy(7,13); cout<<"==========================================================================================================";
		gotoxy(45,15); cout<<"1. Start Game";
		gotoxy(45,16); cout<<"2. Instructions";	
		gotoxy(45,17); cout<<"3. Change the difficulty level";	 
		gotoxy(45,18); cout<<"4. Quit";
		gotoxy(45,19); cout<<"Select option: ";
		// get the user input
		char op = getche();
		
		if( op=='1') {
			
			play(level);
		}
		else if( op=='2'){
			
			instructions();
		}
		else if( op=='3') {
			
			system("cls");
			
			gotoxy(7,1); cout<<" ========================================================================================================== "; 
			gotoxy(8,3); cout << "$$$$$$$$\\ $$\\        $$$$$$\\  $$$$$$$\\  $$$$$$$\\ $$\\     $$\\       $$$$$$$\\  $$$$$$\\ $$$$$$$\\  $$$$$$$\\  \n";
            gotoxy(8,4); cout << "$$  _____|$$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\\\$$\\   $$  |      $$  __$$\\ \\_$$  _|$$  __$$\\ $$  __$$\\ \n";
            gotoxy(8,5); cout << "$$ |      $$ |      $$ /  $$ |$$ |  $$ |$$ |  $$ |\\$$\\ $$  /       $$ |  $$ |  $$ |  $$ |  $$ |$$ |  $$ |\n";
            gotoxy(8,6); cout << "$$$$$\\    $$ |      $$$$$$$$ |$$$$$$$  |$$$$$$$  | \\$$$$  /        $$$$$$$\\ |  $$ |  $$$$$$$  |$$ |  $$ |\n";
            gotoxy(8,7); cout << "$$  __|   $$ |      $$  __$$ |$$  ____/ $$  ____/   \\$$  /         $$  __$$\\   $$ |  $$  __$$< $$ |  $$ |\n";
            gotoxy(8,8); cout << "$$ |      $$ |      $$ |  $$ |$$ |      $$ |         $$ |          $$ |  $$ |  $$ |  $$ |  $$ |$$ |  $$ |\n";
            gotoxy(8,9); cout << "$$ |      $$$$$$$$\\ $$ |  $$ |$$ |      $$ |         $$ |          $$$$$$$  |$$$$$$\\ $$ |  $$ |$$$$$$$  |\n";
            gotoxy(8,10); cout << "\\__|      \\________|\\__|  \\__|\\__|      \\__|         \\__|          \\_______/ \\______|\\__|  \\__|\\_______/ \n";
            gotoxy(7,13); cout<<"==========================================================================================================";
		    gotoxy(45,15); cout<<"Select Difficulty Level to start ";
			gotoxy(45,17); cout<<"1. Easy";
			gotoxy(45,18); cout<<"2. Medium";	 
			gotoxy(45,19); cout<<"3. Hard";
			gotoxy(45,20); cout<<"Select option: ";
			// get the user input
			char difficulty = getche();
			
			if(difficulty == '1') 
			level = 120; // Easy
			else if(difficulty == '2') 
			level = 100; // Medium
			else if(difficulty == '3') 
			level = 60; // Hard
			
		}
		else if( op=='4') {
			exit(0);
		}
		
	}while(true);
	
	return 0;
}                                                                                                                                                                                              

