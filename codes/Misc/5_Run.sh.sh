if [ ! -f $1 ] || [ $1.cpp -nt $1 ]; then
    g++ $1.cpp -std=c++17 -Wall -Wextra -Wshadow -O2 -D LOCAL -g -fsanitize=undefined,address -o  $1 ||          { echo "Compile failed."; exit 1; }
fi

./$1
