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
#copy of moveFlags py for moving name and descriptions to battle_moves
#search [move_name] set print to true
#store move name as key for table/array 
#line sub {  replae w brack line break space field data
#then set print to false so doesnt reprint on next bracket

#do that for entire file then repeat for name data
#print descriptions first use same filter cat
#will result in name being above descriptions
# or can make one dictionary w two fields
#move name as key w name and description as fields 
#hmm

'''
reviewed dictioanry stuff locked to pairs can't have
one key value for multiple values
instead have to have nested dictionary
with that can make dictionary based on move name
have name and description field
then can just print fields

ok had hard time figuring out how to create nested 
w names I need but researched seems
best plan is create empty potentially global dictionary yeah global

screw it cant figure out can just make 2 dicts arrays
for move and description attempt find iterable
that matches list id and use for both
so don't have to double loop
'''

import re

nameDict = {}
descriptionDict = {}

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/text/move_info.h', 'r')
lines = infile.readlines()
newId = re.compile(r'(MOVE\w+)')
strTarget = re.compile(r'(COMPOUND\w+STRING.*)')

add2List = False #if encounter .category set to true start appending, set false on .valid
run = 0 #'set true after reach line where move struct starts'
Printed = False


'''
ok understand now need both of these to be array
then use zip at end to organize them into key pairs
so I need a list of names and a list of flags lists
'''


 #use above arrays to create dictionary format SizeDict = dict(zip(moveId, moveFlags))

for line in lines:

    if re.compile(r'MOVE_NONE').search(line):
        add2List = True
    
    if re.compile(r'\};').search(line):
        add2List = False

    if re.compile(r'gMoveDescriptionPointers').search(line):
        run = 1
    if re.compile(r'gMoveNames').search(line):
        run = 2
    #add update desription dictionary
    #with moveId and desc
    #add2List uses to prevent bringing in array name llne w moves_count
    if run == 1 and add2List == True:
        if Move := newId.search(line):
            redline = re.sub(r'\\n', '/n',line)
            if string := strTarget.search(redline):
                descriptionDict.update({Move.group(1) : string.group(1)})

    #add update movename dictionary
    #with moveId and name
    if run == 2 and add2List == True:
        if Move := newId.search(line):
            if string := strTarget.search(line):
                nameDict.update({Move.group(1) : string.group(1)})

    '''if run == 1:
        if a := newId.search(line):
            #what I need is loop moveId for a match
            #to a.group(1) and do a line sub with that value
            #replacing a.group(1)
            for x in moveId:
                if a.group(1) in x:
                    add2List = a.group(1)
                    line = line.replace(add2List, x)
                    line = line.replace(';\n', '')
    newlines.append(line)   '''         
        

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
#data = dict(zip(moveId, moveFlags))
#x = data.keys()
#print(newlines)
#x = data.values()
#print(moveId[0])
#y = moveId[0]
#x = data.get('[MOVE_POUND]')
#print(x)
#print(data)
#print(descriptionDict)
infile.close()

'''outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/text/move_info.h', 'w')
outfile.writelines(newlines)
outfile.close()'''

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




infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/battle_moves.h', 'r')
lines = infile.readlines()
#to avoid looping dict use reg to pull file moveid in brackets
#can use get function to compare against dict keys
#if matching will return values else returns none
#store return value and assign if not none
moveId = re.compile(r'(MOVE_\w+)\]')
move = 0
values = 0

Active = False # gBattleMoves
Start = False #move_none
Print = False #{ change to moveId match within moveID match set false after line replace  
Run = False

newlines = []


for line in lines:

    if re.compile(r'gBattleMoves').search(line):
        Active = True
    
    if re.compile(r'MOVE_NONE').search(line) and Active == True:
        Start = True

    #think here I need to find iterable oh 
    #I assign move here
    #this was problem print was being set back to true
    if Start == True:
        if a := moveId.search(line):
            move = a.group(1)
            Print = True

    #set Print to false in run portion of script
    #so doesnt retrigger within same moveId
    #actually dont need run value can just 
    #put logic here and set print false
    #mostly works but meed prevent removal of \ in description
    #this most important condition isnt working
    if re.compile(r'\{').search(line) and Print == True:
        Print = False
        #descString = (descriptionDict.get(move))
        #descString = re.sub(r'\n', r'\\n', str(descString))
        line = re.sub(r'\{', '{\n        ' + '.name = ' + str(nameDict.get(move)) + '\n'
        + '        ' + '.description = ' + str(descriptionDict.get(move)),line)

    #if Print == True and re.compile(r'\.effect').search(line):
    #    Print = False

    #after script run vs code replace w regex
    #(\w)/n
    #$1\\n
    newlines.append(line)
    
infile.close()
    
outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/battle_moves.h', 'w')
outfile.writelines(newlines)
outfile.close()
#'''