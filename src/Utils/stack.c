#include "stack.h"
#include <stdlib.h>
#include <string.h>

void initPerutStack(StackPerut *stack, int capacity) {
    stack->items = malloc(capacity * sizeof(Obat));
    stack->top = -1;
    stack->capacity = capacity;
}

int isPerutFull(StackPerut *stack) {
    return stack->top == stack->capacity - 1;
}

int isPerutEmpty(StackPerut *stack) {
    return stack->top == -1;
}

int pushObat(User *user, int obatId, const char *obatNama) {
    if (isPerutFull(&user->perut)) {
        return 0;
    }

    user->perut.top++;
    user->perut.items[user->perut.top].id = obatId;
    strncpy(user->perut.items[user->perut.top].nama, obatNama, 49);
    user->perut.items[user->perut.top].nama[49] = '\0';

    return 1;
}

int popObat(User *user, Obat *obat) {
    if (isPerutEmpty(&user->perut)) {
        return 0;
    }

    *obat = user->perut.items[user->perut.top];
    user->perut.top--;

    return 1;
}