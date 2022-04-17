1. Сборка модуля: make -f Makefile

2. Загрузка модуля: sudo insmod new_segfile.ko

3. Записываем в файл одну за другой строки: 
echo "If a man does his best, what else is there?  Gen. Patton" > /proc/seqdir/seqfile
echo "Success is an individual proposition.  Thomas Watson" > /proc/seqdir/seqfile
echo "Cats: All your base are belong to us.  Zero Wing" > /proc/seqdir/seqfile

4. Выводим по одной строке из файла:
cat /proc/seqdir/seqfile

5. Выгрузка модуля: sudo rmmod new_segfile.ko

6. Смотрим логи: sudo dmesg | grep +

ls -al
