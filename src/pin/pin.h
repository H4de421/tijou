#ifndef PIN_H
#define PIN_H

#include "../color/color.h"

struct pin_s
{
    int num;
    int pos;
    enum color_e color;
};

struct liste_pin
{
    struct pin_s **pins;
    int nb_pin;
};

struct pin_s *create_pin(int num, enum color_e color, int pos);
void destroy_pin(struct pin_s *pin);

struct liste_pin *create_list_pin();
void destroy_list_pin(struct liste_pin *liste);

void append_liste_pin(struct liste_pin *liste, struct pin_s* pin);
struct pin_s *pop_liste_pin(struct liste_pin *liste);

int get_empty_place(struct liste_pin *liste);

#endif /*!PIN_H*/