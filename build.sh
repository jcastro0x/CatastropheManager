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
echo "(1/2) Building Base Program..."
PROGRAM_NAME="catastrophe"
$CC src/main.cpp $COMMON_FILES $INCLUDE_DIR $LIBS $DEBUG -o $PROGRAM_NAME
mv $PROGRAM_NAME $BUILD_DIR/$PROGRAM_NAME

# Build executers
echo "(2/2) Building Executers..."
GENERATOR_NAME="generator"
SOLVER_NAME="solver"
echo ".\$PROGRAM_NAME --mode=generator" >> $GENERATOR_NAME
echo ".\$PROGRAM_NAME --mode=solver" >> $SOLVER_NAME
chmod +x $GENERATOR_NAME
chmod +x $SOLVER_NAME
mv $GENERATOR_NAME $SOLVER_NAME $BUILD_DIR/

echo "Done!"
