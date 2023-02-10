#! /bin/zsh

i=0
for fname in $(ls img/ansicard); do
    i=$(($i + 1))
    echo "$fname,$i"
    mv "img/ansicard/$fname" "img/ansicard/card$i.png"
done
