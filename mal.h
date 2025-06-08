// mal.h - 말 구조체 및 말 관련 함수 선언

#ifndef MAL_H
#define MAL_H

typedef struct {
    int position;   // 칸 번호 (0 ~ 목표 위치)
    int finished;   // 1: 도착 완료, 0: 이동 중
} Mal;

Mal create_mal(char symbol);

#endif // MAL_H