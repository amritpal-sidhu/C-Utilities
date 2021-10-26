import os


UTILITIES_PATH = os.path.abspath("utilities")

# Structure of the source_and_dependency_dict:
#   {
#       utility_subdir_0 :
#           {
#               include_paths : [list of include path names],
#               sources :
#               {
#                   source_file_0 :
#                   {
#                       source_file_path : abspath of source file,
#                       test_file_path : abspath of test file
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
        print("\t\tsource_file_path:", source_paths["source_file_path"])
        print("\t\ttest_file_path:", source_paths["test_file_path"])


for util in os.listdir(UTILITIES_PATH):
    if os.path.isdir(os.path.join(UTILITIES_PATH, util)):
        source_and_dependency_dict[util] = SConscript("utilities/{}/SConscript".format(util))
        # print_dict(util, source_and_dependency_dict)

Export("source_and_dependency_dict")

SConscript("utilities/SConscript_utilities")
