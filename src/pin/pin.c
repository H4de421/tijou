#include "pin.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX_PIN 3


struct pin_s *create_pin(int num, enum color_e color, int pos)
{
    struct pin_s *res = malloc(sizeof(struct pin_s));
    if(!res)
    {
        return NULL;
    }
    res->pos = pos;
    res->color = color;
    res->num = num;
    return res;
}

void destroy_pin(struct pin_s *pin)
{
    free(pin);
}

struct liste_pin *create_list_pin()
{
    struct liste_pin *res = malloc(sizeof(struct liste_pin));
    if (!res)
    {
        return NULL;
    }
    res->nb_pin = 0;
    res->pins = calloc(MAX_PIN, sizeof(struct pin_s));
    return res;
}

void destroy_list_pin(struct liste_pin *liste)
{
    int i = 0;
    while(i<MAX_PIN)
    {
        if (liste->pins[i]!=NULL)
        {
            liste->nb_pin--;
            destroy_pin(liste->pins[i]);
        }
        i++;
    }
    free(liste->pins);
    free(liste);
}

void append_liste_pin(struct liste_pin *liste, struct pin_s* pin)
{
    /*
    if (liste->nb_pin < MAX_PIN)
    {
        liste->pins[liste->nb_pin] = pin;
        liste->nb_pin++;
    }
    */
   int i = 0;
   int ended = 0;
   while (i<MAX_PIN && !ended)
   {
        if(liste->pins[i]==NULL)
        {
            liste->pins[i] = pin;
            liste->nb_pin++;
            ended = 1;
        }
        i++;
   }
   
}

struct pin_s *pop_liste_pin(struct liste_pin *liste)
{
    if (liste->nb_pin)
    {
        struct pin_s *res = liste->pins[liste->nb_pin];
        liste->pins[liste->nb_pin] = NULL;
        liste->nb_pin--;
        return res;
    }
    return NULL;
}

int get_empty_place(struct liste_pin *liste)
{
    int res = 0;
    while (res<MAX_PIN)
    {
        if (liste->pins[res] == NULL)
        {
            return res;
        }
        res++;
    }
    return -1;
}
