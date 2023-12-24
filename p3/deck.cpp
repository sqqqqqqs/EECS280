#include "deck.h"

Deck::Deck() {
    for (int i = 0; i < DeckSize; i++) {
        deck[i].suit = Suit(i / 13);
        deck[i].spot = Spot(i % 13);
    }
    next = 0;
}

void Deck::reset() {//it's totally the same with the Deck() function
    for (int i = 0; i < DeckSize; i++) {
        deck[i].suit = Suit(i / 13);
        deck[i].spot = Spot(i % 13);
    }
    next = 0;
//    for(int i=0;i<3;i++){//from Spades to Diamonds
//        for(int j=0;j<12;j++){//from 2 to Ace
//            deck[i*13+j].suit=(Suit) i;//assign suit
//            deck[i*13+j].spot=(Spot) j;//assign spot
//        }
//    }
//    next=0; //the next card should be the first card spades 2.
}

void Deck::shuffle(int n) {
    Card new_deck[DeckSize];
    int i;
    for (i = 0; i < n && i + n < 52; i++) { //first set the common part of the right sides and the left sides
        new_deck[2 * i] = deck[n + i];
        new_deck[2 * i + 1] = deck[i];
    }
    if (i == n) { //if right part is larger
        for (; i + n < 52; i++) {
            new_deck[i + n] = deck[n + i];
        }
    } else if (i == 52 - n) {// if left part is larger
        for (; i < n; i++) {
            new_deck[52 - n + i] = deck[i];
        }
    }
    for (i = 0; i < 52; i++) {// replace the original deck with the new deck
        deck[i] = new_deck[i];
    }
    next = 0;// set the next to be the first card.
}

Card Deck::deal() {
    if(next==52){
        DeckEmpty empty;//create a Deck
        throw empty;
    }
    next += 1;
    return deck[next - 1];
}

int Deck::cardsLeft() {
    return 52-next;
}