from sys import argv
from pathlib import Path
import ndspy.rom

rom_filename = argv[1]
rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)
path_overrides_filename = 'source_nitrofs_path_overrides.txt'
path_overrides = {}

#Generate dictionary from filename overrides file
try:
    with open(path_overrides_filename, 'r') as path_overrides_file:
        for line in path_overrides_file:
            line_interpreted = line.split('\n')[0].split(sep=',')
            path_overrides[line_interpreted[0]] = int(line_interpreted[1])
except FileNotFoundError:
    pass

#Insert files into ROM
for path in Path('source_nitrofs').rglob('*.*'):
    path_formatted = Path(*path.parts[1:]).as_posix()
    with open(path, 'rb') as extracted_file:
        if path_formatted in path_overrides:
            rom.files[path_overrides[path_formatted]] = extracted_file.read()
        else:
            rom.setFileByName(path_formatted, extracted_file.read())
        print('Inserted external file ' + path_formatted)
rom.saveToFile(rom_filename)
