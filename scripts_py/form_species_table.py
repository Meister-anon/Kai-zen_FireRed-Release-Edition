import re


infile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/form_species_tables.h', 'r')
lines = infile.readlines()
prevLine = None
FormTableStart = re.compile(r'FormSpeciesIdTable')
species = re.compile(r'(SPECIES_\w+),')

Alola = re.compile(r'_ALOLAN')
Gal = re.compile(r'_GALARIAN')
Hisu = re.compile(r'_HISUIAN')
Pal = re.compile(r'_PALDEAN')

'''
rewrite form_species_table.h file to account for change to struct
following changes will add tables to base stats file
and use that to remove cosmetic species from bs file

update species_graphics_info file for gender forms
now that have simple way to add them 

will also need update species file to enum
check how national dex values are used 
see if need match to species if need to can just py

looked into more better to not put formspecies onto base stats
if keep pointer can have entry from any species
if put in base stats only base species would get to table
so what I need to do is add gender form species 
make species into enum w gender form at start of cosmetics
bring in graphics add species to formspecies pointer table
and formspecies table file then can run script

or regex sub  to do national_dex_ v  = species_ v

enum FormInfo
{
    BASE_FORM_SPECIES,
    COSMETIC_FORM,
    MEGA_EVO,
    PRIMAL_FORM,
    REGIONAL_VARIANT,
    GENDER_FORM, //gender forms with material differences
    ALT_FORM, //specific things not mega like zen mode or hangry mode etc.
    FORM_NONE   //for FORM_SPECIES_END
};
'''
#believe file is as done as I can get it
#uhh think need add gender species then actually run script
#when I have all the species I Need
newlines = []

for line in lines:

    #store base species id sans comma
    #filter it after to decide what do
    if a:= species.search(line):
        speciesId = a.group(1)
    
        #do base form species replace
        #did form none manually
        #will set with elif and let else 
        #be cosmetic
        #following that go through gender forms
        #and manually replace ones that arent cosmetic
        #need also filter alt form stuff like castform
        #hangry forms zen mode etc.
        if FormTableStart.search(prevLine):
            line = line.replace(speciesId, r'{' + speciesId +', BASE_FORM_SPECIES}')
        elif re.compile(r'_MEGA').search(line):
            line = line.replace(speciesId, r'{' + speciesId +', MEGA_EVO}')
        elif re.compile(r'_PRIMAL').search(line):
            line = line.replace(speciesId, r'{' + speciesId +', PRIMAL_FORM}')
        elif Alola.search(line) or Gal.search(line) or Hisu.search(line) or Pal.search(line):
            line = line.replace(speciesId, r'{' + speciesId +', REGIONAL_VARIANT}')
        else:
            line = line.replace(speciesId, r'{' + speciesId +', COSMETIC_FORM}')

    prevLine = line
    newlines.append(line)
    
infile.close()
    
outfile = open('/usr/decomp/Kai-zen_FireRed-Release-Edition/src/data/pokemon/form_species_tables.h', 'w')
outfile.writelines(newlines)
outfile.close()