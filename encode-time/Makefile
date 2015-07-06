objs = time-excel.o ec-method.o ec-gf.o

time : $(objs) 
	cc -o time $(objs) -lm -g -lrt
time-excel.o : time-excel.c ec-method.h ec-gf.h
	cc -c time-excel.c 
ec-method.o : ec-method.c ec-method.h
	cc -c ec-method.c
ec-gf.o : ec-gf.c ec-gf.h
	cc -c ec-gf.c

clean :
	rm -rf time $(objs) 
