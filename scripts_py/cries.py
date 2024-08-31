import re
#should be open species graphics file and setup operations
'step 1'
'''
with open("/usr/decomp/Kai-zen_FireRed-Release-Edition/include/constants/cries.h", "r") as f:
    data = f.read()
cryId = None
#replaceAll(data, regex, r"SPECIES_(.*)]")
#regex = re.compile(r'\[(\w+)\]')
#believe assigns mon to captured value should be CAPPED species name
for mon in re.findall(r'Cry_+(.*)', data): 
    cryId = re.sub(r'_', ' ', mon).title() #does cap and remove space
    cryId = re.sub(r' ', '', cryId)
    #print(cryId)
    data = re.sub(r'Cry_'+ mon, 'Cry_'+ cryId, data)
    #print(data)
    #data = re.sub(r'Wishiwashi'+r'(.*)\)','Wishiwashi\")',data)
    #data = re.sub(r"//BACK_PIC\(MiniorCore+(.*)\)","BACK_PIC(MiniorCore)",data)
    #data = re.sub(r"//SHINYPAL\(MiniorCore+(.*)\)","SHINYPAL(MiniorCore)",data)
    #data = re.sub(r"PIC_DATA_ICON_INDEX\(MiniorMeteor+(.*)\)","PIC_DATA_ICON_INDEX(MiniorMeteor, 0)",data)
#    replaceAll(data, mon, cryId)
    
    #data = re.sub(regex,monname,data) # I "think" should be all I need?
#think this is what did cap appears replace _ w space does smt then removes space?
#confirmed title is a python function makes string lowercase 
#then caps 1st char of each word, I make the string separate words
#by adding the spaces

#if species:
        #for x in exceptions:
        #    if species == x[0]:
        #        species = x[1]
        #line = line.replace('CircledQuestionMark', species)  #uses same name convention see if do if species equals name/w+? species = just name
        
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
    #new_lines.append(line)
    

with open("/usr/decomp/Kai-zen_FireRed-Release-Edition/include/constants/cries.h", "w") as f:
    f.write(data)
'''

'step 2'
infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/species_graphic_info.h', 'r')
lines = infile.readlines()
reg = re.compile(r'\[SPECIES_(\w+?)\]')
cryReg = re.compile(r'\.cryData = (\w+)') #(r'\.cryData = (\d)') #original was crydata = 0, for easyreplace
species = None
cryId = None
new_lines = []
for line in lines:
    if m := reg.match(line):
        species = m.group(1).replace('_', ' ').title().replace(' ', '')#replace underscore w space to separate run title function then remove space
        #print(m)
        #if species:
            #for x in exceptions:
            #    if species == x[0]:
            #        species = x[1]
        
    if s := cryReg.search(line):
        cryId = s.group(1)
        if cryId != 'CRY_NONE':
            line = line.replace(r''+cryId, 'CRY_INFO(0x20, 60, 0, 0, '+cryId + ', 0xff, 0, 0xff, 0)')
            #print(line)
        #CRY_INFO(0x20, 60, 0, 0, Cry_Bulbasaur, 0xff, 0, 0xff, 0)
        #line = line.replace(r'Alcremie\w+?', 'Alcremie')
        #line = line.replace(r'\.cryId = Cry_Alcremie\w+', '.cryId = Cry_Alcremie')
        #check base sttas list mon w flag cosmetic to put here
        #nvm just need cry table for that as already illustrates repeating forms
        #w how it works, think I can keep the stuffbelow w the stuff below,
        #just need leave it to just the cry parts withot cryid preceding
        
        line = re.sub(r'Cry_Alcremie\w+', 'Cry_Alcremie',line) #ok this works yippee!!
        line = re.sub(r'Cry_Minior\w+', 'Cry_Minior',line)
        line = re.sub(r'Cry_Silvally\w+', 'Cry_Silvally',line)
        line = re.sub(r'Cry_Arceus\w+', 'Cry_Arceus',line)
        line = re.sub(r'Cry_Vivillon\w+', 'Cry_Vivillon',line)
        line = re.sub(r'Cry_Flabebe\w+', 'Cry_Flabebe',line)
        line = re.sub(r'Cry_Floette\w+', 'Cry_Floette',line) #need replace put eternal flower in
        line = re.sub(r'Cry_Florges\w+', 'Cry_Florges',line)
        line = re.sub(r'Cry_Unown\w+', 'Cry_Unown',line)
        line = re.sub(r'Cry_Pikachu\w+', 'Cry_Pikachu',line)
        line = re.sub(r'Cry_Pichu\w+', 'Cry_Pichu',line)
        line = re.sub(r'Cry_Sandshrew\w+', 'Cry_Sandshrew',line)
        line = re.sub(r'Cry_Sandslash\w+', 'Cry_Sandslash',line)
        line = re.sub(r'Cry_Vulpix\w+', 'Cry_Vulpix',line)
        line = re.sub(r'Cry_Ninetales\w+', 'Cry_Ninetales',line)
        line = re.sub(r'Cry_Rattata\w+', 'Cry_Rattata',line)
        line = re.sub(r'Cry_Raticate\w+', 'Cry_Raticate',line)
        line = re.sub(r'Cry_Raichu\w+', 'Cry_Raichu',line)
        line = re.sub(r'Cry_Diglett\w+', 'Cry_Diglett',line)
        line = re.sub(r'Cry_Dugtrio\w+', 'Cry_Dugtrio',line)
        line = re.sub(r'Cry_Meowth\w+', 'Cry_Meowth',line)
        line = re.sub(r'Cry_Persian\w+', 'Cry_Persian',line)
        line = re.sub(r'Cry_Geodude\w+', 'Cry_Geodude',line)
        line = re.sub(r'Cry_Graveler\w+', 'Cry_Graveler',line)
        line = re.sub(r'Cry_Golem\w+', 'Cry_Golem',line)
        line = re.sub(r'Cry_Grimer\w+', 'Cry_Grimer',line)
        line = re.sub(r'Cry_Muk\w+', 'Cry_Muk',line)
        line = re.sub(r'Cry_Exeggutor\w+', 'Cry_Exeggutor',line)
        line = re.sub(r'Cry_Marowak\w+', 'Cry_Marowak',line)
        line = re.sub(r'Cry_Ponyta\w+', 'Cry_Ponyta',line)
        line = re.sub(r'Cry_Rapidash\w+', 'Cry_Rapidash',line)
        line = re.sub(r'Cry_Slowbro\w+', 'Cry_Slowbro',line)
        line = re.sub(r'Cry_Farfetchd\w+', 'Cry_Farfetchd',line)
        line = re.sub(r'Cry_Weezing\w+', 'Cry_Weezing',line)
        line = re.sub(r'Cry_MrMime\w+', 'Cry_MrMime',line)
        line = re.sub(r'Cry_Articuno\w+', 'Cry_Articuno',line)
        line = re.sub(r'Cry_Zapdos\w+', 'Cry_Zapdos',line)
        line = re.sub(r'Cry_Moltres\w+', 'Cry_Moltres',line)
        line = re.sub(r'Cry_Slowking\w+', 'Cry_Slowking',line)
        line = re.sub(r'Cry_Corsola\w+', 'Cry_Corsola',line)
        line = re.sub(r'Cry_Zigzagoon\w+', 'Cry_Zigzagoon',line)
        line = re.sub(r'Cry_Linoone\w+', 'Cry_Linoone',line)
        line = re.sub(r'Cry_Darumaka\w+', 'Cry_Darumaka',line)
        line = re.sub(r'Cry_Darmanitan\w+', 'Cry_Darmanitan',line)
        line = re.sub(r'Cry_Yamask\w+', 'Cry_Yamask',line)
        line = re.sub(r'Cry_Stunfisk\w+', 'Cry_Stunfisk',line)
        line = re.sub(r'Cry_Growlithe\w+', 'Cry_Growlithe',line)
        line = re.sub(r'Cry_Arcanine\w+', 'Cry_Arcanine',line)
        line = re.sub(r'Cry_Voltorb\w+', 'Cry_Voltorb',line)
        line = re.sub(r'Cry_Electrode\w+', 'Cry_Electrode',line)
        line = re.sub(r'Cry_Typhlosion\w+', 'Cry_Typhlosion',line)
        line = re.sub(r'Cry_Qwilfish\w+', 'Cry_Qwilfish',line)
        line = re.sub(r'Cry_Sneasel\w+', 'Cry_Sneasel',line)
        line = re.sub(r'Cry_Samurott\w+', 'Cry_Samurott',line)
        line = re.sub(r'Cry_Lilligant\w+', 'Cry_Lilligant',line)
        line = re.sub(r'Cry_Zorua\w+', 'Cry_Zorua',line)
        line = re.sub(r'Cry_Zoroark\w+', 'Cry_Zoroark',line)
        line = re.sub(r'Cry_Braviary\w+', 'Cry_Braviary',line)
        line = re.sub(r'Cry_Sliggoo\w+', 'Cry_Sliggoo',line)
        line = re.sub(r'Cry_Goodra\w+', 'Cry_Goodra',line)
        line = re.sub(r'Cry_Avalugg\w+', 'Cry_Avalugg',line)
        line = re.sub(r'Cry_Decidueye\w+', 'Cry_Decidueye',line)
        line = re.sub(r'Cry_Castform\w+', 'Cry_Castform',line)
        line = re.sub(r'Cry_Deoxys\w+', 'Cry_Deoxys',line)
        line = re.sub(r'Cry_Deoxys\w+', 'Cry_Deoxys',line)
        line = re.sub(r'Cry_Burmy\w+', 'Cry_Burmy',line)
        line = re.sub(r'Cry_Wormadam\w+', 'Cry_Wormadam',line)
        line = re.sub(r'Cry_Cherrim\w+', 'Cry_Cherrim',line)
        line = re.sub(r'Cry_Shellos\w+', 'Cry_Shellos',line)
        line = re.sub(r'Cry_Gastrodon\w+', 'Cry_Gastrodon',line)
        line = re.sub(r'Cry_Rotom\w+', 'Cry_Rotom',line)
        line = re.sub(r'Cry_Giratina\w+', 'Cry_Giratina',line)
        line = re.sub(r'Cry_Basculin\w+', 'Cry_Basculin',line)
        line = re.sub(r'Cry_Deerling\w+', 'Cry_Deerling',line)
        line = re.sub(r'Cry_Sawsbuck\w+', 'Cry_Sawsbuck',line)
        line = re.sub(r'Cry_Keldeo\w+', 'Cry_Keldeo',line)
        line = re.sub(r'Cry_Meloetta\w+', 'Cry_Meloetta',line)
        line = re.sub(r'Cry_Genesect\w+', 'Cry_Genesect',line)
        line = re.sub(r'Cry_Greninja\w+', 'Cry_Greninja',line)
        line = re.sub(r'Cry_Furfrou\w+', 'Cry_Furfrou',line)
        line = re.sub(r'Cry_Magearna\w+', 'Cry_Magearna',line)
        line = re.sub(r'Cry_Sinistea\w+', 'Cry_Sinistea',line)
        line = re.sub(r'Cry_Polteageist\w+', 'Cry_Polteageist',line)
        line = re.sub(r'Cry_Ogerpon\w+', 'Cry_Ogerpon',line)
        line = re.sub(r'Cry_Terapagos\w+', 'Cry_Terapagos',line)
        line = re.sub(r'Cry_Gimmighoul\w+', 'Cry_Gimmighoul',line)
        line = re.sub(r'Cry_Zarude\w+', 'Cry_Zarude',line)
        line = re.sub(r'Cry_Poltchageist\w+', 'Cry_Poltchageist',line)
        line = re.sub(r'Cry_Sinistcha\w+', 'Cry_Sinistcha',line)
        line = re.sub(r'Cry_Cramorant\w+', 'Cry_Cramorant',line)
        line = re.sub(r'Cry_Xerneas\w+', 'Cry_Xerneas',line)
        line = re.sub(r'Cry_Mimikyu\w+', 'Cry_Mimikyu',line)
        line = re.sub(r'Cry_Pumpkaboo\w+', 'Cry_Pumpkaboo',line)
        line = re.sub(r'Cry_Gourgeist\w+', 'Cry_Gourgeist',line)
        line = re.sub(r'Cry_Aegislash\w+', 'Cry_Aegislash',line)
        line = re.sub(r'Cry_Basculegion\w+', 'Cry_Basculegion',line)
        line = re.sub(r'Cry_Frillish\w+', 'Cry_Frillish',line)
        line = re.sub(r'Cry_Jellicent\w+', 'Cry_Jellicent',line)
        line = re.sub(r'Cry_Unfezant\w+', 'Cry_Unfezant',line)
        line = re.sub(r'Cry_Pyroar\w+', 'Cry_Pyroar',line)
        line = re.sub(r'Cry_Meowstic\w+', 'Cry_Meowstic',line)
        line = re.sub(r'Cry_Squawkabilly\w+', 'Cry_Squawkabilly',line)
        line = re.sub(r'Cry_Dudunsparce\w+', 'Cry_Dudunsparce',line)
        #print(line) #works, just need add exceptions/species changes for multiforms alcremie, unown arceus vivilon etc.
        #line = line.replace('CircledQuestionMark', species)
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
        #think can use, if put in all exceptions
        #print(s)
    new_lines.append(line)
infile.close()#think group is reg stuff reg are broken into groups
#if that is correct than I might be able to use that to store 2 values
#say match group1 for mon size  and group2 for the yoffset?
#check pumpkabo gourgeist zygard
#need put back floette enternal flower and pumpkaboo super goergeist super
#need alter jangmo_o & zacian zamazenta base forms

outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/species_graphic_info.h', 'w')
outfile.writelines(new_lines)
outfile.close()