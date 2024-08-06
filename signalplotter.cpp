//SIGNAL PLOTTER
#include <stdio.h>
#include <graphics.h>
#include <conio.h>  // For getch()

#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
//global variables are declared here
int gd = 5, gm;
int pos_x = 100, pos_y = 200;
//get input from keyboard
void getSignal(char *signal) {
    printf("Enter signal to be encoded: ");
    scanf("%s", signal);
}
// choose anyone to encode the given signal

int getEncoding() {
    int choice;
    printf("Choose a type of Encoding\n");
    printf("1) Unipolar NRZ\n");
    printf("2) Polar NRZ\n");
    printf("3) NRZ Inverted\n");
    printf("4) Bipolar\n");
    printf("5) RZ\n");
    printf("6) Manchester\n");
    printf("7) Differential Manchester\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}
// for moving the signal
void signalMove(int offset_x, int offset_y) {
    line(pos_x, pos_y, pos_x + offset_x, pos_y + offset_y);
    pos_x = pos_x + offset_x;
    pos_y = pos_y + offset_y;
    }
// for shifting the signals
void signalShift(int new_x, int new_y) {
    line(pos_x, pos_y, new_x, new_y);
    pos_x = new_x;
    pos_y = new_y;
}
// for drawing the x y axis
void drawAxes() {
    line(0, pos_y, 1000, pos_y);
    line(pos_x, 0, pos_x, 500);
}
// initialization of graphics.h
void initGraph() {
    int height =GetSystemMetrics(SM_CYSCREEN);
    int width =GetSystemMetrics(SM_CXSCREEN);
    initwindow(width,height,"Windows BGI");
    //initgraph(&gd, &gm,(char*) "");
    drawAxes();
    setcolor(YELLOW);
}
//Unipolar-NRZ
void drawUnipolarNRZ(char *signal) {
    int logic_high = -80;
    int logic_low = 0;
    int distance = 80;
    int i;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1')
            signalShift(pos_x, 200 + logic_low);
        else
            signalShift(pos_x, 200 + logic_high);
        signalMove(distance, 0);
    }
}
//polar NRZ
void drawPolarNRZ(char *signal) {
    int logic_high = -80;
    int logic_low = 80;
    int distance = 80;
    int i;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1')
            signalShift(pos_x, 200 + logic_low);
        else
            signalShift(pos_x, 200 + logic_high);
        signalMove(distance, 0);
    }
}
//NRZ-l
void drawNRZI(char *signal) {
    int logic_high = -80;
    int logic_low = 80;
    int distance =80;
    int i;
    pos_y = 200 + logic_high;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1')
            signalShift(pos_x, 200 + logic_low);
        else {
            if (pos_y == 200 + logic_low)
                signalShift(pos_x, 200 + logic_high);
            else if (pos_y == 200 + logic_high)
                signalShift(pos_x, 200 + logic_low);
        }
        signalMove(distance, 0);
    }
}
//RZ
void drawRZ(char *signal) {
    int logic_high = -80;
    int logic_low = 80;
    int base = 0;
    int distance = 80;
    int i;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1') {
            signalShift(pos_x, 200 + logic_low);
            signalMove(distance, 0);
            signalShift(pos_x, 200 + base);
            signalMove(distance, 0);
        } else {
            signalShift(pos_x, 200 + logic_high);
            signalMove(distance, 0);
            signalShift(pos_x, 200 + base);
            signalMove(distance, 0);
        }
    }
}
//Bipolar
void drawBipolar(char *signal) {
    int logic_high = -80;
    int logic_low = 80;
    int base = 0;
    int distance = 80;
    int i;
    int prev = 0;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1') {
            if (prev == 0) {
                signalShift(pos_x, 200 + (logic_high / 2));
                signalMove(distance, 0);
            } else {
                signalShift(pos_x, 200 + (logic_low / 2));
                signalMove(distance, 0);
            }
            prev = prev == 0 ? 1 : 0;
        } else {
            signalShift(pos_x, 200 + base);
            signalMove(distance, 0);
        }
    }
}
//Manchester
void drawManchester(char *signal) {
    int logic_high = -80;
    int logic_low = 80;
    int distance = 80;
    int i;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1') {
            signalShift(pos_x, 200 + logic_low);
            signalMove(distance, 0);
            signalShift(pos_x, 200 + logic_high);
            signalMove(distance, 0);
        } else {
            signalShift(pos_x, 200 + logic_high);
            signalMove(distance, 0);
            signalShift(pos_x, 200 + logic_low);
            signalMove(distance, 0);
        }
    }
}
//Differential Manchester
void drawDiffManchester(char *signal) {
    int logic_high = -80;
    int logic_low = 80;
    int distance = 80;
    int i;
    int prev = 2;
    for (i = 0; signal[i] != '\0'; i++) {
        if (signal[i] == '1') {
            int n = (prev == 2 ? 1 : 2);
            if (n == 2) {
                signalShift(pos_x, 200 + logic_low);
                signalMove(distance, 0);
                signalShift(pos_x, 200 + logic_high);
                signalMove(distance, 0);
            } else if (n == 1) {
                signalShift(pos_x, 200 + logic_high);
                signalMove(distance, 0);
                signalShift(pos_x, 200 + logic_low);
                signalMove(distance, 0);
            }
            prev = n;
        } else {
            if (prev == 2) {
                signalShift(pos_x, 200 + logic_low);
                signalMove(distance, 0);
                signalShift(pos_x, 200 + logic_high);
                signalMove(distance, 0);
            } else if (prev == 1) {
                signalShift(pos_x, 200 + logic_high);
                signalMove(distance, 0);
                signalShift(pos_x, 200 + logic_low);
                signalMove(distance, 0);
            }
        }
    }
}

int main() {
    char sgn[100];
    int c;
    getSignal(sgn);
    c = getEncoding();
    initGraph();
    switch (c) {
        case 1:
            drawUnipolarNRZ(sgn);
            break;
        case 2:
            drawPolarNRZ(sgn);
            break;
        case 3:
            drawNRZI(sgn);
            break;
        case 4:
            drawBipolar(sgn);
            break;
        case 5:
            drawRZ(sgn);
            break;
        case 6:
            drawManchester(sgn);
            break;
        case 7:
            drawDiffManchester(sgn);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    getch();
    closegraph();
    return 0;
}
