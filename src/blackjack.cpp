#include "blackjack.h"
#include <cstdlib>
#include <time.h>

void initBlackjack(int pCards[10]) {
    // Init random seed
    srand(time(NULL));

    pCards[0] = rand() % 51 + 1;
    pCards[1] = rand() % 51 + 1;
    while (pCards[1] == pCards[0])
        pCards[1] = rand() % 51 + 1;
    pCards[5]  = rand() % 51 + 1;
    while (pCards[5] == pCards[0] || pCards[5] == pCards[1])
        pCards[5]  = rand() % 51 + 1;
    pCards[6]  = rand() % 51 + 1;
    while (pCards[6] == pCards[0] || pCards[6] == pCards[1] || pCards[6] == pCards[5])
        pCards[6]  = rand() % 51 + 1;
}

void hitBlackjack(int pCards[10]) {
    srand(time(NULL));
    if (pCards[2]) {
        if (pCards[3]) {
            pCards[4] = rand() % 51 + 1;
            for (int i = 0; i < 10; i++) {
                if (i != 4) {
                    if (pCards[i] == pCards[4]) {
                        pCards[4] = rand() % 51 + 1;
                        i = 0;
                    }
                }
            }
        }
        else {
            pCards[3] = rand() % 51 + 1;
            for (int i = 0; i < 10; i++) {
                if (i != 3) {
                    if (pCards[i] == pCards[3]) {
                        pCards[3] = rand() % 51 + 1;
                        i = 0;
                    }
                }
            }
        }
    }   
    else {
        pCards[2] = rand() % 51 + 1;
        for (int i = 0; i < 10; i++) {
            if (i != 2) {
                if (pCards[i] == pCards[2]) {
                    pCards[2] = rand() % 51 + 1;
                    i = 0;
                }
            }
        }
    }
}

void dealerHitBlackjack(int pCards[10]) {
    srand(time(NULL));
    if (pCards[7]) {
        if (pCards[8]) {
            pCards[9] = rand() % 51 + 1;
            for (int i = 0; i < 10; i++) {
                if (i != 9) {
                    if (pCards[i] == pCards[9]) {
                        pCards[9] = rand() % 51 + 1;
                        i = 0;
                    }
                }
            }
        }
        else {
            pCards[8] = rand() % 51 + 1;
            for (int i = 0; i < 10; i++) {
                if (i != 8) {
                    if (pCards[i] == pCards[8]) {
                        pCards[8] = rand() % 51 + 1;
                        i = 0;
                    }
                }
            }
        }
    }   
    else {
        pCards[7] = rand() % 51 + 1;
        for (int i = 0; i < 10; i++) {
            if (i != 7) {
                if (pCards[i] == pCards[7]) {
                    pCards[7] = rand() % 51 + 1;
                    i = 0;
                }
            }
        }
    }
}