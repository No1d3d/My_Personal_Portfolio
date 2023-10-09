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
echo "Checking if s21_cat_f.c is formated..."
clang-format -style=Google -n s21_cat_f.c
echo
echo "Checking if s21_cat.c is formated..."
clang-format -style=Google -n s21_cat.c
echo
echo "Checking if s21_cat.h is formated..."
clang-format -style=Google -n s21_cat.h
echo

make K=-fsanitize=address
touch mycat_output.txt
touch regcat_output.txt
echo
echo
echo "============================================="
echo "Regular Cat"
echo "============================================="
echo
echo
#leaks --atExit -- ./s21_cat Text1.txt Text2.txt Text3.txt
echo
echo
./s21_cat Text1.txt Text2.txt Text3.txt > mycat_output.txt
cat Text1.txt Text2.txt Text3.txt > regcat_output.txt
diff -s mycat_output.txt regcat_output.txt
echo
echo
echo "============================================="
echo "-b Cat"
echo "============================================="
echo
echo
#leaks --atExit -- ./s21_cat -b Text1.txt Text2.txt Text3.txt
echo
echo
./s21_cat -b Text1.txt Text2.txt Text3.txt > mycat_output.txt
cat -b Text1.txt Text2.txt Text3.txt > regcat_output.txt
diff -s mycat_output.txt regcat_output.txt
echo
echo
echo "============================================="
echo "-e Cat"
echo "============================================="
echo
echo
#leaks --atExit -- ./s21_cat -e Text1.txt Text2.txt Text3.txt
echo
echo
./s21_cat -e Text1.txt Text2.txt Text3.txt > mycat_output.txt
cat -e Text1.txt Text2.txt Text3.txt > regcat_output.txt
diff -s -s mycat_output.txt regcat_output.txt
echo
echo
echo "============================================="
echo "-n Cat"
echo "============================================="
echo
echo
#leaks --atExit -- ./s21_cat -n Text1.txt Text2.txt Text3.txt
echo
echo
./s21_cat -n Text1.txt Text2.txt Text3.txt > mycat_output.txt
cat -n Text1.txt Text2.txt Text3.txt > regcat_output.txt
diff -s mycat_output.txt regcat_output.txt
echo
echo
echo "============================================="
echo "-s Cat"
echo "============================================="
echo
echo
#leaks --atExit -- ./s21_cat -s Text1.txt Text2.txt Text3.txt
echo
echo
./s21_cat -s Text1.txt Text2.txt Text3.txt > mycat_output.txt
cat -s Text1.txt Text2.txt Text3.txt > regcat_output.txt
diff -s mycat_output.txt regcat_output.txt
echo
echo
echo "============================================="
echo "-t Cat"
echo "============================================="
echo
echo
#leaks --atExit -- ./s21_cat -t Text1.txt Text2.txt Text3.txt
echo
echo
./s21_cat -t Text1.txt Text2.txt Text3.txt > mycat_output.txt
cat -t Text1.txt Text2.txt Text3.txt > regcat_output.txt
diff -s mycat_output.txt regcat_output.txt
echo
echo
echo "============================================="
make clean
rm mycat_output.txt regcat_output.txt