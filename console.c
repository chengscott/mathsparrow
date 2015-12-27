#include "console.h"

void ShowWelcome() {
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 5, 2, "Math Sparrow", 10);
    putString(74, 8, "Under The MIT License (MIT)", 10, 3);
    putString(49, 9, "Copyright (c) 2015 chengscott <60510scott@gmail.com>", 10, 3);
    putString(5, 11, "================================================================================================", 10, 3);
    drawCmdWindow();
}

void ShowSparrow() {
    Image *sparrow = read_image("resource/sparrow.pixel", "resource/sparrow.color");
    initializeKeyInput();
    // : 5~45
    int loc = 45;
    while (1) {
        //clearScreen();
        if (loc == 5) loc = 45;
        show_image(sparrow, loc--, 13);
        putString(76, 53, "[Press space to continue]", 14, 2);
        if (waitForKeyDown(0.1)) {
            if (getKeyEventASCII() == VK_SPACE) break;
        }
        Sleep(100);
        drawCmdWindow();
    }
    destroy_image(sparrow);
}

int ShowMenu() {
    initializeKeyInput();
    int count = 4, menu = 0, i;
    char *text[4] = { "a. 1 Player", "b. 2 Player", "c. Scoreboard", "d. Help" };
    while (1) {
        if (waitForKeyDown(0.1)) {
            char ch = getKeyEventASCII();
            if (ch == VK_SPACE) return menu;
            else if (ch == 's' || ch == VK_UP)
                ++menu, menu = (menu + 4) % 4;
            else if (ch == 'w' || ch == VK_DOWN)
                --menu, menu = (menu + 4) % 4;
            else menu == ch - 'a';
            if (menu < 0 || menu >= count) menu = 0;
        }
        for (i = 0; i < count; ++i) {
            if (i == menu) putString(5, 13 + i * 2, text[i], 14, 2);
            else putString(5, 13 + i * 2, text[i], 10, 3);
        }
        drawCmdWindow();
    }
}

void Practice_13() {
    int i, hand[34] = {}, list[13];
    srand(time(NULL));
    for (i = 0; i < 13; 1) {
        int idx = rand() % 34;
        if (hand[idx] == 4) continue;
        list[i] = idx, ++hand[idx], ++i;
    }
    ShowMJ(list, 13);
    // Image *dong = read_image("resource/mj/dong.pixel", "resource/mj/dong.color");
    // putString(10, 10, "東", 14, 2);
    // drawCmdWindow();
}

const char *mj[34] = {
	"1條", "2條", "3條", "4條", "5條", "6條", "7條", "8條", "9條",
	"1索", "2索", "3索", "4索", "5索", "6索", "7索", "8索", "9索",
	"1萬", "2萬", "3萬", "4萬", "5萬", "6萬", "7萬", "8萬", "9萬",
	"東風", "能封", "西風", "北風",
	"中", "發", "  "
};

void ShowMJ(const int* list, int count) {
    int i;
    for (i = 0; i < count; ++i)
        putString(10 + i * 5b, 10, mj[list[i]], 14, 2);
    drawCmdWindow();
}
/*
void ShowTable_13() {
	ShowBanner();
	cout << " =============================================================================" << endl;
	cout << " ||                                    W                                    ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " || N                                                                     S ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                                                         ||" << endl;
	cout << " ||                                    E                                    ||" << endl;
}

void ShowMJ(const int* list, int cards) {
	for (int i = 0; i < cards; ++i) cout << " -----";
	cout << endl;
	for (int i = 0; i < cards; ++i) cout << " | " << mahjong[list[i]][0] << " |";
	cout << endl;
	for (int i = 0; i < cards; ++i) cout << " | " << mahjong[list[i]][1] << " |";
	cout << endl;
	for (int i = 0; i < cards; ++i) cout << " -----";
	cout << endl;
}

*/
