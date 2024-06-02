rm -f ./out/demo
mkdir out
cd out
cmake ../
cmake --build . --config Release
cd ..
./out/demo