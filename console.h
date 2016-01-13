#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <mmsystem.h>
#include "audio.h"
#include "console_draw3.h"
#include "kb_input2.h"
#include "font.h"
#include "image.h"
void ShowBanner();
void ShowSparrow();
int ShowMenu();
void Practice(int);
void ShowUserInput();
void ShowMJ(const int, const int*, int);
int ShowResult(const int*, const int, const int *);
void ShowEnding();
void ReadScore(int *);
void SaveScore(int *);
void ShowScoreboard();
void ShowHelp();
