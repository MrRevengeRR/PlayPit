#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "raylib.h"

/*typedef enum CardInd {
    none = 0, clubs_2, diamonds_2, hearts_2, spades_2, 
    clubs_3, diamonds_3, hearts_3, spades_3,
    clubs_4, diamonds_4, hearts_4, spades_4,
    clubs_5, diamonds_5, hearts_5, spades_5,
    clubs_6, diamonds_6, hearts_6, spades_6,
    clubs_7, diamonds_7, hearts_7, spades_7,
    clubs_8, diamonds_8, hearts_8, spades_8,
    clubs_9, diamonds_9, hearts_9, spades_9,
    clubs_10, diamonds_10, hearts_10, spades_10,
    clubs_jack, diamonds_jack, hearts_jack, spades_jack,
    clubs_queen, diamonds_queen, hearts_queen, spades_queen,
    clubs_king, diamonds_king, hearts_king, spades_king,
    clubs_ace, diamonds_ace, hearts_ace, spades_ace
} CardInd;*/

// Init
void initBlackjack(int pCards[10]);
// Draw
void hitBlackjack(int pCards[10]);
// Dealer Hit
void dealerHitBlackjack(int pCards[10]);

#endif



