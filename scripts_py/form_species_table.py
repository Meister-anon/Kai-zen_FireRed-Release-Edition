import re

prevLine
FormTableStart = re.compile(r'FormSpeciesIdTable')

'''
rewrite form_species_table.h file to account for change to struct
following changes will add tables to base stats file
and use that to remove cosmetic species from bs file

update species_graphics_info file for gender forms
now that have simple way to add them 

will also need update species file to enum
check how national dex values are used 
see if need match to species if need to can just py

or regex sub  to do national_dex_ v  = species_ v
'''