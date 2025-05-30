#include "main.h"

void initPerutStack(StackPerut *stack, int capacity) {
    stack->items = malloc(capacity * sizeof(Obat));
    stack->top = -1;
    stack->capacity = capacity;
}

boolean isPerutFull(StackPerut *stack) {
    return (stack->top == stack->capacity - 1);
}

boolean isPerutEmpty(StackPerut *stack) {
    return (stack->top == -1);
}

int pushObat(User *user, int obatId, const char *obatNama) {
    if (isPerutFull(&user->kondisi.perut)) {
        return 0;
    }

    user->kondisi.perut.top++;
    user->kondisi.perut.items[user->kondisi.perut.top].id = obatId;
    strncpy(user->kondisi.perut.items[user->kondisi.perut.top].nama, obatNama, 49);
    user->kondisi.perut.items[user->kondisi.perut.top].nama[49] = '\0';

    return 1;
}

int popObat(User *user, Obat *obat) {
    if (isPerutEmpty(&user->kondisi.perut)) {
        return 0;
    }

    *obat = user->kondisi.perut.items[user->kondisi.perut.top];
    user->kondisi.perut.top--;

    return 1;
}