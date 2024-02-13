CC = gcc
CFLAGS = -Wall -g -c --coverage   # Add --coverage flag for coverage instrumentation
LDFLAGS = -o
LIBS = -lgcov

INC = ../HDR
BIN = ../BIN
SRC = ../SRC
OBJ = ../OBJ
COV = ../coverage_reports       # New directory for coverage reports

IFLAGS = -I $(INC)

# Add 'coverage' target for generating coverage reports
.PHONY: coverage
coverage: cdr
	cd $(BIN) && gcov -o $(OBJ) $(addprefix $(SRC)/, $(notdir $(wildcard $(SRC)/*.c)))   # Generate coverage reports for all source files in SRC directory

all: cdr

cdr: $(OBJ)/main.o $(OBJ)/login.o $(OBJ)/process.o $(OBJ)/CB.o $(OBJ)/IOB.o
	$(CC) $(LDFLAGS) $(BIN)/cdr $(OBJ)/main.o $(OBJ)/login.o $(OBJ)/process.o $(OBJ)/CB.o $(OBJ)/IOB.o $(LIBS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c $(IFLAGS) -o $(OBJ)/main.o $(LIBS)

$(OBJ)/login.o: $(SRC)/login.c
	$(CC) $(CFLAGS) $(SRC)/login.c $(IFLAGS) -o $(OBJ)/login.o $(LIBS)

$(OBJ)/process.o: $(SRC)/process.c
	$(CC) $(CFLAGS) $(SRC)/process.c $(IFLAGS) -o $(OBJ)/process.o $(LIBS)

$(OBJ)/CB.o: $(SRC)/Customer_Billing.c
	$(CC) $(CFLAGS) $(SRC)/Customer_Billing.c $(IFLAGS) -o $(OBJ)/CB.o $(LIBS)

$(OBJ)/IOB.o: $(SRC)/InterOperator_Billing.c
	$(CC) $(CFLAGS) $(SRC)/InterOperator_Billing.c $(IFLAGS) -o $(OBJ)/IOB.o $(LIBS)

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/*
	rm -f $(COV)/*.gcov
	rm -f $(COV)/*.gcda
	rm -f $(COV)/*.gcno            # Clean up generated gcov files in COV directory
	@echo "Cleaning Done!"
