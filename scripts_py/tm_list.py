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

for TMs in tm_Array:
    if FoundTms == TotalTMs:
        break
    for line in lines:
        if re.compile(r'\[' + 'ITEM_').search(line):
            #line = line.replace("\n", "")
            line = line.replace("    [", "    ")
            line = line.replace("] =", ",")
            itemId = line
            #print(itemId)
        if re.compile(r'.secondaryId').search(line):
            #for TMs in tm_moves:
            #    continue
                #check if tmhm from tm_moves is on line w secondaryId
                #if re.compile(r'' + TMs).search(line):
            if re.compile(tm_Array[FoundTms]).search(line):
                line = line.replace("\n", "")
                line = line.replace(",", "")
                line = line.replace("      .secondaryId =  ", "")
                #print(itemId)
                
                Item_Array.append(itemId)
                tm_itemIds += itemId
                if FoundTms < TotalTMs:
                    FoundTms += 1
                if FoundTms == TotalTMs:
                    break 
    #if FoundTms == 3:
    #    break

#print(tm_itemIds)


#print(FoundTms)
#print(tm_itemIds)
#print(tm_moves)
#print(list(Item_Array))
infile.close()

'''
decided rather than just create entirely new file
can search for specific cut off point within tm list file
and print generated data below that
'''

'''
with open("/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h", 'r') as file:
    CurrFile = file.read()

NewFile = CurrFile




separator = '\n' + r'//\n// DO NOT MODIFY BELOW THIS LINE! It is auto-generated from scripts_py/tm_list.py\n//\n\n'


def header_print(str):
    global header
    separator += "    " + str + ",\n"

separator += r"\n" + r"static const u16 gTMHM_List\[\] = {" + r"\n"


for Items in tm_itemIds:
    header_print(Items)

separator += r'};'


if not "// DO NOT MODIFY BELOW THE!" in CurrFile:
    NewFile = NewFile + separator

if NewFile != CurrFile:
    print("Updated Tm List")
'''

#should hold current version of file
curr_lines = []
#store the default version of file without the generatedd sections
modifiable_lines = ''
#stores the generated data from this file
generated_lines = ''

new_lines = []

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
    curr_lines.append(line)
    


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

if out != (modifiable_lines  + generated_lines):
    print("Updated Tm List")

#outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h', 'w')
#outfile.writelines(modifiable_lines + generated_lines)
#outfile.close()


out = (modifiable_lines + generated_lines)

with open("/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h", 'w') as file:
    file.write(out)

'''

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h', 'r')
lines = infile.readlines()

compositeList = []
compositeList = (modifiable_lines + generated_lines)

for line in compositeList:
    new_lines.append(line)
'''

#print(new_lines)

#outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/include/tm_List_data.h', 'w')
#outfile.writelines(new_lines)
#outfile.close()





'''
# actually prepare the file
with open('./src/data/pokemon/teachable_learnsets.h', 'r') as file:
    out = file.read()
    list_of_mons = re.findall(r'static const u16 s(.*)TeachableLearnset', out)
for mon in list_of_mons:
    mon_parsed = parse_mon_name(mon)
    tm_learnset = []
    tutor_learnset = []
    if mon_parsed == "NONE" or mon_parsed == "MEW":
        continue
    if not mon_parsed in compatibility_dict:
        print("Unable to find %s in json" % mon)
        continue
    for move in tm_moves:
        if move in universal_moves:
            continue
        if move in tm_learnset:
            continue
        if move in compatibility_dict[mon_parsed]:
            tm_learnset.append(move)
            continue
    for move in tutor_moves:
        if move in universal_moves:
            continue
        if move in tutor_learnset:
            continue
        if move in compatibility_dict[mon_parsed]:
            tutor_learnset.append(move)
            continue
    tm_learnset.sort()
    tutor_learnset.sort()
    tm_learnset += tutor_learnset
    repl = "static const u16 s%sTeachableLearnset[] = {\n    " % mon
    if len(tm_learnset) > 0:
        repl += ",\n    ".join(tm_learnset) + ",\n    "
    repl += "MOVE_UNAVAILABLE,\n};"
    newout = re.sub(r'static const u16 s%sTeachableLearnset\[\] = {[\s\S]*?};' % mon, repl, out)
    if newout != out:
        out = newout
        print("Updated %s" % mon)

# add/update header
header = "//\n// DO NOT MODIFY THIS FILE! It is auto-generated from tools/learnset_helpers/teachable.py\n//\n\n"
longest_move_name = 0
for move in tm_moves + tutor_moves:
    if len(move) > longest_move_name:
        longest_move_name = len(move)
longest_move_name += 2 # + 2 for a hyphen and a space

universal_title = "Near-universal moves found in sUniversalMoves:"
tmhm_title = "TM/HM moves found in gTM_Moves/gHM_Moves:"


def header_print(str):
    global header
    header += "// " + str + " " * (longest_move_name - len(str)) + " //\n"

header += "// " + longest_move_name * "*" + " //\n"
header_print(tmhm_title)
for move in tm_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n"
header_print(tutor_title)
tutor_moves.sort() # alphabetically sort tutor moves for easier referencing
for move in tutor_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n"
header_print(universal_title)
universal_moves.sort() # alphabetically sort near-universal moves for easier referencing
for move in universal_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n\n"

if not "// DO NOT MODIFY THIS FILE!" in out:
    out = header + out
else:
    out = re.sub(r"\/\/\n\/\/ DO NOT MODIFY THIS FILE!(.|\n)*\* \/\/\n\n", header, out)

with open("./src/data/pokemon/teachable_learnsets.h", 'w') as file:
    file.write(out)
'''