#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

testing()
{
./s21_cat $f test1.txt > test_s21.log
cat $f test1.txt > test_cat.log
DIFF_RES="$(diff -s test_s21.log test_cat.log)"
(( COUNTER++))
if [ "$DIFF_RES" == "Files test_s21.log and test_cat.log are identical" ]
then 
    (( SUCCESS++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: success cat $f test1.txt"
else 
    (( FAIL++ ))
    echo "$FAIL / $SUCCESS / $COUNTER: fail cat $f test1.txt"
fi
rm test_s21.log test_cat.log
}

for n in b e n s t v
do  
        f="-n"
        testing 
done

for n1 in b e n s t v
do
    for n2 in b e n s t v
    do
        if [ $n1 != $n2 ]
        then
            f="-$n1 -$n2"
            testing 
        fi
    done
done

for n1 in b e n s t v
do
    for n2 in b e n s t v
    do
        for n3 in b e n s t v
        do
            if [ $n1 != $n2 ] && [ $n2 != $n3 ] && [ $n1 != $n3 ]
            then
                f="-$n1 -$n2 -$n3"
                testing 
            fi
        done
    done
done


echo "fail:" $FAIL
echo "success:"$SUCCESS
echo "counter:"$COUNTER
