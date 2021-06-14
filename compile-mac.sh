echo "Compiling..."
mkdir -p ./bin
g++ ./src/knights_tour.cpp ./src/parameters.cpp ./src/solver.cpp ./src/validator.cpp ./src/hal-osx.cpp -o ./bin/knights_tour.bin && echo "Done!"
