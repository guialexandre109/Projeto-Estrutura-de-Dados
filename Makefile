all: relatorios_pacientes.o
	gcc relatorios_pacientes.o relatorio.c -o relatorio

relatorios_pacientes.o: relatorios_pacientes.h
	gcc -c relatorios_pacientes.c
	
clean:
	rm -rf *.o
