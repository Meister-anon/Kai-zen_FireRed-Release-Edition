import re

'''
point of script to pull in battle anim related graphics from EE
rn in EE_graphics.c

plan reg search for graphics/battle_anims or battle_anims/
put those lines in global array to print into my graphics.c file

may make 2 passes on my file 1 to delte all battle anim lines
so only new values remain
'''
#global array storing anim defines
animArray = []
#finds reference to battle anim
battleAnims = re.compile(r'graphics\/battle_anims')

#note line replace remove smol before add to array
#can do line replace w or
#search for .smolTM and .smol
#line repalce smolreg  with .lz
smolreg = re.compile(r'(\.s[a-zA-Z]+)')

#phase 1 remove battle anims from fr graphics file
#phase 2 copy values from EE graphics to global array
#end phase reopen FR graphics file and print array

infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/graphics.c', 'r')
lines = infile.readlines()

new_lines = []
for line in lines:

    if battleAnims.search(line):
        line = line.replace(line, "") #should be remove line

    new_lines.append(line)

infile.close()

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/graphics.c', 'w')
outfile.writelines(new_lines)
outfile.close()



infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/EE_graphics.c', 'r')
lines = infile.readlines()

for line in lines:

    if battleAnims.search(line):
        if a := smolreg.search(line):
            line = line.replace(a.group(1), ".lz") #should be remove line
        animArray.append(line)

#print(animArray) works
infile.close()


infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/graphics.c', 'r')
lines = infile.readlines()

Run = True
new_lines = []
for line in lines:

    #should be after first line
    #add line break and fill from array
    #unsure if will print right or with quotations
    if re.compile(r'#include "global.h"').search(line) and Run == True:
        Run = False
        new_lines.append(line)
        #ok sick this worked kept top line
        #and was able to put array into file
        for x in animArray:
            new_lines.append(x)
        continue

    new_lines.append(line)

infile.close()

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/graphics.c', 'w')
outfile.writelines(new_lines)
outfile.close()