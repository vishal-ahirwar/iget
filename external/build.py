from os import system,cpu_count,path
PROJECT_NAME:str="get"
BUILD_DATE_TIME:str="Mon Feb 03 04:04:25 2025"
#Warning : DO NOT REMOVE THIS LINE OR ADD ANYTHING ABOVE EVEN IMPORT SHOULD GO BELOW THIS LINE
GENERATOR:str="\"Ninja\""
conan_file_exist:bool=path.exists("conanfile.txt")
if __name__=="__main__":
    if not conan_file_exist:
        print('Compilling Dependencies...')
        if  system("cmake --install cpr/build --prefix cpr/install"):
            if not system(f"cd cpr && cmake -S . -Bbuild -G{GENERATOR} -DBUILD_SHARED_LIBS=OFF"):
                if not system(f"ninja -C cpr/build -j{cpu_count()}"):
                    system("cmake --install cpr/build --prefix cpr/install")
        if  system("cmake --install fmt/build --prefix fmt/install"):
            if not system(f"cd fmt && cmake -S . -Bbuild -G{GENERATOR} -DBUILD_SHARED_LIBS=OFF"):
                if not system(f"ninja -C fmt/build -j{cpu_count()}"):
                    system("cmake --install fmt/build --prefix fmt/install")           
            