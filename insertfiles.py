#Todo: currently ignores new files
from pathlib import Path
import ndspy.rom

rom_filename = 'rom.nds'
rom = ndspy.rom.NintendoDSRom.fromFile(rom_filename)

for path in Path('source_nitrofs').rglob('*.*'):
    path_formatted = Path(*path.parts[1:]).as_posix()
    with open(path, 'rb') as extracted_file:
        rom.setFileByName(path_formatted, extracted_file.read())
rom.saveToFile(rom_filename)
