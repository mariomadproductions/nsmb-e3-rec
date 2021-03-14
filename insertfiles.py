#!/usr/bin/env python3
"""insertfiles.

Usage:
multisum.py [--type=<type>] <rom>

Options:
  -h, --help         Show this screen.
  -v, --version      Show version.
  -t, --type=<type>  Type of file(s) to insert [default: nitrofs]
                     Values:
                     nitrofs
                     banner
"""
from docopt import docopt
from sys import argv
from pathlib import Path
import ndspy.rom
from subprocess import check_output

arguments = docopt(__doc__, version='multisum.py')
rom_filename = arguments['<rom>']
rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)
path_overrides_filename = 'source_nitrofs_path_overrides.txt'

def insert_nitrofs():
    #Generate dictionary from filename overrides file
    path_overrides = {}
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

def insert_banner():
    rom.iconBanner = open('source_hdr/banner.bin', 'rb').read() # Install banner

def get_git_revision_short_hash():
    return check_output(['git', 'rev-parse', '--short', 'HEAD']).strip()

def insert_buildtime():
    rom.setFileByName('BUILDTIME', get_git_revision_short_hash())
    
def main():
    if arguments['--type'] == 'nitrofs':
        insert_nitrofs()
    elif arguments['--type']  == 'banner':
        insert_banner()
    insert_buildtime()
    rom.saveToFile(rom_filename)

if __name__ == '__main__':
    main()
