obj = sensor
src	:= *.c
all	:
	gcc -o $(obj) $(src)
clean	:
	rm $(obj)
