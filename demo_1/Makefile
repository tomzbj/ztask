CC   = gcc
OBJ  = main.o 
LINKOBJ  = $(OBJ) $(RESOBJ)
DEFS =
CFLAGS = -Os -Wall -I..
LDFLAGS = 
SRCS = main.c ../ztask.c

OBJS    = $(ASRCS:.s=.o) $(SRCS:.c=.o) 
TARGET  = main
CFLAGS += $(UINCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: $(OBJS) $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean: clean-custom
	${RM} $(LINKOBJ) $(TARGET) *~ .*.swp

$(TARGET): $(LINKOBJ)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
