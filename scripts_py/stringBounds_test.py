#meant to read file and return filename and line at which string exceeds intended length of line
#think best to set hard set filename rather than try to automate
#ok think what I'll have to do is loop lines create loopid iterative variable to count the number of lines to be returned when I find an error
#set state toggle of found error to be reset on each new line well at start of main conditional code block
#since don't want to read the entire file I use a line within  the file as a ultimate break cut off point
#which I've already added to ability and moves files
#what I'll have to do is line search to find a description string start point ("
#use that as jumpoff point for main logic
#what I'll need from there is to loop the line itself or lenth of line?
#set start point at (" or "  store current iteration point of line as 0
#stop when I reach terminating point of line  \n  or just \ 
#do if statement here to do things without progressing
#set end point at that character subtract start point from end point if greater than line limit set found error to true
#reset start point to 0, from here start point won't be right since \n is 2 characters will have to subtract 1 from start point for rest of string
#continue loop rather than breaking stop again when I reach next \ character
#hmm actually dont reset start point to 0, that doesnt make sense end point si placement within enire line so shold just subtract from wher i start
#but just have 2 diff contidions first  if line character is " set start point to that
#after I hit end character \ after subtraction and at end of block reset starting point to current id + 2 that will get me to char after \n
#doesnt matter if there's nothing there if I hit eos before I reach another end point to subtract then it doesnt get used anyway
#if the ofudn error state is true I print file name and lineId
#since all I need is to identify where the issue is not how many there are per line
#I can have it break out at that point and continue to the next line

#since dex entry doesnt have everything on same line and different syntax I'd need slightly differnt code
#for just that file, but otherwise should be able to mostly copy paste once I get one file done
#just changing the line limit values

#ok to get correct value need subtract start from endpoint - 1
#ok whether I start on " or / I should do plus 1 for start point to properly get the length of between values
#actually no I do start point + 1 on "  endpoint can stay what it is when im' on \
#that way startpoint is actually the letter I'm trying to read and endpoint is where it ends
#if I'm on \ then I set my start point to index + 2  so i get passed the \n to the actual read letter


'''
Now next thing I need to do is figure how I'm going to integrate this into the make file.
plan was to do moves abilities and the pokedex entry text in one script
but I think that could cause issues with readability in the compiler
ok I'll do it later but
idea I came up with is to setup a state check.
only progress to the next stage of description strings
if on run it found no string bounds issues.
that way it'll create a workflow of building until you fix strings to find all the issues.
'''


#dexLine_Limit 42
#movesLine_Limit 19
#abilityLine_Limit 41

#/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/text/move_info.h
#/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/text/abilities.h
#/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/pokedex_text_fr.h
import re

#global consants
dexLine_Limit = 42
movesLine_Limit = 20
abilityLine_Limit = 41
Phase1_Complete = False #move description check
Phase2_Complete = False #ability description check

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/text/move_info.h', 'r')
lines = infile.readlines()
#index = 0
lineId = 0
startPoint = 0
EndPoint = 0
character = 0
Num_errors = 0
FoundLineError = False
filename = 'move_info.h :'
for line in lines:
    #FoundLineError = False
    lineId += 1
    index = 0 #I'm STUPID it didn't work cuz I forgot to reset index for each line
    #put line break here
    if re.compile(r'//END OF MOVE DESCRIPTIONS').search(line):
        break
    #realixe use while isntead of for so can have string value and letter character
    while index < len(line):
        character = line[index]
        #ok tested it can read a quote but I'm not getin it to read the parenthesi right at all somehwo?
        #aight got it now
        if character == '(' :
            startPoint = index + 2            
            #print(startPoint, lineId)
            #print(line)
            #if lineId == 2333:
            #    print(character, index)
            #    print(line)
            #print(character)
        #think may need do somthing to adjust this right?
        #not quite right doesn't properly catch things in the last line ending in parenthesis
        #ok quote is before end parenthesis think is retriggering first condition which was a quote
        #resetting the startpoint, so swapped it open paren instead
        if character == '\\' or character == ')':
            if character == '\\':
                EndPoint = index
            elif character == ')':
                EndPoint = index - 1
            if EndPoint - startPoint > movesLine_Limit:
                FoundLineError = True
            elif index + 2 < len(line) and character != ')': #extra protection
                startPoint = index + 2
        #index += 1

        if FoundLineError == True:
            #print file name line error occurs and w added index
            #meant to show approx where in the line the error is
            print(filename, lineId, index)
            FoundLineError = False
            Num_errors += 1
            break        
        else:            
            #print(EndPoint, lineId)
            #print(line)
            index += 1
#character search complete
if Num_errors == 0:
    Phase1_Complete = True
    print("No Move Description Errors")
infile.close()



infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/text/abilities.h', 'r')
lines = infile.readlines()
#index = 0
lineId = 0
startPoint = 0
EndPoint = 0
character = 0
Num_errors = 0
FoundLineError = False
filename = 'abilities.h :'
if Phase1_Complete == True:
    for line in lines:
        #FoundLineError = False
        lineId += 1
        index = 0 #I'm STUPID it didn't work cuz I forgot to reset index for each line
        #put line break here
        if re.compile(r'//END OF ABILITY DESCRIPTIONS').search(line):
            break
        #realixe use while isntead of for so can have string value and letter character
        while index < len(line):
            character = line[index]
            if character == '(' :
                startPoint = index + 2            
                #print(startPoint, lineId)
                #print(line)
                #print(character)
            #think may need do somthing to adjust this right?
            if character == '\\' or character == ')':
                if character == '\\':
                    EndPoint = index
                elif character == ')':
                    EndPoint = index - 1
                if EndPoint - startPoint > abilityLine_Limit:
                    FoundLineError = True
                elif index + 2 < len(line) and character != ')': #extra protection
                    startPoint = index + 2
            #index += 1

            if FoundLineError == True:
                #print file name line error occurs and w added index
                #meant to show approx where in the line the error is
                print(filename, lineId, index)
                FoundLineError = False
                Num_errors += 1
                break        
            else:            
                #print(EndPoint, lineId)
                #print(line)
                index += 1
    #character search complete
    if Num_errors == 0:
        Phase2_Complete = True
        print("No Ability Description Errors")
infile.close()