#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <stdbool.h>

void window_size (int width,int height) { 		//setting window size
	SetConsoleTitle("Focus Timer By Reejul");
    HWND console=GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); 
    MoveWindow(console, r.left, r.top, width, height, TRUE);
    long style=GetWindowLong(console, GWL_STYLE);
    style&=~WS_MAXIMIZEBOX;  	//disabling maximize button
    style&=~WS_THICKFRAME;  	//disabling window resizing
    SetWindowLong(console,GWL_STYLE,style);
}

void load_font_size(int size) {			//setting text size
    HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);   
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;   
    cfi.dwFontSize.Y = size;  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName,L"Consolas");
    SetCurrentConsoleFontEx(text, FALSE, &cfi);
}

void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;   //turning that blinking cursor on
    SetConsoleCursorInfo(consoleHandle, &info);
}

void show_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = TRUE;    //turning that blinking cursor back on
    SetConsoleCursorInfo(consoleHandle, &info);
}

void audio() {		//loading all the sounds
	mciSendString("open \"enter.mp3\" type mpegvideo alias enter", NULL, 0, NULL);
	mciSendString("open \"lofi.mp3\" type mpegvideo alias lofi", NULL, 0, NULL);
	mciSendString("open \"rain.mp3\" type mpegvideo alias rain", NULL, 0, NULL);
}

void main_menu() {    //making the main menu using ASCII
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, 11);
    printf("\n");
    printf("  ______                     _______ _                      \n");
    printf(" |  ____|                   |__   __(_)                     \n");
    printf(" | |__ ___   ___ _   _ ___     | |   _ _ __ ___   ___ _ __ \n");
    printf(" |  __/ _ \\ / __| | | / __|    | |  | | '_ ` _ \\ / _ \\ '__|\n");
    printf(" | | | (_) | (__| |_| \\__ \\    | |  | | | | | | |  __/ |   \n");
    printf(" |_|  \\___/ \\___|\\__,_|___/    |_|  |_|_| |_| |_|\\___|_|   \n");
    printf("\n");
    SetConsoleTextAttribute(text_colour, 2);
    printf("  [For Studying and Relaxation]\n\n");
    printf("  Press any key to begin...");
    SetConsoleTextAttribute(text_colour, 7);
    printf("\n\n\n\n\nVersion 1.0 (Made by Reejul Kant)");
    getch();
    system("cls");
}

void draw_mountains() {			//mountains ascii art
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, 2);
    printf("           /\\ \n");
    printf("          /  \\  /\\ \n");
    printf("         /    \\/  \\      /\\ \n");
    printf("    /\\  /      \\   \\    /  \\ \n");
    printf("   /  \\/        \\   \\  /    \\ \n");
    printf("  /    \\         \\   \\/      \\ \n");
    printf(" /      \\         \\  /        \\ \n");
    SetConsoleTextAttribute(text_colour, 3);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); //river art
}
	void music_selection() {		//music selection menu
		HANDLE text_colour = GetStdHandle (STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(text_colour, 13);
		
		printf("\n ===== Select focus audio preference =====\n\n");
		SetConsoleTextAttribute(text_colour, 11);
		printf(" [1] Peaceful music\n [2] Rain sounds\n [3] Music + Rain\n [4] No music\n");
		int music_choice = _getch();
		mciSendString("play enter from 0", NULL, 0, NULL);
		
			if (music_choice == '1') {
			printf(" %c Playing peaceful music.", 14);
			mciSendString("play lofi repeat", NULL, 0, NULL);
		}
		else if (music_choice == '2') {
			printf(" %c Playing rain sounds.", 14);
			mciSendString("play rain repeat", NULL, 0, NULL);
		}
		else if (music_choice == '3') {
			printf(" %c Playing peaceful music + rain sound %c", 14, 14);
			mciSendString("play lofi from 0", NULL, 0, NULL);
			mciSendString("play rain repeat", NULL, 0, NULL);
		}
		else 
		{
		}
		system("cls");
	}

int main(void) {
	
		window_size(550, 325); //width * height of window
		load_font_size(24);  //24 is the font size
	
		HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
		int bar, hour, min, sec, i, j, k, final_hour, final_min, final_sec; //couldnt declare variables inside loop due to C89
		char again;
		
		do{
			system("cls");
			main_menu(); //main menu appears
			audio(); 
			mciSendString("play enter from 0", NULL, 0, NULL);
		
			for (bar = 0; bar <= 30; bar++) {
				printf ("="); //loading bar animation
				Sleep(20);
			}
		
			while (true) { //infinite loop for invalid inputs
				
				SetConsoleTextAttribute(text_colour, 7);
				printf("\n Enter the time in format [HOURS:MINS]: ");
				if (scanf("%d:%d", &hour, &min) == 2 && hour >= 0 && min >= 0 && min < 60) {
					break;
			}
			
			else { //invalid input
			
		    	mciSendString("play enter from 0", NULL, 0, NULL);
				SetConsoleTextAttribute(text_colour, 12);
				printf("Invalid time. Enter it like 2:12, 0:30 etc. \n");
				while (getchar() != '\n');
			}
		}
		
			mciSendString("play enter from 0", NULL, 0, NULL);
			sec = ((hour * 3600) + (min * 60));
		
			system("cls"); //screen clears. I know this is not the best way to do it but it is what I know
		
			music_selection(); // music selection menu appears
		
			SetConsoleTextAttribute(text_colour, 7);
			printf("\n\n Timer set for %d hours %d minutes.\n", hour, min);
			SetConsoleTextAttribute(text_colour, 14);
			printf(" You can press E to exit the timer.\n\n");
		
			draw_mountains(); //dislays the ASCII art of mountains
			hide_cursor(); 
		
			SetConsoleTextAttribute(text_colour, 9);
			for (i = sec; i >= 0; i--) { 
					
			if (kbhit()) { // user presses E key to exit the timer
        		char key = _getch();
        		if (key == 'E' || key == 'e') {
            	break; 
        	}
    	}
    		//converting seconds into hh:mm:ss
			final_hour = (i / 3600);
			final_min = ((i % 3600) / 60);
			final_sec = (i % 60);
			
			if (i <= 10) {
        		SetConsoleTextAttribute(text_colour, 12);
    		} else {
        		SetConsoleTextAttribute(text_colour, 9);
    		}
				printf ("\rTime left: %02d:%02d:%02d", final_hour, final_min, final_sec);
				Sleep(1000);
		}
		
			mciSendString("close lofi", NULL, 0, NULL);
        	mciSendString("close rain", NULL, 0, NULL);
        
        	system("cls");
        	show_cursor();
        	
			SetConsoleTextAttribute(text_colour, 13);
			mciSendString("play enter from 0", NULL, 0, NULL);
			printf("\n Timer stopped at %02d:%02d:%02d\n\n", final_hour, final_min, final_sec);
			SetConsoleTextAttribute(text_colour, 7);
			printf(" Would you like to set another timer? [Y/N]: ");
			scanf(" %c", &again);
			mciSendString("play enter from 0", NULL, 0, NULL);
		
		} while(again == 'Y' || again == 'y'); // goto menu when user presses y
	
	printf("\n Thank you for using Focus Timer!");
	Sleep(1500);
	
return 0;
}
	
