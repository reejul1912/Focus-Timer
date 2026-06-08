/* 
(c) Focus Timer by Reejul Kant

This is a beginner C project.. I have added a few comments explaining my code
*/

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

static void window_size()
{
    SetConsoleTitle("Focus Timer By Reejul");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 55, 14};  // setting the window size
    COORD bufferSize = {50, 17};
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
    HWND console = GetConsoleWindow();
    long style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_THICKFRAME;
    SetWindowLong(console, GWL_STYLE, style);
}

static void load_font_size(int size)		// resize console font
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

static void hide_cursor()		// to disable the blinking cursor
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;   
    SetConsoleCursorInfo(consoleHandle, &info);
}

static void show_cursor()		// to enable the blinking cursor, only when taking inputs
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = TRUE;    
    SetConsoleCursorInfo(consoleHandle, &info);
}

static void audio()			// loads or opens the audio files located within main.c folder
{	
	mciSendString("open \"enter.mp3\" type mpegvideo alias enter", NULL, 0, NULL);
	mciSendString("open \"lofi.mp3\" type mpegvideo alias lofi", NULL, 0, NULL);
	mciSendString("open \"rain.mp3\" type mpegvideo alias rain", NULL, 0, NULL);
}

static void main_menu()
{    
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, LIGHT_CYAN);
    printf("\n\n");
    printf("\t      ~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");
    printf("\t      ~-~-~-~ FOCUS TIMER ~-~-~-~\n");
    printf("\t      ~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");
    SetConsoleTextAttribute(text_colour, LIGHT_BLUE);
    printf("\t     [For Studying and Relaxation]\n\n");
    printf("\t\tPress any key to begin...");
    SetConsoleTextAttribute(text_colour, WHITE);
    printf("\n\n\n\n\n\t    Version 1.1 (Made by Reejul Kant)");
    getch();
    system("cls");		// for clearing console screen.
}

static void draw_mountains() 		//ASCII art for mountains when timer is running
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

static void music_selection()		// menu for selecting the audio or music
{	
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(text_colour, MAGENTA);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" Select focus audio preference\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	
	SetConsoleTextAttribute(text_colour, LIGHT_CYAN);
	printf(" [1] Peaceful music\n [2] Rain sounds\n [3] Music + Rain\n [4] No music \n ");
	int music_choice = _getch();
	
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
		mciSendString("play lofi repeat", NULL, 0, NULL);
		mciSendString("play rain repeat", NULL, 0, NULL);
	}
}

int main(void) 
{
		window_size();
		load_font_size(24);			// font size set to 24
	
		HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);		// handle console text output
		int bar, hour, min, sec, i, j, k, final_hour, final_min, final_sec;		// c89 mode doesnt let me declare variables in a loop
		char again;		
		
		do		// when user wants to run the app again after time is up
		{
			system("cls");
			main_menu();
			audio(); 
		
			for (bar = 0; bar <= 30; bar++) 		// loading bar animation (pretty useless but looks cool)
			{
				printf ("=");
				Sleep(20);		
			}
		
			while(true)		// setting infinite loop for invalid inputs here
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
		    		system("cls");
					SetConsoleTextAttribute(text_colour, LIGHT_RED);
					printf("Please enter valid time (eg. 2:12, 0:30 etc). \n");
					while (getchar() != '\n');
				}
			}
		
			sec = ((hour * 3600) + (min * 60));		// converting hh:mm to seconds
		
			system("cls");
		
			music_selection();		// music selection menu appears
		
			SetConsoleTextAttribute(text_colour, WHITE);
			printf("\n\n Timer set for %d hours %d minutes.\n", hour, min);
			SetConsoleTextAttribute(text_colour, LIGHT_BLUE);
			printf(" Press E to exit or click anywhere to pause the timer.");
			
			printf("\n\n");
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
			
			if (i <= 10) {
        		SetConsoleTextAttribute(text_colour, LIGHT_RED);
    		} 
			else {
        		SetConsoleTextAttribute(text_colour, LIGHT_CYAN);
    		}
				printf ("\r Time left: %02d:%02d:%02d", final_hour, final_min, final_sec);
				Sleep(1000);
			}
			
			// stopping the music
			mciSendString("close lofi", NULL, 0, NULL);
        	mciSendString("close rain", NULL, 0, NULL);
        
        	system("cls");
        	show_cursor();
        	
			SetConsoleTextAttribute(text_colour, CYAN);
			mciSendString("play enter from 0", NULL, 0, NULL);
			printf("\n Timer stopped at %02d:%02d:%02d\n\n", final_hour, final_min, final_sec);
			SetConsoleTextAttribute(text_colour, WHITE);
			printf(" Would you like to set another timer? [Y/N]: ");
			scanf(" %c", &again);
			
		} while(again == 'Y' || again == 'y');		// program starts from beginning if Y key is entered
	
	printf("\n Thank you for using Focus Timer!");
	Sleep(1500);
	
return 0;
}
