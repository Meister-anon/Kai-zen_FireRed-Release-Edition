import re

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/trainers.h', 'r')
lines = infile.readlines()
reg = re.compile(r'.party = (\{.partyData = )\w*(\})')
group1 = None
group2 = None
new_lines = []
for line in lines:
    if m := reg.search(line):
        group1 = m.group(1)
        group2 = m.group(2)
        line = line.replace(group1, "")
        line = line.replace(group2,"")
    new_lines.append(line)
infile.close()


outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/trainers.h', 'w')
outfile.writelines(new_lines)
outfile.close()