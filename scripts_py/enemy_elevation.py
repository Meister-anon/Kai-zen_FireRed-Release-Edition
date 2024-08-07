import re
#file to take values from enemy_mon_elevation.h and transpose into base stats file,

ElevationDict = {}

species = None  #tested regex in regex101 confirm it works, note remember need remove "r"  and quotations for evaluation of expression there
elevation = None

species_array = []
elevation_array = []
'''
/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon_graphics/enemy_mon_elevation.h

EX data, what Ineed for this file is just make a single dictionary and then do a line replace in base stats
for enemymonelevation = 0,  replace with enemymonelevation = value

just need global dictionary made from enemy mon file then put in base stats
following that just uncomment the new gen values that already have that value filled

check if key/species matches speces in file, if so add enemeyMonElevation field below noFLip
since that is constant easy to tack on there

replace noFlip = false 

like so

        .noFlip = FALSE,
        .enemyMonElevation = 18,

        if doing by line think will do 

if line is nofleip = FALSE,

do line replace for

        .noFlip = FALSE,
        .enemyMonElevation = 0,

using line escape to create new line think should work since I'm still doing the entire operation on said line

uner that do search for elevation = 0, if matches dictionary species replace with actual elevation
'''

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon_graphics/enemy_mon_elevation.h', 'r')
lines = infile.readlines()
reg = re.compile(r'\[(\w+)\] = (\w+)') #hopefully break up constant and value into groups to use
#regex = re.compile(r'\[(\w+)\]')
#frontdata = re.compile(r'FRONT_COORD\((0x88,)(0)\)')
speciesdata = None
Size = None
offset = True #base value is 0, so set to true to ensure could tell if was passing correct value
sizedata = None #fill these from dictionary value
offsetdata = None
new_lines = []
for line in lines:
    if m := reg.search(line):
        species_array.append(m.group(1))
        elevation_array.append(m.group(2))
        #species = m.group(1)
        #elevation = m.group(2)

ElevationDict = dict(zip(species_array, elevation_array))
#print(species_array)
#print(elevation_array) #tested and all three print correctly
#print(len(elevation_array))    #for some reaosn Yoff is printing less, though in file they are all equal at 1288???
infile.close()

destFile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/species_graphic_info.h', 'r')
lines = destFile.readlines()
species = None
Elevation = None
new_lines = []
reg = re.compile(r'\[(\w+)\]') #hopefully break up constant and value into groups to use
#reg2 = re.compile(r'\.noFlip')
elev = re.compile(r'\.enemyMonElevation = 0')
for line in lines:
    if b := reg.search(line):
        species = b.group(1)
    if reg2.search(line):
        for x in ElevationDict:
            if species == x:
                line = line.replace(r'.noFlip = FALSE,','.noFlip = FALSE,\n        .enemyMonElevation = 0,')#hopefully works
                line = line.replace(r'.noFlip = TRUE,','.noFlip = TRUE,\n        .enemyMonElevation = 0,')#hopefully works
                #print(line)
    if elev.search(line):
        for y in ElevationDict:
            if species == y:
                Elevation = ElevationDict[y]
                line = line.replace(r'      .enemyMonElevation = 0','      .enemyMonElevation = ' + Elevation)
                print(line)
    new_lines.append(line)
#print(new_lines)
#destFile.writelines(new_lines)
destFile.close()

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/species_graphic_info.h', 'w')
outfile.writelines(new_lines)
outfile.close()

'''

    if s := frontdata.search(line):
        Size = s.group(1)
        offset = s.group(2) #build array list from other file, fill in to end, maybe need make 3 value array?
        if speciesdata:                 #could do species size offset, and if species match line replace group1 and 2 with size and offset?
        #for x in exceptions:
        #    if species == x[0]:
        #        species = x[1]
        #print(offset) seems to work so far here
        #line = line.replace('CircledQuestionMark', species)
        #what need is 2 for loops to match species, to pull values from dictionary
        #SizeDict = dict(zip(speciesList, size))
        #YOffsetDict = dict(zip(speciesList, Yoff))
            for x in SizeDict:
                if speciesdata == x:
                    sizedata = SizeDict[x]
            for y in YOffsetDict:
                if speciesdata == y:
                    offsetdata = YOffsetDict[y] #ok found issue for some reason ofset list is not same size as other lists...
            #print(line)#can't determine why not printing right thnkonly thing left is check count num entries
            #line = line.replace(str(Size), sizedata + r', ') # need add comma to group 1 replace
            #print(offsetdata) #sizedata prints correct but offsetdata is wrong?
            line = line.replace(str(offset), offsetdata)#issue here, printing oddly
            #for some reason it gets broken on loop and repeats end values multiple times?
            #egg ends on 20, and it repeats eggs value but all other values seem to be fine
            
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
        #think can use, if put in all exceptions
    new_lines.append(line)
#infile.writelines(new_lines)
infile.close()

'''