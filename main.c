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
        case 1:
            Practice_13(menu);
            break;
	    }
	    if (menu == 5) break;
	}
	clearScreen();
	ShowBanner();
	ShowEnding();
	return 0;
}
