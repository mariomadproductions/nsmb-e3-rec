# All of the APIs used below are undocumented and subject to change. But anyway...

import ndspy.model
with open('item_block.nsbmd', 'rb') as f:
    data = f.read()
nsbmd = ndspy.model.NSBMD(data)
palette = nsbmd.palettes[0]  # for the first palette -- change the number if you want a different one

# The palette object (instance of ndspy.texture.Palette) has a .colors attribute which is a list of integers (16-bit color values)
# You can convert them to/from RGB(A) tuples using the functions in the ndspy.color module

# also add "import ndspy.texture" at the top of the script

nsbmd.palettes.append(palette)
nsbmd.palettes.append(palette)

# When you're done modifying the palette,
with open('item_block_extended.nsbmd', 'wb') as f:
    f.write(nsbmd.save())