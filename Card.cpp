// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

int ReturnSuitId(const Card& a) {
    int card_id = 0;
    std::string a_suit = a.get_suit();

    for (size_t i = 0; i < NUM_SUITS; ++i) {
        if (a_suit == SUIT_NAMES_BY_WEIGHT[i]) {
            card_id = i;
            break;
        }
    }

    return card_id;
}

int ReturnCardId(const Card& a) {

    int card_id = 0;
    std::string a_rank = a.get_rank();
    for (size_t i = 0; i < NUM_RANKS; ++i) {
        if (a_rank == RANK_NAMES_BY_WEIGHT[i]) {
            card_id = i;
            break;
        }
    }

    return card_id;
}

Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

Card::Card(const std::string& rank_in, const std::string& suit_in) {

    rank = rank_in;
    suit = suit_in;
}

std::string Card::get_rank() const {
    return rank;
}

std::string Card::get_suit() const {
    return suit;
}

std::string Card::get_suit(const std::string& trump) const {

    if (is_left_bower(trump))
        return trump;
    else
        return suit;
}

bool Card::is_face() const {

    std::string c_val = get_rank();
    bool res = false;

    std::array < const char*, 4 > arr =
    { Card::RANK_JACK, Card::RANK_QUEEN, Card::RANK_KING, Card::RANK_ACE };

    for (size_t i = 0; i < arr.size(); ++i) {
        if (c_val == arr[i]) {
            res = true;
            break;
        }
    }

    return res;
}

bool Card::is_right_bower(const std::string& trump) const {

    std::string c_val = get_rank();
    std::string c_suit = get_suit();

    bool res = false;

    if (c_val == Card::RANK_JACK && c_suit == trump) {
        res = true;
    }

    return res;

}

bool Card::is_left_bower(const std::string& trump) const {

    std::string c_val = get_rank();
    std::string c_suit = get_suit();
    std::string n_suit = Suit_next(trump);

    bool res = false;

    if (c_val == Card::RANK_JACK && c_suit == n_suit) {
        res = true;
    }

    return res;

}

bool Card::is_trump(const std::string& trump) const {


    if (get_suit(trump) == trump) {
        return true;
    }

    return false;
}

bool operator<(const Card& lhs, const Card& rhs) {


    if (ReturnCardId(lhs) == ReturnCardId(rhs)) {
        return ReturnSuitId(lhs) < ReturnSuitId(rhs);
    }
    else {
        //cout << "Comparing rnks" << endl;
        return ReturnCardId(lhs) < ReturnCardId(rhs);
    }
}

bool operator==(const Card& lhs, const Card& rhs) {
    return (ReturnCardId(lhs) == ReturnCardId(rhs) &&
        ReturnSuitId(lhs) == ReturnSuitId(rhs));
    //return lhs.get_rank() == rhs.get_rank();
}

bool operator<=(const Card& lhs, const Card& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Card& lhs, const Card& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Card& lhs, const Card& rhs) {
    return !(lhs < rhs);
}

bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs == rhs);
}

std::string Suit_next(const std::string& suit) {

    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else {
        return Card::SUIT_HEARTS;
    }

}

std::ostream& operator<<(std::ostream& os, const Card& card) {

    os << card.get_rank() << " of " << card.get_suit(); //send output to "os"
    return os;
}

bool Card_less(const Card& a, const Card& b, const std::string& trump) {

    if (a.is_right_bower(trump)) {
        return false;
    }

    if (b.is_right_bower(trump)) {
        return true;
    }
    if (a.is_left_bower(trump)) {
        return false;
    }
    if (b.is_left_bower(trump)) {
        return true;
    }

    if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else {
        return (a < b);
    }

}

bool Card_less(const Card& a, const Card& b, const Card& led_card,
    const std::string& trump) {

    std::string led_suit = led_card.get_suit();
    std::string a_suit = a.get_suit();
    std::string b_suit = b.get_suit();

    if (a.is_trump(trump) || b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }

    if (a_suit != led_suit && b_suit == led_suit) {
        return true;
    }

    if (a_suit == led_suit && b_suit != led_suit) {
        return false;
    }

    if ((!a.is_trump(trump) && a_suit != led_suit) &&
        (b.is_trump(trump) || b_suit == led_suit)) {
        return true;
    }
    else if ((!a.is_trump(trump) && a_suit != led_suit) &&
        (!b.is_trump(trump) && b_suit == led_suit)) {
        //cout << "Calling 1 < " << a << " " << b << endl;
         //return (a < b);
        return true;
    }
    else {
        //cout << "Calling 2 < " << a << " " << b << endl;
        return (a < b);
    }
}
