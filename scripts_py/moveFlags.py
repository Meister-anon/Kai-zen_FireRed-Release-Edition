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

data = {} #forgot need this global

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/moves_info.h', 'r')
lines = infile.readlines()
newId = re.compile(r'(\[MOVE_\w+?\])')

add2List = False #if encounter .category set to true start appending, set false on .valid
run = False #'set true after reach line where move struct starts'
Printed = False
previous_line = False #'since want store after .category use when previous line matches'

'''
ok understand now need both of these to be array
then use zip at end to organize them into key pairs
so I need a list of names and a list of flags lists
'''
moveFlags = []
moveId = [] 

 #use above arrays to create dictionary format SizeDict = dict(zip(moveId, moveFlags))

for line in lines:
    if re.compile(r'gMovesInfo').search(line):
        run = True
    
    if run == True:
        if a := newId.search(line):
            flagList = []
            moveId.append(a.group(1))
            
        if re.compile(r'.category').search(str(previous_line)):
            add2List = True
            Printed = False
        
        if re.compile(r'.validApprenticeMove').search(line) or re.compile(r'    \},').search(line):
            Printed = True

        #since conditionals executed in sequence think should be fine
        if add2List == True:
            
            if Printed == False:
                flagList.append(line)
            if Printed == True:
                moveFlags.append(flagList)
                add2List = False


        previous_line = line

'''
#for the most part works
#but seems gets out of order at some point?
#allthe move flags are in, but at some point
started printing from one move id back?
found problem my expression isn't catching every move id...
wrong,issue condition setting Printed True (reset condition)
is being triggered when it shouldn't luckily only a single line
in move make it rains additional effects

seems simple fix just shift white space so doesn't trigger filter
when I print to fill will need to revert that to make it look nice
...nope that did nothing
ok believe found problem wasn't a script error was a file error
one of the moves had the end bracket with bad white space
yup that did it
'''
data = dict(zip(moveId, moveFlags))
#x = data.keys()
#print(x)
#x = data.values()
#print(moveId[0])
#y = moveId[0]
#x = data.get('[MOVE_POUND]')
#print(x)
#print(data)
infile.close()

'''
read battle_moves file 
look for matches to move id 
to then look for previous line .split
if found add move flags to line 
or maybe instead if current line matches .split
do a line sub where I keep current line
then do a new line and add in the move flags from array
yeah that's better

ok here will just read file and do line sub with dict values
and update file
will put new flags after line w .split
so line sub on line w .split
put .split rest of line \n dict value for move id
'''

#'''
infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/moves_info.h', 'r')
lines = infile.readlines()
#to avoid looping dict use reg to pull file moveid in brackets
#can use get function to compare against dict keys
#if matching will return values else returns none
#store return value and assign if not none
reg = re.compile(r'(\[MOVE_\w+?\])')
move = 0
values = 0

newlines = []


for line in lines:
    #look for moveId on line
    #assign to move
    if a := reg.search(line):
        move = a.group(1)
        #print(move)
        values = data.get(move)
        #print(values)
        #break

    #appears to work issue is need revert constant name changes
    #as doesn't allign with dictionary smh
    #luckily simple as checking history of move constants file
    if re.compile(r'\.split').search(line):
        #not none do line replace else keep line as is, do nothing
        if values != None:
            #print(str(values))
            line = line.replace(line, line + str(values))
            line = re.sub(r"'", "",line)
            line = re.sub(r"\[", "",line)
            line = re.sub(r"\]", "",line)
            line = re.sub(r"\\n, ", "\n",line)
            line = re.sub(r"\\n", "\n",line)
            #print(line)
            #break
    newlines.append(line)
    
infile.close()
    
outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/moves_info.h', 'w')
outfile.writelines(newlines)
outfile.close()
#'''