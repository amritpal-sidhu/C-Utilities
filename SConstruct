import os


def main():

    SetOption("num_jobs", 6)

    UTILITIES_PATH = os.path.abspath("utilities")

    include_files_dict = {}
    for dir in os.listdir(UTILITIES_PATH):
        if os.path.isdir(os.path.join(UTILITIES_PATH, dir)):
            include_files_dict[dir] = []

    for dir in include_files_dict:
        include_files_dict[dir] = SConscript("utilities/{}/SConscript".format(dir))
        print(dir, "has the following modules:", include_files_dict[dir])

    Export("include_files_dict")

    SConscript("utilities/SConscript_utilities")

main()