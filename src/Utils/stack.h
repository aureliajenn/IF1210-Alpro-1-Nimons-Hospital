#ifndef STACK_H
#define STACK_H

#include "../../Model/model.h"

void initPerutStack(StackPerut *stack, int capacity);
int isPerutFull(StackPerut *stack);
int isPerutEmpty(StackPerut *stack);
int pushToPerut(User *user, int obatId, const char *obatNama);
int popFromPerut(User *user, Obat *obat);

#endif