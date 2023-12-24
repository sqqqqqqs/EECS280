#include"player.h"

class Simple: public Player{
public:
    int bet(unsigned int bankroll, unsigned int minimum) override{
        //REQUIRES:bankroll>=0
        //MODIFIES:none
        //EFFECTS: return the bet each hand for the simple player
        return minimum;//since simple player always bet the minimum money
    }

    bool draw(Card dealer,const Hand &player) override {
        //REQUIRES:dealer can't be null
        //MODIFIES:none
        //EFFECTS: to judge whether a simple player should draw cards given the information
        HandValue present = player.handValue();
        if (!present.soft) {
            if (present.count <= 11 || (present.count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX)) ||
                (present.count >= 13 && present.count <= 16 && !(dealer.spot >= TWO && dealer.spot <= SIX))) {
                return true;
            }
            return false;
        } else {
            if (present.count <= 17 || (present.count == 18 && dealer.spot!=TWO&&dealer.spot!=SEVEN&&dealer.spot!=EIGHT)) {
                return true;
            }
            return false;
        }
        
    }

    void expose(Card c) override{};
    //No effect with expose for simple player
    void shuffled() override{};
    //NO effect with shuffled for simple player
    Simple(): Player(){};
// EFFECT: generate a pointer pointing to a CountingPlayer class.
};


class Counting: public Player{
    int count;
public:
    int bet(unsigned int bankroll, unsigned int minimum) override{
        //REQUIRES:bankroll>=0
        //MODIFIES:none
        //EFFECTS:given the count and the bankroll, decide whether bet two times the minimum of the money or only minimum money for the couning player
        if(count>=2&&bankroll>=2*minimum){
            return 2*minimum;
        }
        else{
            return minimum;
        }
    }

    bool draw(Card dealer,const Hand &player) override {
        //REQUIRES:dealer can't be null
        //MODIFIES:none
        //EFFECTS: to judge whether a counting player should draw cards given the information
        HandValue present = player.handValue();
        if (!present.soft) {
            if (present.count <= 11 || (present.count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX)) ||
                (present.count >= 13 && present.count <= 16 && !(dealer.spot >= TWO && dealer.spot <= SIX))) {
                return true;
            }
            return false;
        } else {
            if (present.count <= 17 || (present.count == 18 && dealer.spot!=TWO&&dealer.spot!=SEVEN&&dealer.spot!=EIGHT)) {
                return true;
            }
            return false;
        }
        
    }

    void expose(Card c) override{
        //REQUIRES: dealer can't be null
        //MODIFIES:count
        //EFFECT: expose the card to player to help change the count number
        if(c.spot>=TWO&&c.spot<=SIX){
            count=count+1;
        }
        else if(c.spot>=TEN&&c.spot<=ACE){
            count=count-1;
        }
    }

    void shuffled() override{
        //MODIFIES:count
        //EFFECTS: after one shuffling, the count should be renewed with value 0
        count=0;
    }

    Counting(): Player(){
        count=0;
    }

};

extern Player *get_Simple(){
    //EFFECT:return a simple player
    return new Simple();
}

extern Player *get_Counting(){
    //EFFECT:return a counting player
    return new Counting();
}
