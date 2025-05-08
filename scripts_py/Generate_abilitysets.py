import re

CopiedLines = []

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/level_up_learnsets.h', 'r')
lines = infile.readlines()

for line in lines:
    if re.compile(r'static const struct').search(line):
        CopiedLines.append(line)
    if re.compile(r'LEVEL_UP_END').search(line):
        CopiedLines.append(line)
    if re.compile(r'};').search(line):
        CopiedLines.append(line)
        CopiedLines.append('\n')

    if re.compile(r'//Copied gen8 learnsets from EE').search(line):
        break
#print(CopiedLines)

infile.close()


outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/learned_abilities.h', 'w')
outfile.writelines(CopiedLines)
outfile.close()