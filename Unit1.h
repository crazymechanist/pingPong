//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *ball;
        TTimer *ballTimer;
        TShape *background;
        TShape *leftPaddle;
        TShape *rightPaddle;
        TTimer *leftPaddleUpTimer;
        TTimer *leftPaddleDownTimer;
        TTimer *rightPaddleUpTimer;
        TTimer *rightPaddleDownTimer;
        TLabel *score;
        TTimer *ballDelay;
        TImage *pause;
        TImage *play;
        TImage *reset;
        TImage *settings;
        TImage *help;
        TLabel *version;
        TTimer *rightPaddleMove;
        void __fastcall ballTimerTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall leftPaddleDownTimerTimer(TObject *Sender);
        void __fastcall leftPaddleUpTimerTimer(TObject *Sender);
        void __fastcall ballDelayTimer(TObject *Sender);
        void __fastcall playClick(TObject *Sender);
        void __fastcall pauseClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall rightPaddleDownTimerTimer(TObject *Sender);
        void __fastcall rightPaddleUpTimerTimer(TObject *Sender);
        void __fastcall rightPaddleMoveTimer(TObject *Sender);
        void __fastcall resetBallPosition();
        void __fastcall newGame();
        void __fastcall resetClick(TObject *Sender);
        void __fastcall helpClick(TObject *Sender);
        void __fastcall settingsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
