#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <stdbool.h>

void window_size (int width,int height) {
	SetConsoleTitle("Focus Timer By Reejul");
    HWND console=GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); 
    MoveWindow(console, r.left, r.top, width, height, TRUE);
    long style=GetWindowLong(console, GWL_STYLE);
    style&=~WS_MAXIMIZEBOX; 
    style&=~WS_THICKFRAME;  
    SetWindowLong(console,GWL_STYLE,style);
}

void load_font_size(int size) {
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

void main_menu() {
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, 11);
    printf("\n");
    printf("  ______                         _______ _                      \n");
    printf(" |  ____|                       |__   __(_)                     \n");
    printf(" | |__ ___   ___ _   _ ___         | |   _ _ __ ___   ___ _ __ \n");
    printf(" |  __/ _ \\ / __| | | / __|        | |  | | '_ ` _ \\ / _ \\ '__|\n");
    printf(" | | | (_) | (__| |_| \\__ \\        | |  | | | | | | |  __/ |   \n");
    printf(" |_|  \\___/ \\___|\\__,_|___/        |_|  |_|_| |_| |_|\\___|_|   \n");
    printf("\n");
    SetConsoleTextAttribute(text_colour, 2);
    printf("  [For Studying and Relaxation]\n\n");
    printf("   Press any key to begin...");
    SetConsoleTextAttribute(text_colour, 7);
    printf("\n\n\n\n\nVersion 1.0 (Made by Reejul Kant)");
    getch();
    system("cls");
}

void music() {
	mciSendString("open \"lofi.mp3\" type mpegvideo alias lofi", NULL, 0, NULL);
	mciSendString("open \"rain.mp3\" type mpegvideo alias rain", NULL, 0, NULL);
}

void draw_mountains() {
	HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(text_colour, 2);
    printf("           /\\ \n");
    printf("          /  \\  /\\ \n");
    printf("         /    \\/  \\      /\\ \n");
    printf("    /\\  /      \\   \\    /  \\ \n");
    printf("   /  \\/        \\   \\  /    \\ \n");
    printf("  /    \\         \\   \\/      \\ \n");
    printf(" /      \\         \\  /        \\ \n");
    printf("------------------------------------\n");
}

int main(void) {
	
		window_size(550, 325);
		load_font_size(24);
	
		HANDLE text_colour = GetStdHandle(STD_OUTPUT_HANDLE);
		int bar, hour, min, sec, i, j, k, final_hour, final_min, final_sec, music_choice;
		char again;
		
		do{
		system("cls");
		main_menu();
		music();
		
		for (bar = 0; bar <= 30; bar++) {
			printf ("=");
			Sleep(20);
		}
		
		while(true){
		SetConsoleTextAttribute(text_colour, 7);
		printf("\nEnter the time in format [Hours:Minutes]: ");
		if (scanf("%d:%d", &hour, &min) == 2 && hour >= 0 && min >= 0 && min < 60) {
			break;
		}
		else {
			SetConsoleTextAttribute(text_colour, 12);
			printf("\aInvalid time. Enter it like 2:12, 0:30 etc. \n");
			while (getchar() != '\n');
		}
		}
		
		sec = ((hour * 3600) + (min * 60));
		
		system("cls");
		
		SetConsoleTextAttribute(text_colour, 11);
		printf("===== Select focus music preference =====\n\n");
		printf("[1] Peaceful music\n[2] Rain sounds\n[3] Music + Rain\n[4] No music\n");
		music_choice = _getch();
		
		system("cls");
		
		if (music_choice == '1') {
			printf("Playing peaceful music.");
			mciSendString("play lofi repeat", NULL, 0, NULL);
		}
		else if (music_choice == '2') {
			printf("Playing rain sounds.");
			mciSendString("play rain repeat", NULL, 0, NULL);
		}
		else if (music_choice == '3') {
			printf("Playing peaceful music + rain sound");
			mciSendString("play lofi from 0", NULL, 0, NULL);
			mciSendString("play rain repeat", NULL, 0, NULL);
		}
		else 
		{
		}
		
		SetConsoleTextAttribute(text_colour, 7);
		printf("\n\nTimer set for %d hours %d minutes.\n", hour, min);
		SetConsoleTextAttribute(text_colour, 14);
		printf("You can press E to exit the timer.\n\n");
		
		draw_mountains();
		
		SetConsoleTextAttribute(text_colour, 9);
		for (i = sec; i >= 0; i--) {
					
			if (kbhit()) {
        	char key = _getch();
        	if (key == 'E' || key == 'e') {
            break; 
        }
    	}
			final_hour = (i / 3600);
			final_min = ((i % 3600) / 60);
			final_sec = (i % 60);
			
			printf ("\rTime left: %02d:%02d:%02d", final_hour, final_min, final_sec);
			Sleep(1000);
		}
		
		mciSendString("close lofi", NULL, 0, NULL);
        mciSendString("close classical", NULL, 0, NULL);
        mciSendString("close rain", NULL, 0, NULL);
        
        system("cls");
		SetConsoleTextAttribute(text_colour, 13);
		printf("\n\aTimer stopped at %02d:%02d:%02d\n\n", final_hour, final_min, final_sec);
		SetConsoleTextAttribute(text_colour, 7);
		printf("Would you like to set another timer? [Y/N]: ");
		scanf(" %c", &again);
	} while(again == 'Y' || again == 'y');
	
	Sleep(1000);
	printf("Thank you for using Focus Timer!");
	Sleep(1500);
	
return 0;
}
	
