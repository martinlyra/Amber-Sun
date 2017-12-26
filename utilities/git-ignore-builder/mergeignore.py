from os import listdir
from os.path import isfile, join, splitext

import os
import os.path

# Author: Martin Lyrå
# Versions
#
# 0.0.2 (Dec 26, 2017) - Tweaked formatting; added lines and "END of" comment
# 0.0.1 (Jan 27, 2017) - Created

def main():
    """
    Merges one or two, or more, named .gitignore files in a directory into one
	Currently work in working directory only
	
    Version: 0.0.2 (Dec 26, 2017)
    """
    path = os.getcwd() # get current working directory

    # get all named .gitignores
    files = list()
    for f in listdir(path):
        file = join(path, f)
        if isfile(file) and file.endswith(".gitignore") and not f.startswith(".gitignore"):
            files.append(file)

    # append file contents
    content = ""
    for f in files:
        file = open(f)
        content += "\n# " + os.path.basename(f) + "\n# ------------------------\n"
        content += file.read()
        content += "\n\n# ------------------------\n# END of " + os.path.basename(f) + "\n"
        file.close()

    # write content to .gitignore file
    out = open(".gitignore", "w")
    out.write(content)
    out.close()

    print("Done!")


if __name__ == '__main__':
    main()
