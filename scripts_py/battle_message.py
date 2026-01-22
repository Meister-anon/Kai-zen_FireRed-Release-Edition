import re

'''for updating gBattleStringsTable in battle_message.c
make dictionary using sText strings as key values with text as value
start running script when get to string table end on };
search line for match to dict key do line sub replace sTextpointer
 w COMPOUND_STRING dict Value
'''
#global empty dict
#tec don't think need global can prob run in one script
#thanks to placement of values key values I need are before
#strings to replace I'd need dict for

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/battle_message.c', 'r')
lines = infile.readlines()
stringDict = {}
new_lines = []

KeyReg = re.compile(r'(sText.*)\[')
#looks weird but meant to be used on same line as keyreg
#just take everything within the two parenthesis
TextReg = re.compile(r'(\(.*\))')
Phase1_Done = False
Phase2_Done = False


for line in lines:
    if re.compile(r'const gBattleStringsTable').search(line):
        Phase1_Done = True

    #build dictionary
    if Phase1_Done == False:
        if a := KeyReg.search(line):
            key = a.group(1)
            #always true but idk how else to write this
            if b := TextReg.search(line):
                value = b.group(1)
                stringDict.update({key:value})
    elif Phase2_Done == False:
        if re.compile(r'\};').match(line):
            Phase2_Done = True
        #do dictionary line replace here
        #actually re.sub is better 
        if d := re.compile(r'(sText.*)\,').search(line):
            Id = d.group(1)
            string = stringDict[Id]
            line = re.sub(Id, "COMPOUND_STRING" + string, line)

    new_lines.append(line)
infile.close()


outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/battle_message.c', 'w')
outfile.writelines(new_lines)
outfile.close()