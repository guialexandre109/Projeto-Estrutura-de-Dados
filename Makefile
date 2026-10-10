all: relatorios_pacientes.o relatorios_ocupaçao.o relatorios_medicos.o
	gcc relatorios_pacientes.o relatorios_ocupaçao.o relatorios_medicos.o relatorio.c -o relatorio
relatorios_pacientes.o: relatorios_pacientes.h
	gcc -c relatorios_pacientes.c
relatorios_ocupaçao.o: relatorios_ocupaçao.h
	gcc -c relatorios_ocupaçao.c
relatorios_medicos.o: relatorios_medicos.h
	gcc -c relatorios_medicos.c
clean:
	rm -rf *.o
