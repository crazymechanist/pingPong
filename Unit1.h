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
        TTimer *Timer1;
        TImage *pause;
        TImage *play;
        TImage *reset;
        TImage *settings;
        TImage *help;
        TLabel *version;
        void __fastcall ballTimerTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall leftPaddleDownTimerTimer(TObject *Sender);
        void __fastcall leftPaddleUpTimerTimer(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
