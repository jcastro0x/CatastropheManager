# Simple script to build the program
# TODO: Create makefile instead this :)

# We'll save in th(is folder the programs
mkdir build

#BOOST_LIBS = -lboost_date_time -lboost_program_options -lrt

# Build Generator
echo "(1/2) Building Generator..."
g++ src/generator.cpp src/interpreter.cpp src/command.cpp include/common.cpp -Iinclude -lboost_date_time -lboost_program_options -lrt -o generator
mv generator build/generator

# Build Solver
echo "(2/2) Building Solver..."
g++ src/solver.cpp src/interpreter.cpp src/command.cpp include/common.cpp -Iinclude -lboost_date_time -lrt -o solver
mv solver build/solver

echo "Done!"
