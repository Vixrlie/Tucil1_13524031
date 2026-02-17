ifeq ($(OS), Windows_NT)
	EXEC  = main.exe
	MKDIR = if not exist bin mkdir bin
	RM    = rmdir /s /q bin
else
	EXEC  = main
	MKDIR = mkdir -p bin
	RM    = rm -rf bin
endif

CC = g++

all:
	$(MKDIR)
	$(CC) src/main.cpp -o bin/$(EXEC)
	./bin/$(EXEC)

clean:
	$(RM)