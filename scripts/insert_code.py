#!/usr/bin/env python3

import os
from sys import argv
import subprocess
import struct
import ndspy.rom

if len(argv) < 2:
    print("Missing first argument: target rom path")
    exit(0)

rom_filename = argv[1]
verbose = len(argv) > 2 and argv[2] == "--verbose"
outputdir = "__tmp"
ov9dir = outputdir + "/overlay9"
ov7dir = outputdir + "/overlay7"

def run_ncp():
    print("Running NCPatcher")

    args = ["ncpatcher"]
    if verbose:
        args.append("--verbose")
    subprocess.run(args)

def get_header(rom):
    return rom.save(updateDeviceCapacity=True)[0:0x4000]

def get_overlays(rom, tableData):
    ovs = []
    for i in range(0, len(tableData), 32):
        (ovID, ramAddr, ramSize, bssSize, staticInitStart, staticInitEnd,
            fileID, compressedSize_Flags) = struct.unpack_from('<8I', tableData, i)
        ovs.append(fileID)
    return ovs

def unpack():
    print("Extracting the code binaries")

    if not os.path.exists(outputdir):
        os.mkdir(outputdir)
    if not os.path.exists(ov9dir):
        os.mkdir(ov9dir)
    if not os.path.exists(ov7dir):
        os.mkdir(ov7dir)

    rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)

    with open(outputdir + "/header.bin", 'wb') as header_file:
        header_file.write(get_header(rom))
    with open(outputdir + "/arm9.bin", 'wb') as arm9_file:
        arm9_file.write(rom.arm9)
    with open(outputdir + "/arm7.bin", 'wb') as arm7_file:
        arm7_file.write(rom.arm7)
    with open(outputdir + "/arm9ovt.bin", 'wb') as arm9ovt_file:
        arm9ovt_file.write(rom.arm9OverlayTable)
    with open(outputdir + "/arm7ovt.bin", 'wb') as arm7ovt_file:
        arm7ovt_file.write(rom.arm7OverlayTable)

    ovs9 = get_overlays(rom, rom.arm9OverlayTable)
    for i in range(0, len(ovs9)):
        fileID = ovs9[i]
        with open(ov9dir + "/overlay9_" + str(i) + ".bin", 'wb') as ov_file:
            ov_file.write(rom.files[fileID])

    ovs7 = get_overlays(rom, rom.arm7OverlayTable)
    for i in range(0, len(ovs7)):
        fileID = ovs7[i]
        with open(ov7dir + "/overlay7_" + str(i) + ".bin", 'wb') as ov_file:
            ov_file.write(rom.files[fileID])

def pack():
    print("Merging the code binaries")

    rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)

    with open(outputdir + "/arm9.bin", 'rb') as arm9_file:
        rom.arm9 = arm9_file.read()
    with open(outputdir + "/arm7.bin", 'rb') as arm7_file:
        rom.arm7 = arm7_file.read()
    with open(outputdir + "/arm9ovt.bin", 'rb') as arm9ovt_file:
        rom.arm9OverlayTable = arm9ovt_file.read()
    with open(outputdir + "/arm7ovt.bin", 'rb') as arm7ovt_file:
        rom.arm7OverlayTable = arm7ovt_file.read()

    ovs9 = get_overlays(rom, rom.arm9OverlayTable)
    for i in range(0, len(ovs9)):
        fileID = ovs9[i]
        with open(ov9dir + "/overlay9_" + str(i) + ".bin", 'rb') as ov_file:
            rom.files[fileID] = ov_file.read()

    ovs7 = get_overlays(rom, rom.arm7OverlayTable)
    for i in range(0, len(ovs7)):
        fileID = ovs7[i]
        with open(ov7dir + "/overlay7_" + str(i) + ".bin", 'rb') as ov_file:
            rom.files[fileID] = ov_file.read()

    rom.saveToFile(rom_filename, updateDeviceCapacity=True)

def main():
    unpack()
    run_ncp()
    pack()
    print("Done")

if __name__ == '__main__':
    main()
