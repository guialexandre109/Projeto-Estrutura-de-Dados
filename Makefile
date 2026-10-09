all: relatorios_pacientes.o relatorios_ocupaçao.o
	gcc relatorios_pacientes.o relatorios_ocupaçao.o relatorio.c -o relatorio
relatorios_pacientes.o: relatorios_pacientes.h
	gcc -c relatorios_pacientes.c
relatorios_ocupaçao.o: relatorios_ocupaçao.h
	gcc -c relatorios_ocupaçao.c
clean:
	rm -rf *.o
