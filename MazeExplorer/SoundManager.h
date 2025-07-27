#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <bits/stdc++.h>
#include "iGraphics.h"
#include "iSound.h"
#include "MazeExplorer/Signup.h"


int bg_music;
int lvl_completed_music;
int shoot_music;
int hurt_music;
int lost_music;


void init_sound()
{
    iInitializeSound();
}

void play_sound(string sound_name)
{
    if(sound_name == "bgm"){
        bg_music = iPlaySound("MazeExplorer/assests/music/bgm.wav", true, music_volume*90);
    }
    else if(sound_name == "lost"){
        iPlaySound("MazeExplorer/assests/music/lost.wav", false, sfx_volume*100);
    }
    else if(sound_name == "won"){
        iPlaySound("MazeExplorer/assests/music/victory.wav", false, sfx_volume*100);
    }
    else if(sound_name == "shoot"){
        iPlaySound("MazeExplorer/assests/music/shoot.wav", false, sfx_volume*100);
    }
    else if(sound_name == "hurt"){
        iPlaySound("MazeExplorer/assests/music/hurt.wav", false, sfx_volume*100);
    }
}

void update_volume()
{
    iSetVolume(bg_music,music_volume*90);
}
#endif