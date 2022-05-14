#ifndef _DECK_H_
#define _DECK_H_
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Card.h"

/*
    This is a deck class that stores multiple card objects and deal the cards out to the players
*/
class Deck{
private:
    //Vector of all the card objects
    std::vector<Card> deck;
public:
    //Methods:
    void create_deck();
    void print_deck();
    std::vector<Card> draw_cards(int seed_number);
    std::vector<Card> set_cards();
    void redraw_card();
    void reset_cards(const std::vector<Card> &hand);

    //Constructor
    Deck(){}

    //Deconstructor
    ~Deck(){}
};

// Used to initialize all 52 cards into the deck
void Deck::create_deck(){
    std::vector<std::string> card_vals {"A", "2", "3", "4", "5", "6" ,"7", "8", "9", "10", "J", "Q", "K"};
    std::vector<std::string> suit_vals {"S", "C", "D", "H"};
    int index {0};
    for(auto cv:card_vals){
        for(auto sv:suit_vals){
            Card card(cv,sv,index);
            deck.push_back(card);
            index++;
        }
    }
    // std::cout << "\n======================" << std::endl;
    // std::cout << "Deck Created" << std::endl;
    // std::cout << "======================" << std::endl;
}

// Used to make sure all 52 unique playing cards are intialized correctly
void Deck::print_deck(){
    std::cout << "\n======================" << std::endl;
    for(int i{0}; i < deck.size(); i++){
        if(i % 4 == 0){
            std::cout << std::endl;
            std::cout << deck[i].get_card_value() << deck[i].get_card_suit() << " ";
            
        }
        else{
            std::cout << deck[i].get_card_value() << deck[i].get_card_suit() << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "There are " << deck.size() << " cards in the deck" << std::endl;
    std::cout << "======================" << std::endl;
}

// Create a 'hand' of 5 cards for the player 
std::vector<Card> Deck::draw_cards(int seed_number){
    std::vector<Card> hand;
    srand(seed_number);
    //std::cout << "\n======================" << std::endl;
    for(int i{0}; i < 5; i++){
        int random_index = rand() % 52;
        // Checks if the card was drawn before, if not then draw to hand, else redraw another card
        if(deck[random_index].get_drawn() == false){
            deck[random_index].set_drawn(true);
            hand.push_back(deck[random_index]);
            //std::cout << "Cards drawn: " << deck[random_index].get_card_value() << deck[random_index].get_card_suit() << std::endl;
        }
        else{
            while(deck[random_index].get_drawn() != false){
                //std::cout << "Redrawing for card: " << deck[random_index].get_card_value() << deck[random_index].get_card_suit() << std::endl;
                int random_index = rand()%52;
                if(deck[random_index].get_drawn() == false){
                    deck[random_index].set_drawn(true);
                    hand.push_back(deck[random_index]);
                    //std::cout << "Cards drawn: " << deck[random_index].get_card_value() << deck[random_index].get_card_suit() << std::endl;
                    break;
                }
                else{}
            }
        }
    }
    //std::cout << "======================" << std::endl;
    return hand;
}

// Used for ONLY for testing identification of player's hand
std::vector<Card> Deck::set_cards(){
    std::vector<Card> hand;
    std::cout << "\n======================" << std::endl;
    std::cout << "Cards drawn: " << deck[0].get_card_value() << deck[0].get_card_suit() << std::endl;
    hand.push_back(deck[0]);
    std::cout << "Cards drawn: " << deck[48].get_card_value() << deck[48].get_card_suit() << std::endl;
    hand.push_back(deck[48]);
    std::cout << "Cards drawn: " << deck[40].get_card_value() << deck[40].get_card_suit() << std::endl;
    hand.push_back(deck[40]);
    std::cout << "Cards drawn: " << deck[44].get_card_value() << deck[44].get_card_suit() << std::endl;
    hand.push_back(deck[44]);
    std::cout << "Cards drawn: " << deck[36].get_card_value() << deck[36].get_card_suit() << std::endl;
    hand.push_back(deck[36]);
    
    std::cout << "======================" << std::endl;
    return hand;
}

// Reset the card so that it can be drawn again
void Deck::reset_cards(const std::vector<Card> &hand){
    // std::cout << "\n======================" << std::endl;
    // std::cout << "Reshuffling Cards Into Deck" << std::endl;
    for(auto card:hand){
        deck[card.get_deck_index()].set_drawn(false);
    }
    // std::cout << "======================" << std::endl;
}

#endif