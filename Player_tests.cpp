// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

// use to delete all declared players intermittently throughout the tests
// for (int i = 0; i < int(players.size()); ++i) {
//  delete players[i];
// } s

TEST(test_player_get_name) {
    Player* alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

TEST(make_trump_simple_r1) {
    // test make trump with right and left bower trumps, and test normally
    // test with all trump cards and with no trump cards

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);

    //upcards
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    //trumps
    string diamond_trump = Card::SUIT_DIAMONDS;
    string heart_trump = Card::SUIT_HEARTS;
    string empty;

    jill->add_card(ace_hearts);
    jill->add_card(king_hearts);
    jill->add_card(king_diamonds);
    jill->add_card(nine_spades);
    jill->add_card(ten_diamonds);

    ASSERT_FALSE(jill->make_trump(nine_diamonds, false, 1, empty));
    ASSERT_TRUE(jill->make_trump(nine_hearts, false, 1, empty));
    ASSERT_FALSE(jill->make_trump(ten_diamonds, false, 1, empty));

    delete jill;

}

TEST(make_trump_all_trumps) {

    Player* jill = Player_factory("Jill", "Simple");

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    jill->add_card(nine_hearts);
    jill->add_card(ten_hearts);
    jill->add_card(queen_hearts);
    jill->add_card(king_hearts);

    string empty;
    string empty2;

    ASSERT_TRUE(jill->make_trump(ace_hearts, false, 1, empty));
    ASSERT_FALSE(jill->make_trump(nine_diamonds, false, 1, empty));

    delete jill;
}

TEST(make_trump_simple_bowers) {
    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);

    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);

    //upcards
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    //trumps
    string diamond_trump = Card::SUIT_DIAMONDS;
    string heart_trump = Card::SUIT_HEARTS;
    string empty;

    jill->add_card(ace_hearts);
    jill->add_card(king_hearts);
    jill->add_card(king_diamonds);
    jill->add_card(jack_spades);
    jill->add_card(jack_diamonds);

    ASSERT_TRUE(jill->make_trump(nine_diamonds, false, 1, empty));
    ASSERT_FALSE(jill->make_trump(nine_spades, false, 1, empty));

    delete jill;
}

TEST(make_trump_screw_the_dealer) {

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    Card upcard(Card::RANK_KING, Card::SUIT_HEARTS);
    string diamond_trump = Card::SUIT_DIAMONDS;
    string heart_trump = Card::SUIT_HEARTS;

    jill->add_card(ace_diamonds);
    jill->add_card(king_diamonds);
    jill->add_card(queen_diamonds);
    jill->add_card(queen_hearts);
    jill->add_card(queen_clubs);

    ASSERT_FALSE(jill->make_trump(upcard, true, 1, heart_trump));
    ASSERT_TRUE(jill->make_trump(upcard, true, 2, diamond_trump));

    delete jill;
}

TEST(make_trump_screw_the_dealer_1) {

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    Card upcard(Card::RANK_KING, Card::SUIT_HEARTS);
    string diamond_trump = Card::SUIT_DIAMONDS;
    string heart_trump = Card::SUIT_HEARTS;

    jill->add_card(ace_diamonds);
    jill->add_card(king_diamonds);
    jill->add_card(queen_diamonds);
    jill->add_card(queen_hearts);
    jill->add_card(queen_clubs);

    ASSERT_FALSE(jill->make_trump(upcard, false, 1, heart_trump));
    ASSERT_TRUE(jill->make_trump(upcard, false, 2, diamond_trump));

    delete jill;
}

TEST(left_bower_simple) {

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    //upcards
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);

    //trumps
    string diamond_trump = Card::SUIT_DIAMONDS;
    string heart_trump = Card::SUIT_HEARTS;
    string empty;

    jill->add_card(ace_hearts);
    jill->add_card(ten_hearts);
    jill->add_card(jack_diamonds);
    jill->add_card(nine_spades);
    jill->add_card(nine_diamonds);

    ASSERT_FALSE(jill->make_trump(ten_diamonds, false, 1, empty));
    ASSERT_TRUE(jill->make_trump(nine_hearts, false, 1, empty));
    ASSERT_EQUAL(empty, Card::SUIT_HEARTS);

    delete jill;
}

TEST(right_bower_simple) {
    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    //upcards
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);

    //trumps
    string diamond_trump = Card::SUIT_DIAMONDS;
    string heart_trump = Card::SUIT_HEARTS;
    string empty;

    jill->add_card(ace_hearts);
    jill->add_card(jack_hearts);
    jill->add_card(ten_diamonds);
    jill->add_card(nine_spades);
    jill->add_card(nine_diamonds);

    ASSERT_TRUE(jill->make_trump(nine_hearts, false, 1, empty));

    delete jill;

}

TEST(lead_card_1) {

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);

    Player* joe = Player_factory("Joe", "Simple");

    joe->add_card(ace_hearts);
    joe->add_card(king_hearts);
    joe->add_card(nine_hearts);
    joe->add_card(queen_hearts);
    joe->add_card(ten_hearts);

    ASSERT_EQUAL(joe->lead_card(Card::SUIT_HEARTS), ace_hearts);


    delete joe;

    Player* jill = Player_factory("Jill", "Simple");

    jill->add_card(ace_hearts);
    jill->add_card(king_hearts);
    jill->add_card(jack_diamonds);
    jill->add_card(ten_spades);
    jill->add_card(nine_diamonds);

    ASSERT_EQUAL(jill->lead_card(Card::SUIT_HEARTS), ten_spades);

    delete jill;
}

TEST(all_trump) {

    Player* jill = Player_factory("Jill", "Simple");

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);

    jill->add_card(nine_hearts);
    jill->add_card(ten_hearts);
    jill->add_card(queen_hearts);
    jill->add_card(king_hearts);
    jill->add_card(ace_hearts);

    ASSERT_EQUAL(jill->lead_card(Card::SUIT_HEARTS), ace_hearts);

    delete jill;

}

TEST(no_trump) {
    Player* jill = Player_factory("Jill", "Simple");

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);

    jill->add_card(nine_hearts);
    jill->add_card(ten_hearts);
    jill->add_card(queen_hearts);
    jill->add_card(king_hearts);
    jill->add_card(ace_hearts);

    ASSERT_EQUAL(jill->lead_card(Card::SUIT_DIAMONDS), ace_hearts);

    delete jill;
}

TEST(lead_card_2_bowers) {
    Player* jill = Player_factory("Jill", "Simple");
    Player* joe = Player_factory("Joe", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);

    jill->add_card(ace_hearts);
    jill->add_card(king_hearts);
    jill->add_card(jack_spades);
    jill->add_card(nine_spades);
    jill->add_card(nine_diamonds);

    joe->add_card(ace_hearts);
    joe->add_card(king_hearts);
    joe->add_card(nine_hearts);
    joe->add_card(queen_hearts);
    joe->add_card(jack_hearts);

    ASSERT_EQUAL(jill->lead_card(Card::SUIT_HEARTS), jack_spades);
    ASSERT_EQUAL(joe->lead_card(Card::SUIT_HEARTS), jack_hearts);

    delete jill;
    delete joe;

}

TEST(add_and_discard) {

    // Test whether or not the dealer picks up the upcard during round one
    // Check if he discards the lowest card and check if he has five cards

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);

    jill->add_card(ace_hearts);
    jill->add_card(ten_hearts);
    jill->add_card(king_diamonds);
    jill->add_card(king_spades);
    jill->add_card(nine_diamonds);

    jill->add_and_discard(jack_spades);

    string empty;
    string empty1;
    string empty2;

    ASSERT_TRUE(jill->make_trump(nine_spades, false, 1, empty));

    jill->add_and_discard(king_hearts);

    //ASSERT_TRUE(jill->make_trump(nine_spades, false, 1, empty1));
    ASSERT_TRUE(jill->make_trump(nine_hearts, false, 1, empty2));

    delete jill;
}


TEST(add_discard_trump) {
    Player* jill = Player_factory("Jill", "Simple");

    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);

    jill->add_card(jack_hearts);
    jill->add_card(ace_hearts);
    jill->add_card(king_hearts);
    jill->add_card(queen_hearts);
    jill->add_card(nine_diamonds);

    jill->add_and_discard(ten_hearts);

    string empty3;

    ASSERT_TRUE(jill->make_trump(nine_hearts, false, 1, empty3));

    delete jill;
}

TEST(make_trump_when_dealer_add_and_discard) {

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    string trump, trump1;

    Player* gaby = Player_factory("Gaby", "Simple");

    gaby->add_card(king_clubs);
    gaby->add_card(jack_clubs);
    gaby->add_card(jack_spades);
    gaby->add_card(queen_clubs);
    gaby->add_card(ten_clubs);

    Card upcard1(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_TRUE(gaby->make_trump(upcard1, true, 1, trump));
    ASSERT_EQUAL(gaby->play_card(ace_clubs, Card::SUIT_CLUBS), jack_clubs);
    ASSERT_EQUAL(gaby->lead_card(Card::SUIT_CLUBS), jack_spades);
    ASSERT_EQUAL(gaby->lead_card(Card::SUIT_CLUBS), king_clubs);
    ASSERT_EQUAL(gaby->lead_card(Card::SUIT_CLUBS), queen_clubs);
    ASSERT_EQUAL(gaby->lead_card(Card::SUIT_CLUBS), ten_clubs);

    Player* fran = Player_factory("Fran", "Simple");
    fran->add_card(queen_clubs);
    fran->add_card(jack_clubs);
    fran->add_card(nine_hearts);
    fran->add_card(ace_spades);
    fran->add_card(king_spades);

    Card upcard3(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_TRUE(fran->make_trump(upcard3, true, 1, trump1));
    fran->add_and_discard(upcard3);
    ASSERT_EQUAL(fran->play_card(ace_diamonds, Card::SUIT_SPADES), queen_clubs);
    ASSERT_EQUAL(fran->play_card(king_diamonds, Card::SUIT_SPADES), queen_spades);
    ASSERT_EQUAL(fran->lead_card(Card::SUIT_SPADES), jack_clubs);
    ASSERT_EQUAL(fran->lead_card(Card::SUIT_SPADES), ace_spades);
    ASSERT_NOT_EQUAL(fran->lead_card(Card::SUIT_SPADES), queen_diamonds);

    delete gaby;
    delete fran;
}

TEST(play_card_tests) {

    // have a hand with no cards in suit and a hand with all cards in suit

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);

    jill->add_card(ace_hearts);
    jill->add_card(ten_hearts);
    jill->add_card(king_diamonds);
    jill->add_card(king_spades);
    jill->add_card(nine_diamonds);

    ASSERT_EQUAL(jill->play_card(nine_clubs, Card::SUIT_CLUBS), nine_diamonds);
    ASSERT_EQUAL(jill->play_card(nine_spades, Card::SUIT_SPADES), king_spades);
    ASSERT_EQUAL(jill->play_card(nine_hearts, Card::SUIT_HEARTS), ace_hearts);

    delete jill;
}

TEST(play_card_tests_1) {

    Player* jill = Player_factory("Jill", "Simple");

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);

    jill->add_card(ace_hearts);
    jill->add_card(queen_spades);
    jill->add_card(queen_clubs);
    jill->add_card(nine_diamonds);
    jill->add_card(nine_clubs);

    ASSERT_EQUAL(jill->play_card(jack_clubs, Card::SUIT_CLUBS), queen_clubs);
    ASSERT_EQUAL(jill->play_card(jack_spades, Card::SUIT_CLUBS), nine_clubs);
    ASSERT_EQUAL(jill->play_card(queen_hearts, Card::SUIT_CLUBS), ace_hearts);
    ASSERT_EQUAL(jill->play_card(ten_diamonds, Card::SUIT_CLUBS), nine_diamonds);

    delete jill;
}

TEST(play_card_tests_2) {

    Player* jill = Player_factory("Jill", "Simple");

    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    jill->add_card(ace_diamonds);
    jill->add_card(ten_diamonds);
    jill->add_card(queen_diamonds);
    jill->add_card(king_diamonds);
    jill->add_card(nine_diamonds);

    ASSERT_EQUAL(jill->play_card(jack_clubs, Card::SUIT_CLUBS), nine_diamonds);
    ASSERT_EQUAL(jill->play_card(jack_clubs, Card::SUIT_SPADES), ten_diamonds);
    ASSERT_EQUAL(jill->play_card(queen_hearts, Card::SUIT_CLUBS), queen_diamonds);
    ASSERT_EQUAL(jill->play_card(nine_hearts, Card::SUIT_CLUBS), king_diamonds);

    delete jill;
}

TEST_MAIN()
