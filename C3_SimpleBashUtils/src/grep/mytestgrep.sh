#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

testing()
{
./s21_grep $f include s21_grep.c s21_grep.h > test_s21.log
grep $f include s21_grep.c s21_grep.h> test_grep.log
DIFF_RES="$(diff -s test_s21.log test_grep.log)"
(( COUNTER++))
if [ "$DIFF_RES" == "Files test_s21.log and test_grep.log are identical" ]
then 
    (( SUCCESS++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: success grep $f include  s21_grep.c s21_grep.h"
else 
    (( FAIL++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: fail grep $f include s21_grep.c s21_grep.h"
fi
rm test_s21.log test_grep.log
}

testingE()
{
./s21_grep $f -e include -e file s21_grep.c s21_grep.h > test_s21.log
grep $f -e include -e file s21_grep.c s21_grep.h> test_grep.log
DIFF_RES="$(diff -s test_s21.log test_grep.log)"
(( COUNTER++))
if [ "$DIFF_RES" == "Files test_s21.log and test_grep.log are identical" ]
then 
    (( SUCCESS++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: success grep $f -e include -e file  s21_grep.c s21_grep.h"
else 
    (( FAIL++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: fail grep $f -e include -e file s21_grep.c s21_grep.h"
fi
rm test_s21.log test_grep.log
}

testingF()
{
./s21_grep $f -f test_text_for_grep.txt s21_grep.c s21_grep.h > test_s21.log
grep $f -f test_text_for_grep.txt s21_grep.c s21_grep.h> test_grep.log
DIFF_RES="$(diff -s test_s21.log test_grep.log)"
(( COUNTER++))
if [ "$DIFF_RES" == "Files test_s21.log and test_grep.log are identical" ]
then 
    (( SUCCESS++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: success grep $f -f test_text_for_grep.txt  s21_grep.c s21_grep.h"
else 
    (( FAIL++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: fail grep $f -f test_text_for_grep.txt s21_grep.c s21_grep.h"
fi
rm test_s21.log test_grep.log
}

for n in v c l n h o
do  
        
        f="-$n"
        testing 
done

for n1 in v c l n h o
do
    for n2 in v c l n h o
    do
        if [ $n1 != $n2 ]
        then
            f="-$n1 -$n2"
            testing 
        fi
    done
done

for n1 in v c l n h o
do
    for n2 in v c l n h o
    do
        for n3 in v c l n h o
        do
            if [ $n1 != $n2 ] && [ $n2 != $n3 ] && [ $n1 != $n3 ]
            then
                f="-$n1 -$n2 -$n3"
                testing 
            fi
        done
    done
done


for n1 in v c l n h o
do
    for n2 in v c l n h o
    do
        for n3 in v c l n h o
        do
            for n4 in v c l n h o
            do
                if [ $n1 != $n2 ] && [ $n2 != $n3 ] \
                && [ $n1 != $n3 ] && [ $n1 != $n4 ] \
                && [ $n2 != $n4 ] && [ $n3 != $n4 ]
                then
                    f="-$n1 -$n2 -$n3 -$n4"
                    testing 
                fi
            done
        done
    done
done

for n in v c l n h o
do  
        
        f="-$n"
        testingE 
done

for n in v c l n h o
do  
        
        f="-$n"
        testingF 
done

echo "fail:" $FAIL
echo "success:"$SUCCESS
echo "counter:"$COUNTER