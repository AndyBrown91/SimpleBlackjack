//
//  BlackJack.cpp
//  SmallTests
//
//  Created by Andy on 20/07/2013.
//  Copyright (c) 2013 Andy. All rights reserved.
//

#include "BlackJack.h"

void Blackjack::createCards()
{
    string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    string values [] = {"Ace", "2", "3", "4","5", "6",
        "7", "8", "9", "10", "Jack", "Queen", "King"};
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck.push_back(new Card (values[j], suits[i]));
        }
    }
}

void Blackjack::dealCards ()
{
    srand ( time (NULL));
    random_shuffle(deck.begin(), deck.end(), [](int i) { return rand()%i;});
    
    player.clear();
    dealer.clear();
    
    cardTaken = 0;
    
    for (int i = 0; i < 2; i ++)
    {
        player.push_back(deck[cardTaken++]);
        dealer.push_back(deck[cardTaken++]);
    }
}

void Blackjack::displayHand (Hand* hand)
{
    for (int i = 0; i < hand->size(); i++)
        cout << hand->at(i)->first << " of " << hand->at(i)->second << "\n";
}

int Blackjack::calculateHand (Hand* hand)
{
    int value = 0;
    for (int i = 0; i < hand->size(); i++)
        value += calculateCard(hand->at(i));
    
    if (hand->at(0)->first == "Ace" || hand->at(1)->first == "Ace")
    {
        //
        if ((value + 10) <= 21) {
            return value+10;
        }
    }
    
    return value;
}

int Blackjack::calculateCard (Card* card)
{
    if (card->first == "Ace")
        return 1;
    else if (card->first == "Jack" ||
             card->first == "Queen" ||
             card->first == "King")
        return 10;
    else
        return stoi(card->first);
}

bool Blackjack::turn (string youDealer, Hand* hand)
{
    //RETURNS TRUE IF BUST
    char response = 'a';
    
    while (response != 's')
    {
        cout << youDealer <<" hand is: \n";
        displayHand(hand);
        
        int playerValue = calculateHand(hand);
        cout << "The Value of " << youDealer << " hand is " << playerValue << endl;
        if (playerValue == 21)
            return false;
        
        if (youDealer == "Your")
        {
            //PLAYERS TURN
            //REMOVE IF TO ALLOW 2 PLAYER
            cout << "Stick (s) or Twist (t)" << endl;
            cin >> response;
        }
        else
        {
            playerValue = calculateHand(hand);
            if (playerValue < 17)
                response = 't';
            else
                response = 's';
        }
        
        if (response == 't')
        {
            hand->push_back(deck[cardTaken++]);
            playerValue = calculateHand(hand);
            
            if (playerValue == 21)
            {
                displayHand(hand);
                cout << "The Value of " << youDealer << " hand is now " << playerValue << endl;
                return false;
            }
            else if (playerValue > 21)
            {
                displayHand(hand);
                cout << "BUST, the value of " << youDealer << " hand is " << playerValue << endl;
                return true;
            }
        }
        
    }
    //NOT BUST
    return false;
}

void Blackjack::start()
{
    createCards();
    
    while (true)
    {
        cout << "Deal Cards? (Press y, Press n to exit)" << endl;
        char response;
        
        cin >> response;
        
        if (response == 'n')
        {
            break;
        }
        else
        {
            dealCards();
            if (turn("Your", &player))
                cout << "You lost, oh dear" << endl;
            else
            {
                if (!turn("The Dealer's", &dealer))
                {
                    int playerValue = calculateHand(&player);
                    int dealerValue = calculateHand(&dealer);
                    
                    if (dealerValue < playerValue)
                        cout << "You WIN WOOOOOOO" << endl;
                    else
                        cout << "You lost, Booo" << endl;
                    
                }
                else
                    cout << "You WIN WOOOOOOO" << endl;
            }
        }
        
    }
}