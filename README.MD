
# New Super Mario Bros. E3 2005 demo recreation
NSMBHD thread: https://nsmbhd.net/thread/5516-new-super-mario-bros-e3-2005-demo-recreation/  
Pull requests are welcome.


## Building
Pre-requisites:
 - GNU Arm Embedded Toolchain
 - GNU Make
 - Python 3
 - [ndspy](https://pypi.org/project/ndspy/)
 - [NSMBe 5.3 Beta](https://github.com/TheGameratorT/NSMB-Editor/releases)
 - NitroSDK (tested with NitroSDK-3_0-060125)

_Note: On Windows, you can install msys2 and then use pacman to get GNU Arm Embedded Toolchain, GNU Make etc. Alternatively, you can install the [devkitPro](https://github.com/devkitPro/installer/releases) "nds-dev" component, which includes its own verions of those._

Steps:
 - Clone the repo.
 - Go into the repo folder.
 - Copy the NitroSDK ``include`` folder contents into the repo `include` folder.
 - Run `convert_sdk.py`.
 - Place a clean NSMB USA ROM<sup>1</sup> as ``rom.nds`` in the repo.
 - Run `insert_files.py rom.nds`.
 - Open `rom.nds` in NSMB Editor.
 - Go to the `Tools/Options` tab and click `Run 'make' and insert`. If you get a error message box just click continue.

## Credits

-   Hiccup - Research, direction, levels, sound edits and minor graphics
-   TheGameratorT - Coding and minor graphics
-   Alzter - Graphics
-   Zeferrao - Sound edits

### Special Thanks

-   KTRMAmbiance (aka Ambiance69) - Graphics
-   mrrikihino - Graphics
-   MeroMero - No level freeze code (nofreeze.s)
-   Ed_IT - Helped with custom sprite code
-   Doc_Static (aka Mspeter97) - First-hand demo information
    (was present at E3 2005)
-   SiropDeViolette (aka Simpson55) - First-hand demo
    information (was present at E3 2005)
-   KingYoshi - Research/translation of Dutch news articles
-   All contributors to the original
    [Beta Replica project](https://nsmbhd.net/thread/2198-nsmb-beta-replica-2005-demo-replica-v1-released/) (MarioFanatic64,
    Thierry et al)

## Notes
1\.  
> Size: 33554432  
> CRC32: 0197576A  
> MD5: A2DDBA012E5C3C2096D0BE57CC273BE5  
> SHA1: A22713711B5CD58DFBAFC9688DADEA66C59888CE  
> SHA256: 9F67FEF1B4C73E966767F6153431ADA3751DC1B0DA2C70F386C14A5E3017F354
