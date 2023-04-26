put this assimp-vc140-mt.lib you see over here in your project
and click Properies>> C/C++>> general >>additional include Directories>> Edit>> and $(SolutionDir)/../../External_libs/ASSIMP/include
and in >> Linker >> General >> additional Library Directories>> Edit>> $(SolutionDir)/../../External_libs/ASSIMP/lib
and in >> Linker >> Input>> additional Dependencies>> Edit>> assimp-vc140-mt.lib                    ZYA BKA BOY