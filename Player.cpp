// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

using namespace std;

class SimplePlayer : public Player
{
    std::string name;
    std::vector<Card> hand;

public:
    SimplePlayer(const std::string& player_name);
    const std::string& get_name() const;
    void add_card(const Card& c);
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const;
    void add_and_discard(const Card& upcard);
    Card lead_card(const std::string& trump);
    Card play_card(const Card& led_card, const std::string& trump);
};

SimplePlayer::SimplePlayer(const std::string& player_name) {
    name = player_name;
}

const std::string& SimplePlayer::get_name() const {
    return name;
}

void SimplePlayer::add_card(const Card& c) {
    hand.push_back(c);
}

bool SimplePlayer::make_trump(const Card& upcard, bool is_dealer,
    int round, std::string& order_up_suit) const {

    // 1st round if player has 2 or more trump face cards, order up 
    //else pass
    int count = 0;
    std::string upcard_suit = upcard.get_suit();
    if (round == 2) {
        upcard_suit = order_up_suit;
    }

    for (size_t i = 0; i < hand.size(); i++) {
        if (hand[i].get_suit() == upcard_suit && hand[i].is_face()) {
            count++;
        }
        else if (hand[i].is_left_bower(upcard_suit)) {
            count++;
        }
    }
    if (round == 1) {
        if (count >= 2) {
            //player is ordering up since he has two or more face cards 
            //the same suit as upcard
            order_up_suit = upcard_suit;
            return true;
        }
    }
    else {
        if (count >= 1 || is_dealer) {
            order_up_suit = upcard_suit;
            return true;
        }
    }
    return false;
}



void SimplePlayer::add_and_discard(const Card& upcard) {
    add_card(upcard);

    int lowest_idx = 0;
    Card lowest = hand[0];

    for (size_t i = 1; i < hand.size(); i++) {
        if (Card_less(hand[i], lowest, upcard.get_suit())) {
            lowest_idx = i;
            lowest = hand[i];
        }
    }
    hand.erase(hand.begin() + lowest_idx);
}

Card SimplePlayer::lead_card(const std::string& trump) {
    // a player is leading with the highest non-trump card
    std::vector<Card> tmp;
    int highest_idx = -1;
    int highest_trump_idx = -1;
    Card highest, highestTrump;

    if (hand.size() == 1) {
        highest = hand[0];
        highest_idx = 0;
        hand.erase(hand.begin() + highest_idx);
        //cout << highest << " led by " << get_name() << endl;
        return highest;
    }

    if (hand[0].is_trump(trump)) {
        highestTrump = hand[0];
        highest_trump_idx = 0;
    }
    else {
        highest = hand[0];
        highest_idx = 0;
    }

    for (size_t i = 1; i < hand.size(); i++) {
        if (!hand[i].is_trump(trump)) {
            if (highest_idx == -1 ||
                (!Card_less(hand[i], highest, trump))) {
                highest = hand[i];
                highest_idx = i;
            }
        }
        else {
            if (highest_trump_idx == -1 ||
                (!Card_less(hand[i], highestTrump, trump))) {
                highestTrump = hand[i];
                highest_trump_idx = i;
            }
        }
    }

    if (highest_idx < 0) {
        highest_idx = highest_trump_idx;
        highest = highestTrump;
    }
    hand.erase(hand.begin() + highest_idx);
    //cout << highest << " led by " << get_name() << endl; 
    return highest;
}

Card SimplePlayer::play_card(const Card& led_card, const std::string& trump) {

    //if a player can follow suit, play the highest card of the same suit.
    //else play the lowest card

    std::string led_suit = led_card.get_suit(trump);
    Card highest, lowest;
    int highest_idx = -1;
    int lowest_idx = -1;
    highest = hand[0];
    lowest = hand[0];

    for (size_t i = 0; i < hand.size(); i++) {
        if (hand[i].get_suit(trump) == led_suit) {
            if (highest_idx == -1 ||
                (!Card_less(hand[i], highest, led_card, trump))) {
                highest = hand[i];
                highest_idx = i;
            }
        }
        else {
            if (lowest_idx == -1 || Card_less(hand[i], lowest, trump)) {
                lowest = hand[i];
                lowest_idx = i;
            }
        }
    }

    if (highest_idx < 0) {
        highest_idx = lowest_idx;
        highest = lowest;
    }
    hand.erase(hand.begin() + highest_idx);
    return highest;
}

class HumanPlayer : public Player
{
    std::string name;
    std::vector<Card> hand;

public:
    HumanPlayer(const std::string& player_name);
    const std::string& get_name() const;
    void add_card(const Card& c);
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const;
    void add_and_discard(const Card& upcard);
    Card lead_card(const std::string& trump);
    Card play_card(const Card& led_card, const std::string& trump);
};

HumanPlayer::HumanPlayer(const std::string& player_name) {
    name = player_name;
}

const std::string& HumanPlayer::get_name() const {
    return name;
}

void HumanPlayer::add_card(const Card& c) {

    if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
    }
}

bool HumanPlayer::make_trump(const Card& upcard, bool is_dealer,
    int round, std::string& order_up_suit) const {

    std::string upcard_suit = upcard.get_suit();

    std::vector<Card> tmp;
    for (size_t i = 0; i < hand.size(); i++) {
        tmp.push_back(hand[i]);
    }
    std::sort(tmp.begin(), tmp.end());

    for (size_t i = 0; i < tmp.size(); i++) {
        cout << "Human player " << get_name() << "'s hand: ["
            << i << "] " << tmp[i] << endl;
    }
    cout << "Human player " << get_name() <<
        ", please enter a suit, or \"pass\":";
    std::string suit;
    cin >> suit;
    cout << endl;

    if (suit.compare("pass") == 0) {
        return false;
    }

    order_up_suit = suit;
    return true;
}

void HumanPlayer::add_and_discard(const Card& upcard) {

    std::sort(hand.begin(), hand.end());
    for (size_t i = 0; i < hand.size(); i++) {
        cout << "Human player " << get_name() <<
            "'s hand: [" << i << "] " << hand[i] << endl;
    }

    cout << "Discard upcard: [-1]";
    int card_idx;
    cin >> card_idx;

    if (card_idx == -1) {
        cout << "\nHuman player " << get_name() <<
            ", please select a card to discard:\n" << endl;
    }
    else {
        cout << "\nHuman player " << get_name() <<
            ", please select a card to discard:" << endl;
        hand.erase(hand.begin() + card_idx);
        add_card(upcard);
    }
}

Card HumanPlayer::lead_card(const std::string& trump) {
    std::sort(hand.begin(), hand.end());
    for (size_t i = 0; i < hand.size(); i++) {
        cout << "Human player " << get_name() << "'s hand: ["
            << i << "] " << hand[i] << endl;
    }

    cout << "Human player " << get_name() << ", please select a card:";
    int l_card_idx;
    cin >> l_card_idx;
    Card l_card(hand[l_card_idx]);
    cout << endl;
    //cout << "\n" << l_card << " led by " << get_name() << endl;
    hand.erase(hand.begin() + l_card_idx);
    return l_card;
}

Card HumanPlayer::play_card(const Card& led_card, const std::string& trump) {

    std::sort(hand.begin(), hand.end());
    for (size_t i = 0; i < hand.size(); i++) {
        cout << "Human player " << get_name()
            << "'s hand: [" << i << "] " << hand[i] << endl;
    }

    cout << "Human player " << get_name() << ", please select a card:";
    int p_card_idx;
    cin >> p_card_idx;

    Card p_card(hand[p_card_idx]);
    cout << endl;
    hand.erase(hand.begin() + p_card_idx);
    return p_card;
}

Player* Player_factory(const std::string& name, const std::string& strategy) {
    // We need to check the value of strategy and return
    // the corresponding player type.

    if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    // Repeat for each other type of Player
    if (strategy == "Human") {
        // The "new" keyword dynamically allocates an object.
        return new HumanPlayer(name);
    }
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.get_name();
    return os;
}