#include "deck.h"
#include <iostream>
Deck::Deck(){
    // Initialize the DECK as a specified order.
    for(int i=0;i<=DIAMONDS;i++){
        for(int j=0;j<=ACE;j++){
            deck[i*(ACE+1)+j].suit = (Suit) i;
            deck[i*(ACE+1)+j].spot = (Spot) j;
        }
    }
    //Initialize the first card.
    next = 0;
}

void Deck::reset(){
    // Initialize the DECK as a specified order.
    for(int i=0;i<=DIAMONDS;i++){
        for(int j=0;j<=ACE;j++){
            deck[i*(ACE+1)+j].suit = (Suit) i;
            deck[i*(ACE+1)+j].spot = (Spot) j;
        }
    }
    //Initialize the first card.
    next = 0;
}

void Deck::shuffle(int n){
    if(n>=0&&n<=52){
        Card copy[DeckSize];
        int i=0;
        for(i=0;i<n&&i+n<52; i++){
            copy[2*i] = deck[n+i];//The right segments.
            copy[2*i+1] = deck[i];//The left segments; 
        }
        if(i==n){
            for(;i+n<52;i++) copy[i+n] = deck[n+i];//If right remains;
        }
        else if(i+n==52){
            for(;i<n;i++) copy[52-n+i] = deck[i];//If left remains;
        }
        //Copy copy to this;
        for(i=0;i<DeckSize;i++) deck[i] = copy[i];
        next = 0;
    }
}

Card Deck::deal(){
    if (next == DeckSize){
        DeckEmpty emptydeck;
        throw emptydeck;
    }
    return deck[next++];
}

int Deck::cardsLeft(){
    return DeckSize-next;
}