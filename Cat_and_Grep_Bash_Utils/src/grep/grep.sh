echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
clear
echo
echo "Checking if s21_grep.c is formated..."
clang-format -style=Google -n s21_grep.c
echo
echo "Checking if s21_grep.h is formated..."
clang-format -style=Google -n s21_grep.h
echo

make #K=-fsanitize=address
touch mygrep_output.txt
touch reggrep_output.txt
echo
echo
echo "============================================="
echo "Regular grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-e grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -e T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -e T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -e T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-i grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -i t Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -i t Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -i t Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-v grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -v T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -v T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -v T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-c grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -c T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -c T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -c T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-l grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -l T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -l T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -l T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-n grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -n T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -n T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -n T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-h grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -h T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -h T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -h T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-s grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -s T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -s T Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -e T Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-f grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -f regex.txt Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -f regex.txt Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -f regex.txt Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
echo "-o grep"
echo "============================================="
echo
echo
leaks --atExit -- ./s21_grep -o T Text1.txt Text2.txt Text3.txt
echo
echo
./s21_grep -o Text1.txt Text1.txt Text2.txt Text3.txt > mygrep_output.txt
grep -o Text1.txt Text1.txt Text2.txt Text3.txt > reggrep_output.txt
diff -s mygrep_output.txt reggrep_output.txt
echo
echo
echo "============================================="
make clean
rm mygrep_output.txt reggrep_output.txt
