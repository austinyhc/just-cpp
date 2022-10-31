TARGET = console

CC = gcc
CFLAGS = -O1 -g -Wall -Werror -I.

Q := @
VECHO = @printf

OBJS := console.o linenoise.o
deps := $(OBJS:%.o=.%.o.d)

$(TARGET): $(OBJS)
	$(VECHO) " LD\t$@\n"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o : %.c
	$(VECHO) " CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

clean:
	rm -f $(OBJS) $(deps) *~
	rm -rf *.dSYM *.out $(TARGET)

watch:
	watchmedo shell-command --command "make test" --pattern="*.c;*.h" --recursive --drop

-include $(deps)
