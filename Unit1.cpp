//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x=-8, y=-8;

int left;
int top;

int centerX(TShape *shape){
return shape->Left + shape->Width/2;
}
int centerX(TImage *image){
return image->Left + image->Width/2;
}

int centerY(TShape *shape){
return shape->Top + shape->Height/2;
}
int centerY(TImage *image){
return image->Top + image->Height/2;
}

int leftBorder(TImage *image){
return image->Left;
}
int leftBorder(TShape *shape){
return shape->Left;
}

int rightBorder(TImage *image){
return image->Left+image->Width;
}
int rightBorder(TShape *shape){
return shape->Left+shape->Width;
}

int topBorder(TImage *image){
return image->Top;
}
int topBorder(TShape *shape){
return shape->Top;
}

int downBorder(TImage *image){
return image->Top+image->Height;
}
int downBorder(TShape *shape){
return shape->Top+shape->Height;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballTimerTimer(TObject *Sender)
{
    ball->Left+=x; ball->Top+=y;

    int margin =3;

    //podazaj za pilka
    rightPaddle->Top=ball->Top-(rightPaddle->Height - ball->Height)/2;

    //jezeli pilka poza zakresem z lewej
    if(leftBorder(ball) < leftBorder(background)- 4*margin){
    ball->Left = leftBorder(background) + 2*ball->Width;
    }

    //jezeli pilka poza zakresem z prawej
        if(rightBorder(ball) >= rightBorder(background)+ 4*margin){
    ball->Left= rightBorder(background) - 2*ball->Width;
    }

    //jezeli pilka poza zakresem z gory
    if(topBorder(ball) < topBorder(background)- 4*margin){
    ball->Top = topBorder(background) + 2*ball->Height;
    }

    //jezeli pilka poza zakresem z doly
    if(downBorder(ball) >= downBorder(background)+ 4*margin){
    ball->Top= downBorder(background) - 2*ball->Height;
    }

    //odbij od lewej sciany
    if (leftBorder(ball) <= leftBorder(background) + margin) x=-x;

    //odbij od górnej sciany
    if (topBorder(ball) <= topBorder(background)+margin) y=-y;

    //odbij od dolnej sciany
    if (downBorder(ball) >= downBorder(background)-margin) y=-y;

   //odbij od prawej sciany
    if (rightBorder(ball) >= rightBorder(background) - margin) x=-x;


   //odbicie od prawej paletki
   if(leftBorder(rightPaddle) <= rightBorder(ball)
   && leftBorder(rightPaddle) + 3* margin >= rightBorder(ball)
   && topBorder(ball)<downBorder(rightPaddle)
   && downBorder(ball)>topBorder(rightPaddle)) {
   x=-8;
   }

   //odbicie od lewej paletki
   if(rightBorder(leftPaddle) >= leftBorder(ball)
   && rightBorder(leftPaddle) - 3* margin <= leftBorder(ball)
   && topBorder(ball)<downBorder(leftPaddle)
   && downBorder(ball)>topBorder(leftPaddle)){
        if(centerY(ball)>centerY(leftPaddle)-.15*leftPaddle->Height
        && centerY(ball)<centerY(leftPaddle)+.15*leftPaddle->Height){
        x=16;
                if(y<0) y=4;
                else y=-4;
        }
        else if(centerY(ball)>centerY(leftPaddle)-.45*leftPaddle->Height
        && centerY(ball)<centerY(leftPaddle)+.45*leftPaddle->Height){
        x=10;
                if(y<0) y=8;
                else y=-8;
        }
        else{
        x=8;
        y=-y;}
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
ballTimer->Enabled=false;
int offset=50;
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
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftPaddleDownTimerTimer(TObject *Sender)
{
int margin = 10;
if(downBorder(leftPaddle)<downBorder(background)-margin){
leftPaddle->Top+=10;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftPaddleUpTimerTimer(TObject *Sender)
{
int margin = 10;
if(topBorder(leftPaddle)>topBorder(background)+margin){
leftPaddle->Top-=10;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
ballTimer->Enabled=True;
Timer1->Enabled=False;
}
//---------------------------------------------------------------------------





