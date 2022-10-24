// euchre.cpp
// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cassert>
#include "Player.h"
#include "Pack.h"

using namespace std;

class Game {
public:
    Game(std::istream& input, char* shuffle_mode,
        vector<string>& v1, vector<string>& v2);
    bool ContinueGame();
    void PlayHand(int hand_idx);
    void ShufflePack();
    Card DealCards(int hand_idx, int eldest_hand_idx);
    std::string MakeTrump(Card upcard, int dealer_idx,
        int eldest_hand_idx, int& player_idx);
    int PlayTrick(int trick_id, int leader_idx, const std::string& trump);
    void ReportHandStatus(int* arr, int who_ordered_up);
    void ReportMarchEuchered(bool team_ordered_up, int count, int& score_team);
    void ReportScore();
    bool CheckGame(int n_of_points);
    void CleanGame();

private:
    std::vector<Player*> players;
    Pack pack_of_cards;
    int score_team_one;
    int score_team_two;
    bool shuffle;
};

//EFFECTS Initializes Game 
Game::Game(std::istream& input, char* shuffle_mode,
    vector<string>& v1, vector<string>& v2) {

    Pack pack_of_cards(input);

    for (size_t i = 0; i < v1.size(); i++) {
        players.push_back(Player_factory(v1[i], v2[i]));
    }

    score_team_one = 0;
    score_team_two = 0;
    shuffle = false;
    if (strcmp(shuffle_mode, "shuffle") == 0) {
        shuffle = true;
    }
}

// REQUIRES: 
// MODIFIES: 
// EFFECTS: to run the game with shuffling disabled/enables
void Game::ShufflePack() {

    if (shuffle) {
        pack_of_cards.shuffle();
        pack_of_cards.reset();
    }
    else {
        pack_of_cards.reset();
    }

}

// REQUIRES: valid hand , the dealer id
// MODIFIES:
// EFFECTS: declares the upcard
Card Game::DealCards(int hand_idx, int eldest_hand_idx) {

    int pl[4];
    for (int i = 0; i < int(players.size()); ++i) {
        pl[i] = eldest_hand_idx;

        eldest_hand_idx++;

        if (eldest_hand_idx == int(players.size())) {
            eldest_hand_idx = 0;
        }
    }

    std::array < int, 8 > arr = { 3, 2, 3, 2 , 2, 3, 2, 3 };
    // Use a for-loop and index to decide which person to deal.
    int j, p = 0;
    //pack_of_cards.reset();
    for (size_t i = 0; i < arr.size(); ++i) {
        j = 0;
        while (j < arr[i]) {
            Card a_card = pack_of_cards.deal_one();
            players[pl[p]]->add_card(a_card);
            //cout << *players[pl[p]] << " got a crad " << a_card << endl;
            j++;
        }
        p++;
        if (p == 4) {
            p = 0;
        }
    }

    Card upcard = pack_of_cards.deal_one();
    cout << upcard << " turned up" << endl;
    return upcard;
}

// REQUIRES: valid upcard , dealer id
// MODIFIES: 
// EFFECTS: declares the trump
std::string Game::MakeTrump(Card upcard, int dealer_idx,
    int eldest_hand_idx, int& player_idx) {

    bool keep_playing = true;
    bool is_dealer = false;

    int round_idx = 1;
    std::string order_up_suit = upcard.get_suit();

    int arr[4];
    int j = eldest_hand_idx;
    for (int i = 0; i < int(players.size()); ++i) {
        arr[i] = j;
        j++;
        if (j >= 4) {
            j = 0;
        }
    }

    for (int i = 0; i < int(players.size()); ++i) {
        if (players[arr[i]]->make_trump(upcard, is_dealer,
            round_idx, order_up_suit)) {
            keep_playing = false;
            cout << *players[arr[i]] << " orders up " <<
                upcard.get_suit() << "\n\n";
            player_idx = arr[i];
            break;
        }
        else {
            cout << *players[arr[i]] << " passes" << endl;
        }
    }

    if (!keep_playing) {
        players[dealer_idx]->add_and_discard(upcard);
        return order_up_suit;
    }
    round_idx++;
    order_up_suit = Suit_next(upcard.get_suit());

    for (int i = 0; i < int(players.size()); ++i) {
        if (players[arr[i]]->make_trump(upcard, is_dealer,
            round_idx, order_up_suit)) {
            keep_playing = false;
            cout << *players[arr[i]] << " orders up " << order_up_suit << "\n";
            player_idx = arr[i];
            break;
        }
        else {
            cout << *players[arr[i]] << " passes" << endl;
        }
    }
    cout << endl;
    return order_up_suit;

}

// REQUIRES:  hand Id
// MODIFIES:
// EFFECTS: driver that runs a single hand
void Game::PlayHand(int hand_idx) {

    cout << "Hand " << hand_idx << endl;

    ShufflePack();
    // the 1st Hand is led by the eldest hand , need to calculate 
    // the player Id based on the dealer Id
    int n_of_players = 4;
    int number_of_tricks = 5;

    int dealer_idx = (hand_idx - n_of_players * (hand_idx / n_of_players));
    int eldest_hand_idx = dealer_idx + 1;
    if (eldest_hand_idx == n_of_players) {
        eldest_hand_idx = 0;
    }

    int order_up_idx = eldest_hand_idx;

    cout << *players[dealer_idx] << " deals" << endl;

    Card upcard = DealCards(hand_idx, eldest_hand_idx);
    // also need to record what team had ordered up
    string trump = MakeTrump(upcard, dealer_idx, eldest_hand_idx, order_up_idx);
    //cout << "Became Trump " << trump << endl; 
    int winner_idx;
    int arr[5];
    // need to record the number of tricks each team won
    for (int i = 0; i < number_of_tricks; i++) {
        winner_idx = PlayTrick(i, eldest_hand_idx, trump);
        arr[i] = winner_idx;
        eldest_hand_idx = winner_idx;
    }

    ReportHandStatus(arr, order_up_idx);

}

//The team that takes the majority of tricks receives points for that hand. 
//If the winning team had also ordered up, they get 1 point for taking 
//3 or 4 tricks, and 2 points for taking all 5. 
//Taking all 5 tricks is called a march. 
// If the winning team did not order up, they receive 2 points 
//for taking 3, 4 or 5 tricks, which is called euchred.

void Game::ReportMarchEuchered(bool team_ordered_up, int count, int& score_team) {

    if (team_ordered_up) {
        if (count == 3 || count == 4) {
            score_team++;
        }
        else if (count == 5) {
            cout << "march!" << endl;
            score_team = score_team + 2;
        }
    }
    else {
        if (count >= 3) {
            score_team = score_team + 2;
            cout << "euchred!" << endl;
        }
    }
}

// REQUIRES: , recorder umber of tricks each team won, player id
// MODIFIES:
// EFFECTS: reports the hand status
void Game::ReportHandStatus(int* arr, int who_ordered_up) {
    int even_count = 0;
    int odd_count = 0;
    bool team_one_ordered_up = false;
    bool team_two_ordered_up = false;

    if (who_ordered_up % 2 == 0) {
        team_one_ordered_up = true;
    }
    else {
        team_two_ordered_up = true;
    }

    for (int i = 0; i < 5; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        }
        else {
            odd_count++;
        }
    }
    if (even_count > odd_count) {
        cout << *players[0] << " and " << *players[2] <<
            " win the hand" << endl;
        ReportMarchEuchered(team_one_ordered_up, even_count, score_team_one);
    }
    else {
        cout << *players[1] << " and " << *players[3] <<
            " win the hand" << endl;
        ReportMarchEuchered(team_two_ordered_up, odd_count, score_team_two);
    }
    cout << *players[0] << " and " << *players[2] << " have "
        << score_team_one << " points" << endl;
    cout << *players[1] << " and " << *players[3] << " have "
        << score_team_two << " points" << endl;
    cout << endl;
}

// REQUIRES: number of points to win the game
// MODIFIES:
// EFFECTS: Returns true if the game continues 
bool Game::CheckGame(int points) {

    bool end_game = false;

    if (score_team_one >= points) {
        cout << *players[0] << " and " << *players[2] <<
            " win!" << endl;
        end_game = true;
    }
    else if (score_team_two >= points) {
        cout << *players[1] << " and " << *players[3] <<
            " win!" << endl;
        end_game = true;
    }
    if (end_game) {
        CleanGame();
    }
    return end_game;
}

// REQUIRES: hand id, leader id, valid trumpe
// MODIFIES:
// EFFECTS: Returns the id of the winner
int Game::PlayTrick(int trick_id, int leader_idx, const std::string& trump) {

    Card l_card = players[leader_idx]->lead_card(trump);
    cout << l_card << " led by " << *players[leader_idx] << endl;

    int winner_idx = leader_idx;

    int arr[4];
    arr[0] = leader_idx;
    leader_idx++;
    for (int i = 1; i < int(players.size()); ++i) {
        if (leader_idx == int(players.size())) {
            leader_idx = 0;
        }
        arr[i] = leader_idx;
        leader_idx++;
    }

    Card win_card = l_card;
    for (int j = 1; j < 4; j++) {
        Card p_card = players[arr[j]]->play_card(l_card, trump);
        cout << p_card << " played by " << *players[arr[j]] << endl;

        if (!Card_less(p_card, win_card, l_card, trump)) {
            winner_idx = arr[j];
            win_card = p_card;
        }
    }

    cout << *players[winner_idx] << " takes the trick" << endl;
    cout << endl;

    return winner_idx;
}

// REQUIRES: 
// MODIFIES:
// EFFECTS: delete the Player objects created by the Player_factory
void Game::CleanGame() {
    for (int i = 0; i < int(players.size()); ++i) {
        delete players[i];
    }
}

void Usage() {

    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

}


bool CheckArgs(int num_args, char** cmd_args) {

    for (int i = 0; i < num_args; i++) {
        cout << cmd_args[i] << " ";
    }
    cout << endl;

    if (num_args != 12) {
        Usage();
        return false;
    }

    ifstream fin;
    fin.open(cmd_args[1]);

    if (!fin.is_open()) {
        cout << "Error opening " << cmd_args[1] << endl;
        return false;
    }

    if (strcmp(cmd_args[2], "shuffle") != 0 &&
        strcmp(cmd_args[2], "noshuffle") != 0) {
        Usage();
        return false;
    }

    if (atoi(cmd_args[3]) < 1 || atoi(cmd_args[3]) > 100) {
        Usage();
        return false;
    }

    std::array < int, 4 > arr = { 5, 7, 9, 11 };
    for (size_t i = 0; i < arr.size(); ++i) {
        if (strcmp(cmd_args[arr[i]], "Simple") != 0 &&
            strcmp(cmd_args[arr[i]], "Human") != 0) {
            Usage();
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {

    if (!CheckArgs(argc, argv)) {
        return 1;
    }

    char* pack_file_name = argv[1];
    char* shuffle_mode = argv[2];
    int n_of_points = atoi(argv[3]);

    vector<string> pl_names, pl_types;

    for (int i = 4; i < 12; i++) {
        pl_names.push_back(argv[i++]);
        pl_types.push_back(argv[i]);
    }

    bool keep_playing = true;

    ifstream ifs(pack_file_name);
    assert(ifs.is_open());
    Game game = Game(ifs, shuffle_mode, pl_names, pl_types);

    int hand_idx = 0;
    while (keep_playing) {
        game.PlayHand(hand_idx);

        if (game.CheckGame(n_of_points)) {
            keep_playing = false;
        }

        hand_idx++;

    }

    return 0;
}