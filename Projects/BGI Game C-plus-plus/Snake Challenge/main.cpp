#include<bits/stdc++.h>
#include<graphics.h>

using namespace std;

void openpage();
void gameplay();
void gameStatus();
void losspage();
void winpage();
void setGameSpeed();

char setSpeed[100], setScore[100], setTime[100];
char scoredisplay[100], clockdisplay[100];

int gameSpeed=90; int speedCounter=0; int Score=40; int timelimit=75;
int currentScore=0; int currentTime=0;
int m[500],n[500],con=20;

clock_t startCount, stopCount;

///:::::::::::::::::::::::::::::::::::::::::::::::::::::::::///
///::::::::::::::::::: Starting Main Function ::::::::::::::///
///:::::::::::::::::::::::::::::::::::::::::::::::::::::::::///
int main()
{

    initwindow(810,570);
    openpage();
    getch();


}

///:::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ///
///:::::::::: function declaration area ::::::::::::::::::::: ///
///:::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ///
void openpage()
{
    PlaySound(TEXT("sounds//openPage.wav"),NULL,SND_ASYNC);

    setcolor(GREEN);
    settextstyle(4,0,5);
    outtextxy(150,20,"Snake Challenge");
    setlinestyle(1,0,4);
    rectangle(140,20,660,80);

    settextstyle(3,0,4);
    outtextxy(280,100,"Select Option");
    setlinestyle(1,0,4);
    rectangle(260,140,490,100);

    setcolor(GREEN);
    rectangle(140,155,660,290);

    settextstyle(3,0,4); outtextxy(150,160,"Game Speed:   x (F5 for change)");

    settextstyle(3,0,4); outtextxy(150,200,"TimeLimit:      Sec (F6 for change)");

    settextstyle(3,0,4); outtextxy(150,240,"Score:     point (F7 for change)");

    settextstyle(3,0,4); outtextxy(160,310,"Press 'Home' for enter the game ");
    int ch=getch();

    if(kbhit())
    {
        sprintf(setSpeed,"%d",speedCounter); settextstyle(3,0,4); outtextxy(348,160,setSpeed);
        sprintf(setTime,"%d",timelimit); settextstyle(3,0,4);outtextxy(305,200,setTime);
        sprintf(setScore,"%d",Score); settextstyle(3,0,4); outtextxy(245,240,setScore);
        while(1)
        {

            setcolor(GREEN);
            ch=getch();
            if(ch==63) /// F5
            {
                speedCounter=speedCounter%5+1;
                sprintf(setSpeed,"%d",speedCounter);settextstyle(3,0,4); outtextxy(348,160,setSpeed);
            }
            if(ch==64) /// F6
            {
                switch(timelimit)
                {
                    case 60: timelimit=75; break;
                    case 75: timelimit=90; break;
                    case 90: timelimit=60; break;
                }
                sprintf(setTime,"%d",timelimit), settextstyle(3,0,4), outtextxy(305,200,setTime);
            }
            if(ch==65) /// F7
            {
                switch(Score)
                {
                    case 30: Score=40; break;
                    case 40: Score=50; break;
                    case 50: Score=70; break;
                    case 70: Score=30; break;
                }
                sprintf(setScore,"%d",Score), settextstyle(3,0,4), outtextxy(245,240,setScore);
            }
            if(ch==27) /// Escape
                exit(0);
            if(ch==71) /// Home
            {
                delay(500);
                PlaySound(NULL,NULL,0);
                for(int blink=0;blink<20;blink++)
                    setcolor(rand()%16),outtextxy(250,360,"Press Any arrow key"),
                    PlaySound(TEXT("snakeRunning.wav"),NULL,SND_ASYNC),
                    delay(100),PlaySound(NULL,NULL,0);
                cleardevice();
                break;
            }
        }
    }
    ///::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::///
    ///:::::::::::::::: calling game play function ::::::::::::::::::::///
    ///::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::///

    setGameSpeed();
    gameplay();
}
void gameplay()
{
    int x=13, y=14, ch, fx, fy;
    int maxx=798; int maxy=496; int temp;

    fx=rand()%maxx; temp=fx%13; fx=fx-temp;
    fy=rand()%maxy; temp=fy%14; fy=fy-temp;

    int a=0, i=0, j;
    startCount=clock();


    while(1)
    {
        setcolor(GREEN);
        setfillstyle(SOLID_FILL,con+5);
        circle(fx,fy,5);
        floodfill(fx,fy,GREEN);

        if(kbhit())
        {
            ch=getch(); if(ch==0) ch=getch();
            if(ch==72&& a!=2) a=1; ///up
            if(ch==80&& a!=1) a=2; ///down
            if(ch==75&& a!=4) a=3; ///left
            if(ch==77&& a!=3) a=4; ///right
        }
        else
        {
            if(ch==27) break;
        }


        ///::::::::::::::game status:::::::::::::::::///
        setcolor(GREEN);
        setfillstyle(SOLID_LINE,2);
        rectangle(-1,-1,800,500);
        rectangle(2,502,800,550);

        setcolor(GREEN);
        settextstyle(2,0,6);
        sprintf(setScore, "Score Target : %d",Score);
        outtextxy(20,505,setScore);

        settextstyle(2,0,6);
        sprintf(setTime,"Time Limit : %d",timelimit);
        outtextxy(20,523,setTime);

        line(170,500,170,550);

        settextstyle(2,0,8);
        sprintf(clockdisplay, "Time : %d",currentTime);
        outtextxy(180,505,clockdisplay);

        settextstyle(2,0,8);
        sprintf(scoredisplay,"Score : %d",currentScore);
        outtextxy(345,505,scoredisplay);

        settextstyle(2,0,8);
        sprintf(setSpeed,"%dx",speedCounter);
        outtextxy(510,505,setSpeed);

        settextstyle(2,0,6);
        line(570,500,570,550);
        outtextxy(580,505,"Move Snake: ARROWS");
        outtextxy(580,523,"Exit Game: Esc");

        ///::::::::::: snake moving :::::::::::::::::///
        if(i<20)
        {
            m[i]=x;
            n[i]=y;
            i++;
        }
        if(i>=20)
        {
            for(j=con;j>=0;j--)
            {
                m[1+j]=m[j];
                n[1+j]=n[j];
            }
            m[0]=x;
            n[0]=y;

            setcolor(GREEN);
            setfillstyle(SOLID_FILL,con);
            circle(m[0],n[0],8);
            floodfill(m[0],n[0],GREEN);

            setcolor(GREEN);
            for(j=1;j<con;j++)
            {
                setfillstyle(SOLID_FILL,con+j%3);
                circle(m[j],n[j],5);
                floodfill(m[j],n[j],GREEN);
            }
            delay(gameSpeed);

            setcolor(BLACK);
            setfillstyle(SOLID_FILL,BLACK);
            circle(m[0],n[0],8);
            floodfill(m[0],n[0],8);

            setcolor(BLACK);
            setfillstyle(SOLID_FILL,BLACK);
            circle(m[j],n[j],5);
            floodfill(m[j],n[j],BLACK);

        }
        ///:::::::: Game Timer::::::::::::::::::::::///
        stopCount=clock();
        currentTime=(stopCount-startCount)/CLK_TCK;

        ///;;;;;;;;; Check game condition:::::::::::::: ///
        gameStatus();

        if(x==fx && y==fy)
        {
            con++;
            currentScore+=2;
            fx=rand()%maxx; temp=fx%13; fx=fx-temp;
            fy=rand()%maxy; temp=fy%14; fy=fy-temp;

            PlaySound(TEXT("sounds//food.wav"),NULL,SND_ASYNC);
        }
        if(a==1)  y =  y-14; if(y<0) { temp=maxy%14;y=maxy-temp;}
        if(a==2)  y =  y+14; if(y>maxy) y=0;
        if(a==3)  x =  x-13; if(x<0) { temp=maxx%13;x=maxx-temp;}
        if(a==4)  x =  x+13; if(x>maxx) x=0;
        if(a==0){  y = y+14 ;  x=x+13; }
    }

}

void gameStatus()
{
    for(int i=1;i<con;i++)
    {
        if(m[0]==m[i] && n[0]==n[i])
            losspage();
    }
    if(currentTime>timelimit)
        losspage();
    if(currentScore==Score && currentTime<=timelimit)
        winpage();
}
void losspage()
{
    setcolor(RED);
    rectangle(-1,-1,800,500);
    for(int i=0;i<3;i++)
    {
        PlaySound(TEXT("sounds//loss.wav"),NULL,SND_ASYNC);

        rectangle(-1,-1,800,500);
        delay(500);
        cleardevice();
        delay(500);
        for(int j=0;j<con;j++)
        {
            setfillstyle(SOLID_FILL,RED);
            circle(m[j],n[j],5);
            floodfill(m[j],n[j],RED);

        }
    }
    rectangle(-1,-1,800,500);
    settextstyle(3,0,4);
    cleardevice();
    outtextxy(260,150,"YOU LOSS");

    sprintf(scoredisplay,"You Score %d in",currentScore);
    outtextxy(200,250,scoredisplay);

    sprintf(clockdisplay,"%d Sec.",currentTime);
    outtextxy(435,250,clockdisplay);

    delay(2000);

    getch();
    getch();
    exit(0);
}
void winpage()
{
    setcolor(GREEN);
    rectangle(-1,-1,800,500);
    for(int i=0;i<2;i++)
    {
        PlaySound(TEXT("sounds//win.wav"),NULL,SND_ASYNC);

        rectangle(-1,-1,800,500);
        for(int j=0;j<=con;j++)
        {
            setfillstyle(SOLID_FILL,con);
            circle(m[j],n[j],5);
            floodfill(m[j],n[j],GREEN);
        }
        delay(500);
        cleardevice();
        delay(500);
    }
    rectangle(-1,-1,800,500);
    settextstyle(3,0,4);
    outtextxy(260,150," YOU WIN!");

    sprintf(scoredisplay,"You Score %d in",currentScore);
    outtextxy(200,250,scoredisplay);

    sprintf(clockdisplay,"%d Sec",currentTime);
    outtextxy(435,250,clockdisplay);

    delay(2000);

    getch();
    exit(0);
}
void setGameSpeed()
{
    switch(speedCounter)
    {
        case 1: gameSpeed=90; break;
        case 2: gameSpeed=70; break;
        case 3: gameSpeed=50; break;
        case 4: gameSpeed=30; break;
        case 5: gameSpeed=10; break;
    }
}
