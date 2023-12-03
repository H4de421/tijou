#include "cards.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card_s *create_card(enum card_e nb, int kind)
{
    struct card_s *res = malloc(sizeof(struct card_s));
    if (!res)
    {
        return NULL;
    }
    res->num = nb;
    res->kind = kind;
    res->color = (kind == HEART || kind == SQUARE)? red : reg;
    return res;
}

void destroy_card(struct card_s *card)
{
    free(card);
}

void print_card(struct card_s *card)
{
    if (card == NULL)
    {
        printf("  ");
    }
    else if (card->num < 10)
    {
        printf("\e[%dm %c\e[0m", card->color, card->num+'0');
    }
    else if (card->num == card_10)
    {
        printf("\e[%dm10\e[0m", card->color);
    }
    else if (card->num == card_J)
    {   
        printf("\e[%dm J\e[0m", card->color);
    }
    else if (card->num == card_Q)
    {   
        printf("\e[%dm Q\e[0m", card->color);
    }
    else if (card->num == card_K)
    {   
        printf("\e[%dm K\e[0m", card->color);
    }
    else if (card->num == joker)
    {
        printf("\e[32mJO\e[0m");
    }
    
}


struct deck_s *create_deck(int b_joker)
{
    struct deck_s *res = malloc(sizeof(struct deck_s));
    if(!res)
    {
        return NULL;
    }
    res->cards = calloc((REG_DECK + b_joker*2), sizeof(struct card_s));
    res->max_card = REG_DECK + 2*b_joker;
    res->current_nb_card = res->max_card;
    for (int nb = 0; nb < 13; nb++)
    {
        for (int kind = 0; kind < 4; kind++)
        {
            res->cards[kind*(13) + nb] = create_card(nb+1, kind);
        }
    }
    if(b_joker)
    {
        res->cards[52] = create_card(joker, PICK);
        res->cards[53] = create_card(joker, PICK);   
    }
    return res;
}

void destroy_deck(struct deck_s *deck)
{
    for (int i = 0; i < deck->current_nb_card; i++)
    {
        destroy_card(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}

void shuffle_deck(struct deck_s *deck)
{
    time_t *tim = NULL;
    int set_rand = time(tim);
    srand((set_rand/5) + 2*set_rand);

    for (int i = 0; i < deck->current_nb_card; i++)
    {
        int swap_id = (rand())%deck->current_nb_card;
        struct card_s *tmp = deck->cards[i];
        deck->cards[i] = deck->cards[swap_id];
        deck->cards[swap_id] = tmp;
    }
    
}

void add_to_deck(struct deck_s *deck, struct card_s *card)
{
    if(deck->current_nb_card == deck->max_card)
    {
        fprintf(stdout, "ERROR add_to_deck : deck is already full");
        return ;
    }
    deck->cards[deck->current_nb_card] = card;
    deck->current_nb_card++;
}

struct card_s *get_from_deck(struct deck_s *deck)
{
    if(deck->current_nb_card == 0)
    {
        fprintf(stdout, "ERROR get_from_deck : deck is already empty");
        return NULL;
    }
    struct card_s *res = deck->cards[deck->current_nb_card-1];
    deck->cards[deck->current_nb_card-1] = NULL;
    deck->current_nb_card--;
    return res;
}

void print_deck(struct deck_s *deck)
{
    printf("+----+----+----+----+----+\n");
    printf("| current Deck           |\n");
    printf("+----+----+----+----+----+\n");
    for (int i = 0; i < 13; i++)
    {
        printf("| ");
        print_card(deck->cards[i]);
        printf(" | ");
        print_card(deck->cards[i+13]);
        printf(" | ");
        print_card(deck->cards[i+26]);
        printf(" | ");
        print_card(deck->cards[i+39]);
        printf(" | ");
        (deck->max_card == 52 || i >= 2)? printf("  ") : print_card(deck->cards[52+i]);
        printf(" |\n");
        printf("+----+----+----+----+----+\n");
    }
    //printf("+---+---+---+---+---+\n");
}


struct hand_s *create_hand()
{
    struct hand_s *res = malloc(sizeof(struct hand_s));
    if (!res)
    {
        return NULL;
    }
    res->cards = calloc(MAX_HAND, sizeof(struct card_s));
    res->current_nb_card = 0;
    return res;
}

void destroy_hand(struct hand_s *hand)
{
    for (int i = 0; i < hand->current_nb_card; i++)
    {
        destroy_card(hand->cards[i]);
    }
    free(hand->cards);
    free(hand);
}

void sort_hand(struct hand_s *hand)
{
    int nb_swap = 1;
    int i = 0;
    while (nb_swap)
    {
        nb_swap = 0;
        for (int j = 0; j < hand->current_nb_card-1; j++)
        {
            //printf("i1 = %d | i2 = %d\n", index, index2);
            if(hand->cards[j]->num < hand->cards[j+1]->num)
            {
                struct card_s *tmp = hand->cards[j];
                hand->cards[j] = hand->cards[j+1];
                hand->cards[j+1] = tmp;
                nb_swap++;
            }
        }
        i++;
    }
}

void add_to_hand(struct hand_s *hand, struct card_s *card)
{
    if(hand->current_nb_card == MAX_HAND)
    {
        fprintf(stdout, "ERROR add_to_hand : hand is already full");
        return ;
    }
    hand->cards[hand->current_nb_card] = card;
    hand->current_nb_card++;
    sort_hand(hand);
}

struct card_s *get_from_hand(struct hand_s *hand, int id)
{
    if(hand->current_nb_card == 0)
    {
        fprintf(stdout, "ERROR get_from_hand : hand is already empty");
        return NULL;
    }
    if(hand->current_nb_card < id)
    {
        fprintf(stdout, "ERROR get_from_hand : this cart doesn't exist");
        return NULL;
    }
    struct card_s *res = hand->cards[id];
    hand->cards[id] = hand->cards[hand->current_nb_card];
    hand->cards[hand->current_nb_card] = NULL;
    hand->current_nb_card--;
    sort_hand(hand);
    return res;
}

void print_hand(struct hand_s *hand)
{
    printf("+----+----+----+----+----+\n");
    printf("| current hand           |\n");
    printf("+----+----+----+----+----+\n");
    printf("| ");
    print_card(hand->cards[0]);
    printf(" | ");
    print_card(hand->cards[1]);
    printf(" | ");
    print_card(hand->cards[2]);
    printf(" | ");
    print_card(hand->cards[3]);
    printf(" | ");
    print_card(hand->cards[4]);
    printf(" |\n");
    printf("+----+----+----+----+----+\n");  
}