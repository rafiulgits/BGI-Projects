#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
using namespace std;

bool gameIsRunning=true; int gameLife=3;/// game life and running key
int gameX1=100,gameX2=900,gameY1=50,gameY2=600,statusX=1100; /// game window
int bX=450,bY=565,radius=10, ballspeedX=-10,ballspeedY=-10; /// ball configuration
int Px1=400,Py1=575,Px2=580,Py2=595,padspeedX=15; /// pad configuration
int gameLevel=1, gameScore=0, gameHighScore;/// game status
bool padisgoingRight=true, padisgoingLeft=false; /// pad move control
char scoreDisplay[10], levelDisplay[10], highScoreDisplay[10],lifeDisplay[10]; /// display game status

int page=0; bool mouseTrigured=false; /// updated variables

void gamePlay();
void openPage();
void loadGame();
void saveGame();
void display();
void ballMove();
void operationHandle();
void BallAndPad();
void intialBrick();
void displayBricks();
void BallAndBricks();
void SocreAndLevel();
void levelUpPage();
void highScoreChecker();
void gameOverPage();
void gameCompletePage();
/// Update function
void PadControl();
void mouseControl();

struct defineBrick
{
    int x;
    int y;
    bool visible;
};

defineBrick brick[20];
int levelOneBricks=16,levelTwoBricks=9,levelThreeBricks=5;

int main()
{
    gamePlay();
}

/* Function  Defining Area
   All component functions are called in gamePlay function
   And gamePlay function is called in main function
   All functions are defining serial-wise as i declare in top
   Functions name refer the functions objective
   Functions name refer the functions objective
*/

void gamePlay()
{
    ///get full screen size
    DWORD Width =GetSystemMetrics(SM_CXSCREEN);
    DWORD Height=GetSystemMetrics(SM_CYSCREEN);

    cout<<Width<<" "<<Height<<endl;

    ///initwindow(1200,700);
    initwindow(Width,Height);
    intialBrick();
    openPage();
    getch();
    while(gameIsRunning)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        PadControl(); /// Pad Manual Function
        display();
        ballMove();
        mouseControl(); /// Pad Mouse Control
        operationHandle();
        BallAndPad();
        displayBricks();
        BallAndBricks();
        page=1-page;
        delay(30);
    }
}
void openPage()
{
    PlaySound(TEXT("sounds\\gameOpening.wav"),NULL,SND_ASYNC);

    rectangle(gameX1,gameY1,statusX,gameY2);

    settextstyle(9,0,8);
    outtextxy(350,100,"DX Ball");


    settextstyle(8,0,6);
    outtextxy(350,300,"F1. New Game");
    outtextxy(350,380,"F2. Load Game");

    while(1)
    {
        int chooser=getch();
        if(chooser==59)
        {
            PlaySound(TEXT("sounds\\gameSelect.wav"),NULL,SND_ASYNC);
            cleardevice();
            outtextxy(300,200,"New Game Selected"); delay(2000);
            outtextxy(210,300,"Press any key to continue");
            break;
        }
        if(chooser==60)
        {
            PlaySound(TEXT("sounds\\gameSelect.wav"),NULL,SND_ASYNC);
            cleardevice();
            outtextxy(300,200,"Load Game Selected");
            loadGame(); /// game Load from file
            delay(2000);
            outtextxy(220,300,"Press any key to continue");
            break;
        }
    }
    freopen("AppData\\highScore.txt","r",stdin);
    cin>>gameHighScore;

}
void loadGame()
{
    ///::::::::::::::::::::::::::::::::::::;///
    /// open game status file and load data ///
    ///::::::::::::::::::::::::::::::::::::;///
    freopen("AppData\\status.txt","r",stdin);
    string statusFile; cin>>statusFile;
    cout<<statusFile<<endl;
    if(statusFile.empty())
    {
        cleardevice();
        outtextxy(300,300,"Sorry No Data !");
        fclose(stdin);
        delay(4000); exit(0);
    }
    else
    {
        freopen("AppData\\status.txt","r",stdin);
        cin>>gameLife>>gameLevel>>gameScore;
    }


    ///::::::::::::::::::::::::::::::::::::///
    /// open game brick file and load data ///
    ///:::::::::::::::::::::::::::::::::::;///
    freopen("AppData\\bricks.txt","r",stdin);
    string brickFile; cin>>brickFile;
    cout<<brickFile<<endl;
    if(brickFile.empty())
    {
        cleardevice();
        outtextxy(300,300,"Sorry No Data !");
        fclose(stdin);
        delay(4000); exit(0);
    }
    else
    {
        freopen("AppData\\bricks.txt","r",stdin);
        for(int i=1;i<=20;i++)
            cin>>brick[i].visible;
    }

}
void saveGame()
{
    /*
    save game will call in pad handle function
    when user press 'Home' key
    */


    ///::::::::::::::::::::::::::::::::::::;///
    /// open game status file and save data ///
    ///::::::::::::::::::::::::::::::::::::;///
    freopen("AppData\\status.txt","w",stdout);
    cout<<gameLife<<" "<<gameLevel<<" "<<gameScore<<" ";
    fclose(stdout); /// close this file

    ///::::::::::::::::::::::::::::::::::::///
    /// open game brick file and save data ///
    ///:::::::::::::::::::::::::::::::::::;///
    freopen("AppData\\bricks.txt","w",stdout);
    for(int i=1;i<=20;i++)
        cout<<brick[i].visible<<" ";
    fclose(stdout); /// close the file

    setvisualpage(page);
    settextstyle(4,0,6);
    outtextxy(260,300,"Game Saved");
    delay(2000);

}
void display()
{
    rectangle(gameX1,gameY1,statusX,gameY2);
    line(gameX2,gameY1,gameX2,gameY2);

    bar(Px1,Py1,Px2,Py2);

    fillellipse(bX,bY,radius,radius);

    settextstyle(6,0,3); /// status text format

    outtextxy(gameX2+10,80,"Score:"); /// game score view
    sprintf(scoreDisplay,"%d",gameScore);  ///...
    outtextxy(gameX2+130,80,scoreDisplay); ///...

    outtextxy(gameX2+10,160,"Level:");  /// game level view
    sprintf(levelDisplay,"%d",gameLevel); ///...
    outtextxy(gameX2+120,160,levelDisplay); ///...

    outtextxy(gameX2+10,240,"Life:"); /// game life view
    sprintf(lifeDisplay,"%d",gameLife-1); ///...
    outtextxy(gameX2+100,240,lifeDisplay); ///...

    outtextxy(gameX2+10,320,"Record:"); /// game high score view
    sprintf(highScoreDisplay,"%d",gameHighScore); ///...
    outtextxy(gameX2+130,320,highScoreDisplay); ///...

    outtextxy(gameX2+10,400,"Save: 'Home'");

    outtextxy(gameX2+10,480,"Exit: 'esc'");

}
void ballMove()
{
    bX+=ballspeedX; bY+=ballspeedY;
    if(bX<gameX1 || bX>gameX2)
    {
        ballspeedX*=-1;
        bX+=ballspeedX;
    }
    if(bY<gameY1) /// || bY>gameY2
    {
        ballspeedY*=-1;
        bY+=ballspeedY;
    }
    if(bY>gameY2) /// condition for game over
    {
        if(gameLife>0)
        {
            bX=450;bY=565; /// replace the ball position
            Px1=400; Py1=575; /// replace the pad position
            Px2=580;Py2=595;  ///...
            if(gameLife>1)
            {
                setvisualpage(page);
                settextstyle(4,0,6);
                outtextxy(300,300,"New Life");
                delay(1000);
            }
            gameLife--;
            ballspeedY*=-1;
            bY+=ballspeedY;


        }
        if(gameLife==0)
            gameOverPage();
    }
}
void operationHandle()
{
    while(kbhit())
    {
        int operation=getch();
        if(operation==71)
            saveGame();
        if(operation==27)
            exit(1000);
    }

}
void BallAndPad()
{
    if(bY==Py1)
    {
        if(bX-Px1>=0 && bX-Px2<=0)
        {
            PlaySound(TEXT("sounds//BallAndPad.wav"),NULL,SND_ASYNC); /// sound
            ballspeedY*=-1; bY+=ballspeedY;
        }
    }
    if(bX == Px2 || bX==Px1)
    {
        if(bY-Py1>=0 && bY-Py2<=0)
        {
            PlaySound(TEXT("sounds//BallAndPad.wav"),NULL,SND_ASYNC); /// sound
            ballspeedX*=-1; bX+=ballspeedX;
        }
    }
}
void intialBrick()
{
    for(int i=1;i<=20;i++)
    {
        brick[i].visible=true;
    }
}
void displayBricks()
{
    switch(gameLevel)
    {
    case 1:
        {
            int inBrickX=200,inBrickY=100,dx=40,dy=20; /// level-wise position
            for(int i=1;i<=levelOneBricks;i++)
            {
                brick[i].x=inBrickX; brick[i].y=inBrickY;
                if(brick[i].visible)
                {
                    bar(brick[i].x,brick[i].y,brick[i].x+dx-2,brick[i].y+dy);
                    inBrickX+=dx;
                }
                else
                    inBrickX+=dx;
            }
            break;
        }
    case 2:
        {
            int inBrickX=440,inBrickY=100,dx=40,dy=20; /// level-wise position
            for(int i=1;i<=levelTwoBricks;i++)
            {
                brick[i].x=inBrickX; brick[i].y=inBrickY;
                if(brick[i].visible)
                {
                    bar(brick[i].x,brick[i].y,brick[i].x+dx-2,brick[i].y+dy-2);
                    inBrickX+=dx;
                    if(i==5)
                        inBrickX=480, inBrickY=120;
                    if(i==8)
                        inBrickX=520, inBrickY=140;
                }
                else
                {
                    inBrickX+=dx;
                    if(i==5)
                        inBrickX=480, inBrickY=120;
                    if(i==8)
                        inBrickX=520, inBrickY=140;
                }
            }
            break;
        }
    case 3:
        {
            int inBrickX=400,inBrickY=200,dx=40,dy=-20; /// level-wise position
            for(int i=1;i<=levelThreeBricks;i++)
            {
                brick[i].x=inBrickX; brick[i].y=inBrickY;
                if(brick[i].visible)
                {
                    bar(brick[i].x,brick[i].y,brick[i].x+dx-2,brick[i].y+dy);
                    inBrickX+=dx; inBrickY+=dy;
                    if(i==3) inBrickY=160,dy*=-1;
                }
                else
                {
                    inBrickX+=dx; inBrickY+=dy;
                    if(i==3) inBrickY=160,dy*=-1;
                }
            }
            break;
        }
    }
}
void BallAndBricks()
{
    int stop;
    switch(gameLevel)
    {
        case 1: stop=levelOneBricks; break;
        case 2: stop=levelTwoBricks; break;
        case 3: stop=levelThreeBricks; break;
    }


    int ballUp=bY-radius; int ballDown=bY+radius;
    int ballLeft=bX-radius; int ballRight=bX+radius;
    for(int i=1;i<=stop;i++)
    {
        if((ballUp==brick[i].y || ballDown==brick[i].y+25) && bX>=brick[i].x && bX<=brick[i].x+50)
        {
            if(brick[i].visible)
            {
                PlaySound(TEXT("sounds//BallAndBrick.wav"),NULL,SND_ASYNC); /// sound
                brick[i].visible=false;
                ballspeedY*=-1;
                bY+=ballspeedY;
                SocreAndLevel();  /// check level and score
                break;
            }
            else
                continue;
        }
        if((ballRight==brick[i].x || ballLeft==brick[i].x+50) && bY>=brick[i].y && bY<=brick[i].y+25)
        {
            if(brick[i].visible)
            {
                PlaySound(TEXT("sounds//BallAndBrick.wav"),NULL,SND_ASYNC); /// sound
                brick[i].visible=false;
                ballspeedX*=-1;
                bX+=ballspeedX;
                SocreAndLevel();  /// check level and score
                break;
            }
            else
                continue;
        }
    }
}
void SocreAndLevel()
{
    switch(gameLevel)
    {
    case 1: gameScore+=5; break;
    case 2: gameScore+=10; break;
    case 3: gameScore+=20; break;
    }
    switch(gameScore)
    {
    case 80 : gameLevel=2; break;
    case 170: gameLevel=3; break;
    case 270: gameCompletePage(); break; /// game end point
    }
    if(gameScore==80 || gameScore==170)
    {
        intialBrick(); levelUpPage();
        bX=450; bY=565; ballspeedX=-10; ballspeedY=-10; /// restore ball position
        Px1=400; Px2=580; Py1=575; Py2=595; /// restore pad position
    }
}
void levelUpPage()
{
    setvisualpage(page);
    cleardevice();
    rectangle(gameX1,gameY1,statusX,gameY2);
    settextstyle(6,0,4); outtextxy(450,300,"Level Loading...");
    delay(2000);

}
void highScoreChecker()
{
    if(gameScore>gameHighScore)
    {
        freopen("AppData\\highScore.txt","w",stdout);
        cout<<gameScore;
    }
}
void gameOverPage()
{
    setvisualpage(page);
    PlaySound(TEXT("sounds\\gameOver.wav"),NULL,SND_ASYNC);
    highScoreChecker();
    cleardevice(); gameIsRunning=false;
    rectangle(gameX1,gameY1,statusX,gameY2); /// box
    settextstyle(10,0,8); outtextxy(350,100,"Game Over"); /// game over text
    outtextxy(350,250,"Score:"); /// game score view
    sprintf(scoreDisplay,"%d",gameScore);  ///...
    outtextxy(650,250,scoreDisplay); ///...
    if(gameScore>gameHighScore)
        outtextxy(350,400,"New Record !"); /// new Record show
    delay(5000); getch();

}
void gameCompletePage()
{
    setvisualpage(page);
    PlaySound(TEXT("sounds\\gameComplete.wav"),NULL,SND_ASYNC);
    highScoreChecker();
    cleardevice(); gameIsRunning=false;
    rectangle(gameX1,gameY1,statusX,gameY2);
    settextstyle(10,0,7); outtextxy(300,100,"Congratulation");
    settextstyle(10,0,7); outtextxy(310,300,"Game Complete");
    delay(5000); getch();
}
void PadControl()
{
    if(GetAsyncKeyState(VK_LEFT))
    {
        if(Px1-20>=gameX1)
        {
            Px1-=20; Px2-=20;
        }
    }
    if(GetAsyncKeyState(VK_RIGHT))
    {
        if(Px2+20<=gameX2)
        {
            Px2+=20; Px1+=20;

        }
    }
    if(GetAsyncKeyState(VK_LBUTTON))
        mouseTrigured=true;

}
void mouseControl()
{
    if(mouseTrigured)
    {
        POINT clickPos; GetCursorPos(&clickPos);
        /// Pixel edit for get the pad using mouse cursor more easily
        if(clickPos.x>=Px1-50 && clickPos.x<=Px2+50 && clickPos.y>=Py1+10 && clickPos.y<=Py2+100)
        {
            POINT movePos; GetCursorPos(&movePos);

            int newPx1=movePos.x-90;
            int newPx2=movePos.x+90;
            if(newPx1>=gameX1 && newPx2<=gameX2)
            {
                Px1=newPx1;
                Px2=newPx2;
            }
        }
    }
    mouseTrigured=false; /// restore mouse click
}
