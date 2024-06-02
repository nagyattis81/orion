rmdir /s /q .\out\Release\
mkdir out
cd out
cmake ../
cmake --build . --config Release
cd ..
.\out\Release\demo.exe