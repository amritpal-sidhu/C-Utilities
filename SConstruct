import os


UTILITIES_DIR = Dir(os.path.abspath("utilities"))

# Structure of the source_and_dependency_dict:
#   {
#       utility_subdir_0 :
#           {
#               include_paths : [list of include path names],
#               sources :
#               {
#                   source_0 :
#                   {
#                       source_file : source file object
#                       test_file : test file object
#                   }
#                   ...
#               }
#           }
#       ...
#   }
#
#   NOTE: Test filenames should be the source filename prefixed with "test_"
source_and_dependency_dict = {}


def print_dict(util, dict):
    print(util, "has the following entries:")
    print("\tinclude_paths:", dict[util]["include_paths"])
    for source_name, source_paths in dict[util]["sources"].items():
        print("\tsource:", source_name)
        print("\t\tsource_file:", source_paths["source_file"].abspath)
        print("\t\ttest_file:", source_paths["test_file"].abspath)


for util_DirEntry in os.scandir(UTILITIES_DIR.abspath):
    if util_DirEntry.is_dir():
        source_and_dependency_dict[util_DirEntry.name] = SConscript("utilities/{}/SConscript".format(util_DirEntry.name))
        # print_dict(util_DirEntry.name, source_and_dependency_dict)

Export("source_and_dependency_dict")

SConscript("utilities/SConscript_utilities")
