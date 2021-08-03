# Simple script to build the program
# TODO: Create makefile instead this :)

BUILD_DIR="out"
if [ -d $BUILD_DIR ]; then
    echo "Remove old $BUILD_DIR folder"
    rm -r $BUILD_DIR
fi
mkdir $BUILD_DIR



#BOOST_LIBS = -lboost_date_time -lboost_program_options -lrt

# Build Generator
echo "(1/2) Building Generator..."
GENERATOR_NAME="generator"
g++ src/generator.cpp src/interpreter.cpp src/command.cpp include/common.cpp -Iinclude -lboost_date_time -lboost_program_options -lrt -o $GENERATOR_NAME
mv $GENERATOR_NAME $BUILD_DIR/$GENERATOR_NAME

# Build Solver
echo "(2/2) Building Solver..."
SOLVER_NAME="solver"
g++ src/solver.cpp src/interpreter.cpp src/command.cpp include/common.cpp -Iinclude -lboost_date_time -lrt -o $SOLVER_NAME
mv $SOLVER_NAME $BUILD_DIR/$SOLVER_NAME

echo "Done!"
