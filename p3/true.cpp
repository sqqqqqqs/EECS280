#include "deck.h"
#include "player.h"
#include "rand.h"
#include "hand.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void shuffle_7(Deck &deck, Player *player){
    const int cuts_num = 7;//shuffle 7 times
    cout<<"Shuffling the deck\n";
    for(int i=0;i<cuts_num;i++){
        int cut = get_cut();
        deck.shuffle(cut);
        cout<<"cut at "<<cut<<endl;
    }
    player->shuffled();
}
//MODIFIES: the deck and player;
//EFFECT: Shuffle the deck 7 tiems at any number between 13 and 39. Tell the counting
//player the deck is shuffled.

void deal_four(Deck &deck, Player *aplayer, Hand &player, Hand &dealer, Card &exposed, Card &hole){
    Card deal;
    //deal four cards at the beginning of each hand
    deal = deck.deal();
    player.addCard(deal);
    aplayer->expose(deal);
    cout<<"Player dealt "<<SpotNames[deal.spot]<<" of "<<SuitNames[deal.suit]<<endl;

    exposed = deck.deal();
    dealer.addCard(exposed);
    aplayer->expose(exposed);
    cout<<"Dealer dealt "<<SpotNames[exposed.spot]<<" of "<<SuitNames[exposed.suit]<<endl;

    deal = deck.deal();
    player.addCard(deal);
    aplayer->expose(deal);
    cout<<"Player dealt "<<SpotNames[deal.spot]<<" of "<<SuitNames[deal.suit]<<endl;

    hole = deck.deal();
    dealer.addCard(hole);
    //the second card of dealer is not exposed to player
}
//MODIFIES: deck, player, player's hand, dealer's hand.
//EFFECT: Deal four cards, two for player and two for dealer. Count every exposed card
//if the player is counting. Record the dealer's hole card and exposed card.

bool player_turn(Deck &deck, Player *aplayer, Hand &player, const Card exposed){
    bool busts;
    while(aplayer->draw(exposed, player)){
        Card deal = deck.deal();
        player.addCard(deal);
        aplayer->expose(deal);
        cout<<"Player dealt "<<SpotNames[deal.spot]<<" of "<<SuitNames[deal.suit]<<endl;
    }
    cout<<"Player's total is "<<player.handValue().count<<endl;
    if(player.handValue().count>21) {
        busts = true;
        cout<<"Player busts\n";
    }
    else busts = false;
    return busts;
}
//MODIFIES: deck, player, player's hand;
//EFFECT: The player decide whether to deal again. The function returns if the player
//is busts. The counting player will count every exposed card. The function will
//print the deal information.

bool dealer_turn(Deck &deck, Player *aplayer, Hand &dealer, const Card hole){
    bool busts;
    cout<<"Dealer's hole card is "<<SpotNames[hole.spot]<<" of "<<SuitNames[hole.suit]<<endl;
    aplayer->expose(hole);
    while(dealer.handValue().count<17){
        Card deal = deck.deal();
        dealer.addCard(deal);
        aplayer->expose(deal);
        cout<<"Dealer dealt "<<SpotNames[deal.spot]<<" of "<<SuitNames[deal.suit]<<endl;
    }
    cout<<"Dealer's total is "<<dealer.handValue().count<<endl;
    if(dealer.handValue().count>21){
        busts = true;
        cout<<"Dealer busts\n";
    }
    else busts = false;
    return busts;
}
//MODIFIES: deck, dealer, dealer's hand;
//EFFECT: The dealer decide whether to deal again. The function returns if the dealer
//is busts. The function will print the deal information, also the hole card of dealer
//if neccessary.

int main(int argc, char *argv[]){
    if(argc!=4) assert(0);
    else{   
        const unsigned int minimum_bet = 5; //default minimum bet 
        
        //define variables
        unsigned int bankroll = atoi(argv[1]);
        int hands = atoi(argv[2]);
        string player(argv[3]);
        Player * aplayer;
        if(player=="simple") aplayer = get_Simple();
        else if(player=="counting") aplayer = get_Counting();
        else assert(0);
        Hand handOfdealer;
        Hand handOfplayer;        
        Deck deck;

        //start with shuffling
        shuffle_7(deck, aplayer);
        //start hands
        int thishand = 0;
        while(true){
            if(bankroll<minimum_bet||thishand>=hands) break; //if original bankroll is less than minimum bet, break
            thishand++;
            cout<<"Hand "<<thishand<<" bankroll "<<bankroll<<endl;
            if(deck.cardsLeft()<20) shuffle_7(deck, aplayer); //if cards less than 20, reshuffle
            
            int wager = aplayer->bet(bankroll, minimum_bet);
            cout<<"Player bets "<<wager<<endl;
            
            //draw four cards and get the exposed card information for player
            Card exposed, hole;
            deal_four(deck, aplayer, handOfplayer,handOfdealer, exposed, hole);

            //player's turn
            if (handOfplayer.handValue().count == 21){
                cout<<"Player dealt natural 21\n";
                bankroll+= wager*3/2;
            }
            else if(player_turn(deck, aplayer, handOfplayer, exposed)) bankroll-=wager;

            //dealer's turn
            else if(dealer_turn(deck, aplayer, handOfdealer, hole)) bankroll+=wager;

            //compare
            else if(handOfdealer.handValue().count>handOfplayer.handValue().count){
                cout<<"Dealer wins\n";
                bankroll-=wager;
            }
            else if(handOfdealer.handValue().count<handOfplayer.handValue().count){
                cout<<"Player wins\n";
                bankroll+=wager;
            }
            else cout<<"Push\n";

            //last of the turn   
            handOfdealer.discardAll();
            handOfplayer.discardAll();       
        }
        cout<<"Player has "<<bankroll<<" after "<<thishand<<" hands\n";
    }
    return 0;
}