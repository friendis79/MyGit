// 원소의 논리적 & 물리적 순서 확인하기
/* # include <stdio.h>

int main (){
    int i, sale[4] = {157, 209, 251, 312};

    for (i = 0; i < 4; i++){
        printf("\n adress : %u sale[%d] = %d", &sale[i], i, sale[i]);
    }

    printf("\n");

    return 0;
} */

// 2차원 배열의 논리적 & 물리적 순서 확인하기
/* # include <stdio.h>

int main (){
    int i, n = 0, *ptr;
    int sale[2][4] = {{63, 84, 140, 130}, {157, 209, 251, 312}};

    ptr = &sale[0][0];
    for (i = 0; i < 8; i++){
        printf("\n adress : %u sale %d = %d", ptr, i, *ptr);
        ptr++;
    }

    printf("\n");

    return 0;
} */

// 3차원 배열의 논리적 & 물리적 순서 확인하기
/* #include <stdio.h>

int main(){
    int i, n =0, *ptr;
    int sale[2][2][4] = {{{63, 84, 140, 130},
                         {157, 209, 251, 312},
                         {59, 80, 130, 135},
                         {149, 187, 239, 310}}};
    
    ptr = &sale[0][0][0];   // 3차원 배열을 포인터에 설정

    for (i = 0; i < 16; i++){
        printf("\n adress : %u sale %2d = %3d", ptr, i, *ptr);
        ptr++;
    }

    printf("\n");

    return 0;
} */

// 선형 리스트의 원소 삽입
/* #include <stdio.h>

void insertElement(int L[], int *n, int x) {
    int i, k;
    
    for (i = 0; i < *n; i++) {
        if (L[i] <= x && x <= L[i+1]) {
            k = i + 1;
            break;
        }
    }
    
    if (i == *n)
        k = *n;

    for (i = *n; i > k; i--) {
        L[i] = L[i - 1];
    }

    L[k] = x;
    (*n)++;
}

int main() {
    int L[] = {10, 20, 30, 40, 50};
    int n = 5; // 현재 리스트의 길이
    int x = 25; // 삽입할 원소

    printf("Before insertion:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");

    insertElement(L, &n, x);

    printf("After insertion:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");

    return 0;
} */

// 선형 리스트의 원소 삭제
/* #include <stdio.h>

void deleteElement(int L[], int *n, int x) {
    int i, k;
    
    for (i = 0; i < *n; i++) {
        if (L[i] == x) {
            k = i;
            break;
        }
    }
    
    if (i == *n)
        return; // 리스트에 삭제할 원소가 없는 경우 함수 종료

    for (i = k; i < *n - 1; i++) {
        L[i] = L[i + 1];
    }

    (*n)--;
}

int main() {
    int L[] = {10, 20, 30, 40, 50};
    int n = 5; // 현재 리스트의 길이
    int x = 30; // 삭제할 원소

    printf("Before deletion:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");

    deleteElement(L, &n, x);

    printf("After deletion:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");

    return 0;
} */





