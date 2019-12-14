echo Start > out.txt
echo Start >in.txt
for ((i=0;i<10000;i++))
do
    ./a2.exe
    ./a1.exe
    sleep 5
    echo "Test case" $i >> out.txt
    echo "Test case" $i >> in.txt
    cat output.txt >> out.txt
    cat input.txt >> in.txt
done