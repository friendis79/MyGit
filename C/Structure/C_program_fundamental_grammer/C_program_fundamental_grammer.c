// 3차원 배열을 이용한 문자 배열 입출력하기
/* #include <stdio.h>
int main() {
    int i, j, k;
    char student[2][3][20]; // 3-dimensional array

    for (i = 0; i < 2; i++) {
        printf("\n 학생 %d의 이름 : ", i + 1);
        fgets(student[i][0], sizeof(student[i][0]), stdin);
        printf("\n 학생 %d의 학과 : ", i + 1);
        fgets(student[i][1], sizeof(student[i][1]), stdin);
        printf("\n 학생 %d의 학번 : ", i + 1);
        fgets(student[i][2], sizeof(student[i][2]), stdin);
    }

    for (i = 0; i < 2; i++) {
        printf("\n\n 학생 %d : ", i + 1);
        for (j = 0; j < 3; j++) {
            printf("\n\t");
            for (k = 0; student[i][j][k] != '\0'; k++) {
                printf("%c", student[i][j][k]);
            }
        }
    }

    getchar();

    return 0;
} */

// 포인터 연산자를 이용한 변수 액세스하기
/* #include <stdio.h>
int main(){
    int i = 10, j = 20;
    int* ptr;
    printf("\n i의 값 = %d \n j의 값 = %d", i, j);
    printf("\n i의 메모리 주소 (&i) = &u", &i);
    printf("\n j의 메모리 주소 (&j) = &u", &j);

    printf("\n========================================================================================");

    ptr = &j;
    printf("\n ptr의 메모리 주소 (&ptr) = %%u", &ptr);
    printf("\n ptr의 값 (ptr) = %u", ptr);
    printf("\n ptr의 참조값 (*ptr) = %d", *ptr);

    printf("\n========================================================================================");

    i = *ptr;
    printf("\n <<i=*ptr 실행>>");
    printf("\n i의 값 = %d", i);

    getchar();
} */

// 포인터를 이용한 문자열 처리하기
/* #include <stdio.h>
int main(){
    int i;
    char string1[20] = "Dreams come true!", string2[20], *ptr1, *ptr2;

    ptr1 = string1;
    printf("\n string1의 주소 = %u \t ptr1 = %u", string1, ptr1);
    printf("\n string1 = %s \n ptr1 = %s", string1, ptr1);
    printf("\n\n %s", ptr1 + 7);
    ptr2 = &string1[7];
    printf("\n %s \n\n", ptr2);

    for (i = 16; i >= 0; i--){
        putchar(*(ptr1+i));
    }
    for (i = 0; i < 20; i++){
        string2[i] = *(ptr1 + i);
    }

    printf("\n\n string1 = %s", string1);
    printf("\n string2 = %s", string2);

    *ptr1 = 'P';
    *(ptr1 + 1) = 'e';
    *(ptr1 + 2) = 'a';
    *(ptr1 + 3) = 'c';
    *(ptr1 + 4) = 'e';
    printf("\n\n string1 = %s \n", string1);

    return 0;
} */

// 포인터 배열을 이용한 문자열 저장하기
/* #include <stdio.h>
int main(){
    int i;
    char* ptrArray[4] = {{"Korea"}, {"Seoul"}, {"Mapo"}, {"152번지 2/3"}};
    for (i = 0; i < 4; i++)
        printf("\n %s", ptrArray[i]);

    ptrArray[2] ="Jongno";

    printf("\n\n");
    for (i = 0; i < 4; i++)
        printf("\n %s", ptrArray[i]);

    getchar();

    return 0;
} */

// 점 연산자를 이용한 데이터 항목 참조하기
/* #include <stdio.h>
#include <string.h>

struct employee{
    char name[10];
    int year;
    int pay;
};

int main() {
    int i;
    struct employee Lee[4] = {
        {"이진호", 2022, 4200},
        {"이한영", 2023, 3300},
        {"이상원", 2024, 3500},
        {"이상범", 2025, 2900},
    };

    for(i = 0; i < 4; i++){
        printf("\n 이름 : %s", Lee[i].name);
        printf("\n 입사 : %d", Lee[i].year);
        printf("\n 연봉 : %d \n", Lee[i].pay);
    }
    getchar();
} */

// 화살표 연산자를 이용한 데이터 항목 참조하기
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct employee {
    char name[10];
    int year;
    int pay;
};

int main(){
    struct employee Lee;
    struct employee *Sptr = &Lee;
    strcpy(Sptr->name, "이순신");
    Sptr->year = 2023;
    Sptr->pay = 5900;
    printf("\n 이름 : %s", Sptr -> name);
    printf("\n 입사 : %d", Sptr -> year);
    printf("\n 연봉 : %d", Sptr -> pay);

    getchar();

    return 0;
} */

// 재귀호출을 이용한 팩토리얼 값 구하기
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

long int fact(int);

int main(){
    int n, result;
    printf("\n 정수를 입력하세요 : ");
    scanf("%d", &n);
    result = fact(n);
    printf("\n\n %d의 팩토리얼 값은 %d입니다. \n", n, result);
    getchar(); getchar();

    return 0;
}

long int fact(int n){
    int value;
    if (n <= 1){
        printf("\n fact(1) 함수 호출!");
        printf("\n fact(1) 값 1 반환!");
        return 1;
    }
    else {
        printf("\n fact(%d) 함수 호출!", n);
        value = (n * fact(n-1));
        printf("\n fact(%d) 값 %d 반환!", n, value);
        return value;
    }
} */

//재귀호출을 이용해 하노이 탑 퍼즐 풀기
/* #include <stdio.h>

void hanoi (int n, int start, int work, int target);
int main() {
    hanoi(3, 'A', 'B', 'C');

    getchar();

    return 0;
}

void hanoi (int n, int start, int work, int target){
    if (n==1)
        printf("%c에서 원반 %d를(을) %c로 옮김 \n", start, n, target);
    
    else {
        hanoi(n-1, start, target, work);
        printf("%c에서 원반 %d를(을) %c로 옮김 \n", start, n, target);
        hanoi(n-1, work, start, target);
    }
} */

