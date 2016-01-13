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
            ShowScoreboard();
            break;
        case 3:
            ShowHelp();
            break;
	    }
	    if (menu == 4) break;
	}
	clearScreen();
	ShowBanner();
	ShowEnding();
	return 0;
}
