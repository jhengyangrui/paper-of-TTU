#include <windows.h>
#include <math.h>
#include "fmod.h"
#include "fmod_errors.h"

FSOUND_SAMPLE *samp;
FSOUND_SAMPLE *samp2;
FSOUND_SAMPLE *samp3;
FSOUND_SAMPLE *samp4;
FSOUND_SAMPLE *samp5;
//FSOUND_SAMPLE *ping_pong;
int channel1, channel2, channel3, channel4, channel5 ;

#define music "mario_music.mp3"
#define music2 "mario_music2.mp3"
#define music3 "applause.mp3"
#define music4 "Say Goodbye.mp3"
#define music5 "boom.mp3"
static int vol = 100;

void musicchange(int musicnum)
{
	int num = musicnum;
	switch(num){
	case 1:
		FSOUND_SetPaused(channel3, TRUE);
		FSOUND_SetPaused(channel4, TRUE);
		FSOUND_SetPaused(channel2, TRUE);
		FSOUND_SetPaused(channel1, FALSE);
		break;
	case 2:
		FSOUND_SetPaused(channel1, TRUE);
		FSOUND_SetPaused(channel3, TRUE);
		FSOUND_SetPaused(channel4, TRUE);
		FSOUND_SetPaused(channel2, FALSE);
		break;
	case 3:
		FSOUND_SetPaused(channel1, TRUE);
		FSOUND_SetPaused(channel2, TRUE);
		FSOUND_SetPaused(channel4, TRUE);
		FSOUND_SetPaused(channel3, FALSE);
		break;
	case 4:
		FSOUND_SetPaused(channel1, TRUE);
		FSOUND_SetPaused(channel2, TRUE);
		FSOUND_SetPaused(channel3, TRUE);
		FSOUND_SetPaused(channel4, FALSE);
		break;
	case 5:
		/*FSOUND_SetPaused(channel1, TRUE);
		FSOUND_SetPaused(channel2, TRUE);
		FSOUND_SetPaused(channel3, TRUE);
		FSOUND_SetPaused(channel4, TRUE);*/
		FSOUND_SetPaused(channel5, FALSE);
		break;
	case 6:
		/*FSOUND_SetPaused(channel1, TRUE);
		FSOUND_SetPaused(channel2, TRUE);
		FSOUND_SetPaused(channel3, TRUE);
		FSOUND_SetPaused(channel4, TRUE);*/
		FSOUND_SetPaused(channel5, TRUE);
		break;
	}
}
void init_fmod ()
{     
	FSOUND_Init(44100, 32, 0);
	samp = FSOUND_Sample_Load (FSOUND_UNMANAGED, music, FSOUND_LOOP_NORMAL, 0,0);
	samp2 = FSOUND_Sample_Load (FSOUND_UNMANAGED, music2, FSOUND_LOOP_NORMAL, 0,0);
	samp3 = FSOUND_Sample_Load (FSOUND_UNMANAGED, music3, FSOUND_LOOP_NORMAL, 0,0);
	samp4 = FSOUND_Sample_Load (FSOUND_UNMANAGED, music4, FSOUND_LOOP_NORMAL, 0,0);
	samp5 = FSOUND_Sample_Load (FSOUND_UNMANAGED, music5, FSOUND_LOOP_NORMAL, 0,0);

	// increasing min_distance makes it louder in 3d space
    FSOUND_Sample_SetMinMaxDistance(samp, 4.0f, 10000.0f);
    FSOUND_Sample_SetMode(samp, FSOUND_LOOP_NORMAL);
	FSOUND_3D_SetDopplerFactor (4.0);

	FSOUND_Sample_SetMinMaxDistance(samp2, 4.0f, 10000.0f);
    FSOUND_Sample_SetMode(samp2, FSOUND_LOOP_NORMAL);
	FSOUND_3D_SetDopplerFactor (4.0);

	FSOUND_Sample_SetMinMaxDistance(samp3, 4.0f, 10000.0f);
    FSOUND_Sample_SetMode(samp3, FSOUND_LOOP_NORMAL);
	FSOUND_3D_SetDopplerFactor (4.0);

	FSOUND_Sample_SetMinMaxDistance(samp4, 4.0f, 10000.0f);
    FSOUND_Sample_SetMode(samp4, FSOUND_LOOP_NORMAL);
	FSOUND_3D_SetDopplerFactor (4.0);

	FSOUND_Sample_SetMinMaxDistance(samp5, 4.0f, 10000.0f);
    FSOUND_Sample_SetMode(samp5, FSOUND_LOOP_NORMAL);
	FSOUND_3D_SetDopplerFactor (4.0);

    channel1 = FSOUND_PlaySoundEx(FSOUND_FREE, samp, NULL, TRUE);
	channel2 = FSOUND_PlaySoundEx(FSOUND_FREE, samp2, NULL, TRUE);
	channel3 = FSOUND_PlaySoundEx(FSOUND_FREE, samp3, NULL, TRUE);
	channel4 = FSOUND_PlaySoundEx(FSOUND_FREE, samp4, NULL, TRUE);
	channel5 = FSOUND_PlaySoundEx(FSOUND_FREE, samp5, NULL, TRUE);

	musicchange(1);
	FSOUND_Update();
}

