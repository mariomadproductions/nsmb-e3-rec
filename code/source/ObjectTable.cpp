#if defined(gen_obj_table) || defined(IDE)

#define repl_obj(objID, class)
#define repl_stageObj(objID, stageObjID, class)

#include "scene/MainMenu.hpp"
#include "actor/BackgroundSwapper.hpp"
#include "actor/BetaSwitch.hpp"
#include "actor/ItemBlock.hpp"

repl_obj(4, MainMenu)

repl_stageObj(251, 143, BackgroundSwapper)
repl_stageObj(253, 145, ItemBlock)
repl_stageObj(255, 169, BetaSwitch)

#endif
