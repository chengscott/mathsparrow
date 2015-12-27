#include "console.h"

void ShowBanner() {
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 5, 2, "Math Sparrow", 10);
    putString(74, 8, "Under The MIT License (MIT)", 10, 3);
    putString(49, 9, "Copyright (c) 2015 chengscott <60510scott@gmail.com>", 10, 3);
    putString(5, 11, "================================================================================================", 10, 3);
    drawCmdWindow();
    destroy_font(large_font);
}

void ShowSparrow() {
    Audio bird[1];
    openAudioFile("resource/bird.wav", bird);
    playAudio(bird);
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
    int count = 6, menu = 0, i;
    char *text[6] = { "a. 1 Player Practice", "b. 1 Player Hard", "c. 2 Player", "d. Scoreboard", "e. Help", "f: Exit" };
    while (1) {
        if (waitForKeyDown(0.1)) {
            char ch = getKeyEventASCII();
            if (ch == VK_SPACE) return menu;
            else if (ch == 's' || ch == VK_DOWN)
                ++menu, menu = (menu + count) % count;
            else if (ch == 'w' || ch == VK_UP)
                --menu, menu = (menu + count) % count;
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

int cmp (const void * a, const void * b) { return ( *(int*)a - *(int*)b ); }

void Practice_13(int unsorted) {
    putString(10, 5, "牌面:", 14, 2);
    int i, hand[34] = {}, list[13];
    srand(time(NULL));
    for (i = 0; i < 13; 1) {
        int idx = rand() % 34;
        if (hand[idx] == 4) continue;
        list[i] = idx, ++hand[idx], ++i;
    }
    if (!unsorted) qsort(list, 13, sizeof(int), cmp);
    ShowMJ(10, list, 13);
    // Computer listen
    int listen[34] = {};
    int listen_count = test(list, listen);
    // User listen
    int userListen[34] = {};
    ShowUserInput(userListen);
    // Show Computer listen
    char str_listen[2];
    putString(10, 19, "電腦聽   張牌:", 14, 2);
    sprintf(str_listen, "%d", listen_count);
    putString(17, 19, str_listen, 14, 2);
    drawCmdWindow();
    ShowMJ(21, listen, listen_count);
    ShowResult(listen, listen_count, userListen);
    while (1)
        if (waitForKeyDown(0.1))
            if (getKeyEventASCII() == VK_SPACE) return ;

}

const char *mj[34] = {
	"1條", "2條", "3條", "4條", "5條", "6條", "7條", "8條", "9條",
	"1索", "2索", "3索", "4索", "5索", "6索", "7索", "8索", "9索",
	"1萬", "2萬", "3萬", "4萬", "5萬", "6萬", "7萬", "8萬", "9萬",
	"東風", "南風", "西風", "北風",
	"中", "發", "  "
};

void ShowMJ(const int y, const int* list, int count) {
    if (count == 0) {
        putString(10, y, "N", 14, 2);
    } else {
        int i;
        for (i = 0; i < count; ++i)
            putString(10 + i * 5, y, mj[list[i]], 14, 2);
        // Image *dong = read_image("resource/mj/dong.pixel", "resource/mj/dong.color");
    }
    drawCmdWindow();
}

void ShowUserInput(int *listen) {
    int i, cur = -1;
    while (1) {
        if (waitForKeyDown(0.1)) {
            char ch = getKeyEventASCII();
            if (ch == VK_SPACE && cur == -1) return ;
            else if (ch == VK_SPACE) listen[cur] = !listen[cur] ;
            else if (ch == 's' || ch == VK_DOWN) cur = -1;
            else if (ch == 'w' || ch == VK_UP) cur = 0;
            else if (ch == 'a' || ch == VK_LEFT) --cur, cur = (cur + 34) % 34;
            else if (ch == 'd' || ch == VK_RIGHT) ++cur, cur = (cur + 34) % 34;
        }
        putString(10, 15, "請選擇可能聽牌:", 14, 2);
        for (i = 0; i < 34; ++i) {
            if (cur == i) putString(10 + i * 5, 17, mj[i], 10, 3);
            else if (listen[i]) putString(10 + i * 5, 17, mj[i], 15, 3);
            else putString(10 + i * 5, 17, mj[i], 14, 2);
        }
        if (cur == -1) putString(10, 19, "確定", 15, 3);
        else putString(10, 19, "確定", 14, 2);
        drawCmdWindow();
    }
}

void ShowResult(const int *listen, const int count, const int *userListen) {
    int i, comp[34] = {}, res = 0;
    char ch_res[5];
    for (i = 0; i < count; ++i) comp[listen[i]] = 1;
    for (i = 0; i < 34; ++i) if (comp[i] == userListen[i]) ++res;
    sprintf(ch_res, "%d", res);
    Font *large_font = read_font("font.txt");
    if (res == 34) putStringLarge(large_font, 10, 30, ch_res, 10);
    else putStringLarge(large_font, 10, 30, ch_res, 12);
    putStringLarge(large_font, 35, 30, "x 34", 8);
    drawCmdWindow();
    destroy_font(large_font);
}

void ShowEnding() {
    Image *dong = read_image("resource/mj/dong.pixel", "resource/mj/dong.color");
    Image *nan = read_image("resource/mj/nan.pixel", "resource/mj/nan.color");
    Image *xi = read_image("resource/mj/xi.pixel", "resource/mj/xi.color");
    Image *bei = read_image("resource/mj/bei.pixel", "resource/mj/bei.color");
    initializeKeyInput();
    int pos[4] = {5, 30, 55, 80}, loc = 0;
    while (1) {
        clearScreen();
        //ShowBanner();
        show_image(dong, pos[loc], 13);
        show_image(nan, pos[(loc + 1)%4], 13);
        show_image(xi, pos[(loc + 2)%4], 13);
        show_image(bei, pos[(loc + 3)%4], 13);
        loc = (loc + 5) % 4;
        putString(76, 43, "[Press space to continue]", 14, 2);
        if (waitForKeyDown(0.1)) {
            if (getKeyEventASCII() == VK_SPACE) break;
        }
        Sleep(700);
        drawCmdWindow();
        ShowBanner();
    }
    destroy_image(dong);
    destroy_image(nan);
    destroy_image(xi);
    destroy_image(bei);
 }
