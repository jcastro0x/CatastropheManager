mkdir build

echo "Building Generator..."
g++ src/generator.cpp include/common.cpp -Iinclude -lboost_date_time -lrt -o generator
mv generator build/generator

echo "Building Solver..."
g++ src/solver.cpp include/common.cpp -Iinclude -lboost_date_time -lrt -o solver
mv solver build/solver

echo "Done"
