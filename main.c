#include "console.h"
#include "sparrow.h"

int main() {
	ShowWelcome();
	ShowSparrow();
	clearScreen();
	ShowWelcome();
	int menu = ShowMenu();
	clearScreen();
	switch (menu) {
    case 0:
    case 1:
        Practice_13(menu);
        break;
	}
	/*string s[13];
	for (int i = 0; i < 13; ++i) cin >> s[i];
	int list[13], list_count = test(s, list);
	cout << 1;*/
	return 0;
}
