from distutils.spawn import find_executable
from http.server import executable
import os
from tracemalloc import start

def __prt_clr_help(str,color):
    white = "\033[39m"
    print(color,str,white)
    return
def color_print(str, color):
    red = "\033[31m"
    green = "\033[32m"
    yellow = "\033[33m"
    blue = "\033[34m"
    white = "\033[39m"
    if(color == "red"):
        __prt_clr_help(str,red)
    elif(color == "green"):
        __prt_clr_help(str,green)
    elif(color == "yellow"):
        __prt_clr_help(str,yellow)
    elif(color == "blue"):
        __prt_clr_help(str,blue)
    elif(color == "white"):
        __prt_clr_help(str,white)
    return

class PythonConfiguration:
    vulkan = False
    cmake = False
    compiler = True # will be changed to False if a C++ compiler is not found
    git = False
    validated_all = False
    has_been_run = False

    @classmethod
    def ValidateAll(self, min_validation:bool):
        self.has_been_run = True
        if(min_validation):
            color_print("Starting Minimum Validation...","blue")
        else:
            color_print("Starting Standard Validation...","blue")
        self.ValidateGit()
        self.ValidateCMake()
        self.ValidateCompiler()
        if(not min_validation):
            self.ValidateVulkan()
        if(self.vulkan and self.cmake and self.compiler and self.git):
            self.validated_all = True
        return

    @classmethod
    def ValidateVulkan(self):
        color_print("Validating Vulkan...(optional)","yellow")
        if("VULKAN_SDK" in os.environ.keys()):
            color_print("Vulkan SDK path has been found!","green")
            print("Vulkan SDK path",os.environ["VULKAN_SDK"])
            print("Running vulkan cube example... If you see a rotating cube then Vulkan is working correctly!")
            print("Close 'Vulkan Cube' to continue the Validation")
            os.system(os.environ["VULKAN_SDK"]+"\\bin\\vkcube.exe")
            color_print("Vulkan is installed!","green")
            self.vulkan = True
        return
        
    @classmethod
    def ValidateCMake(self):
        color_print("Validating CMake...","blue")
        if(find_executable("cmake") is not None):
            os.system("cmake --version")
            color_print("CMake is installed!","green")
            self.cmake = True
        else:
            color_print("CMake is NOT installed!","red")
        return
    
    @classmethod
    def ValidateCompiler(self):
        color_print("Validating C++ Compiler...","blue")
        if(find_executable("g++") is not None):
            os.system("g++ --version")
            color_print("g++ is installed!","green")
        elif(find_executable("gcc") is not None):
            os.system("gcc --version")
            color_print("gcc is installed!","green")
        elif(find_executable("cl") is not None):
            os.system("cl --version")
            color_print("MSVC is installed!","green")
        else:
            color_print("Couldn't find a C++ compiler!","red")
            self.compiler = False
        return
    
    @classmethod
    def ValidateGit(self):
        color_print("Validating Git...","blue")
        if(find_executable("git") is not None):
            color_print("git is installed!","green")
            self.git = True
        else:
            color_print("git is NOT installed!","red")
        return

if(__name__ == "__main__"):
    PythonConfiguration.ValidateAll(False)