// 3���� �迭�� �̿��� ���� �迭 ������ϱ�
/* #include <stdio.h>
int main() {
    int i, j, k;
    char student[2][3][20]; // 3-dimensional array

    for (i = 0; i < 2; i++) {
        printf("\n �л� %d�� �̸� : ", i + 1);
        fgets(student[i][0], sizeof(student[i][0]), stdin);
        printf("\n �л� %d�� �а� : ", i + 1);
        fgets(student[i][1], sizeof(student[i][1]), stdin);
        printf("\n �л� %d�� �й� : ", i + 1);
        fgets(student[i][2], sizeof(student[i][2]), stdin);
    }

    for (i = 0; i < 2; i++) {
        printf("\n\n �л� %d : ", i + 1);
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

// ������ �����ڸ� �̿��� ���� �׼����ϱ�
/* #include <stdio.h>
int main(){
    int i = 10, j = 20;
    int* ptr;
    printf("\n i�� �� = %d \n j�� �� = %d", i, j);
    printf("\n i�� �޸� �ּ� (&i) = &u", &i);
    printf("\n j�� �޸� �ּ� (&j) = &u", &j);

    printf("\n========================================================================================");

    ptr = &j;
    printf("\n ptr�� �޸� �ּ� (&ptr) = %%u", &ptr);
    printf("\n ptr�� �� (ptr) = %u", ptr);
    printf("\n ptr�� ������ (*ptr) = %d", *ptr);

    printf("\n========================================================================================");

    i = *ptr;
    printf("\n <<i=*ptr ����>>");
    printf("\n i�� �� = %d", i);

    getchar();
} */

// �����͸� �̿��� ���ڿ� ó���ϱ�
/* #include <stdio.h>
int main(){
    int i;
    char string1[20] = "Dreams come true!", string2[20], *ptr1, *ptr2;

    ptr1 = string1;
    printf("\n string1�� �ּ� = %u \t ptr1 = %u", string1, ptr1);
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

// ������ �迭�� �̿��� ���ڿ� �����ϱ�
/* #include <stdio.h>
int main(){
    int i;
    char* ptrArray[4] = {{"Korea"}, {"Seoul"}, {"Mapo"}, {"152���� 2/3"}};
    for (i = 0; i < 4; i++)
        printf("\n %s", ptrArray[i]);

    ptrArray[2] ="Jongno";

    printf("\n\n");
    for (i = 0; i < 4; i++)
        printf("\n %s", ptrArray[i]);

    getchar();

    return 0;
} */

// �� �����ڸ� �̿��� ������ �׸� �����ϱ�
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
        {"����ȣ", 2022, 4200},
        {"���ѿ�", 2023, 3300},
        {"�̻��", 2024, 3500},
        {"�̻��", 2025, 2900},
    };

    for(i = 0; i < 4; i++){
        printf("\n �̸� : %s", Lee[i].name);
        printf("\n �Ի� : %d", Lee[i].year);
        printf("\n ���� : %d \n", Lee[i].pay);
    }
    getchar();
} */

// ȭ��ǥ �����ڸ� �̿��� ������ �׸� �����ϱ�
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
    strcpy(Sptr->name, "�̼���");
    Sptr->year = 2023;
    Sptr->pay = 5900;
    printf("\n �̸� : %s", Sptr -> name);
    printf("\n �Ի� : %d", Sptr -> year);
    printf("\n ���� : %d", Sptr -> pay);

    getchar();

    return 0;
} */

// ���ȣ���� �̿��� ���丮�� �� ���ϱ�
/* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

long int fact(int);

int main(){
    int n, result;
    printf("\n ������ �Է��ϼ��� : ");
    scanf("%d", &n);
    result = fact(n);
    printf("\n\n %d�� ���丮�� ���� %d�Դϴ�. \n", n, result);
    getchar(); getchar();

    return 0;
}

long int fact(int n){
    int value;
    if (n <= 1){
        printf("\n fact(1) �Լ� ȣ��!");
        printf("\n fact(1) �� 1 ��ȯ!");
        return 1;
    }
    else {
        printf("\n fact(%d) �Լ� ȣ��!", n);
        value = (n * fact(n-1));
        printf("\n fact(%d) �� %d ��ȯ!", n, value);
        return value;
    }
} */

//���ȣ���� �̿��� �ϳ��� ž ���� Ǯ��
/* #include <stdio.h>

void hanoi (int n, int start, int work, int target);
int main() {
    hanoi(3, 'A', 'B', 'C');

    getchar();

    return 0;
}

void hanoi (int n, int start, int work, int target){
    if (n==1)
        printf("%c���� ���� %d��(��) %c�� �ű� \n", start, n, target);
    
    else {
        hanoi(n-1, start, target, work);
        printf("%c���� ���� %d��(��) %c�� �ű� \n", start, n, target);
        hanoi(n-1, work, start, target);
    }
} */

