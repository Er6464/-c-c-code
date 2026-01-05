#include <stdio.h>

int main() {
    int start, end;
    int i, j;

    printf("ใส่แม่เริ่มต้น: ");
    scanf("%d", &start);

    printf("ใส่แม่สุดท้าย: ");
    scanf("%d", &end);

    for (i = start; i <= end; i++) {
        printf("แม่ %d\n", i);
        for (j = 1; j <= 12; j++) {
            printf("%d x %d = %d\n", i, j, i * j);
        }
        printf("\n");
    }
    printf("พัชรพล ");
    return 0;
}
