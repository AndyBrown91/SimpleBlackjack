//
//  BlackJack.h
//  SmallTests
//
//  Created by Andy on 20/07/2013.
//  Copyright (c) 2013 Andy. All rights reserved.
//

#ifndef BlackJack__
#define BlackJack__

#include <iostream>

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <utility>
#include <vector>

#include <algorithm>

using namespace std;
typedef pair<string, string> Card;
typedef vector<Card*> Hand;

class Blackjack
{
public:
    Blackjack() {}
    ~Blackjack() {}
    
    void start();
    
private:
    void createCards();
    void dealCards();

    void displayHand (Hand* hand);
    int calculateHand (Hand* hand);
    int calculateCard (Card* card);
    
    bool turn (string youDealer, Hand* hand);
    
    vector<Card*> deck;
    
    Hand player, dealer;
    int cardTaken;
};


#endif /* defined(BlackJack__) */
