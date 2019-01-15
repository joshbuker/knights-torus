echo "Compiling..."
g++ -std=c++11 ./src/knights_tour.cpp ./src/parameters.cpp ./src/solver.cpp ./src/validator.cpp ./src/hal-linux.cpp -o ./bin/knights_tour.bin && echo "Done!"
