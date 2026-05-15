#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <stdbool.h>

#define WHITE      7
#define GREEN      2
#define CYAN       3
#define LIGHT_CYAN 11
#define LIGHT_RED  12
#define LIGHT_BLUE 9
#define YELLOW     14
#define MAGENTA    13

void window_size()     // keeping window size fixed at 60 rows and 17 columns
{
    SetConsoleTitle("Focus Timer By Reejul");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 59, 16};  
    COORD bufferSize = {60, 17};
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
    HWND console = GetConsoleWindow();
    long style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;    // bitwise to turn maximize button off
    style &= ~WS_THICKFRAME;     // bitwise to disable window resizing 
    SetWindowLong(console, GWL_STYLE, style);
}

void load_font_size(int size)		// resize console font
{	
    HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);   
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;   
    cfi.dwFontSize.Y = size;  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(text, FALSE, &cfi);
}

void hide_cursor()		// to disable the blinking cursor
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;   
    SetConsoleCursorInfo(consoleHandle, &info);
}

void show_cursor()		// to enable the blinking cursor, only when taking inputs
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = TRUE;    
    SetConsoleCursorInfo(consoleHandle, &info);
}

void audio()			// loads or opens the audio files located within main.c folder
{	
	mciSendString("open \"enter.mp3\" type mpegvideo alias enter", NULL, 0, NULL);
	mciSendString("open \"lofi.mp3\" type mpegvideo alias lofi", NULL, 0, NULL);
	mciSendString("open \"rain.mp3\" type mpegvideo alias rain", NULL, 0, NULL);
}

void main_menu() 		// main menu
{    
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, LIGHT_CYAN);
    printf("\n");
    printf("  ______                     _______ _                      \n");	// ASCII art for Focus Timer
    printf(" |  ____|                   |__   __(_)                     \n");
    printf(" | |__ ___   ___ _   _ ___     | |   _ _ __ ___   ___ _ __ \n");
    printf(" |  __/ _ \\ / __| | | / __|    | |  | | '_ ` _ \\ / _ \\ '__|\n");
    printf(" | | | (_) | (__| |_| \\__ \\    | |  | | | | | | |  __/ |   \n");
    printf(" |_|  \\___/ \\___|\\__,_|___/    |_|  |_|_| |_| |_|\\___|_|   \n");
    printf("\n");
    SetConsoleTextAttribute(text_colour, GREEN);
    printf("  [For Studying and Relaxation]\n\n");
    printf("  Press any key to begin...");
    SetConsoleTextAttribute(text_colour, WHITE);
    printf("\n\n\n\n\nVersion 1.0 (Made by Reejul Kant)");
    getch();
    system("cls");		// for clearing console screen. Its not the best way but it's all I can do as of now.
}

void draw_mountains() 		//ASCII art for mountains when timer is running
{	
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, GREEN);
    printf("           /\\ \n");
    printf("          /  \\  /\\ \n");
    printf("         /    \\/  \\      /\\ \n");
    printf("    /\\  /      \\   \\    /  \\ \n");
    printf("   /  \\/        \\   \\  /    \\ \n");
    printf("  /    \\         \\   \\/      \\ \n");
    printf(" /      \\         \\  /        \\ \n");
    SetConsoleTextAttribute(text_colour, CYAN);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void music_selection()		// menu for selecting the audio or music
{	
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(text_colour, MAGENTA);
	printf("\n ===== Select focus audio preference =====\n\n");
	
	SetConsoleTextAttribute(text_colour, LIGHT_CYAN);
	printf(" [1] Peaceful music\n [2] Rain sounds\n [3] Music + Rain\n [4] No music\n");
	int music_choice = _getch();
	mciSendString("play enter from 0", NULL, 0, NULL);
	
	system("cls");
	if (music_choice == '1') 
	{
		printf(" %c Playing peaceful music.", 14);
		mciSendString("play lofi repeat", NULL, 0, NULL);
	}
	else if (music_choice == '2') 
	{
		printf(" %c Playing rain sounds.", 14);
		mciSendString("play rain repeat", NULL, 0, NULL);
	}
	else if (music_choice == '3') 
	{
		printf(" %c Playing peaceful music + rain sound %c", 14, 14);
		mciSendString("play lofi from 0", NULL, 0, NULL);
		mciSendString("play rain repeat", NULL, 0, NULL);
	}
	else 
	{
	}
}

int main(void) 
{
		window_size();
		load_font_size(24);			// font size set to 24
	
		HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);		// handle console text output
		int bar, hour, min, sec, i, j, k, final_hour, final_min, final_sec;		// c89 mode doesn't let me declare variables in a loop
		char again;		
		
		do		// when user wants to run the app again after time is up
		{
			system("cls");
			main_menu();
			audio(); 
			mciSendString("play enter from 0", NULL, 0, NULL);
		
			for (bar = 0; bar <= 30; bar++) 		// loading bar animation
			{
				printf ("=");
				Sleep(20);		
			}
		
			while (true)		// setting infinite loop for invalid inputs
			{   
				SetConsoleTextAttribute(text_colour, WHITE);
				printf("\n Enter the time in format [HOURS:MINS]: ");
				if (scanf("%d:%d", &hour, &min) == 2 && hour >= 0 && min >= 0 && min < 60) 
				{
					break;
			    }
			    else 
			    { 
		    	    mciSendString("play enter from 0", NULL, 0, NULL);
				    SetConsoleTextAttribute(text_colour, LIGHT_RED);
				    printf("Invalid time. Enter it like 2:12, 0:30 etc. \n");
				    while (getchar() != '\n');
			}
			}
		
			mciSendString("play enter from 0", NULL, 0, NULL);
			sec = ((hour * 3600) + (min * 60));		// converting hh:mm to seconds
		
			system("cls");
		
			music_selection();		// music selection menu appears
		
			SetConsoleTextAttribute(text_colour, WHITE);
			printf("\n\n Timer set for %d hours %d minutes.\n", hour, min);
			SetConsoleTextAttribute(text_colour, YELLOW);
			printf(" You can press E to exit the timer.\n\n");
		
			draw_mountains();		// displays ASCII mountain art
			hide_cursor(); 
		
			SetConsoleTextAttribute(text_colour, LIGHT_BLUE);
			for (i = sec; i >= 0; i--)		// loop for timer begins
			{ 
			    if (kbhit())		// will check for E input every second
			    {
        		    char key = _getch();
        		    if (key == 'E' || key == 'e') 
				    {
            		    break; 
        		    }
    		    }
    		
    		// converting seconds into hh:mm:ss
			final_hour = (i / 3600);
			final_min = ((i % 3600) / 60);
			final_sec = (i % 60);
			
			if (i <= 10) 
			{
        		SetConsoleTextAttribute(text_colour, LIGHT_RED);
    		} 
			else 
			{
        		SetConsoleTextAttribute(text_colour, LIGHT_BLUE);
    		}
				printf ("\rTime left: %02d:%02d:%02d", final_hour, final_min, final_sec);
				Sleep(1000);
			}
			
			// stopping the music
			mciSendString("close lofi", NULL, 0, NULL);
        	mciSendString("close rain", NULL, 0, NULL);
        
        	system("cls");
        	show_cursor();
        	
			SetConsoleTextAttribute(text_colour, MAGENTA);
			mciSendString("play enter from 0", NULL, 0, NULL);
			printf("\n Timer stopped at %02d:%02d:%02d\n\n", final_hour, final_min, final_sec);
			SetConsoleTextAttribute(text_colour, WHITE);
			printf(" Would you like to set another timer? [Y/N]: ");
			scanf(" %c", &again);
			mciSendString("play enter from 0", NULL, 0, NULL);
		
		} 
		while(again == 'Y' || again == 'y');		// program starts from beginning if Y key is entered
	
	printf("\n Thank you for using Focus Timer!");
	Sleep(1500);
	
return 0;
}
