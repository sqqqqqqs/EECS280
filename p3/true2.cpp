#include "player.h"

class Simple:public Player{

    public:
    Simple():Player(){}

    int bet(unsigned int bankroll, unsigned int minimum) override{
        return minimum; //simple player always bet the minimum
    }

    bool draw(Card dealer, const Hand &player) override{
        HandValue curhand = player.handValue();
        if(curhand.soft == false){
            if(curhand.count<=11) return true;
            if(curhand.count==12&&!(dealer.spot>=FOUR&&dealer.spot<=SIX)) return true;
            if(curhand.count>=13&&curhand.count<=16&&!(dealer.spot>=TWO&&dealer.spot<=SIX)) return true;
            return false;
        }
        else{
            if(curhand.count<=17) return true;
            if(curhand.count==18&&dealer.spot!=TWO&&dealer.spot!=SEVEN&&dealer.spot!=EIGHT) return true;
            return false;
        }
    }

    void expose(Card c) override{}
    void shuffled() override{}
};

class Counting:public Player{
    int count;

    public:

    Counting():Player(){
        count=0;
    }

    int bet(unsigned int bankroll, unsigned int minimum) override{
        if(bankroll>=2*minimum&&count>=2) return 2*minimum;
        else return minimum; //counting player bet according to the count
    }

    bool draw(Card dealer, const Hand &player) override{
        HandValue curhand = player.handValue();
        if(curhand.soft == false){
            if(curhand.count<=11) return true;
            if(curhand.count==12&&!(dealer.spot>=FOUR&&dealer.spot<=SIX)) return true;
            if(curhand.count>=13&&curhand.count<=16&&!(dealer.spot>=TWO&&dealer.spot<=SIX)) return true;
            return false;
        }
        else{
            if(curhand.count<=17) return true;
            if(curhand.count==18&&dealer.spot!=TWO&&dealer.spot!=SEVEN&&dealer.spot!=EIGHT) return true;
            return false;
        }
    }

    void expose(Card c) override{
        if(c.spot>=TEN&&c.spot<=ACE) count--;
        if(c.spot>=TWO&&c.spot<=SIX) count++;
    }

    void shuffled() override{
        count =0;
    }
};


static Simple simple_player;
static Counting count_player;

extern Player *get_Simple(){
    return new Simple();
}

extern Player *get_Counting(){
    return new Counting();
}
