#include "hand.h"
#include "card.h"

//default card value for all cards
static const int card_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

Hand::Hand(){
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll(){
    curValue.count = 0;
    curValue.soft = false;
}


void Hand::addCard(Card c){
    //if ace make the total larger than 21, make it hard, if not, make it soft
    if (c.spot == ACE&&curValue.count + card_value[c.spot] >21)
        curValue.count++;
    else if(curValue.soft&&curValue.count + card_value[c.spot] >21){
        curValue.soft = false;
        curValue.count = curValue.count + card_value[c.spot] -10;
    }
    else{
        curValue.count = curValue.count + card_value[c.spot];
        if(c.spot == ACE) curValue.soft = true;
    }
}

HandValue Hand::handValue() const{
    return curValue;
}