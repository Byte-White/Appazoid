import os
from PythonConfig import PythonConfiguration as PyConfig, color_print

# install CLI
def SetupCLI():
    got_input = input("Would you like to install Appazoid CLI? (y/n): ")
    if(got_input.capitalize() == "Y"):
        print("Installing CLI...")
        #Cloning the CLI
        if(PyConfig.git):
            if(os.listdir("cli") == 0): #checks if the directory is empty
                os.system("git clone --recursive https://github.com/Byte-White/Appazoid-CLI cli")
            else: #if the directory is empty then it will update it
                color_print("CLI is already installed!","yellow")
                got_input = input("Would you like to check for updates? (y/n): ")
                if(got_input.capitalize() == "Y"):
                    color_print("Updating CLI...", "green")
                    os.chdir("cli")
                    os.system("git checkout .")
        #installing Typer package
            if(find_executable("pip") is not None):
                os.system("pip install typer")
            else:
                color_print("Could not install needed packages(typer). Could not find pip.","red")
        else:
            print("Could not install the CLI because git is not installed.")
    return

if(__name__ == "__main__"):
    SetupCLI()