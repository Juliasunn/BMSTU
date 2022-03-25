1. Сборка модуля: make -f Makefile

2. Загрузка модуля: sudo insmod cookie_module.ko

3. Записываем в файл одну за другой строки: 
echo "If a man does his best, what else is there?  Gen. Patton"> /proc/fortune_dir/fortune
echo "Success is an individual proposition.  Thomas Watson" > /proc/fortune_dir/fortune
echo "Cats: All your base are belong to us.  Zero Wing" > /proc/fortune_dir/fortune

4. Выводим по одной строке из файла:
cat /proc/fortune_dir/fortune

5. Выгрузка модуля: sudo rmmod cookie_module

6. Смотрим логи: sudo dmesg | grep +
