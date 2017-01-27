from os import listdir
from os.path import isfile, join, splitext

import os
import os.path


def main():
    """
    Merges one or two, or more, named .gitignore files in a directory into one
    Version 0.0.1
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
        content += "\n\n# " + os.path.basename(f) + "\n\n"
        content += file.read()
        file.close()

    # write content to .gitignore file
    out = open(".gitignore", "w")
    out.write(content)
    out.close()

    print("Done!")


if __name__ == '__main__':
    main()
