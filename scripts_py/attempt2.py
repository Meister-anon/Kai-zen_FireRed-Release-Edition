
import re

infile = open('/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h', 'r')
lines = infile.readlines()
reg = re.compile(r'\[SPECIES_(\w+?)\]')
species = None
new_lines = []
for line in lines:
    if m := reg.match(line):
        species = m.group(1).replace('_', ' ').title().replace(' ', '')
    if species:
        line = line.replace('CircledQuestionMark', species)
    new_lines.append(line)
infile.close()

outfile = open('/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h', 'w')
outfile.writelines(new_lines)
outfile.close()