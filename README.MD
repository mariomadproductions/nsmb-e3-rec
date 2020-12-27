
# nsmb-e3-rec
This project aims to recreate the New Super Mario Bros. E3 2005 demo.

## Building
Pre-requisites:
 - [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
 - [GNU Make](https://www.msys2.org/)
 - [Python 3](https://www.python.org/downloads/)
 - [ndspy](https://pypi.org/project/ndspy/)
 - [NSMBe 5.3 Beta](https://github.com/TheGameratorT/NSMB-Editor/releases) (currently Windows-only)
 - NitroSDK (tested with NitroSDK-3_0-060125)

_Note: The [devKitPro](https://github.com/devkitPro/installer/releases) "nds-dev" component includes GNU Make and GNU Arm Embedded Toolchain._

Steps:
 - Clone the repo.
 - Go into the repo folder.
 - Copy the NitroSDK ``include`` folder contents into the repo `include` folder.
 - Run `convert_sdk.py`.
 - Place a clean NSMB USA ROM<sup>1</sup> as ``rom.nds`` in the repo.
 - Run `insert_files.py rom.nds`.
 - Open `rom.nds` in NSMB Editor.
 - Go to the `Tools/Options` tab and click `Run 'make' and insert`. If you get a error message box just click continue.

## Playing
The hack has been tested on:
 - [DeSmuME](http://desmume.org/download/)
 - [MelonDS](http://melonds.kuribo64.net/downloads.php)
 - [nds-bootstrap](https://github.com/DS-Homebrew/nds-bootstrap) using the [TWiLight Menu++](https://github.com/DS-Homebrew/TWiLightMenu/releases) frontend
 - R4i-SDHC 3DS RTS flashcard (default firmware)
 - Acekard 2i (AKAIO)

## Credits
 - **Hiccup** - Research, direction, levels and minor graphics
 - **TheGameratorT** - Coding and minor graphics
 - **Alzter** - Graphics

### Special Thanks
 - **KTRMAmbiance** (aka Ambiance69) - Graphics
 - **MeroMero** - No level freeze code (nofreeze.s)
 - **Ed_IT** - Helped with custom sprite code
 - **Doc_Static** (aka Mspeter97) - First-hand demo information (was present at E3 2005)
 - **SiropDeViolette** (aka Simpson55) - First-hand demo information (was present at E3 2005)
 - **All contributors to the original "Beta Replica" project**

## Notes
1\.  
> Size: 33554432  
> CRC32: 0197576A  
> MD5: A2DDBA012E5C3C2096D0BE57CC273BE5  
> SHA1: A22713711B5CD58DFBAFC9688DADEA66C59888CE  
> SHA256: 9F67FEF1B4C73E966767F6153431ADA3751DC1B0DA2C70F386C14A5E3017F354
