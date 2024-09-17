import re
SpeciesType = {}    #create empty ditionary for storing mon type

'''
script works perfectly now issue was ogerpon species macro
overwrites type for mon before it, i.e fezandipiti,
so placed a space in the montypes macro so it gets excluded
and there's no issue.

Prints list of species in type order at bottom of pokedex_orders.h
to use after running script, copy created list and replace current list
in gPokedexOrder_Type

because of ogerpon macro ogerpon isn't added to list,
but it should go directly after Capsakid so add it in manually.

Following that, replace SPECIES w NATIONAL_DEX
and adjust for names that don't follow national_dex defines
'''



infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/base_stats.h', 'r')
lines = infile.readlines()
reg = re.compile(r'\[(SPECIES_\w+)\]') #exclusively find spcies
MonType = re.compile(r'MON_TYPES\((TYPE_\w+)') #find 1st type
MonType2 = re.compile(r',\s(TYPE_\w+)') #find 2nd type
species = None
new_lines = []
#need below array to exclude form species that are placed before
#form cutoff of mega venusaur
exceptions = ["SPECIES_URSALUNA_BLOODMOON", "SPECIES_WOOPER_PALDEAN",
"SPECIES_SQUAWKABILLY_BLUE_PLUMAGE", "SPECIES_SQUAWKABILLY_YELLOW_PLUMAGE",
"SPECIES_SQUAWKABILLY_WHITE_PLUMAGE", "SPECIES_TERAPAGOS_TERASTAL", "SPECIES_TERAPAGOS_STELLAR",
"SPECIES_DUDUNSPARCE_THREE_SEGMENT", "SPECIES_MAUSHOLD_FAMILY_OF_FOUR", "SPECIES_OINKOLOGNE_FEMALE",
"SPECIES_GIMMIGHOUL_ROAMING", "SPECIES_PALAFIN_HERO", "SPECIES_POLTCHAGEIST_ARTISAN",
"SPECIES_SINISTCHA_MASTERPIECE", "SPECIES_TATSUGIRI_DROOPY", "SPECIES_TATSUGIRI_STRETCHY",
"SPECIES_TAUROS_PALDEAN_COMBAT_BREED", "SPECIES_TAUROS_PALDEAN_BLAZE_BREED", "SPECIES_TAUROS_PALDEAN_AQUA_BREED",
"SPECIES_CEFIREON", "SPECIES_FRAEYJTA"]
Types = [] #not append instead assign based on type1 type2 within MonTYpe if conditional
Type1 = None
Type2 = None #before assign to types check if is still none if so
#assign to type1 i.e type2 = type1, set types to dictionary
#then reset type2 to None
Print = True #use to tell it when to stop doing assingments

for line in lines:
    if m := reg.search(line):
        species = m.group(1)        
        if species == 'SPECIES_VENUSAUR_MEGA': #hopefully got this right?
            Print = False
    if Print and species not in exceptions: #prevents assingment of form species
        if a := MonType.search(line):
            Type1 = a.group(1)
            if b := MonType2.search(line):
                Type2 = b.group(1)
            #print(Type2) #works
            if Type2 == None:
                Type2 = Type1
            Types = [Type1, Type2]
            SpeciesType[species] = Types
            Type2 = None
            #print(species)
            #print(Types)   #works
            #print(SpeciesType) #lets go it works!!
infile.close()
'''ok everyhting works, last thing I need to do is set the loop
conditions, and have it printed to end file, think best I can do 
w my present knowledge is append the key to end of page
then just replace the list afterwards.



//TYPE list goes in this order starts mono, then second types, starting back at beginning, so normal|normal first,
/*      TYPE_NORMAL,   0x00
	.set TYPE_FIGHTING, 0x01
	.set TYPE_FLYING,   0x02
	.set TYPE_POISON,   0x03
	.set TYPE_GROUND,   0x04
	.set TYPE_ROCK,     0x05
	.set TYPE_BUG,      0x06
	.set TYPE_GHOST,    0x07
	.set TYPE_STEEL,    0x08
	.set TYPE_MYSTERY,  0x09
	.set TYPE_FIRE,     0x0a
	.set TYPE_WATER,    0x0b
	.set TYPE_GRASS,    0x0c
	.set TYPE_ELECTRIC, 0x0d
	.set TYPE_PSYCHIC,  0x0e
	.set TYPE_ICE,      0x0f
	.set TYPE_DRAGON,   0x10
	.set TYPE_DARK,     0x11
	.set TYPE_FAIRY,	0x12*/
'''


infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/pokedex_orders.h', 'r')
lines = infile.readlines()
#reg = re.compile(r'\[(SPECIES_\w+)\]') #exclusively find spcies
#MonType = re.compile(r'MON_TYPES\((TYPE_\w+)') #find 1st type
#MonType2 = re.compile(r',\s(TYPE_\w+)') #find 2nd type
species = None
new_lines = []
TypeList = ["TYPE_NORMAL", "TYPE_FIGHTING", "TYPE_FLYING", "TYPE_POISON", "TYPE_GROUND", 
"TYPE_ROCK", "TYPE_BUG", "TYPE_GHOST", "TYPE_STEEL", "TYPE_MYSTERY", "TYPE_FIRE",
"TYPE_WATER", "TYPE_GRASS", "TYPE_ELECTRIC", "TYPE_PSYCHIC", "TYPE_ICE", "TYPE_DRAGON",
"TYPE_DARK", "TYPE_FAIRY"]
#ok now that I have everything, could potentially use two varialbes and just loop typelist?
#i.e type1 = TypeList[a]   and a can be 0, and I just increment the value each time
#long as it doesn't equal fairy?
SpeciesList = [] #for final list append to new line at end
a = 0   #for type1
b = 0   #for type2
Type1 = None
Type2 = None #before assign to types check if is still none if so
#assign to type1 i.e type2 = type1, set types to dictionary
#then reset type2 to None
#need figure how assign, type names by value,

for line in lines:
    new_lines.append(line)

for TYPE1 in TypeList:
    for TYPE2 in TypeList:
        for x in SpeciesType:
            species = x
            Type1 = SpeciesType[species][0]
            Type2 = SpeciesType[species][1]
            if Type1 == TYPE1 and Type2 == TYPE2:
                if species not in SpeciesList:
                    SpeciesList.append(species)
                    SpeciesList.append(",\n")
infile.close()


outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/pokedex_orders.h', 'w')
outfile.writelines(new_lines)
outfile.writelines(SpeciesList)
outfile.close()
