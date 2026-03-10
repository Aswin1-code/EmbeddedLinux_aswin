#!/bin/bash
#This is comment line
echo "My first Linux Shell Script"
echo "This month calender"
cal
echo "Today date is:"
date
echo "My current directory:"
pwd
echo "Enter your name"
read a
echo "Welcome $a"

#!/bin/bash
#Sum of Two Numbers
echo "Enter two numbers"
read i
read j
c=`expr $i + $j`
echo "The sum is: $c"

#!/bin/bash
#Product of Two Numbers
echo "Enter a number"
read a
echo "Enter another number"
read b
echo "$a * $b"|bc
c=`echo "$a * $b"|bc`
echo "The product is:$c"

#!/bin/bash
#Demo of if-elif-fi
echo "Enter a number"
read c
if [ $c > 10 ];
then
  echo "Yes $c is greater than 10"
elif [ $c < 10 ];
then
  echo "Yes $c is less than 10"
fi

#!/bin/bash
#Demo of while loop
echo "Enter a number"
read c
while [ $c -gt 0 ]
do
   echo "$c"
   c=`expr $c - 1`
done

#!/bin/bash
#Demo of until loop
echo "Enter a number"
read c
until [ $c -gt 0 ]
do
   echo "$c"
   c=`expr $c - 1`
done

#!/bin/bash
#Demo of for loop
for i in 1 2 3 4 5 6 7 8 9 10
do
    echo $i
done
for i in {1..20}
do
    echo $i
done
for i in {1..10..2}
do
    echo $i
done
for((i=0;i<10;i++))
do
    echo $i
done
for i in $(seq 1 2 20)
do
    echo $i
done
for i in {15..20}
do
    echo $i
done

#!/bin/bash
#Linux Shell Script to find sum and avg of N numbers
echo "Enter a number"
read N
echo "Enter $N numbers"
sum=0
for((i=0;i<N;i++))
do
  read a[i]
  sum=`echo "$sum + ${a[i]}"|bc`
done
echo "Sum is:$sum"
av=`echo "scale=2; $sum/$N"|bc`
echo "Avg is:$av"
