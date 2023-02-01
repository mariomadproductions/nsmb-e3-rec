#!/usr/bin/env python3
from sys import argv
from pathlib import Path
import ndspy.rom
import subprocess

rom_filename = argv[1]
keeptmp = len(argv) > 1 and argv[2] == "keeptmp"
rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)
outputdir = "__tmp"

def run_ncp():
    subprocess.run(["ncpatcher"])

def main():
    
    run_ncp()

if __name__ == '__main__':
    main()
