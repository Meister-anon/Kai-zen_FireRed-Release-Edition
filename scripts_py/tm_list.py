import re
#purpose create list of itemIds in order of tms
# to be displayed in bag
#hms first then tms

'''
step one build total list of move ids in correct order
from global.h arrays.

step 2 loop src/data/items.h for size of array
storing item id (one in brackets)
think just check if line matches reg for [ITEM_]
and take entire line to storage
strip out brackets white space and = sign put comma on end

if encounter move id that matches order assign item id to list
by end of loops will have list I need.

step 3 create file and put array in file
'''

tm_moves = ''
tm_Array = []

tm_itemIds = ''
Item_Array = []

# scan TMs and HMs

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h', 'r')
lines = infile.readlines()
append = None
set = 0

for line in lines:
    if re.compile(r'gHM_Moves' +'\[').search(line):
    #if not 'gHM_Moves' in line:
        append = True
    if re.compile(r'LIST_END').search(line):
        append = False
        #if set < 1:
        #    set += 1
        #print(set)
    if hm := re.compile(r'MOVE').search(line) and append == True and set == 0:
        #cleanup before append        
        line = line.replace(",", "")
        line = line.replace("    ","")

        
        #should be add to list if not already in it
        if not line in tm_Array:
            tm_moves += line
            line = line.replace("\n", "")
            tm_Array.append(line)
            
        #print(line)
    

    if re.compile(r'gTM_Moves' +'\[').search(line):
        append = True
        set = 1
    #if re.compile(r'LIST_END').search(line):
    #    append = False
        #set += 1
    if tm:= re.compile(r'MOVE').search(line) and append == True and set == 1:
        #cleanup before append
        #
        line = line.replace(",", "")
        line = line.replace("    ","")
        #should be add to list if not already in it
        if not line in tm_Array:
            tm_moves += line
            line = line.replace("\n", "")
            tm_Array.append(line)
            
        #print(line)
    


infile.close()

#print(tm_moves)
#print(tm_Array)

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/items.h', 'r')
lines = infile.readlines()


TotalTMs = len(tm_Array)
FoundTms = 0
itemId = None

#putting the break directly under this doesn't work
#believe issue is doesn't update value until loop ends?
#put print foundtms here and it only returned 3 times
while FoundTms != TotalTMs:
#for TMs in tm_Array:
    for line in lines:
        if re.compile(r'\[' + 'ITEM_').search(line):
            line = line.replace("    [", "    ")
            line = line.replace("] =", ",")
            itemId = line
            #print(itemId)
        if re.compile(r'.secondaryId').search(line):
            #print(FoundTms)
            #check if tmhm from tm_moves is on line w secondaryId
            if re.compile(tm_Array[FoundTms]).search(line):
            #if re.compile(TMs).search(line):
                #print(FoundTms, line)
                line = line.replace("\n", "")
                line = line.replace(",", "")
                line = line.replace("      .secondaryId =  ", "")
                
                #print(line, tm_Array[FoundTms])
                #print(line, TMs)
                #surprisingly simple
                if (re.match(line, tm_Array[FoundTms])):
                #if (re.match(line, TMs)):
                    #print(TMs)
                    #print(itemId)
                    if not itemId in Item_Array:
                        Item_Array.append(itemId)
                        tm_itemIds += itemId
                        if FoundTms < TotalTMs:
                            FoundTms += 1
                        if FoundTms == TotalTMs:
                            break

#print(TMs)
#print(FoundTms)
#print(tm_itemIds)
#print(tm_moves)
#print(Item_Array)
#print(tm_Array)
#print(TotalTMs)
infile.close()






'''
decided rather than just create entirely new file
can search for specific cut off point within tm list file
and print generated data below that
'''


#store the default version of file without the generatedd sections
modifiable_lines = ''
#stores the generated data from this file
generated_lines = ''


#because I'm trying to print within file,
#need to read it 2 different ways and adjsut by line as well
with open("/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h", 'r') as file:
    out = file.read()

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h', 'r')
lines = infile.readlines()

state = 0


for line in lines:
    #if as expected should copy edited portion of file over unchanged
    if state == 0:
        modifiable_lines += line
    


    #copy break line / nvm above covers it this is just a toggle
    if re.compile(r'//FILE_END').search(line) and state == 0:

        state = 1

    if state == 1:
        generated_lines += ('\n\n' + r'//''\n' + r'// DO NOT MODIFY BELOW THE LINE! It is auto-generated from scripts_py/tm_list.py' +'\n' + r'//' + '\n\n')
        generated_lines += ('\n' + r'static const u16 gTMHM_List[]' + r' = {' + '\n')
        state = 2
    if state == 2:
        #for Items in Item_Array:
        generated_lines += (tm_itemIds) 
        generated_lines += (r'};')
        state = 3


        
infile.close()
#print(state)
#print(curr_lines)
#print(modifiable_lines)
#print(generated_lines)

#realized there's not much point in the else,
#generated lines are only ones that matter here,
#as modifables have already been saved beforehand thus are identical
#and because the file is global, changing modifiables is already enough to make it build globally
#all it would do is prevent printing an identical output to the destination file,
#which is an trivial process
if out != (modifiable_lines  + generated_lines):
    print("Updated Tm List")
else:
    quit() #idea stop unnecessary building, if data is same don't output to file

out = (modifiable_lines + generated_lines)

with open("/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h", 'w') as file:
    file.write(out)
