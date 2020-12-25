
# nsmb-e3-rec
This project aims to recreate the New Super Mario Bros. E3 Demo.

# Building
Pre-requisites:
 - [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
 - [GNU Make](https://www.msys2.org/)
 - [Python 3](https://www.python.org/downloads/)
 - [ndspy](https://pypi.org/project/ndspy/)
 - [NSMBe 5.3 Beta](https://github.com/TheGameratorT/NSMB-Editor/releases)
 - Nitro SDK v3.0

Pre-requisites (devKitPro users):
 - [libnds](https://github.com/devkitPro/installer/releases)
 - [Python 3](https://www.python.org/downloads/)
 - [ndspy](https://pypi.org/project/ndspy/)
 - [NSMBe 5.3 Beta](https://github.com/TheGameratorT/NSMB-Editor/releases)
 - Nitro SDK v3.0

Copy the `nitrosdk/include` folder contents into the `nsmb-e3-rec/include` folder.
Run `convert_sdk.py`.
Place a clean NSMB (US) ROM in the following path `nsmb-e3-rec/rom.nds`, open the command line/terminal in the `nsmb-e3-rec` folder and execute: `py -3 insert_files.py nsmb-e3-rec/rom.nds`.
Open `nsmb-e3-rec/rom.nds` in NSMB Editor, go to the `Tools/Options` tab and click `Run 'make' and insert`, if you get a error message box just click continue.
Close the command line/terminal and NSMB Editor.
The ROM should now be ready to use!

# Playing
You can use an emulator on your computer like [DeSmuME](http://desmume.org/download/) or [MelonDS](http://melonds.kuribo64.net/downloads.php). To play on your Nintendo DS you must use an R4 card or [nds-bootstrap](https://github.com/DS-Homebrew/nds-bootstrap) (included in [TwlMenu++](https://github.com/DS-Homebrew/TWiLightMenu/releases)).

# Credits
 - **Hiccup** - Graphics and levels
 - **TheGameratorT** - Coding and minor graphics
 - **Alzter** - Graphics
 - **Ed_IT** - Helped with custom sprite code
 - **Doc_Static** - Informer (was present at E3 2005)
 - **SiropDeViolette** - Informer (was present at E3 2005)
