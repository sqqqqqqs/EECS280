#include "hand.h"
#include "card.h"


Hand::Hand() {
    curValue.count=0;
    curValue.soft=false;
}

void Hand::discardAll() {
    curValue.count=0;
    curValue.soft=false;
}

void Hand::addCard(Card c) {
    int sum=0;
    if(c.spot==TWO||c.spot==THREE||c.spot==FOUR||c.spot==FIVE||c.spot==SIX||c.spot==SEVEN||c.spot==EIGHT||c.spot==NINE||c.spot==TEN){
        sum=sum+c.spot+2;
    }
    else if(c.spot==JACK||c.spot==QUEEN||c.spot==KING){
        sum=sum+10;
    }
    else{sum=sum+11;}
    if(c.spot==ACE&&curValue.count+sum>21){//if the c is Ace and after adding 11, exceed 21, treat the new Ace as hard;
        curValue.count=curValue.count+1;
    }
    else if(curValue.soft && curValue.count + sum > 21){
        curValue.soft= false;
        curValue.count=curValue.count+sum-10;
    }
    else{
        curValue.count=curValue.count+sum;
        if(c.spot==ACE){
            curValue.soft= true;
        }
    }
}

HandValue Hand::handValue() const {
 return curValue;
}