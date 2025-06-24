#include <stdio.h>

typedef struct {
    int x, y;
} Point;

void finder(Point A, Point B, Point C, Point D){
    long long s = (long long)(A.x - B.x) * (C.y - D.y) - (long long)(A.y - B.y) * (C.x - D.x);
    long long sx = ((long long)A.x * B.y - (long long)A.y * B.x) * (C.x - D.x) - ((long long)A.x - B.x) * ((long long)C.x * D.y - (long long)C.y * D.x);
    long long sy = ((long long)A.x * B.y - (long long)A.y * B.x) * (C.y - D.y) - ((long long)A.y - B.y) * ((long long)C.x * D.y - (long long)C.y * D.x);
    double x = (double)sx/s;
    double y = (double)sy/s;
    printf("1\n");
    printf("%.10lf %.10lf", x, y);
}

int ccw(Point A, Point B, Point C){
    long long res = ((long long)A.x)*B.y + ((long long)B.x)*C.y + ((long long)C.x)*A.y - ((long long)A.y)*B.x - ((long long)B.y)*C.x - ((long long)C.y)*A.x;
    if(res > 0) return 1;
    else if(res < 0) return -1;
    else return 0;
}

void check(Point A, Point B, Point C, Point D){
    int abc = ccw(A, B, C);
    int abd = ccw(A, B, D);
    int cda = ccw(C, D, A);
    int cdb = ccw(C, D, B);

    int ccw1_product = abc * abd;
    int ccw2_product = cda * cdb;

    if (abc == 0 && abd == 0 && cda == 0 && cdb == 0) {
        int min_ax = A.x < B.x ? A.x : B.x;
        int max_ax = A.x > B.x ? A.x : B.x;
        int min_ay = A.y < B.y ? A.y : B.y;
        int max_ay = A.y > B.y ? A.y : B.y;

        int min_cx = C.x < D.x ? C.x : D.x;
        int max_cx = C.x > D.x ? C.x : D.x;
        int min_cy = C.y < D.y ? C.y : D.y;
        int max_cy = C.y > D.y ? C.y : D.y;

        int overlap_max_x = max_ax < max_cx ? max_ax : max_cx;
        int overlap_min_x = min_ax > min_cx ? min_ax : min_cx;
        int overlap_max_y = max_ay < max_cy ? max_ay : max_cy;
        int overlap_min_y = min_ay > min_cy ? min_ay : min_cy;

        if (overlap_min_x > overlap_max_x || overlap_min_y > overlap_max_y) {
            printf("0\n");
        } else {
            printf("1\n");
            if (overlap_min_x == overlap_max_x && overlap_min_y == overlap_max_y) {
                printf("%.10lf %.10lf\n", (double)overlap_min_x, (double)overlap_min_y);
            }
        }
    }
    else if (ccw1_product <= 0 && ccw2_product <= 0) {
        finder(A, B, C, D);
    }
    else {
        printf("0\n");
    }
}


int main(){
    Point A,B,C,D;

    scanf("%d %d %d %d",&A.x,&A.y,&B.x,&B.y);
    scanf("%d %d %d %d",&C.x,&C.y,&D.x,&D.y);

    check(A,B,C,D);


    return 0;
}