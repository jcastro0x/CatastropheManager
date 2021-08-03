# Simple script to build the program
# TODO: Create makefile instead this :)

BUILD_DIR="out"
if [ -d $BUILD_DIR ]; then
    echo "Remove old $BUILD_DIR folder"
    rm -r $BUILD_DIR
fi
mkdir $BUILD_DIR


INCLUDE_DIR="-Iinclude"
LIBS="-lboost_date_time -lboost_program_options -lrt -lpthread"
COMMON_FILES="src/interpreter.cpp src/command.cpp include/memory_manager.cpp include/options.cpp"


# Build Generator
echo "(1/2) Building Generator..."
GENERATOR_NAME="generator"
g++ src/generator.cpp $COMMON_FILES $INCLUDE_DIR $LIBS -o $GENERATOR_NAME
mv $GENERATOR_NAME $BUILD_DIR/$GENERATOR_NAME

# Build Solver
echo "(2/2) Building Solver..."
SOLVER_NAME="solver"
g++ src/solver.cpp $COMMON_FILES $INCLUDE_DIR $LIBS -o $SOLVER_NAME
mv $SOLVER_NAME $BUILD_DIR/$SOLVER_NAME

echo "Done!"
