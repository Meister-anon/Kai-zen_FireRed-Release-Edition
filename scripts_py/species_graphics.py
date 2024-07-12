import re
#import fileinput
#import sys

#def replaceAll(file, search,mon):
#        for line in fileinput.input(file, inplace=1):
#            if mon in line:
#                monname = re.sub(r"_", " ", mon).title().replace(" ", "")
#            if search in line:
#                line = line.replace(search, monname)
            #sys.stdout.write(line)
#            with open("/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h", "w") as f:
#                f.write(line)

regex = r"CircledQuestionMark"

#should be open species graphics file and setup operations
with open("/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h", "r") as f:
    data = f.read()

#replaceAll(data, regex, r"SPECIES_(.*)]")

#believe assigns mon to captured value should be CAPPED species name
for mon in re.findall(r"SPECIES_MINIOR_CORE+(.*)]", data): 
    #monname = re.sub(r"_", " ", mon).title().replace(" ", "") 
    #print(monname)
    data = re.sub(r"//FRONT_PIC\(MiniorCore+(.*)\)","FRONT_PIC(MiniorCore)",data)
    data = re.sub(r"//BACK_PIC\(MiniorCore+(.*)\)","BACK_PIC(MiniorCore)",data)
    data = re.sub(r"//SHINYPAL\(MiniorCore+(.*)\)","SHINYPAL(MiniorCore)",data)
    #data = re.sub(r"PIC_DATA_ICON_INDEX\(MiniorMeteor+(.*)\)","PIC_DATA_ICON_INDEX(MiniorMeteor, 0)",data)
#    replaceAll(data, regex, r"SPECIES_(.*)]")
    
    #data = re.sub(regex,monname,data) # I "think" should be all I need?
#think this is what did cap appears replace _ w space does smt then removes space?
#confirmed title is a python function makes string lowercase 
#then caps 1st char of each word, I make the string separate words
#by adding the spaces

    

with open("/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h", "w") as f:
    f.write(data)