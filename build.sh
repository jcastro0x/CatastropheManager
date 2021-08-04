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
COMMON_FILES="src/interpreter.cpp src/memory_manager.cpp src/options.cpp"
COMMANDS_FILES="src/command.cpp src/commands/generate.cpp src/commands/quit.cpp src/commands/solve.cpp src/commands/status.cpp src/commands/help.cpp src/commands/options.cpp src/commands/clear.cpp"
DEBUG="-DNDEBUG -O3"
#DEBUG=""

# Build Generator
echo "(1/2) Building Base Program..."
PROGRAM_NAME="catastrophe"
$CC src/main.cpp $COMMON_FILES $COMMANDS_FILES $INCLUDE_DIR $LIBS $DEBUG -o $PROGRAM_NAME
mv $PROGRAM_NAME $BUILD_DIR/$PROGRAM_NAME

# Build executers
echo "(2/2) Building Executers..."
GENERATOR_NAME="generator"
SOLVER_NAME="solver"
echo "./catastrophe --mode=generator" >> $GENERATOR_NAME
echo "./catastrophe --mode=solver" >> $SOLVER_NAME

chmod +x $GENERATOR_NAME
chmod +x $SOLVER_NAME
mv $GENERATOR_NAME $SOLVER_NAME $BUILD_DIR/

echo "Done!"
