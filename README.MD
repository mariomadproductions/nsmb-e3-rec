## nsmb-e3-rec

## Unknown things about the demo
* Level design (marked in-level with underneath the view with "closed door" tiles):
  * distance between first swiging platform and righthand ledge in Fortress is possibly inaccurate. Rotation is also possibly inaccurate. Getting rotation right may help with getting distance between platform and ledge right, by comparing video with footage of the recreation.
  * bit with big rotating platform is likely inaccurate.
  * bit after big rotating platform is unknown
  * smb 1-1 bit in field is based on description only
  * coins high up in the air in cannon's path may be in the wrong place - try using desert level to get cannon pwoer right, then use that to work out correct postioning of coins in field level
  * latter part of field's underground section is unknown
  * the end of the cave section is guessed - need to ask mspeter if it was like this
  * some of the moving mushroom positions are incorrect
  * mega mario section may be inaccurate in parts
* Not known what bottom screen of title, level select and thank you for playing looks like

## To do
* make sure camera is correct in fort
* make sure desert is accurate by watching videos frame by frame
* Big wheel platform
  * platforms should be bigger horizontally and vertically
  * bg part may need to be shifted/resized
  * platforms may move/be attched differently relative to the bg part
* Field and fort tilesets and backgrounds, underground backgrounds [could base some of these off ones in alpha/beta co-op hacks - but would be best to ask for source pngs if i do so]
** is bottom bg of unused staletite bg same or similar to e3 cave bg?
* It'd be cleaner to do sfx switches in code, rather than moving data around in sdat
* the delay to load a level is too long, but this might be hard to fix
* checkpoint ring sound might not be exactly the right tone. also maybe sounds a bit harsh - might need different instrument.
* enemy postitioning and cameras may need tweaking
* "k" in "Thank you for playing" is the capital K - couldn't find a lowercase one. need to make or find a lowercase one.
* make castle and underground BGs link to standard jyotyu pallete: https://nsmbhd.net/thread/22-changing-which-tileset-0-palette-is-used-for-each-bg-tutorial/
* compare orig and current jyotyu pallete to work out what changes were made to fix the ! switch coins, and then make changes to make the coins static
* Revert removal of bah commands as thegameratort did it in asm
* make sure all progress paths work properly

## Modifications
* ASM
  * various [todo: specify] //TheGameratorT
  * bossParticles.s //Skawo 
  * noFreeze.s //Dirbaio, MeroMero
* `sound_data.sdat` //Hiccup
  * SSEQ
    * Removed "wahs" from desert, underground and ground themes replacing samples with silent ones
	* Removed enemy dance commands from desert, underground and ground themes
  * SSAR
	* `SAR_VS_COMMON_PLAYER_BASE`
	  * Red Ring sound points to new sound which is current a toned-down version of the stock item get sound, using the original ring sfx's volume and instrument
	* `SAR_ENEMY_BASE`
      * Big Piranha Plant chomp sound edited to point to small Piranha Plant chomp sound
    * `SAR_COURSE`
	  * Door open sound made same as pipe/powerdown sound
      * Door close sound made silent
	* `SAR_ENEMY_01`
		* Lakitu appear and throw spiny sounds made silent
  * SMAP
	* BGM_BOSS_CLEAR entry edited to match BGM_COURSE_CLEAR entry (excluding ID fields etc of course)
* Tilesets/backgrounds
  * Field tileset (WIP) //Alzter
  * Underground titleset and background (WIP) //Unknown, via Ambience69's alpha replica
  * Desert titleset and background (WIP) //Unknown, via Ambience69's alpha replica
* `enemy`
  * Bump-from-below platform //Unknown, someone on NSMBHD thread
    * `I_m_yuka.nsbtx`
    * `I_m_yuka_hidari.nsbtx`
    * `I_m_yuka_hidari.nsbtx`
  * Goal flag
    * `obj_goal_flag.nsbmd` //Hiccup
  * Lift //Hiccup
    * `n_lift.nsbtx` (replaced with `wheel_lift.nsbtx`)
* `obj`
  * ! Switch //Hiccup or someone on nsmbhd thread
    * `I_switch_ncg.bin` 
* `polygon_unit`
  * Pipes //TheGameratorT [todo: which textures in the file were changed?]
    * `I_dokan.nsbtx` 
  * Pipe joint //Alzter
    * `I_do_kanagu_lu.nsbtx` 
    * `I_do_kanagu_lu.nsbtx`
    * `I_do_kanagu_rd.nsbtx`
    * `I_do_kanagu_ru.nsbtx`
* `demo` //TheGameratorT and/or Alzter [todo: specify]
    * `boot_sub_bg_ncg.bin`
    * `boot_sub_bg_ncl.bin`
    * `boot_sub_bg_nsc.bin`
* `uiStudio` //TheGameratorT, Alzter, Hiccup
  * Top screen in-level HUD
    * `UI_O_1P_game_in_u.bncl`
  * Title hud graphics edited for use in E3 menu
    * `d_2d_UI_O_menu_title_o_d_ncl.bin`
    * `UI_O_menu_title_d.bnbl`
    * `UI_O_menu_title_d.bncl`
    * `UI_O_menu_title_o_d_ncg.bin`
  * Various [todo: specify] //TheGameratorT and/or Alzter [todo: specify]
    * `d_2d_UI_O_1P_game_in_b_d_ncg.bin`
    * `d_2d_UI_O_1P_game_in_b_d_ncl.bin `
    * `d_2d_UI_O_1P_game_in_d_nsc.bin`
    * `d_2d_UI_O_1P_game_in_kabe01_d_nsc.bin`
    * `UI_O_1P_game_in_d.bnbl`
    * `UI_O_1P_game_in_d.bncl`
    * `UI_O_1P_game_in_d_ncg.bin`
    * `UI_O_1P_game_in_o_ud_ncl.bin`
    * `UI_O_1P_gameover_o_u_ncg.bin`
* Levels //Hiccup, MarioFanatic64
* mario/luigi clear ncg swapped with jp version ones [todo: get file/folder names] //TheGameratorT

## Other credits
### Tools
[todo]

### Research
* Hiccup

## Possibly relevant sm64ds sounds
num,name,bank,note
273,NCS_SE_SCT_LKB_DOWN,NCS_BANK_SE_T_BOMBHEI,koopa stomp sound heard in trailer
david@ubuntu:/media/david/DAVID16GB/nsmb/nsmb-e3-rec$ 

## Possibly relevant nsmb sounds
0
	1 walk rope
	2 monkey bars
	7 switch [and other things?] appears
	8 step on switch
	12 open door
	13 close door
	14 boss door open
	15 boss door close
	16 switch countdown
	17 switch countdown last
5
	stomp player
7
	1 mega goomba walk
11
	0 goomba stomp
	1 koopa stomp
	10 pplant chomp
	11 big pplant chomp
	12 pplant damage
	13 pplant down
12
	0 lakitu appears
	1 spiny thrown
14
	0 mario lava burn
	1 luigi lava burn
	8 dry bones stomp
	9 whomp walk
	10 whomp falldown
	11 whomp break
	12 fire bubble out
	13 fire bubble in [unused]
	14 dry bones revival
22
	1 mario wall jump
	2 " 2
	3 " 3
	4 " mario become mega
	5 mario triple jump
	6 mario stage clear
	7 mario throw
	8 " 2
25
	0 menu item selector move
	4 menu item click
	5 menu item back
	6 pause
28
	28 open file
29
	0 pipe cannon aim
	1 " fire
	2 punch [unused]
	3 kick [unused]
	4 land [unused]
	8-12 early mega mushroom out of block sounds [unused]
	16 block kick [unused]
	30 enemy down by punch
	36 mid point
	40 hurry up
	41 down flagpole
31
	0 jump 1 [small?]
	1 jump 2 [big?] [same]
	3 mega jump
	4 slide
	5 slide 2
	6 ground pound
	7 " mega
	11 player down
	13 footnote normal
	14 footnote fast
	15 footnote sand
	17 drill stomp
	18 crouch
	19 footnote mega
	24 pole slide
	25 pole climb
	25 power-up
	31 lose mega power
	32 throw fireball
	34 pre-groundpound
	35 lose power-up [+ entet pipe?]
	36 hit block
	37 get coin
	40 koopa shell hit wall
	45 item appears
	46 mega mushroom appears
	47 item appears 2
	48 break block
	49 mega mario hit enemy
	52 1up
	54 stock item get
	55 stock item use
	56 red ring
38
	0 boss damage
	5 boss defeated
	7 boss key appear
	8 boss key bounc

