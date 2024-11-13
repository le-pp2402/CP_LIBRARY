#!/bin/bash
GEN="tc_generator.cpp"; MAX=10000; B="b.cpp"; M="a.cpp"
c(){ g++ -std=c++20 "$1" -o "$2" || { echo "Error compiling $1"; exit 1; }; }
cln(){ rm -f in.txt gen main brute out1.txt out2.txt; }
test(){ echo "Running $MAX tests..."; for((i=0;i<MAX;i++)); do
    ./gen > in.txt; ./main < in.txt > out1.txt; ./brute < in.txt > out2.txt
    if diff -q out1.txt out2.txt > /dev/null; then echo "pass"
    else echo "fail at test #$i"; echo "Input:"; cat in.txt; echo "Main output:"; cat out1.txt
         echo "Expected:"; cat out2.txt; break; fi; done; }
main(){ while [[ $# -gt 0 ]]; do
    case $1 in
        -b) B="$2"; shift 2 ;;
        -m) M="$2"; shift 2 ;;
        -t) MAX="$2"; shift 2 ;;
        -h) echo "Usage: $(basename "$0") -b <brute> -m <main> [-t <tests>]"; exit ;;
        *) echo "Unknown option $1"; exit 1 ;;
    esac; done
    c "$GEN" "gen"; c "$M" "main"; c "$B" "brute"; test; cln; }
main "$@"
