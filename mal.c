// mal.c - 말 관련 기능 구현

#include "mal.h"

Mal create_mal(char symbol) {
    Mal m;
    m.position = 0;
    m.finished = 0;
    return m;
}