cmake CMakeLists.txt
make
g++ RB_tree.cpp
for num in 1 2 3
do
echo -e "\ntest ${num}"
cat "tests/test${num}.txt" | ./AVL_tree > ".answer1"
cat "tests/test${num}.txt" | ./a.out > ".answer2"
if diff .answer1 .answer2
then
echo "test ${num} OK"
else
echo "test ${num} Fail"
fi
done
for num in 4
do
echo -e "\ntest ${num}"
echo -e "\nAVL tree time"
time cat "tests/test${num}.txt" | ./AVL_tree > ".answer1"
echo -e "\nRed-black tree time"
time cat "tests/test${num}.txt" | ./a.out > ".answer2"
if diff .answer1 .answer2
then
echo "test ${num} OK"
else
echo "test ${num} Fail"
fi
done
rm .answer1
rm .answer2
