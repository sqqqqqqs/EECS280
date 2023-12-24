#include"rand.h"
#include"deck.h"
#include"hand.h"
#include"player.h"
#include <iostream>
#include<string>
using namespace std;

void shuffle(Deck &deck){//shuffle the deck using random function for 7 times
//MODOFIES:deck
//EFFECTS: shuffle the cards for 7 times
    cout << "Shuffling the deck\n";
    for(int i=0;i<7;i++){
        int cut=get_cut();//use the random function to help cut
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
}

void deal_four_cards(Deck &deck,Player *player,Hand &player_hand,Hand &dealer_hand,Card &dealer_up,Card &dealer_down){//record the two cards of the dealer
//MODIFIES: deck,player, hand_of player, hand_of dealer
//EFFECTS:deal in total 4 cards, the first up to player, the second up to dealer, the third up to the player, the fourth down to the dealer

    //first card to player face-up
    Card draw;
    draw=deck.deal();  //to deal the four cards
    player_hand.addCard(draw);
    player->expose(draw);//expose face-up cards to player
    cout<<"Player dealt "<<SpotNames[draw.spot]<<" of "<<SuitNames[draw.suit]<<endl;

    //second card to dealer face-up
    dealer_up=deck.deal();
    dealer_hand.addCard(dealer_up);
    player->expose(dealer_up);
    cout<<"Dealer dealt "<<SpotNames[dealer_up.spot]<<" of "<<SuitNames[dealer_up.suit]<<endl;

    //third card to player face-up,exactly the same as the first card
    draw=deck.deal();
    player_hand.addCard(draw);
    player->expose(draw);
    cout<<"Player dealt "<<SpotNames[draw.spot]<<" of "<<SuitNames[draw.suit]<<endl;

    //fourth card to dealer face-down.
    dealer_down=deck.deal();
    dealer_hand.addCard(dealer_down);
    // the last card shouldn't be exposed to player and shouldn't output anything
}

bool Player_round(Deck *deck,Player *player,Hand &player_hand, Card dealer_up){
//MODIFIES: deck,player,player_hand
//EFFECTS:after the player's round,tell whether the player has busts
    while(player->draw(dealer_up,player_hand)){//when the player want to continue drawing
        Card draw;              //the card draw process is exactly the same as the first two of the player
        draw=deck->deal();
        player_hand.addCard(draw);
        player->expose(draw);
        cout<<"Player dealt "<<SpotNames[draw.spot]<<" of "<<SuitNames[draw.suit]<<endl;
    }
    cout<<"Player's total is "<<player_hand.handValue().count<<endl;
    bool busts;
    if(player_hand.handValue().count>21){
        busts=true;
        cout << "Player busts\n";
    }
    else{
        busts= false;
    }
    return busts;//return the state whether player has met busts
}

bool Dealer_round(Deck *deck,Player *player, Hand &dealer_hand,Card dealer_down){
//MODIFIES: deck,player,dealer_hand
//EFFECTS:after the dealer's round,tell whether the dealer has busts
    cout<<"Dealer's hole card is "<<SpotNames[dealer_down.spot]<<" of "<<SuitNames[dealer_down.suit]<<endl;
    player->expose(dealer_down);//expose the down card of dealer to the player

    while(dealer_hand.handValue().count<17){//if the total is smaller than17, draw card and expose to player
        Card draw=deck->deal();
        dealer_hand.addCard(draw);
        player->expose(draw);
        cout<<"Dealer dealt "<<SpotNames[draw.spot]<<" of "<<SuitNames[draw.suit]<<endl;
    }
    //when the amount is equal or greater than 17
    cout << "Dealer's total is " << dealer_hand.handValue().count << endl;
    bool busts;
    if(dealer_hand.handValue().count>21){
        busts=true;
        cout<<"Dealer busts\n";
    }
    else{
        busts= false;
    }
    return busts;//return the state whether the dealler has busts
}

int main(int argc, char *argv[]){// the main function
    if(argc!=4){
        return 1;
    }
    else {
        const unsigned int Min = 5;
        unsigned int bankroll = stoi(argv[1]);
        int hands = stoi(argv[2]);
        string type = argv[3];
        Deck deck;
        Player *player;
        Hand player_hand;
        Hand dealer_hand;
        int thishand = 0;
        if (type == "simple")//detect the player type
            player = get_Simple();
        else if (type == "counting") {
            player = get_Counting();
        } else {
            return 1;
        }
        shuffle(deck);
        player->shuffled();
//start the game
        while (true) {
            if (bankroll < Min || thishand >= hands) {
                break;
            }
            thishand = thishand + 1;
            if (deck.cardsLeft() < 20) {
                shuffle(deck);
                player->shuffled();
            }
            cout << "Hand " << thishand << " bankroll " << bankroll << endl;
            int wager = player->bet(bankroll, Min);
            cout << "Player bets " << wager << endl;

            Card dealer_up;
            Card dealer_down;
            deal_four_cards(deck, player, player_hand, dealer_hand, dealer_up, dealer_down);//make the deal_four draw;

            if (player_hand.handValue().count == 21) {
                cout << "Player dealt natural 21\n";
                bankroll +=wager*3/2;
            } else if (Player_round(&deck, player, player_hand, dealer_up)) {//if player busts
                bankroll = bankroll - wager;
            } else if (Dealer_round(&deck, player, dealer_hand, dealer_down)) {//if dealer busts
                bankroll = bankroll + wager;
            } else if (player_hand.handValue().count > dealer_hand.handValue().count) {//if player's value is larger than dealer's
                cout << "Player wins\n";
                bankroll = bankroll + wager;
            } else if (player_hand.handValue().count < dealer_hand.handValue().count) {//if player's value is smaller than dealer's
                cout << "Dealer wins\n";
                bankroll = bankroll - wager;
            } else {
                cout << "Push\n";
            }
            dealer_hand.discardAll();//discard for dealer hand
            player_hand.discardAll();//discard for player hand


        }
        cout << "Player has " << bankroll << " after " << thishand << " hands\n";
    }
 return 0;
}
