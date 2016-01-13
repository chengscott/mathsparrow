#include "console.h"
#include "sparrow.h"

int main() {
	ShowBanner();
	ShowSparrow();
	while (1) {
        clearScreen();
	    ShowBanner();
	    int menu = ShowMenu();
	    clearScreen();
	    switch (menu) {
        case 0:
            Practice(13);
            break;
        case 1:
            Practice(16);
            break;
        case 2:
            break;
        case 4:
            ShowHelp();
            break;
	    }
	    if (menu == 5) break;
	}
	clearScreen();
	ShowBanner();
	ShowEnding();
	return 0;
}
