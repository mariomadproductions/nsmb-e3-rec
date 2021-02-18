#!/usr/bin/env python3
from sys import argv
from pathlib import Path
import ndspy.rom

rom_filename = argv[1]
rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)
path_overrides_filename = 'source_nitrofs_path_overrides.txt'
path_overrides = {}

#Generate dictionary from filename overrides file
with open(path_overrides_filename, 'r') as path_overrides_file:
    for line in path_overrides_file:
        line_interpreted = line.split('\n')[0].split(sep=',')
        path_overrides[line_interpreted[0]] = int(line_interpreted[1])

#Insert files into ROM
for path in Path('source_nitrofs').rglob('*.*'):
    path_formatted_ = Path(*path.parts[1:])
    path_formatted = path_formatted_.as_posix()
    with open(path, 'rb') as extracted_file:
        if path_formatted in path_overrides:
            # Get file ID
            fileID = path_overrides[path_formatted]
            
            # Rename file
            sub_folder = rom.filenames.subfolder(path_formatted_.parent.as_posix())
            sub_folder.files[fileID - sub_folder.firstID] = path_formatted_.name

            # Set file data
            rom.files[fileID] = extracted_file.read()
        else:
            if path_formatted != 'banner.bin':
                rom.setFileByName(path_formatted, extracted_file.read())
        print('Inserted external file ' + path_formatted)

rom.iconBanner = open('source_nitrofs/banner.bin', 'rb').read() # Install banner

rom.saveToFile(rom_filename)
