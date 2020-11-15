
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

# remember to include "Project.h" again
_DEPS := Label.h Task.h TaskList.h ProjectOrganizer.h Display.h  
DEPS  := $(patsubst %,$(IDIR)/%,$(_DEPS))

# remember to include "Project.o" again
_OBJ := Label.o main.o Task.o TaskList.o ProjectOrganizer.o Display.o MainMenu.o 
OBJ  := $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
