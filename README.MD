
# New Super Mario Bros. E3 2005 demo recreation
NSMBHD thread: https://nsmbhd.net/thread/5516-new-super-mario-bros-e3-2005-demo-recreation/  
Pull requests are welcome.


## Building
Pre-requisites:
 - GNU Arm Embedded Toolchain
 - GNU Make
 - Python 3
 - [ndspy](https://pypi.org/project/ndspy/)
 - [NSMBe 5.3 Beta](https://github.com/TheGameratorT/NSMB-Editor/releases) (works on Windows and Wine, with .NET Framework)
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
    
## Notes
1\.  
> Size: 33554432  
> CRC32: 0197576A  
> MD5: A2DDBA012E5C3C2096D0BE57CC273BE5  
> SHA1: A22713711B5CD58DFBAFC9688DADEA66C59888CE  
> SHA256: 9F67FEF1B4C73E966767F6153431ADA3751DC1B0DA2C70F386C14A5E3017F354
