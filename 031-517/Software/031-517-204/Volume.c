/*****************************************************************************

    Volume module

    This module implements a volume control via a LM4811 IC.

    David Annett, david@lynxinnovation.com, 4 Jan 2009

 ****************************************************************************/

// ------- Includes ----------

#include "Globals.h"
#include "CommonTypes.h"
#include "Volume.h"
#include "Timer.h"
#include "Wm8960.h"

// ------- Constants ---------


// ------- Types -------------


// ------- Public vars -------


// ------- Private vars ------

Uint8 CurrentVolume;
static Uint8 ChMaxVolume[5] = {127,127,127,127,127};
static Uint8 ChAdjVolume[5] = {0,0,0,0,0};
extern Uint8 ChannelNumbers;

// ------- Private functions -
#if HWVer == 1
/*
  Volume_Clock routine

  This routine pulses the clock line.
 */
void Volume_Clock(void)
{
  SetBit(VolPort, VolClk);
  NOP;
  ClearBit(VolPort, VolClk);
  NOP;
}



// ------- Public functions -

/*
  Volume_Init routine

  This routine sets up the volume chip with maximum attenuation
 */
void Volume_Init(void)
{
  ClearBit(VolPort, VolClk);   // Preset clock state
  CurrentVolume = MaxVol;
  Volume_Set(0);               // Effectively mute
}



/*
  Volume_Set routine

  This routine set the volume level using the volume IC.
 */
void Volume_Set(Uint8 Volume)
{
  if (Volume)
    UnMute;
  else
    Mute;

  // Ramp volume if needed

  if (CurrentVolume < Volume) {         // Need to ramp up
    SetBit(VolPort, VolData);
    for (; CurrentVolume < Volume; CurrentVolume++)
      Volume_Clock();

  } else if (CurrentVolume > Volume) {  // Need to ramp down
    ClearBit(VolPort, VolData);
    for (; CurrentVolume > Volume; CurrentVolume--)
      Volume_Clock();
  }
}



/*
  Volume_Up routine

  This routine will step up the volume one step
 */
void Volume_Up(void)
{
  Uint8 Volume;

  Volume = CurrentVolume;
  if (Volume < MaxVol)
    Volume_Set(Volume + 1);
}



/*
  Volume_Down routine

  This routine will step down the volume one step
 */
void Volume_Down(void)
{
  Uint8 Volume;

  Volume = CurrentVolume;
  if (Volume > MinVol)
    Volume_Set(Volume - 1);
}


#elif HWVer == 2


/*
  Volume_Set routine

  This routine set the volume volume value and channel.
 */
void Volume_Set(Uint8 Volume,Uint8 ChannelIn)
{
  Uint8 Channel;
  Uint8 LimtedVolume;

  if(ChannelIn)
  {
    WM8960_SetVolume(ChannelIn, Volume);
  }
  else
  {
    for(Channel = 1; Channel <= ChannelNumbers; Channel++)
    {
      LimtedVolume = Volume;
      if(Volume > ChMaxVolume[Channel-1])
      {
        LimtedVolume = ChMaxVolume[Channel-1];
      }
      if (LimtedVolume > ChAdjVolume[Channel])
        LimtedVolume -= ChAdjVolume[Channel];
      else
        LimtedVolume = 0;
      WM8960_SetVolume(Channel, LimtedVolume);
    }
  }
}



void SetChannelAdjust(Uint8 Channel ,Uint8 Adjust)
{
  if((Channel <= 5) && (Channel > 0))
    ChAdjVolume[Channel] = Adjust;
}



void SetChMaxVolume(Uint8 Channel, Uint8 MaxVolume)
{
  if((MaxVolume <= 127) && ((Channel <= 5) && (Channel > 0)))
  {
    ChMaxVolume[Channel-1] = MaxVolume;
  }
}

#endif
