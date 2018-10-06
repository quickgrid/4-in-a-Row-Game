/*
	author: Asif Ahmed
	==============================
	start date: August 23, 2014
	last modified: August 31, 2014
	
	TODO:
	=====
	1. Fix the in game options so back button takes back to game instead of main menu
	2. Add play vs AI game
	3. Add extra decorations, graphics and animations
*/

# include "iGraphics.h"
# include "mmsystem.h"


# define N 7

/*
	variable declarations
*/

//splash
int sp1_x, sp1_y, sp2_x, sp2_y;
int splashAnimationSpeed;
int times,jumpHeight;
//loader bar
int loaderBarWidth, loaderBarHeight;
bool showLoaderBar, hideSplashLoader;
bool doDownAnim = true;
//button
int btn1_x, btn1_y, btn2_x, btn2_y; //main menu buttons 2 in a group 
int headerResolution, btnRes;
//mouse click actions
bool playModesButtonClick, playGameButtonClick, optionsButtonClick, optionsBackClick, helpBackClick, menuMouseClick, aboutBackClick;
bool showHelp, showMainMenu, showOptions, showGame, showPlayModes, showLogo, showAbout, showGameEnd;
bool soundMarked, musicMarked;
bool showActivePlayer, showBalls, gameEnded;
int options_sound_x, options_sound_y, options_music_x, options_music_y, options_back_x, options_back_y;
int help_back_x, help_back_y, help_x, help_y;
int about_x, about_y, about_back_x, about_back_y;
int modes_back_x, modes_back_y, modes_x, modes_y;
int game_board_x,game_board_y,game_back_x,game_back_y,game_repset_x,game_repset_y;
int active_player_x, active_player_y;
int playMode, endType, columnFillCount;


//window
int windowWidth, windowHeight, midWidth, midHeight;
int midWidthMinus64, midHeightMinus64, val64, val28;


//gameplay
int boardFill[N][N];
int k[N];
int player;


/*
	function prototypes
*/

//all variable intiavlization
void initializeVariables();

//calculation function prototypes
void findMenuButton(int mx, int my);
void findHelpBackButton(int mx, int my);
void findOptionsBackClick(int mx,int my);
void findOptionsButtonClick(int mx,int my);
void findAboutBackClick(int mx, int my);
void findPlayModesButtonClick(int mx,int my);
void findPlayGameButtonClick(int mx,int my);
//drawing function prototypes
void drawBackground();
void drawMainMenu(); 
void drawLoaderBar();
void drawHideSplashLoader();
void drawHelp();
void drawOptions();
void drawAbout();
void drawGame();
void drawLogo();
void drawPlayModes();
void drawBalls();
void drawActivePlayer();
void drawGameEnd();
//extra functions
void changePlayer();
void resetBoard();
void playSound();
void playMusic();
void stopMusic();


/*
	structure declaration
*/



/* 
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here	
	iClear();
	
	//spash screen with animation
	drawBackground();

	if(showLogo){
		drawLogo();
	}

	//draw loader bar
	if(showLoaderBar){
		drawLoaderBar();
	}

	//hide splash screen and show main menu
	if(hideSplashLoader){
		drawHideSplashLoader();

		//show after hiding splash screen
		if(showMainMenu){
			drawMainMenu();
		}

		if(showHelp){
			drawHelp();
		}

		if(showOptions){
			drawOptions();
		}


		if(showAbout){
			drawAbout();
		}

		if(showPlayModes){
			drawPlayModes();
		}
		
	 	if(showGame){
			drawGame();
			
			//shows which player will play
			if(showActivePlayer){
				drawActivePlayer();
			}

			//draw balls in chosen location
			if(showBalls){
				drawBalls();
			}

			if(showGameEnd){
				drawGameEnd();
			}

		}
		
	}
}

/*
	set all variable states
*/
void initializeVariables(){
	//main window resolution
	windowWidth = 1000, windowHeight = 600;

	//reuseable variable calculation
	headerResolution = 256;
	btnRes = 128;
	midWidth = windowWidth/2;
	midHeight = windowHeight/2;
	val64 = btnRes/2;
	val28 = btnRes/4;
	midWidthMinus64 = midWidth - val64;
	midHeightMinus64 = midHeight - val64;
	
	//main menu button group
	btn1_x = btn2_x = midWidthMinus64;
	btn1_y = midHeightMinus64;
	btn2_y = midHeight - btnRes*1.5;

	//splash co-ordinates
	sp1_x = sp1_y = 0;
	sp2_x = midWidth - btnRes;
	sp2_y = windowHeight;
	splashAnimationSpeed = 10;
	times = 2, jumpHeight = 20;
	doDownAnim = true;


	//loader bar
	loaderBarWidth = 0;
	loaderBarHeight = 10;
	showLoaderBar = false;

	//after splash
	hideSplashLoader = false;
	showMainMenu = true;

	//mouse click actions
	showHelp = helpBackClick = menuMouseClick = false;
	help_x = midWidth - headerResolution;
	help_y = val64;
	help_back_x = val28;
	help_back_y = windowHeight-val64;


	//option properties
	options_back_x = val28;
	options_back_y = windowHeight-val64;
	options_sound_x = midWidthMinus64;
	options_sound_y = midHeightMinus64;
	optionsButtonClick = optionsBackClick = showOptions = false;
	soundMarked = musicMarked = true;
	options_music_x = midWidthMinus64;
	options_music_y = midWidth-btnRes*1.5;

	//about properties
	showAbout = aboutBackClick = false;
	about_x = midWidth - headerResolution;
	about_y = val64;
	about_back_x = val28;
	about_back_y = windowHeight-val64;

	//play properties
	showGame = showPlayModes = playModesButtonClick = false;
	showLogo = true;
	playMode = 0; 
	modes_back_x = val28;
	modes_back_y = windowHeight-val64;
	modes_x = midWidth - btnRes;
	modes_y = midWidth - btnRes*2.5;

	//main game
	game_board_x = btnRes;
	game_board_y = 0;
	game_back_x = 0;
	game_back_y = windowHeight - btnRes;
	game_repset_x = windowWidth - headerResolution;
	game_repset_y = windowHeight - btnRes;
	playGameButtonClick = false;
	player = 1;
	endType = 0;
	columnFillCount = 0;
	showActivePlayer = true;
	showBalls = true;
	gameEnded = false;

	//shows currently active player marker
	active_player_x = btnRes*5.5;
	active_player_y = btnRes*1.5;

	//reset ball arrays
	for(int i=0; i<N; i++){
		k[i] = 0;
		for(int j=0; j<N; j++){
			boardFill[i][j] = 0;
		}
	}
}

void drawBackground(){
	iShowBMP(sp1_x, sp1_y, "assets\\MainSplashBg.bmp");
}

void drawLogo(){
	iShowBMP(sp2_x, sp2_y, "assets\\MainLogo.bmp");
}

void drawMainMenu(){
	iShowBMP(btn1_x, btn1_y, "assets\\playOpt.bmp");
	iShowBMP(btn2_x, btn2_y, "assets\\helpAbout.bmp");
	helpBackClick = playGameButtonClick = aboutBackClick = optionsBackClick = playModesButtonClick = optionsButtonClick = false;
}

void drawLoaderBar(){
	//loader border
	iSetColor(15,255,85);
	iFilledRectangle(windowWidth/3,windowHeight/6, loaderBarWidth, loaderBarHeight);
	if(loaderBarWidth<= 350){
		loaderBarWidth += loaderBarHeight/4;
	}else{
		hideSplashLoader = true;
		//plays sound after the loader bar is hidden
		playMusic();
	}
}

void drawHideSplashLoader(){
	//sp2_x = sp2_y = windowWidth;
	//sp1_x = sp1_y = windowWidth;
	sp2_x = midWidth - btnRes;
	sp2_y = midHeight + headerResolution/3;
	//loaderBarWidth = 0;
	showLoaderBar = false;
	menuMouseClick = true;
}

void drawHelp(){
	iShowBMP(help_x, help_y, "assets//helpPage.bmp");
	iShowBMP(help_back_x,help_back_y, "assets//backBtn.bmp");
	helpBackClick = true;
	menuMouseClick = optionsButtonClick = optionsBackClick = playModesButtonClick = playGameButtonClick = false;
}

void drawOptions(){
	iShowBMP(options_back_x, options_back_y, "assets//backBtn.bmp");

	if(soundMarked){
		iShowBMP(options_sound_x, options_sound_y, "assets//soundCheckBoxMarked.bmp");
	}else{
		iShowBMP(options_sound_x, options_sound_y, "assets//soundCheckBoxUnMarked.bmp");
	}

	if(musicMarked){
		iShowBMP(options_music_x, options_music_y, "assets//musicCheckBoxMarked.bmp");
	}else{
		iShowBMP(options_music_x, options_music_y, "assets//musicCheckBoxUnMarked.bmp");
	}

	optionsBackClick = optionsButtonClick = true;
	menuMouseClick = playGameButtonClick = playModesButtonClick = showMainMenu = helpBackClick = false;
}

void drawAbout(){
	iShowBMP(about_x, about_y, "assets//aboutPage2.bmp");
	iShowBMP(about_back_x, about_back_y, "assets//backBtn.bmp");
	aboutBackClick = true;
	menuMouseClick = playGameButtonClick = playModesButtonClick = optionsButtonClick = optionsBackClick = helpBackClick = false;
}

void drawPlayModes(){
	iShowBMP(modes_x, modes_y, "assets//playModesPage.bmp");
	iShowBMP(modes_back_x, modes_back_y, "assets//backBtn.bmp");
	playModesButtonClick = true;
	menuMouseClick = playGameButtonClick = optionsButtonClick = aboutBackClick = optionsBackClick = helpBackClick = false;
}

void drawGame(){
	iShowBMP(game_board_x, game_board_y, "assets//gameBoardv4.bmp");
	//iShowBMP(game_board_x, game_board_y, "assets//gameBoard.bmp");
	iShowBMP(game_repset_x, game_repset_y, "assets//replaySettingsBtn.bmp");
	iShowBMP(game_back_x, game_back_y, "assets//playGameBackBtn.bmp");
	playGameButtonClick = true;
	menuMouseClick = optionsButtonClick = helpBackClick = optionsBackClick = aboutBackClick = playModesButtonClick = showLogo = false;
}

void drawActivePlayer(){
	if(player == 1){
		iShowBMP(active_player_x, active_player_y, "assets//activePlayer1.bmp");	
	}else{
		iShowBMP(active_player_x, active_player_y, "assets//activePlayer2.bmp");
	}
}

void drawBalls(){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(boardFill[i][j] == 1){
				iShowBMP(btnRes+6 + 70*i, j*(btnRes/2), "assets//ball1.bmp");
			}
			if(boardFill[i][j] == 2){
				iShowBMP(btnRes+6 + 70*i, j*(btnRes/2), "assets//ball2.bmp");
			}
		}
	}
}

void drawGameEnd(){
	if(endType == 1){
		iShowBMP(active_player_x,active_player_y,"assets//player1won.bmp");
	}else if(endType == 2){
		iShowBMP(active_player_x,active_player_y,"assets//player2won.bmp");
	}else if(endType == 3){
		iShowBMP(active_player_x,active_player_y,"assets//gameDraw.bmp");
	}
}

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//printf("click at mx:%d, my:%d\n", mx, my);

		//place your codes here
		if(menuMouseClick){
			findMenuButton(mx, my);
		}
		if(helpBackClick){
			findHelpBackButton(mx,my);
		}
		if(optionsBackClick){
			findOptionsBackClick(mx,my);
		}
		if(optionsButtonClick){
			findOptionsButtonClick(mx,my);
		}
		if(aboutBackClick){
			findAboutBackClick(mx,my);
		}
		if(playModesButtonClick){
			findPlayModesButtonClick(mx,my);
		}
		if(playGameButtonClick){
			findPlayGameButtonClick(mx,my);
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == 'q')
	{
		//do something with 'q'
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	//place your codes for other keys here
}


void splashAnimationDown(){
	//check if spash 2 is out bound
	if(doDownAnim){
		if(sp2_y <= btnRes){
			if(times){
				sp2_y = jumpHeight*times;
				--times;
			}else{
				sp2_y = btnRes;
				doDownAnim = false;
				iPauseTimer(0);
			}
		}else{
			sp2_y -= splashAnimationSpeed;
		}
	}

	if(times==0){
		showLoaderBar = true;
	}
}


void findMenuButton(int mx, int my){
	//debug
	printf("x:%d y:%d\n", mx, my);
	printf("btn1_x:%d\n", btn1_x);
	printf("btn1_x - (headerResolution/2):%d\n", btn1_x - btnRes);
	printf("btn1_y:%d\n", btn1_y);
	printf("btn1_y - (headerResolution/2):%d\n", btn1_y - btnRes);

	//button 1 location play button
	if(mx >= btn1_x && mx <= (btn1_x + btnRes) && my >= btn1_y+ val64 && my <= (btn1_y + btnRes)){
		printf("x:%d y:%d PLAY CLICKED\n", mx, my);
		showPlayModes = showLogo = true;
		showMainMenu = showGame = showAbout = showHelp = showOptions = false;
		//button sound
		playSound();
	}
	
	//button 2 location option button
	if(mx >= btn1_x && mx <= (btn1_x + btnRes) && my >= btn1_y && my <= (btn1_y + val64)){
		printf("x:%d y:%d OPTION CLICKED\n", mx, my);
		showOptions = true;
		//button sound
		playSound();
	}
	
	//button 3 location help button
	if(mx >= btn2_x && mx <= (btn2_x + btnRes) && my >= btn2_y+ val64 && my <= (btn2_y + btnRes)){
		printf("x:%d y:%d HELP CLICKED\n", mx, my);
		showHelp = true;
		//button sound
		playSound();
	}

	//button 4 location about button
	if(mx >= btn2_x && mx <= (btn2_x + btnRes) && my >= btn2_y && my <= (btn2_y + val64)){
		printf("x:%d y:%d ABOUT CLICKED\n", mx, my);
		showAbout = true;
		//button sound
		playSound();
	}
}


void findHelpBackButton(int mx, int my){
	if(mx>= help_back_x && mx<= help_back_x+btnRes && my>= help_back_y && my<= help_back_y+btnRes){
		printf("mx:%d, my:%d Help BACK CLICKED\n",mx,my);
		showHelp = false;
		//button sound
		playSound();
	}
}

void findOptionsBackClick(int mx,int my){
	if(mx>= help_back_x && mx<= help_back_x+btnRes && my>= help_back_y && my<= help_back_y+btnRes){
		printf("mx:%d, my:%d Help BACK CLICKED\n",mx,my);
		showOptions = false;
		showMainMenu = true;
		//button sound
		playSound();
	}
}


void findOptionsButtonClick(int mx,int my){
	if(mx>= options_sound_x && mx<= options_sound_x + btnRes && my>= options_sound_y && my <= options_sound_y + val64){
		printf("mx:%d, my:%d Options SOUND CLICKED\n",mx,my);
		if(soundMarked){
			soundMarked = false;
		}else{
			soundMarked = true;
		}
	}
	if(mx>= options_music_x && mx<= options_music_x + btnRes && my>= options_music_y && my <= options_music_y + val64){
		printf("mx:%d, my:%d Options MUSIC CLICKED\n",mx,my);
		if(musicMarked){
			musicMarked = false;
			stopMusic();
		}else{
			musicMarked = true;
			playMusic();
		}
	}
}


void findAboutBackClick(int mx, int my){
	if(mx>= about_back_x && mx<= about_back_x+btnRes && my>= about_back_y && my<= about_back_y+btnRes){
		printf("mx:%d, my:%d About Back CLICKED\n",mx,my);
		showMainMenu = true;
		showAbout = false;
		//button sound
		playSound();
	}
}

void findPlayModesButtonClick(int mx,int my){
	if(mx>= modes_back_x && mx<= modes_back_x+btnRes && my>= modes_back_y && my<= modes_back_y+btnRes){
		printf("mx:%d, my:%d Play Modes Back CLICKED\n",mx,my);
		showMainMenu = true;
		showPlayModes = false;
		//button sound
		playSound();
	}

	if(mx>= modes_x && mx<= modes_x + headerResolution && my>= modes_y + val64 && my <= modes_y + btnRes){
		printf("mx:%d, my:%d Play Modes Continue CLICKED\n",mx,my);
		//playMode = 1;
		showGame = true;
		showPlayModes = false;
		//button sound
		playSound();
	}

	if(mx>= modes_x && mx<= modes_x + headerResolution && my>= modes_y && my <= modes_y + val64){
		printf("mx:%d, my:%d Play Modes New Game CLICKED\n",mx,my);
		//playMode = 2;
		showGame = true;
		showPlayModes = false;
		resetBoard();
		//button sound
		playSound();
	}
}

void findPlayGameButtonClick(int mx,int my){
	if(mx>= game_back_x && mx<= game_back_x + btnRes && my>= game_back_y && my <= game_back_y + btnRes){
		printf("mx:%d, my:%d Game Back CLICKED\n",mx,my);
		showHelp = showAbout = showOptions = showGame = showPlayModes = false;
		showLogo = menuMouseClick = showMainMenu = true;
		//button sound
		playSound();
	}

	if(mx>=  windowWidth - btnRes && mx<= windowWidth && my>= windowHeight - btnRes && my <= windowHeight){
		printf("mx:%d, my:%d Game Settings CLICKED\n",mx,my);
		/*
			Implement a different options pop up window
			uncomment booleans below
		*/
		showOptions = optionsButtonClick = optionsBackClick = showLogo = true;
		playGameButtonClick = showGame = showPlayModes = false;
		//button sound
		playSound();
	}

	if(mx>=  windowWidth - headerResolution && mx<= windowWidth - btnRes && my>= windowHeight - btnRes && my <= windowHeight){
		printf("mx:%d, my:%d Game Replay CLICKED\n",mx,my);
		//reset game board to empty
		resetBoard();
		//button sound
		playSound();
	}

	if(!gameEnded){
		for(int i=0; i<N; i++){
			//tracking bar co-ordinates based on predrawn board
			if(mx>= btnRes+6 + 70*i && mx<= btnRes + 70*(i+1)  && my>= 0 && my <= btnRes*3.5){
				printf("Clicked at %d column\n", i);
				
				//check if a column is filled
				if(k[i] == N){
					break;
				}
				
				//set ball count for appropriate user
				boardFill[i][k[i]] = player;	//k[i] counts the number of ball from 0 to increment 1 until limit reached
				++k[i];
				
				//change to next player
				printf("player before: %d\n", player);
				changePlayer();
				printf("player after: %d\n", player);

				//checking logic check if player won
				//If only if used insted of else if then it will check every type of matches also useful if want check all matches
				//check balls down
				if(boardFill[i][k[i]-1] == boardFill[i][k[i]-2] && boardFill[i][k[i]-1] == boardFill[i][k[i]-3] && boardFill[i][k[i]-1] == boardFill[i][k[i]-4]){
					printf("works....down\n");
					endType = boardFill[i][k[i]-1];
					showGameEnd = true;
					showActivePlayer = false;
					gameEnded = true;
				}
				//check 3 more ball to right
				if(i+3 < N){
					if(boardFill[i][k[i]-1] == boardFill[i+1][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i+2][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i+3][k[i]-1]){
						printf("works....right\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check 3 more ball to left
				if(i-3 >= 0){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i-2][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i-3][k[i]-1]){
						printf("works....left\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check 1 ball left 2 ball right
				if(i-1 >= 0 && i+2 < N){
					if(boardFill[i][k[i]-1] == boardFill[i+1][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i+2][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i-1][k[i]-1]){
						printf("works....left1....right2\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check 1 ball right 2 ball left
				if(i+1 < N && i-2 >= 0){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i-2][k[i]-1] && boardFill[i][k[i]-1] == boardFill[i+1][k[i]-1]){
						printf("works....right1....left2\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check 3 more ball to down left
				if(i-3 >= 0 && k[i]-4 >= 0){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]-2] && boardFill[i][k[i]-1] == boardFill[i-2][k[i]-3] && boardFill[i][k[i]-1] == boardFill[i-3][k[i]-4]){
						printf("works....down....left\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check 3 more ball to down right
				if(i+3 < N && k[i]-4 >= 0){
					if(boardFill[i][k[i]-1] == boardFill[i+1][k[i]-2] && boardFill[i][k[i]-1] == boardFill[i+2][k[i]-3] && boardFill[i][k[i]-1] == boardFill[i+3][k[i]-4]){
						printf("works....down....right\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}

				//experimental code
				//check 2 balls down left 1 balls up right
				if(i-2 >= 0 && k[i]-3 >= 0 && i+1 < N && k[i]-2 >= 0){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]-2] && boardFill[i][k[i]-1] == boardFill[i-2][k[i]-3] && boardFill[i][k[i]-1] == boardFill[i+1][k[i]-2]){
						printf("works....downleft2....upright1\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check 2 balls down right 1 balls up left
				if(i+2 < N && k[i]-3 >= 0 && i-1 >= 0 && k[i]-2 >= 0 ){
					if(boardFill[i][k[i]-1] == boardFill[i+1][k[i]-2] && boardFill[i][k[i]-1] == boardFill[i+2][k[i]-3] && boardFill[i][k[i]-1] == boardFill[i-1][k[i]-2]){
						printf("works....downright2....upleft1\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//experinmetal code
				if(i-1 >= 0 && k[i]-2 >= 0 && i+2 < N && k[i]+1 < N){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]-2] && boardFill[i][k[i]-1] == boardFill[i+1][k[i]] && boardFill[i][k[i]-1] == boardFill[i+2][k[i]+1]){
						printf("works....downleft1....upright2\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				if(i-2 >= 0 && k[i]+1 < N && i+1 < N && k[i]-2 >= 0){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]] && boardFill[i][k[i]-1] == boardFill[i-2][k[i]+1] && boardFill[i][k[i]-1] == boardFill[i+1][k[i]-2]){
						printf("works....up....left\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check  3 balls up left
				if(i-3 >= 0 && k[i]+2 < N){
					if(boardFill[i][k[i]-1] == boardFill[i-1][k[i]] && boardFill[i][k[i]-1] == boardFill[i-2][k[i]+1] && boardFill[i][k[i]-1] == boardFill[i-3][k[i]+2]){
						printf("works....up....left\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				//check  3 balls up right
				if(i+3 < N && k[i]+2 < N){
					if(boardFill[i][k[i]-1] == boardFill[i+1][k[i]] && boardFill[i][k[i]-1] == boardFill[i+2][k[i]+1] && boardFill[i][k[i]-1] == boardFill[i+3][k[i]+2]){
						printf("works....up....right\n");
						endType = boardFill[i][k[i]-1];
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}
				
				
				//check if game drawn
				if(endType != 1 || endType != 2){
					//game draw checking logic
					columnFillCount = 0;
					for(int ci=0; ci<N; ci++){
						for(int cj=0; cj<N; cj++){
							if(boardFill[ci][cj] == 1 || boardFill[ci][cj] == 2){
								++columnFillCount;
							}
						}	
						//printf("columnFillCount: %d\n", columnFillCount);
					}
					if(columnFillCount == N*N){
						printf("game is drawn....\n");
						endType = 3;
						showGameEnd = true;
						showActivePlayer = false;
						gameEnded = true;
					}
				}

				/*
				//up checking logic never reqired
				else if(boardFill[i][k[i]-1] == boardFill[i][k[i]] && boardFill[i][k[i]-1] == boardFill[i][k[i]+1] && boardFill[i][k[i]-1] == boardFill[i][k[i]+2]){
					printf("works....up\n");
				}
				*/
				//end basic checking code

			}
		}
	}
}

void changePlayer(){
	if(player == 1){
		player = 2;
	}else if(player == 2){
		player = 1;
	}
}

void resetBoard(){
	//
	showGameEnd = false;
	showActivePlayer = true;
	gameEnded = false;
	//reset player to 1 otherwise the next player will stay as the 1st player
	player = 1;
	//reset the game board
	for(int i=0; i<N; i++){
		k[i] = 0;
		for(int j=0; j<N; j++){
			boardFill[i][j] = 0;
		}
	}
}

void playMusic(){
	PlaySound(TEXT("gameLoopSound.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void stopMusic(){
	PlaySound(NULL, 0, 0);
}

void playSound(){
	if(soundMarked){
		PlaySound(TEXT("button-29.wav"), NULL, SND_ASYNC);
		Sleep(100);
		//for(int t=0; t<50000000; t++);	//delay technique
	}
	if(musicMarked){
		playMusic();
	}
}


int main()
{
	//set all variables
	initializeVariables();

	//splash animation
	iSetTimer(50, splashAnimationDown);

	//place your own initialization codes here. 
	iInitialize(windowWidth, windowHeight, "4 in a Row");

	return 0;
}	