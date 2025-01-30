#(ITEM_\wM\d+)\w*   use this regex for tms

import re

'''
'''

#first set items file,
#2nd set tmhm learnset file
'''
infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/items.h', 'r')
lines = infile.readlines()
regex = re.compile(r'(ITEM_\wM\d+)([A-Z0-9_]*,)')
lineid = re.compile(r'.secondaryId\s*=\s*(\d)')
itemId = None
IdSub = None
itemName = None
MoveSub = None
FoundVal = False
offset = True #base value is 0, so set to true to ensure could tell if was passing correct value
sizedata = None #fill these from dictionary value
offsetdata = None
new_lines = []
for line in lines:
    if m := regex.search(line):
        #itemId = m.group(1).replace('_', ' ').title().replace(' ', '')
        IdSub = m.group(2)
        MoveSub = 'MOVE' +IdSub
        #IdSub = m.group(1).replace(r'(ITEM_\wM\d+)',r'MOVE')
        #print(MoveSub)
        #re.sub(r'SPECIES_'+ mon +r'\]
        FoundVal = True
        #data = re.sub(r"//BACK_PIC\(MiniorCore+(.*)\)","BACK_PIC(MiniorCore)",data)
    if s := lineid.search(line):
        if FoundVal == True:
            line = line.replace('0,', MoveSub)
            #print(line)
        FoundVal = False
        
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
        #think can use, if put in all exceptions
    new_lines.append(line)
#infile.writelines(new_lines)
infile.close()#think group is reg stuff reg are broken into groups

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/items.h', 'w')
outfile.writelines(new_lines)
outfile.close()
'''


'''
infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/tmhm_learnsets.h', 'r')
lines = infile.readlines()
regex = re.compile(r'(ITEM_\wM\d+)([A-Z0-9_]*,)')
IdSub = None
MoveSub = None
FoundVal = False
new_lines = []
for line in lines:
    if m := regex.search(line):
        #itemId = m.group(1).replace('_', ' ').title().replace(' ', '')
        IdSub = m.group(2)
        MoveSub = 'MOVE' +IdSub
        line = MoveSub +'\n'
        #print(line)
    new_lines.append(line)
#infile.writelines(new_lines)
infile.close()#think group is reg stuff reg are broken into groups

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/tmhm_learnsets.h', 'w')
outfile.writelines(new_lines)
outfile.close()
'''