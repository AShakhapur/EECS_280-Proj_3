// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include <array>
#include <string>

using namespace std;

static const int PACK_SIZE = 24;

Pack::Pack() {

    next = 0;
    int idx = 0;
    for (int i = 0; i < NUM_SUITS; ++i) {
        for (int j = 7; j < NUM_RANKS; ++j) {
            cards[idx] = Card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
            idx++;
        }
    }
}

Pack::Pack(std::istream& pack_input) {

    int idx = 0;
    std::string p1, p2, p3;

    next = 0;
    while (idx < PACK_SIZE) {
        pack_input >> p1;
        pack_input >> p2;
        pack_input >> p3;
        cards[idx] = Card(p1, p3);
        idx++;
    }
}


Card Pack::deal_one() {

    return cards[next++];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {

    int n_of_shuffles = 7;
    int half_of_pack = PACK_SIZE / 2;
    int pos = 0;
    int new_pos = 0;
    Card tmp_card1;
    std::array<Card, PACK_SIZE> cards_tmp;
    for (int i = 0; i < n_of_shuffles; ++i) {
        pos = 0;
        new_pos = 0;
        for (int j = half_of_pack; j < PACK_SIZE; ++j) {
            cards_tmp[new_pos] = cards[j];
            new_pos++;
            cards_tmp[new_pos] = cards[pos];
            new_pos++;
            pos++;
        }
        for (int z = 0; z < PACK_SIZE; ++z) {
            cards[z] = cards_tmp[z];
        }
    }
}

bool Pack::empty() const {

    if (next == PACK_SIZE) {
        return true;
    }
    else if (next > PACK_SIZE) {
        return true;
    }
    else {
        return false;
    }

}

