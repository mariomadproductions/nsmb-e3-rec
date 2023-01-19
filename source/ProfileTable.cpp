// This file allows us to install the actors on the actor table

#include "scene/MainMenu.hpp"
#include "actor/BackgroundSwapper.hpp"
#include "actor/BetaSwitch.hpp"
#include "actor/ItemBlock.hpp"

// Table entry addr = (0x203997C + (classID * 4))
#define replace(addr, actor) ncp_over(addr) static ObjectProfile* profile_ ## addr = &actor::profile;

replace(0x0203998C, MainMenu) // 4
replace(0x02039D68, BackgroundSwapper) // 251
replace(0x02039D70, ItemBlock) // 253
replace(0x02039D78, BetaSwitch) // 255
