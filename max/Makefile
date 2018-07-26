#################################################################
############################# Makefile ##########################
################### Walter Nascimento Barroso ###################
#################################################################
CC = g++
ENTRADA = $(wildcard *.cpp)
SAIDA = saida.o
CFLAGS = -g -O0 -W -Wall -Werror
LDFLAGS = -lm
EXTRAS = --std=c++11 -o

all:
	@echo %%%%%%%%%%%%%%%%%%%%%%%%
	@echo %% Compilando arquivo %%
	@echo %%%%%%%%%%%%%%%%%%%%%%%%
	@$(CC) $(ENTRADA) $(EXTRAS) $(SAIDA) $(LDFLAGS)
	@make test

debug:
	@echo %%%%%%%%%%%%%%%%%%%%%%%%%%
	@echo % Debugando Fluxo Maximo %
	@echo %%%%%%%%%%%%%%%%%%%%%%%%%%
	@echo 
	@gdb ./$(SAIDA)

test:
	@echo %%%%%%%%%%%%%%%%%%%%%%%%%
	@echo % Testando Fluxo Maximo %
	@echo %%%%%%%%%%%%%%%%%%%%%%%%%
	@echo 
	@./$(SAIDA)

.PHONY: clean
clean:
	@echo %%%%%%%%%%%%%%%%%%%%%%%
	@echo %% Limpando arquivos %%
	@echo %%%%%%%%%%%%%%%%%%%%%%%
	@rm -f *.o *~