all: relatorios_pacientes.o relatorios_ocupaçao.o relatorios_medicos.o relatorios_remedios.o
	gcc relatorios_pacientes.o relatorios_ocupaçao.o relatorios_medicos.o relatorios_remedios.o relatorio.c -o relatorio
relatorios_pacientes.o: relatorios_pacientes.h
	gcc -c relatorios_pacientes.c
relatorios_ocupaçao.o: relatorios_ocupaçao.h
	gcc -c relatorios_ocupaçao.c
relatorios_medicos.o: relatorios_medicos.h
	gcc -c relatorios_medicos.c
relatorios_remedios.o: relatorios_remedios.h
	gcc -c relatorios_remedios.c
clean:
	rm -rf *.o
