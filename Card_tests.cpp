// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_get) {
    Card c(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::RANK_QUEEN, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit());

    ASSERT_NOT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_NOT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit());

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_CLUBS, jack_spades.get_suit(Card::SUIT_CLUBS));

}

TEST(test_card_id) {
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);


}

TEST(test_card_face) {
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(ace_spades.is_face());

    Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_TRUE(king_clubs.is_face());

    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(nine_clubs.is_face());

    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(jack_clubs.is_face());

    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(queen_clubs.is_face());
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);

    ASSERT_NOT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_DIAMONDS);
    ASSERT_NOT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_HEARTS);
}

TEST(test_card_trump) {
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);

    ASSERT_TRUE(ten_spades.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_clubs.is_trump(Card::SUIT_SPADES));

    ASSERT_FALSE(ten_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(ten_spades.is_trump(Card::SUIT_HEARTS));
    ASSERT_FALSE(ten_spades.is_trump(Card::SUIT_DIAMONDS));

}

TEST(test_card_left_right_bower) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);

    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));

    ASSERT_TRUE(jack_spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(jack_spades.is_right_bower(Card::SUIT_CLUBS));
    //ASSERT_FALSE(jack_spades.is_right_bower(Card::SUIT_HEARTS));

    ASSERT_TRUE(jack_clubs.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(jack_clubs.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_clubs.is_left_bower(Card::SUIT_HEARTS));
    //ASSERT_FALSE(jack_clubs.is_left_bower(Card::SUIT_DIAMONDS));
}

TEST(test_card_less) {
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card eight_hearts = Card(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card eight_diamonds = Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);

    ASSERT_FALSE(Card_less(nine_hearts, nine_hearts, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(nine_hearts, nine_hearts, nine_hearts,
        Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(eight_hearts, nine_hearts, Card::SUIT_HEARTS));

    ASSERT_TRUE(Card_less(nine_hearts, jack_diamonds, Card::SUIT_HEARTS));

    ASSERT_TRUE(Card_less(eight_diamonds, eight_hearts, nine_hearts, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_diamonds, eight_hearts, nine_hearts, Card::SUIT_HEARTS));
}

TEST(test_card_print) {
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card none;

    ostringstream oss;
    oss << ten_spades;
    ASSERT_EQUAL(oss.str(), "Ten of Spades");
    ASSERT_NOT_EQUAL(oss.str(), "Ten of Clubs");
    ASSERT_NOT_EQUAL(oss.str(), "Queen of Spades");
}

TEST(test_card_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);

    ASSERT_TRUE(three_spades < ten_spades);
    ASSERT_TRUE(three_spades <= ten_spades);
    ASSERT_FALSE(three_spades >= ace_spades);
    ASSERT_TRUE(three_spades != ace_spades);
    ASSERT_TRUE(ace_spades > ten_spades);
    ASSERT_TRUE(ace_spades == ace_spades);
    ASSERT_TRUE(nine_hearts > nine_spades);
    ASSERT_TRUE(king_hearts < king_diamonds);
}


TEST_MAIN()