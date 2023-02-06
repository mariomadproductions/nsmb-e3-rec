#!/usr/bin/env python3
from sys import argv
from pathlib import Path
import ndspy.rom
from subprocess import check_output

if len(argv) < 2:
    print("Missing first argument: target rom path")
    exit(0)

rom_filename = argv[1]
rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)
path_overrides_filename = 'nitrofs_overrides.txt'
newfs_dir = 'nitrofs'

def insert_nitrofs():
    #Generate dictionary from filename overrides file
    path_overrides = {}
    with open(path_overrides_filename, 'r') as path_overrides_file:
        for line in path_overrides_file:
            line_interpreted = line.split('\n')[0].split(sep=',')
            path_overrides[line_interpreted[0]] = int(line_interpreted[1])

    #Insert files into ROM
    for path in Path(newfs_dir).rglob('*.*'):
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

def insert_banner():
    rom.iconBanner = open(newfs_dir + '/banner.bin', 'rb').read() # Install banner
    print('Inserted banner')

def get_git_revision_short_hash():
    return check_output(['git', 'rev-parse', '--short', 'HEAD']).strip()

def insert_buildtime():
    rom.setFileByName('BUILDTIME', get_git_revision_short_hash())
    print('Inserted buildtime')

def main():
    insert_nitrofs()
    insert_banner()
    insert_buildtime()
    rom.saveToFile(rom_filename)

if __name__ == '__main__':
    main()
