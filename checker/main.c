//  Raduta Alexandru - 315CB
#include <stdio.h>
#include <stdlib.h>

// functie pe care o voi folosii pentru a afisa o matrice de n pe m
void matrixWrite(int** mat, int n, int m) {
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// functie pe care o voi folosii pentru a aloca o matrice
int** matrixRead(int n, int m) {
    int** mat = malloc(n * sizeof(int*));
    if (mat == NULL) {
        return NULL;
    }
    for ( int i = 0; i < n; i++ ) {
        mat[i] = malloc(m * sizeof(int));
        if (mat[i] == NULL) {
            for ( int j = 0; j < i; j++ ) {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }
    }
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            scanf("%d", &mat[i][j]);
        }
    }
    return mat;
}

// functie pe care o voi folosii pentru a elibera o matrice
void matrixFree(int** mat, int n, int m) {
    for ( int i = 0; i < n; i++ ) {
        free(mat[i]);
    }
    free(mat);
}

// functie pentru a rotii coloana columnNumber cu positionShift pozitii
int** columnShifting(int** mat, int n, int columnNumber, int positionShift) {
    // creez o copie a coloanei care trebuie rotita
    int* originalColumn = malloc(n * sizeof(int));
    if (originalColumn == NULL) {
        exit(1);
    }
    for ( int i = 0; i < n; i++ ) {
        originalColumn[i] = mat[i][columnNumber];
    }
    // trunchiez positionShift, deoarece kn rotiri inseamna 0 rotiri, oricare k
    positionShift = positionShift % n;
    // observ ca fiecare element devine
    // nr linii + pozitia lui - numarul de pozitii rotite, totul mod n
    for ( int i = 0; i < n; i++ ) {
        mat[i][columnNumber] = originalColumn[(n + i - positionShift) % n];
    }
    // eliberez vectorul folosit pentru salvarea coloanei originala
    free(originalColumn);
    return mat;
}

// functie pentru a afisa scorul unei matrice
int* calculatePanelScore(int** mat, int m) {
    // declar n, care in cazul cadranului este mereu 3
    // si imi declar un vector unde memorez numarul de combinatii si scorul
    int n = 3;
    int* comboNrAndScore = calloc(2, 2 * sizeof(int));
    if (comboNrAndScore == NULL) {
        return NULL;
    }
    // calculez scorul pentru conditia de linii
    for ( int i = 0; i < n; i++ ) {
        // salvez intr-o variabila numarul maxim de simboluri identice
        // dintr-o linie si mai fac 2 variabile pentru verificare de 7
        int maxOfLineTotal = 1;
        int sevenChecker = 0;
        char isSeven = 0;
        for ( int j = 0; j < m - 2; j++ ) {
            // salvez intr-o variabila numarul maxim de
            // simboluri identice incepand cu j
            int lineTotalFromJ = 1;
            int sevenChecker = 0;
            // parcurg linia sa vad cate elemente identice am de la j incolo
            for ( int k = j; k < m - 1; k++ ) {
                sevenChecker = mat[i][k];
                if (mat[i][k] == mat[i][k+1]) {
                    lineTotalFromJ++;
                } else {
                    break;
                }
            }
            // daca este mai mare decat maximul, inlocuiesc maximul
            // si aici verific si daca momentan cea mai lunga secventa este 7
            if (lineTotalFromJ > maxOfLineTotal) {
                maxOfLineTotal = lineTotalFromJ;
                if (7 == sevenChecker) {
                    isSeven = 1;
                } else {
                    isSeven = 0;
                }
            }
        }
        // verific ca maximul sa fie cel putin 3 si daca
        // sirul de elemente este format din 7
        if (maxOfLineTotal > 2) {
            if (isSeven) {
                comboNrAndScore[1] += 2 * maxOfLineTotal;
                comboNrAndScore[0]++;
            } else {
                comboNrAndScore[1] += maxOfLineTotal;
                comboNrAndScore[0]++;
            }
        }
    }
    // calculez scorul pentru conditia de diagonale
    for ( int i = 1; i < m - 1; i++ ) {
        // verific daca este un x
        if (mat[1][i] == mat[0][i - 1] && mat[1][i] == mat[0][i+1] &&
            mat[1][i] == mat[2][i-1] && mat[1][i] == mat[2][i + 1]) {
            // verific daca este 7
            if (mat[1][i] == 7) {
                comboNrAndScore[1] += 42;
                comboNrAndScore[0]++;
            } else {
                comboNrAndScore[1] += 21;
                comboNrAndScore[0]++;
            }
            //  verific daca este o diagonala principala sau secundara
        } else if ( (mat[1][i] == mat[0][i-1] && mat[1][i] == mat[2][i+1]) ||
        (mat[1][i] == mat[0][i+1] && mat[1][i] == mat[2][i-1]) ) {
            // verific daca este 7
            if (mat[1][i] == 7) {
                comboNrAndScore[1] += 14;
                comboNrAndScore[0]++;
            } else {
                comboNrAndScore[1] += 7;
                comboNrAndScore[0]++;
            }
        }
    }
    // salvez intr-o variabila cate elemente unice am gasit pana acum
    // si aflu asta folosind un vector de 10 elemente, initiat cu 0,
    // elementul i al vectorului devenind 1 daca i este gasit
    // la fiecare element al matricii, verific daca este gasit, si daca nu
    // este gasit actualizez vectorul si incrementez numarul elementelor unice
    int nrOfUniqueElements = 0;
    int* elementsThatAppeared = calloc(10, sizeof(int));
    if (elementsThatAppeared == NULL) {
        return NULL;
    }
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            if (elementsThatAppeared[mat[i][j]] == 0) {
                elementsThatAppeared[mat[i][j]] = 1;
                nrOfUniqueElements++;
            }
        }
    }
    if (nrOfUniqueElements < 3) {
        comboNrAndScore[1] += 100;
    } else if (nrOfUniqueElements < 5) {
        comboNrAndScore[1] += 15;
    }
    free(elementsThatAppeared);
    return comboNrAndScore;
}

int task1() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int** mat = matrixRead(n, m);
    if (mat == NULL) {
        exit(1);
    }
    int columnNumber = 0, positionShift = 0;
    scanf("%d%d", &columnNumber, &positionShift);
    mat = columnShifting(mat, n, columnNumber, positionShift);
    matrixWrite(mat, n, m);
    matrixFree(mat, n, m);
    return 0;
}

int task2() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int** mat = matrixRead(n, m);
    if (mat == NULL) {
        exit(1);
    }
    int* comboNrAndScore = calculatePanelScore(mat, m);
    if (comboNrAndScore == NULL) {
        exit(1);
    }
    printf("%d\n%d\n", comboNrAndScore[0], comboNrAndScore[1]);
    free(comboNrAndScore);
    matrixFree(mat, n, m);
    return 0;
}

int task3() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int** mat = matrixRead(n, m);
    if (mat == NULL) {
        exit(1);
    }
    int t = 0;
    scanf("%d", &t);
    int totalScore = 0;
    int columnNumber = 0, positionShift = 0;
    for ( int i = 0; i < t; i++ ) {
        scanf("%d%d", &columnNumber, &positionShift);
        mat = columnShifting(mat, n, columnNumber, positionShift);
        int *comboNrAndScore = calculatePanelScore(mat, m);
        if (comboNrAndScore == NULL) {
            exit(1);
        }
        totalScore += comboNrAndScore[1];
        free(comboNrAndScore);
    }
    matrixFree(mat, n, m);
    printf("%d\n", totalScore);
    return 0;
}

int task4() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int** mat = matrixRead(n, m);
    if (mat == NULL) {
        exit(1);
    }
    // creez o varibila care sa retina scorul maxim pana acum
    int maxScore = 0;
    // trec prin fiecare pozitie a cadranului
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < m; j++ ) {
            // salvez valoarea originala a celulei si dupa trec prin fiecare
            // simbol posibil si verific daca scorul rezultat
            // ar fii mai mare decat maxim
            int realValue = mat[i][j];
            for ( int k = 0; k < 10; k++ ) {
                mat[i][j] = k;
                int* comboNrAndScore = calculatePanelScore(mat, m);
                if (comboNrAndScore == NULL) {
                    exit(1);
                }
                if (maxScore < comboNrAndScore[1]) {
                    maxScore = comboNrAndScore[1];
                }
                free(comboNrAndScore);
            }
            // redau celulei valoare originala
            mat[i][j] = realValue;
        }
    }
    matrixFree(mat, n, m);
    printf("%d\n", maxScore);
    return 0;
}

int task5() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int** mat = matrixRead(n, m);
    if (mat == NULL) {
        exit(1);
    }
    // creez o variabila care sa retina scorul maxim pana acum
    int maxScore = 0;
    // trec prin fiecare combinatie de doua coloane si
    // nr de rotire a fiecarei coloane
    for ( int i = 0; i < m - 1; i++ ) {
        for ( int j = i + 1; j < m; j++ ) {
            for ( int k = 1; k <= n; k++ ) {
                for ( int l = 1; l <= n; l++ ) {
                    mat = columnShifting(mat, n, j, 1);
                    int* comboNrAndScore = calculatePanelScore(mat, m);
                    if (comboNrAndScore == NULL) {
                        exit(1);
                    }
                    if (maxScore < comboNrAndScore[1]) {
                        maxScore = comboNrAndScore[1];
                    }
                    free(comboNrAndScore);
                }
                mat = columnShifting(mat, n, i, 1);
            }
        }
    }
    matrixFree(mat, n, m);
    printf("%d\n", maxScore);
    return 0;
}

int main() {
    int nrTask = 0;
    scanf("%d", &nrTask);
    switch (nrTask) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
    }
    return 0;
}
