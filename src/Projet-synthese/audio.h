#ifndef _AUDIO_H
#define _AUDIO_H

#include "libs/soloud20200207/include/soloud.h"
#include "libs/soloud20200207/include/soloud_wav.h"

class audio
{
private:
    SoLoud::Soloud soloud;
    SoLoud::Wav boom;
    SoLoud::Wav pluie;
    SoLoud::Wav vase;
    SoLoud::Wav saut;
    SoLoud::Wav cri;
    SoLoud::Wav violon;
    SoLoud::Wav thunder;
public:
    audio();
    ~audio();

    //initialise les sons
    int audio_Init();

    //joue une musique
    void play_audio(SoLoud::Wav & b);
    //arretes une musique
    void pause_audio(SoLoud::Wav & b);
    //récupère les musiques à jouer
    SoLoud::Wav & getWav();
    SoLoud::Wav & getVase();
    SoLoud::Wav & getSaut();
    SoLoud::Wav & getPluie();
    SoLoud::Wav & getCri();
    SoLoud::Wav & getViolon();
    SoLoud::Wav & getThunder();
    //détruit les musiques
    void audio_Quit();
};




#endif
