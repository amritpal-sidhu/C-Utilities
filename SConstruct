import os


SetOption("num_jobs", 6)

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
#                       source_path : source_abspath_str,
#                       test_path : test_abspath_str
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
        print("\t\tsource_path:", source_paths["source_path"])
        print("\t\ttest_path:", source_paths["test_path"])


for util in os.listdir(UTILITIES_PATH):
    if os.path.isdir(os.path.join(UTILITIES_PATH, util)):
        source_and_dependency_dict[util] = SConscript("utilities/{}/SConscript".format(util))
        # print_dict(util, source_and_dependency_dict)

Export("source_and_dependency_dict")

SConscript("utilities/SConscript_utilities")
