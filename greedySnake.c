#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define High 20
#define Width 30
int canvas[High][Width]={0};
void moveSnakeByDirection();
int  food_x,food_y;
int goods_x,goods_y;
int life;
void updateWithoutlnput();
void updateWithlnput();
void gotoxy(int x,int y);
void startup();
void show();
int main()
{
    startup();
    while(1)
    {
        show();
        updateWithoutlnput();
        updateWithlnput();
    }
    return 0;
}




void updateWithoutlnput()
{
    static int waitIndex=1;
    waitIndex++;
    if(waitIndex==10000){
    moveSnakeByDirection(0);
    waitIndex=1;
    }
}
void updateWithlnput()
{
    char input;
    if(kbhit())
    {
        input=getch();
        int moveDirection;
        if(input=='w'){
            moveDirection=1;
        }else if(input=='s'){
            moveDirection=2;
        }else if(input=='a'){
            moveDirection=3;
        }else{moveDirection=4;}
        moveSnakeByDirection(moveDirection);

    }
}
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}
void startup()
{
    int i,j;
    life=1;
    for (i=0;i<High;i++)
    {
        canvas[i][0]=-1;
        canvas[i][Width-1]=-1;
    }
    for(j=0;j<Width;j++)
    {
        canvas[0][j]=-1;
        canvas[High-1][j]=-1;
        
    }
    canvas[High/2][Width/2]=1;
    for(i=1;i<=4;i++)
    {
        canvas[High/2][Width/2-i]=i+1;
    }
    food_x=rand()%(High-5)+2;
    food_y=rand()%(Width-5)+2;
    canvas[food_x][food_y]=-2;
    goods_x=rand()%(High-5)+3;
    goods_y=rand()%(Width-5)+3;
    canvas[goods_x][goods_y]=-3;
}
void show()
{
    int i,j;
    gotoxy(0,0);
    for(i=0;i<High;i++)
    {
        for(j=0;j<Width;j++)
        {
            if(canvas[i][j]==0)
            {
                printf(" ");
            }
            else if(canvas[i][j]==-1)
            {
                printf("#");
            }
            else if(canvas[i][j]==-2)
            {
                printf("F");
            }
            else if(canvas[i][j]==1){
                printf("@");
            }else if(canvas[i][j]==-3)
            {printf("G");}else{printf("*");}
            if(j==29){printf("\n");}
        }
    }
}
void moveSnakeByDirection(int moveDirection)
{
    int i,j,max =0,oldTail_i=0,oldTail_j=0,oldHead_i=0,oldHead_j=0,newHead_j=0, newHead_i=0;
    for(i=0;i<20;i++)
    {for(j=0;j<30;j++){
   
            if(canvas[i][j]>0) canvas[i][j]++;
    }}for(i=0;i<20;i++)
    {for(j=0;j<30;j++){
            if(canvas[i][j]>max)
            {
                max=canvas[i][j];
                oldTail_i=i;
                oldTail_j=j;
            
            }}}for(i=0;i<20;i++)
    {for(j=0;j<30;j++){
            if(canvas[i][j]==2)
            {
                oldHead_i=i;oldHead_j=j;
                }}} newHead_i=oldHead_i;newHead_j=oldHead_j;
        
    
    if(moveDirection==1){
        newHead_i=oldHead_i-1;newHead_j=oldHead_j;
        
    }
    if(moveDirection==2){
        newHead_i=oldHead_i+1;newHead_j=oldHead_j;
        
    }
    if(moveDirection==3){
        newHead_i=oldHead_i;newHead_j=oldHead_j-1;
        
    }
    if(moveDirection==4){
        newHead_i=oldHead_i;newHead_j=oldHead_j+1;
        
    }
    if(canvas[newHead_i][newHead_j]>0||canvas[newHead_i][newHead_j]==-1)
    {
        life--;
        printf("life=%d",life);
        if(life>0){
            newHead_i=oldHead_i;
            newHead_j=oldHead_j;
            canvas[newHead_i][newHead_j]=1;
            canvas[oldTail_i][oldTail_j]=max;        
            }else{
                printf("game over");
                exit(0);
            }
    }
    canvas[newHead_i][newHead_j]=1;
    if (newHead_i==food_x&&newHead_j==food_y)
    {
        
        food_x=rand()%(High-5)+2;
        food_y=rand()%(Width-5)+2;
        canvas[food_x][food_y]=-2;
    }else if(newHead_i==goods_x&&newHead_j==goods_y){
        life++;
        printf("life=%d",life);
        canvas[goods_x][goods_y];
        goods_x=rand()%(High-5)+3;
        goods_y=rand()%(Width-5)+3;
        canvas[goods_x][goods_y]=-3;
    }
    else {canvas[oldTail_i][oldTail_j]=0;}
    

}