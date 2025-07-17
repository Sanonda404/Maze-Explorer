#include <bits/stdc++.h>
#include "iGraphics.h"
#include "iSound.h"


int bg_music;
int lvl_completed_music;
int shoot_music;
int hurt_music;
int lost_music;

float music_volume=0;

void init_sound()
{
    iInitializeSound();
}

void play_sound(string sound_name)
{
    if(sound_name == "bgm"){
        bg_music = iPlaySound("MazeExplorer/assests/music/bgm.wav", true, music_volume*0.8);
    }
    else if(sound_name == "lost"){
        iPlaySound("MazeExplorer/assests/music/lost.wav", false, music_volume);
    }
    else if(sound_name == "won"){
        iPlaySound("MazeExplorer/assests/music/victory.wav", false, music_volume);
    }
    else if(sound_name == "shoot"){
        iPlaySound("MazeExplorer/assests/music/shoot.wav", false, music_volume);
    }
    else if(sound_name == "hurt"){
        iPlaySound("MazeExplorer/assests/music/hurt.wav", false, music_volume);
    }
}