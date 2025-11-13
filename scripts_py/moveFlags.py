'''setup to copy over move flag data from EE moves_info file
require take list of data from EE  populate to own array based on move ids
plan print beneath .flags spacing is uneven for .flags potentially see
if can copy preceding whitespace to put after new line
since some moves have multiple flag options based on defines
will also need a state toggle to identify if I've already printed \
data for said move id, and reset at regex of [MOVE_
for EE will setup range want everything from below .category
and inclusively ending with .battleAnimScript
This will include the additional effects rework which I'll aplly after I'm done
w flags.

Will need to make pass over file once everything is copied to remove
unnecessary additions...well I DO want contests eventually it'd just be too much
for me to add ok for future reference MAY keep contest stuff just remove the 
zmove line, which I can do with simple regex search

do like tm_list_Data file use const struct BattleMove gBattleMoves[MOVES_COUNT] =
as the start point

looking at species_graphics.py
appears I may need to make a dictionary to properly line up file
'''

import re

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/moves_info.h', 'r')
lines = infile.readlines()
newId = re.compile(r'\[MOVE_(\w+?)\]')
reg = re.compile(r'.category')
species = None
run = False 'set true after reach line where move struct starts'
Printed = False
previous_line = None 'since want store after .category use when previous line matches'
moveFlags = []
mon = []
size = []
Yset = []
for line in lines:
    if re.compile(r'gMovesInfo').search(line)
        run = True
    
    if run == True
        if m := reg.match(line):
            #mon.append(reg)
            species = m.group(1).replace('_', ' ').title().replace(' ', '')
        if species:
            if re.compile(r'.abilityLearnset = NULL').search(line):
            #for x in exceptions:
            #    if species == x[0]:
            #        species = x[1]
                line = line.replace(r'NULL', 's'+species+'AbilityLearnset')
                print(line)
            #size.append(r'\.size = (\w)')
            #Yset.append(r'\.y_offset = (\w)')
            #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
        
        moveFlags.append(line)
infile.close()

outfile = open('/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon_graphics/front_pic_coordinates.h', 'w')
outfile.writelines(new_lines)
outfile.close()