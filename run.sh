rm memory.o
gcc -Wall -Wextra -g3 memory.c -o memory.o
echo -e " -- First Fit -- "
./memory.o R tests/memFirst.txt
echo -e "\n -- Best Fit -- "
./memory.o R tests/memBest.txt
echo -e "\n -- Worst Fit -- "
./memory.o R tests/memWorst.txt
echo -e "\n -- Full Edge Case -- "
./memory.o R tests/memFull.txt