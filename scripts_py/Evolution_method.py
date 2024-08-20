'''point update people coming from base firered that have fakemon etc. in evolutio table
base version works if already in, base statas but will need to adjust based on evo table since pret firered
still use evo table
'''

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/base_stats.h', 'r')
lines = infile.readlines()
reg = re.compile(r'\[SPECIES_(\w+?)\]')
evoMethod = re.compile(r'EVO_LEVEL_FAMILY_OF_THREE, (\d+)')
value = None
species = None
new_lines = []
mon = []
size = []
Yset = []
for line in lines:
    if m := evoMethod.search(line):
        value = m.group(1)
        line = line.replace('EVO_LEVEL_FAMILY_OF_THREE, '+ value, 'EVO_LEVEL_FAMILY_OF_THREE, RELATIVE_EVO('+ value + ', AVERAGE_EFFORT)')
        #print(line)
        #new_lines.append(line)
        #mon.append(reg)
        #species = m.group(1).replace('_', ' ').title().replace(' ', '')
    #if species:
        #for x in exceptions:
        #    if species == x[0]:
        #        species = x[1]
        #line = line.replace('CircledQuestionMark', species)
        #size.append(r'\.size = (\w)')
        #Yset.append(r'\.y_offset = (\w)')
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
    new_lines.append(line)
#print(new_lines)
infile.close()

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/base_stats.h', 'w')
outfile.writelines(new_lines)
outfile.close()