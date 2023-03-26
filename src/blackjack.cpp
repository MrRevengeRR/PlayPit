#include "blackjack.h"
#include <cstdlib>
#include <time.h>

void initBlackjack(int &card1, int &card2, int &dCard1, int &dCard2) {
    // Init random seed
    srand(time(NULL));

    card1 = rand() % 51 + 1;
    card2 = card1 = rand() % 51 + 1;
    while (card2 == card1)
        card2 = rand() % 51 + 1;
    dCard1  = rand() % 51 + 1;
    while (dCard1 == card1 || dCard1 == card2)
        dCard1  = rand() % 51 + 1;
    dCard2  = rand() % 51 + 1;
    while (dCard2 == card1 || dCard2 == card2 || dCard2 == dCard1)
        dCard2  = rand() % 51 + 1;
}