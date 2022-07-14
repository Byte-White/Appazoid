import os
from PythonConfig import PythonConfiguration as PyConfig, color_print
from distutils.spawn import find_executable

# install CLI
def SetupCLI():
    got_input = input("Would you like to install Appazoid CLI? (y/n): ")
    if(got_input.capitalize() == "Y"):
        if(not PyConfig.has_been_run):
            PyConfig.ValidateGit()
        print("Installing CLI...")
        #Cloning the CLI
        if(PyConfig.git):
            if(os.path.isdir("cli")): #if there is a dir
                if(os.listdir("cli").__len__() == 0): #checks if the directory is empty
                    os.system("git clone --recursive https://github.com/Byte-White/Appazoid-CLI cli")
                else: #if the directory is not empty
                    if(os.path.isdir("cli/.git")): #if the directory has .git folder
                        color_print("CLI is already installed!","yellow")
                        got_input = input("Would you like to check for updates? (y/n): ")
                        if(got_input.capitalize() == "Y"): #if you want to update
                            color_print("Updating CLI...", "green")
                            os.chdir("cli")
                            os.system("git checkout .")
                    else:# if the directory is not empty
                        color_print("directory is not empty","yellow")
            else: #if there isnt a dir
                os.system("git clone --recursive https://github.com/Byte-White/Appazoid-CLI cli")

        #installing Typer package
            if(find_executable("pip") is not None):
                os.system("pip install typer")
                os.system("pip install inquirer")
                os.system("pip install pyfiglet")
            else:
                color_print("Could not install needed packages(typer, inquirer, figlet). Could not find pip.","red")
        else:
            print("Could not install the CLI because git is not installed.")
    return

if(__name__ == "__main__"):
    SetupCLI()