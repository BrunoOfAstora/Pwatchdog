IDIR = include
SDIR = src
ODIR = $(BDIR)/obj
BDIR = build

CC = gcc

CFLAGS = -I$(IDIR)

_DEPS = wd_h.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/pwatchdog: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(shell mkdir -p $(ODIR))
$(shell mkdir -p $(BDIR))
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/pwatchdog *~ core $(IDIR)/*~
