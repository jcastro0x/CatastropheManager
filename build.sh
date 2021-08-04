# Simple script to build the program
# TODO: Create makefile instead this :)

BUILD_DIR="out"
if [ -d $BUILD_DIR ]; then
    echo "Remove old $BUILD_DIR folder"
    rm -r $BUILD_DIR
fi
mkdir $BUILD_DIR

CC="g++"
INCLUDE_DIR="-Iinclude"
LIBS="-lboost_date_time -lboost_program_options -lrt -lpthread"
COMMON_FILES="src/interpreter.cpp src/command.cpp src/memory_manager.cpp src/options.cpp"
#DEBUG="-DNDEBUG -O3"
DEBUG=""

# Build Generator
echo "(1/2) Building Generator..."
GENERATOR_NAME="generator"
$CC src/generator.cpp $COMMON_FILES $INCLUDE_DIR $LIBS $DEBUG -o $GENERATOR_NAME
mv $GENERATOR_NAME $BUILD_DIR/$GENERATOR_NAME

# Build Solver
echo "(2/2) Building Solver..."
SOLVER_NAME="solver"
$CC src/solver.cpp $COMMON_FILES $INCLUDE_DIR $LIBS $DEBUG -o $SOLVER_NAME
mv $SOLVER_NAME $BUILD_DIR/$SOLVER_NAME

echo "Done!"
