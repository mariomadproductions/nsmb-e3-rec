
# New Super Mario Bros. E3 2005 demo recreation
NSMBHD thread: https://nsmbhd.net/thread/5516-new-super-mario-bros-e3-2005-demo-recreation/  
Pull requests are welcome.


## Building
Prerequisites:
 - Git
 - GNU Arm Embedded Toolchain
 - GNU Make
 - Python 3
 - [ndspy](https://pypi.org/project/ndspy/)
 - [NSMBe 5.3 Beta](https://github.com/TheGameratorT/NSMB-Editor/releases)
 - NitroSDK (tested with NitroSDK-3_0-060125<sup>1</sup>)
 - Clean NSMB USA ROM<sup>2</sup> 

_Note: On Windows, you can install msys2 and then use pacman to get GNU Arm Embedded Toolchain, GNU Make etc. Alternatively, you can install the [devkitPro](https://github.com/devkitPro/installer/releases) "nds-dev" component, which includes its own versions of those._

Steps:
 - Clone the repo.
 - Go into the repo folder.
 - Copy the NitroSDK ``include`` folder contents into the repo `include` folder.
 - Run `convert_sdk.py`.
 - Place the ROM as ``rom.nds`` in the repo.
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
> Common filename: NitroSDK-3_0-060125.zip  
> Size: 58349333  
> CRC32: c023d994  
> MD5: eed72648a1a10a622ee65b7ee5d3e7f4  
> SHA1: 36b7d2f66b828f5575e96c4c689c2aaa592304f6  
> SHA256: b791c9e331bc0b2026c58c8cec0ea74a496b0594ea03c272af3f75b726a656cf

2\.  
> Common filename: New Super Mario Bros (USA).nds  
> Size: 33554432  
> CRC32: 0197576a  
> MD5: a2ddba012e5c3c2096d0be57cc273be5  
> SHA1: a22713711b5cd58dfbafc9688dadea66c59888ce  
> SHA256: 9f67fef1b4c73e966767f6153431ada3751dc1b0da2c70f386c14a5e3017f354
