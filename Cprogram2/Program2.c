#include <stdio.h>

void printScoreCombinations(int score) {
    int i, j, k, l, m;
    for (i = 0; i <= score / 8; i++) {
        for (j = 0; j <= score/ 7; j++) {
            for (k = 0; k <= score/ 6; k++) {
                for (l = 0; l <= score / 3; l++)
                    for (m = 0; m <= score/ 2; m++) {
                        if ((8*i + 7*j + 6*k + 3*l + 2*m) == score) {
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", i, j, k, l, m);
                        }
                }
            }
        }
    }
}

int main() {
    int score;
    do {
        printf("Enter the NFL score: ");
        scanf("%d", &score);
        if (score > 1) {
            printf("Possible combinations of scoring plays:\n");
            printScoreCombinations(score);
        }
    } while (score > 1);

    printf("Program terminated.\n");
    return 0;
}
