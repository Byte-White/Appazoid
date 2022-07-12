from PythonConfig import PythonConfiguration as PyConfig, color_print
from cli_setup import SetupCLI


#Validation
got_input = input("Would you like to validate? (y/n): ")
if(got_input.capitalize() == "Y"):
    PyConfig.ValidateAll(min_validation=False)

#Setup CLI
SetupCLI()