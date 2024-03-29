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
    Font *large_font = read_font("font.txt");
    initializeKeyInput();
    // loc: 5~45
    int loc = 45;
    while (1) {
        clearScreen();
        if (loc == 5) loc = 45;
        show_image(sparrow, loc--, 13);
        // putString(76, 53, "[Press space to continue]", 14, 2);
        if (loc % 6 > 3) putStringLarge(large_font, 10, 53, "Press Space", 10);
        if (waitForKeyDown(0.1)) {
            if (getKeyEventASCII() == VK_SPACE) break;
        }
        drawCmdWindow();
        ShowBanner();
        Sleep(100);
    }
    destroy_font(large_font);
    destroy_image(sparrow);
}

int ShowMenu() {
    Font *large_font = read_font("font.txt");
    initializeKeyInput();
    int count = 5, menu = 0, i;
    char *text[11] = { "a. 13 Practice Mode", "b. 16 Practice Mode", "c. Scoreboard", "d. Help", "e: Exit" };
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
            if (i == menu) putStringLarge(large_font, 8, 13 + i * 8, text[i], 14);
            else  putStringLarge(large_font, 8, 13 + i * 8, text[i], 7);
        }
        drawCmdWindow();
    }
    destroy_font(large_font);
}

int cmp (const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void Practice(int type) {
    // Show title
    char str_type[2];
    sprintf(str_type, "%d", type);
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 5, 2, str_type, 14);
    putStringLarge(large_font, 5, 2, "   Practice Mode", 14);
    // Show collection
    putString(5, 9, "牌面:", 14, 2);
    int i, j, hand[34] = {}, list[16], idx;
    srand(time(NULL));
    for (i = 0; i < type; 1) {
        int rnd = rand(), num = 3;
        if (rnd % 3 == 0) idx = rnd % 34;
        else if (rnd % 3 == 1) idx = (idx + 35) % 34;
        else if (rnd % 3 == 2) idx = (idx + 33) % 34;
        if (hand[idx] + num > 4) continue;
        for (j = 0; j < num; ++j) list[i++] = idx;
        hand[idx] += num;
    }
    qsort(list, type, sizeof(int), cmp);
    ShowMJ(12, list, type);
    // Computer listen
    int listen[34] = {};
    int listen_count = test(list, listen, type);
    // Set timer
    clock_t timer1, timer2;
    timer1 = clock();
    // User listen
    int userListen[34] = {};
    ShowUserInput(userListen);
    // Show Computer listen
    char buff[2];
    putString(5, 21, "電腦聽   張牌:", 14, 2);
    sprintf(buff, "%d", listen_count);
    putString(12, 21, buff, 14, 2);
    drawCmdWindow();
    ShowMJ(24, listen, listen_count);
    // Show timer
    timer2 = clock();
    int time = (timer2 - timer1)/(CLOCKS_PER_SEC);
    sprintf(buff, "%d", time);
    putStringLarge(large_font, 75, 30, buff, 11);
    putStringLarge(large_font, 78, 30, " sec", 11);
    // Show result and record
    if (ShowResult(listen, listen_count, userListen) == 34) {
        if (time > 1000) time = 999;
        int score[6];
        ReadScore(score);
        if (score[((type == 16) + 1) * 3 - 1] > time)
            score[((type == 16) + 1) * 3 - 1] = time;
        SaveScore(score);
    }
    destroy_font(large_font);
    while (1)
        if (waitForKeyDown(0.1))
            if (getKeyEventASCII() == VK_SPACE) return ;

}

const char *mj[34] = {
	" 1條", " 2條", " 3條", " 4條", " 5條", " 6條", " 7條", " 8條", " 9條",
	" 1索", " 2索", " 3索", " 4索", " 5索", " 6索", " 7索", " 8索", " 9索",
	"一萬", "二萬", "三萬", "四萬", "五萬", "六萬", "七萬", "八萬", "九萬",
	"東風", "南風", "西風", "北風",
	" 中 ", " 發 ", "　　"
};

const char* filename[34] = {
	"1T", "2T", "3T", "4T", "5T", "6T", "7T", "8T", "9T",
	"1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S",
	"1W", "2W", "3W", "4W", "5W", "6W", "7W", "8W", "9W",
	"DONG", "NAN", "XI", "BEI",
	"ZHONG", "FA", "BAI"
};

void ShowMJ(const int y, const int* list, int count) {
    if (count == 0) {
        putString(5, y, "N", 14, 2);
    } else {
        int i;
        for (i = 0; i < count; ++i) {
            putString(5 + i * 5, y - 1, "　　", 14, 2);
            putString(5 + i * 5, y, mj[list[i]], 14, 2);
            putString(5 + i * 5, y + 1, "　　", 14, 2);
        }
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
        putString(5, 15, "請選擇可能聽牌:", 14, 2);
        for (i = 0; i < 34; ++i) {
            if (cur == i) {
                putString(5 + i * 5, 17, "　　", 10, 3);
                putString(5 + i * 5, 18, mj[i], 10, 3);
                putString(5 + i * 5, 19, "　　", 10, 3);
            } else if (listen[i]) {
                putString(5 + i * 5, 17, "　　", 15, 3);
                putString(5 + i * 5, 18, mj[i], 15, 3);
                putString(5 + i * 5, 19, "　　", 15, 3);
            } else {
                putString(5 + i * 5, 17, "　　", 14, 2);
                putString(5 + i * 5, 18, mj[i], 14, 2);
                putString(5 + i * 5, 19, "　　", 14, 2);
            }
        }
        if (cur == -1) putString(5, 21, "確定", 15, 3);
        else putString(5, 21, "確定", 14, 2);
        drawCmdWindow();
    }
}

int ShowResult(const int *listen, const int count, const int *userListen) {
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
    return res;
}

void ShowEnding() {
    Image *img_mj[34];
    int i;
    for (i = 0; i < 34; ++i) {
        char pixel[51] = "resource/mj/", color[51] = "resource/mj/";
        strcat(pixel, filename[i]);
        strcat(pixel, ".pixel");
        strcat(color, filename[i]);
        strcat(color, ".color");
        img_mj[i] = read_image(pixel, color);
    }
    srand(time(NULL));
    initializeKeyInput();
    while (1) {
        clearScreen();
        show_image(img_mj[rand() % 34], 5, 13);
        show_image(img_mj[rand() % 34], 30, 13);
        show_image(img_mj[rand() % 34], 55, 13);
        show_image(img_mj[rand() % 34], 80, 13);
        putString(80, 43, "[Press space to exit]", 14, 2);
        if (waitForKeyDown(0.7)) {
            if (getKeyEventASCII() == VK_SPACE) break;
        }
        drawCmdWindow();
        ShowBanner();
        Sleep(700);
    }
    for (i = 0; i < 34; ++i) {
        destroy_image(img_mj[i]);
    }
 }

 void ShowHelp() {
     clearScreen();
     ShowBanner();
     putString(5, 13, "〈數學麻雀〉程式操作說明", 14, 4);
     putString(5, 15, "上(W), 下(S), 左(A), 右(D), 選擇(SPACE)", 14, 2);
     putString(5, 17, "〈數學麻雀〉模式說明", 14, 4);
     putString(5, 19, "模式A: 練習13ㄠ(13張)聽牌，選出正確聽牌組，若無，則直接按確定", 14, 2);
     putString(5, 21, "模式B: 練習麻將(16張)聽牌，選出正確聽牌組，若無，則直接按確定", 14, 2);
     putString(5, 23, "模式C: 記分板", 14, 2);
     putString(5, 25, "模式D: 說明", 14, 2);
     putString(5, 27, "模式E: 離場麻將動畫", 14, 2);
     putString(5, 29, "〈數學麻雀〉程式創作動機", 14, 4);
     putString(5, 31, "　　這個程式的作者，鄭余玄 (chengscott)，因為打麻將時常放槍，於是數學系雀聖品帝，就說「可以不要再放槍了嗎，趕快去寫一隻程式來幫你算牌，這樣就不會放槍了！」", 14, 2);
     putString(5, 33, "於是這就成為了我的Final Project，名為「mathsparrow」，程式碼在github上開源，使用MIT授權。", 14, 2);
     putString(75, 39, "[Press space to continue]", 14, 2);
     drawCmdWindow();
     initializeKeyInput();
     while (waitForKeyDown(100)) if (getKeyEventASCII() == VK_SPACE) return;
 }

void ReadScore(int *score) {
    FILE *file = fopen("score.txt", "r");
    int i, n;
    for (i = 0; i < 6; ++i) {
        fscanf(file, "%d", &n);
        if (n > 0 && n < 1000) score[i] = n;
        else score[i] = 999;
    }
    fclose(file);
}

void SaveScore(int *score) {
    qsort(score, 3, sizeof(int), cmp);
    qsort(score + 3, 3, sizeof(int), cmp);
    FILE *file = fopen("score.txt", "w+");
    int i;
    for (i = 0; i < 6; ++i)
        fprintf(file, "%d ", score[i]);
    fclose(file);
}

void ShowScoreboard() {
    clearScreen();
    int list[6], i;
    char score[6][4];
    ReadScore(&list);
    for (i = 0; i < 6; ++i)
        sprintf(score[i], "%d", list[i]);
    Font *large_font = read_font("font.txt");
    putStringLarge(large_font, 5, 2, "Scoreboard", 5);
    putStringLarge(large_font, 5, 9, "13 Practice Mode", 14);
    putStringLarge(large_font, 5, 15, "    sec", 11);
    putStringLarge(large_font, 5, 15, score[0], 11);
    putStringLarge(large_font, 5, 21, "    sec", 11);
    putStringLarge(large_font, 5, 21, score[1], 11);
    putStringLarge(large_font, 5, 27, "    sec", 11);
    putStringLarge(large_font, 5, 27, score[2], 11);
    putStringLarge(large_font, 5, 35, "16 Practice Mode", 14);
    putStringLarge(large_font, 5, 42, "    sec", 11);
    putStringLarge(large_font, 5, 42, score[3], 11);
    putStringLarge(large_font, 5, 48, "    sec", 11);
    putStringLarge(large_font, 5, 48, score[4], 11);
    putStringLarge(large_font, 5, 54, "    sec", 11);
    putStringLarge(large_font, 5, 54, score[5], 11);
    destroy_font(large_font);
    putString(107, 57, "[Press space to continue]", 14, 2);
    drawCmdWindow();
    initializeKeyInput();
    while (waitForKeyDown(100)) if (getKeyEventASCII() == VK_SPACE) return;
}
