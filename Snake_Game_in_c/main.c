#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//Snake
#define N 20
#define M 40

int i,j,Field[N][M],x,y,Gy,Head,Tail,Game,Frogs,a,b,var,dir,HighScore,score,Speed;
//create snake

FILE *f;

void snakeIntilization() {
    f=fopen("highscore.txt","r");
    fscanf(f,"%d",&HighScore);
    fclose(f);

    for(i=0;i<N;i++) {
        for(j=0;j<M;j++){
            Field[i][j]=0;
        }
    }
    x=N/2;y=M/2; Gy = y; Head = 5; Tail =1; Game = 0,Frogs = 0,dir='d',HighScore,score =0,Speed = 99;

    for(i=0;i<Head;i++) {
        Gy++;
        Field[x][Gy-Head] = i+1;
    }
}
//create borders
void print(){

    for(i=0;i<=M+1;i++) {
        if(i==0) {
            printf("%c", 201);
        } else if(i==M+1){
            printf("%c",187);
        }else{
            printf("%c",205);
        }
    }
    printf("Current Score: %d HighScore: %d", score,HighScore);
    printf("\n");

    for(i=0;i<N;i++) {
        printf("%c",186);
        for(j=0;j<M;j++){
            if(Field[i][j]==0) printf(" ");
            if(Field[i][j]>0 && Field[i][j]!=Head) printf("%c", 176);
            if(Field[i][j]==Head) printf("%c", 178);
            if(Field[i][j]==-1) printf("%c", 15);
            if(j==M-1) printf("%c\n", 186);
            }
        }
          for(i=0;i<=M+1;i++) {
        if(i==0) {
            printf("%c", 200);
        } else if(i==M+1){
            printf("%c",188);
        }else{
            printf("%c",205);
        }
    }
}
//Random position of frog
Random(){
    srand(time(0));
    a = 1 + rand() % 18;
    b = 1 + rand() % 38;
    if(Frogs == 0 && Field[a][b] == 0) {
        Field[a][b] = -1;
        Frogs = 1;
        if(Speed>10 && score!=0) Speed = Speed - 5;
    }
}

void ResetScreenPosition() {
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);
}

int getch_noblock(){
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void movement() {
    var = getch_noblock();
    var = tolower(var);

    if(((var =='d'||var == 'a')||(var=='s'||var == 'w'))
       &&(abs(dir-var)> 5)) dir = var;
    if(dir == 'd') {
        y++;
        if(Field[x][y] != 0 && Field[x][y]!=-1) GameOver();
        if(y==M-1) y = 0;
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'a') {
        y--;
        if(Field[x][y] != 0 && Field[x][y]!=-1) GameOver();
        if(y==0) y =M-1;
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }if(dir == 'w') {
        x--;
        if(Field[x][y] != 0 && Field[x][y]!=-1) GameOver();
        if(x==-1) x = N-1;
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 's') {
        x++;
        if(Field[x][y] != 0 && Field[x][y]!=-1) GameOver();
        if(x==N-1) x=0;
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }


}

void TailRemove(){
    for(i=0;i<N;i++){
        for(j=0;j<M;j++) {
            if(Field[i][j]==Tail) {
                Field[i][j] = 0;
            }
        }
    }
    Tail++;
}

void GameOver() {
    printf("\a");
    Sleep(1500);
    system("Cls");

    if(score > HighScore){
        printf("  New HighScore: %d !!!\n\n", score);
        system("pause");
        f=fopen("highscore.txt","w");
        fprintf(f,"%d",score);
        fclose(f);

    }
    system("Cls");
    printf("\n\n        GAME OVER!!!!\n");
    printf("            Score: %d \n\n",score);
    printf("             Press ENTER to play again or ESC to exit...\n");
    while(1) {
        var = getch_noblock();
        if(var == 13){
            Game =0;
            snakeIntilization();
            break;
        } else if(var == 27){
            Game = 1;
            break;
        }
    }
    system("Cls");
}

void main()
{
    snakeIntilization();

    while(Game==0) {
        print();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(Speed);
    }

}
