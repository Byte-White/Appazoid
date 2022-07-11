# THIS SCRIPT IS USED ONLY FOR FLEXING!
# THERE IS NO OTHER USE CASE BESIDES SHOWING
# HOW MANY LINES THIS PROJECT HAS.

# import required module
from msilib.schema import Directory
import os
from unittest import skip



def get_lines_count(file):
    count = 0
    for lines in file:
        count+=1
    return count
# iterate over files in
# that directory
total = 0
def get_total_lines_in_directory(directory):
    for filename in os.listdir(directory):
        f = os.path.join(directory, filename)
        global total
        # checking if it is a file
        if os.path.isfile(f):
            if (".cpp" in f) or (".h" in f): # only for C++ files
                if "vendor" in f: #ignores this directory
                    pass
                elif "out" in f: #ignores this directory
                    pass
                else:
                    file = open(f,"r", encoding="utf-8")
                    lines = get_lines_count(file)
                    print("file ",f," has ", lines) #prints each file's lines count individually
                    total += lines
                    file.close()
        else:
            get_total_lines_in_directory(f)

# assign directory
main_directory = '..\\..\\'
 
print("SELECTED DIRECTORY: ", main_directory)
get_total_lines_in_directory(main_directory)
print("total lines = ", total) # prints the total lines count