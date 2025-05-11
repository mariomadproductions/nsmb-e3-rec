//by IllyCat
//normally this sound is played using a different function, which means it doesn't play for some reason
#include <nsmb/game/sound.hpp>
ncp_jump(0x0212B830, 11)
int playerSFXFuncRepl(int sfxID, Vec3* pos, int volume)
{

        SND::playSFXUnique(sfxID, pos);
    
    return 0;
}
