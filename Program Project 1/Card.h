#ifndef _CARD_H_
#define _CARD_H_
#include <iostream>
#include <string>
#include <vector>

/*  
    This is a class to represent a card which is used to create an object for the card
*/
class Card{
private:
    //This is the value of the card(e.g. A, 2, 3, ...)
    std::string value;
    //This is the suit of the card(e.g. Spade (S), Club (C), Diamond (D), Heart (H))
    std::string suit;
    //This is the deck index to make it easer to reference location within deck and for random number generator
    int deck_index; 
    //This is a bool value to check if the card have been drawn before
    bool drawn {false};
public:
    //Methods:
    std::string get_card_value(){
        return value;
    }
    
    std::string get_card_suit(){
        return suit;
    }
    
    bool get_drawn(){
        return drawn;
    }
    
    void set_drawn(bool drawn_val){
        drawn = drawn_val;
        // Uncomment to check whether a card is drawn (e.g. true) or no (e.g. false)
        // std::cout << "\n======================" << std::endl;
        // std::cout << "Card drawn set to " << drawn << std::endl;
        // std::cout << "======================" << std::endl;
    }

    //Set the deck index of a card to use with random number generator
    void set_deck_index(int index_val){
        deck_index = index_val;
    }

    // Get deck index of card to make it easier to insert card back into deck to reshuffle
    int get_deck_index(){
        //std::cout << deck_index << std::endl;
        return deck_index;
    }

    //Constructor
    Card(std::string card_val, std::string suit_val, int index_val) : value{card_val}, suit{suit_val}, deck_index{index_val}{}

    //Deconstructor
    ~Card(){}
};

#endif