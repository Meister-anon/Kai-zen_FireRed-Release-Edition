import re

newlines = []
infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/form_change_tables.h', 'r')
lines = infile.readlines()

runState = True

if_reg = re.compile(r'#if')
end_reg = re.compile(r'#endif')


for line in lines:
    
    #clear familiy related if end if
    #to avoid impact normal logic
    if re.compile(r'P_FAMILY').search(line):
        line = line.replace(line, '')
        
    if if_reg.search(line):
        runState = False


    if end_reg.search(line) and runState == True:
        line = line.replace(line, '')

    if end_reg.search(line):
        runState = True

    newlines.append(line)

infile.close()

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/form_change_tables.h', 'w')
outfile.writelines(newlines)
outfile.close()
        