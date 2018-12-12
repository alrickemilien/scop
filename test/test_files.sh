BIN=../scop

for X in $(find -type f ./files); do
    $BIN $X
done
