
import re

"""
exceptions = [ # the following exceptions are hardcoded to streamline the process. you may need to manually check what happens in case you have added forms that work similar to these below
    ["AlcremieStrawberryRubyCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryMatchaCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryMintCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryLemonCream", "AlcremieStrawberry"],
    ["AlcremieStrawberrySaltedCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryRubySwirl", "AlcremieStrawberry"],
    ["AlcremieStrawberryCaramelSwirl", "AlcremieStrawberry"],
    ["AlcremieStrawberryRainbowSwirl", "AlcremieStrawberry"],
    ["AlcremieBlueberryVanillaCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryRubyCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryMatchaCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryMintCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryLemonCream", "AlcremieBlueberry"],
    ["AlcremieBlueberrySaltedCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryRubySwirl", "AlcremieBlueberry"],
    ["AlcremieBlueberryCaramelSwirl", "AlcremieBlueberry"],
    ["AlcremieBlueberryRainbowSwirl", "AlcremieBlueberry"],
    ["AlcremieLoveVanillaCream", "AlcremieLove"],
    ["AlcremieLoveRubyCream", "AlcremieLove"],
    ["AlcremieLoveMatchaCream", "AlcremieLove"],
    ["AlcremieLoveMintCream", "AlcremieLove"],
    ["AlcremieLoveLemonCream", "AlcremieLove"],
    ["AlcremieLoveSaltedCream", "AlcremieLove"],
    ["AlcremieLoveRubySwirl", "AlcremieLove"],
    ["AlcremieLoveCaramelSwirl", "AlcremieLove"],
    ["AlcremieLoveRainbowSwirl", "AlcremieLove"],
    ["AlcremieStarVanillaCream", "AlcremieStar"],
    ["AlcremieStarRubyCream", "AlcremieStar"],
    ["AlcremieStarMatchaCream", "AlcremieStar"],
    ["AlcremieStarMintCream", "AlcremieStar"],
    ["AlcremieStarLemonCream", "AlcremieStar"],
    ["AlcremieStarSaltedCream", "AlcremieStar"],
    ["AlcremieStarRubySwirl", "AlcremieStar"],
    ["AlcremieStarCaramelSwirl", "AlcremieStar"],
    ["AlcremieStarRainbowSwirl", "AlcremieStar"],
    ["AlcremieCloverVanillaCream", "AlcremieClover"],
    ["AlcremieCloverRubyCream", "AlcremieClover"],
    ["AlcremieCloverMatchaCream", "AlcremieClover"],
    ["AlcremieCloverMintCream", "AlcremieClover"],
    ["AlcremieCloverLemonCream", "AlcremieClover"],
    ["AlcremieCloverSaltedCream", "AlcremieClover"],
    ["AlcremieCloverRubySwirl", "AlcremieClover"],
    ["AlcremieCloverCaramelSwirl", "AlcremieClover"],
    ["AlcremieCloverRainbowSwirl", "AlcremieClover"],
    ["AlcremieFlowerVanillaCream", "AlcremieFlower"],
    ["AlcremieFlowerRubyCream", "AlcremieFlower"],
    ["AlcremieFlowerMatchaCream", "AlcremieFlower"],
    ["AlcremieFlowerMintCream", "AlcremieFlower"],
    ["AlcremieFlowerLemonCream", "AlcremieFlower"],
    ["AlcremieFlowerSaltedCream", "AlcremieFlower"],
    ["AlcremieFlowerRubySwirl", "AlcremieFlower"],
    ["AlcremieFlowerCaramelSwirl", "AlcremieFlower"],
    ["AlcremieFlowerRainbowSwirl", "AlcremieFlower"],
    ["AlcremieRibbonVanillaCream", "AlcremieRibbon"],
    ["AlcremieRibbonRubyCream", "AlcremieRibbon"],
    ["AlcremieRibbonMatchaCream", "AlcremieRibbon"],
    ["AlcremieRibbonMintCream", "AlcremieRibbon"],
    ["AlcremieRibbonLemonCream", "AlcremieRibbon"],
    ["AlcremieRibbonSaltedCream", "AlcremieRibbon"],
    ["AlcremieRibbonRubySwirl", "AlcremieRibbon"],
    ["AlcremieRibbonCaramelSwirl", "AlcremieRibbon"],
    ["AlcremieRibbonRainbowSwirl", "AlcremieRibbon"]
]
"""

#MasterDict = {}
SizeDict = {}
YOffsetDict = {}
mon = [] #species list to loop over in destination file
speciesList = []
size = []
Yoff = []

sourcefile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon_graphics/back_pic_coordinates.h', 'r')
lines = sourcefile.readlines()
reg = re.compile(r'\[(\w+)\]')
sizeValue = re.compile(r'\.size = (\w+)')
OffsetValue = re.compile(r'\.y_offset = (\w+)')
species = None  #may not need
#new_lines = []


for line in lines:
    if m := reg.search(line): #something is wrong here its not progressing, its always reading as none, when none is first value
        #print(reg.match(line)) #identified issue had to use search instead of match cuz of how match works, w my changed regex
        species = m.group(1)
        speciesList.append(species)

    if s := sizeValue.search(line):  #not explained well in w3chools but believe to be do assignment then continue expression/condition
        size.append(s.group(1))     #so here, is do assignment, then run if, conditional, can also be used in function argument ex. print(x:3)
        #print(species)
    if y := OffsetValue.search(line):
        Yoff.append(y.group(1))

SizeDict = dict(zip(speciesList, size))
YOffsetDict = dict(zip(speciesList, Yoff)) # should build dictionaries for use in other file, after finish loop

#print(speciesList)
#print(size)
#print(Yoff) #tested and all three print correctly
#print(len(Yoff))    #for some reaosn Yoff is printing less, though in file they are all equal at 1288???
sourcefile.close()



"""
        #creates ditionary based on values, want species = to mean dict name is that of regex species
        don't know if work, species is a value/variable, so possible its only storing the name species itself,
        so need test and figure out
"""

"""
        a = dict(one=1, two=2, three=3)
        b = {'one': 1, 'two': 2, 'three': 3}
        c = dict(zip(['one', 'two', 'three'], [1, 2, 3])) # of interest
        d = dict([('two', 2), ('one', 1), ('three', 3)])
        e = dict({'three': 3, 'one': 1, 'two': 2})
        f = dict({'one': 1, 'three': 3}, two=2)

        multiple identical methods for dictionary creation
        I'm curious of method 3/c if its bracketed because its an array
        then its possible I could use two arrays compiled separately...
        no that wouldn't work the key would be the value I need, making it  unusable

        but if I wanted to do it the lazy way I could potentially use species and just store one value at a time.
        rather than both size and offset
        could do species & size or species & offset
        taht would work then would just need a separate species value in the destination file
        and do a line check for size/yoffset
        then do the dictionary loop for key that matches species and substitute the value

        potential difficult part is just ensuring I store the species values in a proper syntax to be used as keys
        i.e make sure when appended to the species array its done so along with open and close quotes surrouding the value

        and of course all this is assuming I can use dictionary case C as dict(zip(arrayname, 2ndarrayname))
        #back to the drawing board, looked up zip, and it doesn't create arrays it specifically creates tuples
        which are explicitly 3 value arrays, wait no that was my assumption tuple is NOT limited to 3 values
        but I do have to be careful w using zip as it seems it allows ranges of different length data

        -zip() is often used in cases where the iterables are assumed to be of equal length.
        In such cases, its recommended to use the strict=True option. Its output is the same as regular zip():-
        ok got this verified for the most part, they said I'm good to go far as an attempting

        so reset layouot of py script to use case C
"""

    #if species:
        #for x in exceptions:
        #    if species == x[0]:
        #        species = x[1]
        #line = line.replace('CircledQuestionMark', species)
        
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
    #new_lines.append(line)



infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/species_graphic_info.h', 'r')
lines = infile.readlines()
regex = re.compile(r'\[(\w+)\]')
frontdata = re.compile(r'BACK_COORD\((0x88)(,0)\)')
speciesdata = None
Size = None
offset = True #base value is 0, so set to true to ensure could tell if was passing correct value
sizedata = None #fill these from dictionary value
offsetdata = None
new_lines = []
for line in lines:
    if m := regex.search(line):
        speciesdata = m.group(1)
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
                    line = line.replace(str(Size), sizedata + r', ')
            for y in YOffsetDict:
                if speciesdata == y:
                    offsetdata = YOffsetDict[y] #ok found issue for some reason ofset list is not same size as other lists...
                    line = line.replace(str(offset), offsetdata)
                    #print(line)
            #print(line)#can't determine why not printing right thnkonly thing left is check count num entries
             # need add comma to group 1 replace
            #print(line)
            #print(offsetdata) #sizedata prints correct but offsetdata is wrong?
            #issue here, printing oddly
            #print(line)
            #for some reason it gets broken on loop and repeats end values multiple times?
            #egg ends on 20, and it repeats eggs value but all other values seem to be fine
            
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
        #think can use, if put in all exceptions
    new_lines.append(line)
#infile.writelines(new_lines)
infile.close()#think group is reg stuff reg are broken into groups

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/species_graphic_info.h', 'w')
outfile.writelines(new_lines)
outfile.close()

#if that is correct than I might be able to use that to store 2 values
#say match group1 for mon size  and group2 for the yoffset?

#idea use nested dictionary(curly bracket) to store size and offset
#loop the dictionary to keep it in line with the main loop
# since I"m moving on line don't want to have to loop every line so instead
#make dictionary values match species_name  syntax so every time I reach a line tha has that
#syntax, use regex to identify, well I have "m" for that already,
#but when I have that, run the dictionary loop and update the values of size and offset based off that,
#then can use those to assign stored values, following that I should just need 
#the filter to make sure only fills frontcoord, then change for back coord

#but main problem is still the method of creating the dictionary lookup table/
#i.e themain dictionary making the individual ones should be no problem
#BUt I need to understand how to add the ones I create within the first loop,
#to a bigger table, either using the dict command,
#or some other method or if there's a way to append it idk
#well since I plan use the species_name as the key I guess what I could do is make a list
#of those values as I go and use that to generate the master dictionary

"""
this is a comment -

child1 = {
  "name" : "Emil",
  "year" : 2004
}
child2 = {
  "name" : "Tobias",
  "year" : 2007
}
child3 = {
  "name" : "Linus",
  "year" : 2011
}

myfamily = {
  "child1" : child1,
  "child2" : child2,
  "child3" : child3
}

note this is the syntax for nested dictionaries I'd have to follow
#think will use dict command for loop is much simpler, just need store values as species = dict etc.
and since its within loop species will never be the same
#order
make species list  List
make values for size and offset and species
open front pic coord file to read
loop by line
check for species_  match
if line matches
assign reg to species & append species constant to species list
filter for .size match, and take value assign to size
filter for .y_offset match assign to Yoffset
at same time create dictionary as that's last value for the species block I need
do species = dict( size,  Yoffset)

after that I have everything I need, its just a matter of building the master dictionarty from the species list
but idk maybe its possible to append the dictionary to the main dictionary?
yeah I think that can work, can use append

but enconter other issue plan was to use species to be for dictionary
but species is a variable not a string


idea make variable end of list set to false
make it say add comma before new line if end of list is false? (don't know how I would do that...)

and define end of list based on speciesname value, just basing on last value from source table
for front/back coord last value is species egg, preceded by frilish female

even better since I'm using the species constant rather than actual species  name won't have to worry about exclusions/duplicates
"""

#outfile = open('/usr/decomp/Kai-zen_Firered-Release-Edition/src/data/pokemon/species_graphic_info.h', 'w')
#outfile.writelines(new_lines)
#outfile.close()