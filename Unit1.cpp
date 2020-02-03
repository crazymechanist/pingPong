//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x=10, y=0;
int pointsOfLeftPlayer;
int pointsOfRightsPlayer;

bool isAppPaused;
bool isStartFirst;

template <class T>
int centerX(T *shape){
return shape->Left + shape->Width/2;
}

template <class T>
int centerY(T *shape){
return shape->Top + shape->Height/2;
}

template <class T>
int leftBorder(T *shape){
return shape->Left;
}

template <class T>
int rightBorder(T *shape){
return shape->Left+shape->Width;
}

template <class T>
int topBorder(T *image){
return image->Top;
}

template <class T>
int downBorder(T *image){
return image->Top+image->Height;
}

void __fastcall TForm1::resetBallPosition(){
ball->Left = centerX(background);
ball->Top = centerY(background);
ballTimer->Enabled=false;
ballDelay->Enabled=true;
if(x>0)x=-10;
else x=10;
}

AnsiString setScore(int leftPoint, int rightPoint){
return IntToStr(leftPoint) + ":" + IntToStr(rightPoint);
}

void __fastcall TForm1::newGame(){
pointsOfLeftPlayer=0;
pointsOfRightsPlayer=0;
score->Caption = setScore(pointsOfLeftPlayer,pointsOfRightsPlayer);
resetBallPosition();
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballTimerTimer(TObject *Sender)
{       if(x<-30)x=-30;
        if(x>-5 && x<0)x=-5;
        if(x>30)x=30;
        if(x<5 && x>0)x=5;
    ball->Left+=x; ball->Top+=y;

    int margin =3;

    //podazaj za pilka
    //rightPaddle->Top=ball->Top-(rightPaddle->Height - ball->Height)/2;

    //jezeli pilka poza zakresem z lewej
    if(leftBorder(ball) < leftBorder(background)- 4*margin){
    ball->Left = leftBorder(background) + 2*ball->Width;
    }

    //jezeli pilka poza zakresem z prawej
        if(rightBorder(ball) >= rightBorder(background)+ 4*margin){
    //ball->Left= rightBorder(background) - 2*ball->Width;
    }

    //jezeli pilka poza zakresem z gory
    if(topBorder(ball) < topBorder(background)- 4*margin){
    ball->Top = topBorder(background) + 2*ball->Height;
    }

    //jezeli pilka poza zakresem z doly
    if(downBorder(ball) >= downBorder(background)+ 4*margin){
    ball->Top= downBorder(background) - 2*ball->Height;
    }

    //punkt po lewej
    if (leftBorder(ball) <= leftBorder(background) + 2*margin) {
     score->Caption = setScore(pointsOfLeftPlayer,++pointsOfRightsPlayer) ;
     resetBallPosition();}

    //odbij od górnej sciany
    if (topBorder(ball) <= topBorder(background)+ 2*margin) y=-y;

    //odbij od dolnej sciany
    if (downBorder(ball) >= downBorder(background)-2*margin) y=-y;

   //punkt po prwaej
    if (rightBorder(ball) >= rightBorder(background) - 2* margin) {
     score->Caption = setScore(++pointsOfLeftPlayer,pointsOfRightsPlayer) ;
     resetBallPosition();}


   //odbicie od prawej paletki
   if(leftBorder(rightPaddle) <= rightBorder(ball)
   && leftBorder(rightPaddle) + 10* margin >= rightBorder(ball)
   && topBorder(ball)<downBorder(rightPaddle)
   && downBorder(ball)>topBorder(rightPaddle)){
        if(centerY(ball)>centerY(rightPaddle)-.15*rightPaddle->Height
        && centerY(ball)<centerY(rightPaddle)+.15*rightPaddle->Height){
        x=-x;
        x-=3;
                if(y<0) y=-4;
                else y=4;
        }
        else if(centerY(ball)>centerY(rightPaddle)-.45*rightPaddle->Height
        && centerY(ball)<centerY(rightPaddle)+.45*rightPaddle->Height){
        x=-x;
        x-=1;
                if(y<0) y=-8;
                else y=8;
        }
        else{
        x=-x;
        y=-y;
        }
   }

   //odbicie od lewej paletki
   if(rightBorder(leftPaddle) >= leftBorder(ball)
   && rightBorder(leftPaddle) - 10* margin <= leftBorder(ball)
   && topBorder(ball)<downBorder(leftPaddle)
   && downBorder(ball)>topBorder(leftPaddle)){
        if(centerY(ball)>centerY(leftPaddle)-.15*leftPaddle->Height
        && centerY(ball)<centerY(leftPaddle)+.15*leftPaddle->Height){
        x=-x;
        x+=3;
                if(y<0) y=-4;
                else y=4;
        }
        else if(centerY(ball)>centerY(leftPaddle)-.45*leftPaddle->Height
        && centerY(ball)<centerY(leftPaddle)+.45*leftPaddle->Height){
        x=-x;
        x+=1;
                if(y<0) y=-8;
                else y=8;
        }
        else{
        x=-x;
        y=-y;
        }
   }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==VK_UP) leftPaddleUpTimer->Enabled=false;
    if(Key==VK_DOWN) leftPaddleDownTimer->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_UP) leftPaddleUpTimer->Enabled=true;
  if(Key==VK_DOWN) leftPaddleDownTimer->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
pauseClick(pause);
int left=background->Left;
int top=background->Top;
background->Left = (Form1->ClientWidth - background->Width)/2;
background->Top = (Form1->ClientHeight - background->Height)/2;
score->Left = (Form1->ClientWidth - score->Width)/2;
score->Top = (Form1->ClientHeight - score->Height)/2;
ball->Left+=background->Left-left;
ball->Top += background->Top - top;
leftPaddle->Left += background->Left-left;
leftPaddle->Top+=background->Top-top;
rightPaddle->Left+=background->Left-left;
rightPaddle->Top+=background->Top-top;
version->Left+=background->Left-left;
version->Top+=background->Top-top;
play->Left+=background->Left-left;
play->Top+=background->Top-top;
pause->Left+=background->Left-left;
pause->Top+=background->Top-top;
settings->Left+=background->Left-left;
settings->Top+=background->Top-top;
reset->Left+=background->Left-left;
reset->Top+=background->Top-top;
help->Left+=background->Left-left;
help->Top+=background->Top-top;
if(pause->Visible==true) playClick(play);
if(isStartFirst==true)  {helpClick(help); isStartFirst=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftPaddleDownTimerTimer(TObject *Sender)
{
int margin = 10;
if(downBorder(leftPaddle)<downBorder(background)-margin
&& !isAppPaused){
leftPaddle->Top+=10;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightPaddleDownTimerTimer(TObject *Sender)
{
int margin = 10;
if(downBorder(rightPaddle)<downBorder(background)-margin
&& !isAppPaused){
rightPaddle->Top+=10;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftPaddleUpTimerTimer(TObject *Sender)
{
int margin = 10;
if(topBorder(leftPaddle)>topBorder(background)+margin
&& !isAppPaused
&&centerX(ball)<rightBorder(background)-80){
leftPaddle->Top-=10;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightPaddleUpTimerTimer(TObject *Sender)
{
int margin = 10;
if(topBorder(rightPaddle)>topBorder(background)+margin
&& !isAppPaused
&& centerX(ball)<rightBorder(background)-80){
rightPaddle->Top-=10;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballDelayTimer(TObject *Sender)
{
ballTimer->Enabled=True;
ballDelay->Enabled=False;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::playClick(TObject *Sender)
{
if(ballTimer->Enabled==false){
ballTimer->Enabled=true;
isAppPaused=false;
play->Visible=false;
pause->Visible=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pauseClick(TObject *Sender)
{
if(ballTimer->Enabled==true){
ballTimer->Enabled=false;
isAppPaused=true;
pause->Visible=false;
play->Visible=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
isAppPaused=false;
pointsOfLeftPlayer=0;
pointsOfRightsPlayer=0;
pauseClick(pause);
isStartFirst=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::rightPaddleMoveTimer(TObject *Sender)
{
if(centerX(ball)>centerX(background)-100){
        if(centerY(ball)>centerY(rightPaddle)){
        rightPaddleUpTimer->Enabled=false;
        rightPaddleDownTimer->Enabled=true;
        }else{
        rightPaddleDownTimer->Enabled=false;
        rightPaddleUpTimer->Enabled=true;
}}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::resetClick(TObject *Sender)
{
newGame();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::helpClick(TObject *Sender)
{
pauseClick(pause);
Application->MessageBox("Witaj w grze PingPong.\n\nLewy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\nPrawym graczem steruje komputer.\n\nDla urozmaicenia zabawy:\nKiedy d³u¿ej odbijesz pi³kê na œrodku paletki, wówczas zmienisz jej k¹t odbicia i pi³ka przyspieszy.\nSkraj paletki natomiast odbija pi³kê wtym kierunku z którego ona przyby³a. Mo¿esz zapauzowaæ grê ,\na tak¿e j¹ zresetowaæ. To okno wywo³uje siê znakiem zapytania.\nIm d³u¿ej odbijsz, tym pi³ka szybciej przemieszcza siê.\nPole gry jest sta³e.\n\nMi³ej zabawy!","Info",MB_ICONQUESTION);
playClick(play);}
//---------------------------------------------------------------------------

void __fastcall TForm1::settingsClick(TObject *Sender)
{
pauseClick(pause);
Application->MessageBox("Tu jeszcze nic nie ma","Ustawienia");
playClick(play);}
//---------------------------------------------------------------------------

