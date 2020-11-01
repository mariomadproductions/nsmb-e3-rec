# NSMB Nitro SDK converter by TheGameratorT
# 30th October 2020

import re
import glob
import sys

# Headers to ignore the global to local header change
libHeaders = ['stdio.h', 'stdarg.h']

# Regular Expressions
regex_clz = re.compile('\s+asm\s+\{\s+clz\s+x,\s+x\}')
regex_include = re.compile('(#include)\s*(<)')
regex_pragma_1 = re.compile('(#pragma)\s*(warn_padding)')
regex_pragma_2 = re.compile('(#pragma)\s*(unused)')
regex_pragma_3 = re.compile('(#pragma)\s*(thumb)')
regex_multichar = re.compile('\'.{4}\'')

def isLibHeader(txt: str):
    for x in libHeaders:
        if x in txt:
            return True
    return False

for filename in glob.iglob('./include/**/*.h', recursive=True):

    unix_filename = filename.replace('\\', '/')
    print('Processing {0}'.format(unix_filename))

    new_lines = []
    
    with open(filename, 'r') as f:

        text = ''.join(f.readlines())

        # Paretheses warning supression
        if(
            unix_filename == './include/nitro/gx/gx.h' or
            unix_filename == './include/nitro/gx/g3x.h'
            ):
            text = '#pragma GCC diagnostic push\n#pragma GCC diagnostic ignored "-Wparentheses"\n' + text + '\n#pragma GCC diagnostic pop'

        if(unix_filename == './include/nitro.h'):
            # Fix comment bug
            text = text.replace('mi/*.h', 'mi/(...).h')

        elif(
            unix_filename == './include/nitro/gx/g2.h' or
            unix_filename == './include/nitro/gx/gx.h' or
            unix_filename == './include/nitro/gx/gx_bgcnt.h'
            ):
            text = text.replace('*(volatile', '*(')

        elif(unix_filename == './include/nitro/os/common/spinLock.h'):
            text = text.replace('typedef volatile struct', 'typedef struct')

        elif(unix_filename == './include/nitro/math/math.h'):
            text = regex_clz.sub('\n    asm("clz x, x");', text)

        elif(unix_filename == './include/nitro/ctrdg/ARM9/ctrdg_backup.h'):
            text = text.replace('(*maxtime)', '*maxtime')
            text = text.replace('(*ctrdgi_fl_maxtime)', '*ctrdgi_fl_maxtime')

        elif(unix_filename == './include/nitro/wfs/format.h'):
            text = text.replace('(*sinit_init)', '*sinit_init')
            text = text.replace('(*sinit_init_end)', '*sinit_init_end')

        for line in text.split('\n'):

            # Convert lib header path to local header path
            if isLibHeader(line):
                newLine = line
            else:
                newLine = regex_include.sub('#include "', line)
                newLine = newLine.replace('.h>', '.h"')

            # Remove unknown pragmas
            newLine = regex_pragma_1.sub('//#pragma warn_padding', newLine)
            newLine = regex_pragma_2.sub('//#pragma unused', newLine)
            newLine = regex_pragma_3.sub('//#pragma thumb', newLine)

            # Multi-character constants
            mCharFound = regex_multichar.search(newLine)
            if mCharFound is not None:
                str1 = newLine[mCharFound.start():mCharFound.end()]
                str2 = str1[1:5]

                encoded = str2.encode('ascii')
                value = int.from_bytes(encoded, sys.byteorder)
                hex_str = hex(value)

                newLine = newLine.replace(str1, hex_str + ' //' + str1)
                # print(newLine)

            new_lines.append(newLine + '\n')

    with open(filename, 'w') as f:
        f.writelines(new_lines)
