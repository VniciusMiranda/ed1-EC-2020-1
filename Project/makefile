
# project directories
IDIR := include/
SDIR := src
ODIR := obj

# compiler specs
CC     := gcc
CFLAGS := -I $(IDIR) 

# executable name
EXECUTABLE := executable/project-organizer

# libraries
LIBS := -lncurses -lpthread 

_DEPS := Label.h Task.h TaskList.h Display.h utils.h Project.h
DEPS  := $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ := Label.o main.o  Task.o TaskList.o Display.o MainMenu.o utils.o Project.o ProjectScreen.o
OBJ  := $(patsubst %,$(ODIR)/%,$(_OBJ))



$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
