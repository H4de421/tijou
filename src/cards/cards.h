#ifndef CARD_H
#define CARD_H

#define MAX_HAND 5
#define REG_DECK 52
#define SQUARE 0
#define PICK 1
#define HEART 2
#define LEAVE 3

#include "../color/color.h"

enum card_e {
    card_AS = 1,
    card_2,
    card_3,
    card_4,
    card_5,
    card_6,
    card_7,
    card_8,
    card_9,
    card_10,
    card_J,
    card_Q,
    card_K,
    joker,
};

struct card_s {
    enum card_e num;
    enum color_e color;
    int kind; 
};

struct deck_s {
    struct card_s **cards;
    int max_card;
    int current_nb_card;
};

struct hand_s {
    struct card_s **cards;
    int current_nb_card;
};

struct card_s *create_card(enum card_e nb, int kind);
void destroy_card(struct card_s *card);
void print_card(struct card_s *card);

struct deck_s *create_deck(int b_joker);
void destroy_deck(struct deck_s *deck);

void shuffle_deck(struct deck_s *deck);
void add_to_deck(struct deck_s *deck, struct card_s *card);
struct card_s *get_from_deck(struct deck_s *deck_s);
void print_deck(struct deck_s *deck);

struct hand_s *create_hand();
void destroy_hand(struct hand_s *hand);

void add_to_hand(struct hand_s *hand, struct card_s *card);
void sort_hand(struct hand_s *hand);
struct card_s *get_from_hand(struct hand_s *hand, int id);
void print_hand(struct hand_s *hand);

#endif /*!CARD_H*/