TARGET = fetcher

CC = gcc
CFLAGS = -O1 -g -Wall -Werror -I.
LIBS = -lcurl -lm -lcjson

Q := @
VECHO = @printf

OBJS := fetcher.o
deps := $(OBJS:%.o=.%.o.d)

$(TARGET): $(OBJS)
	$(VECHO) " LD\t$@\n"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o : %.c
	$(VECHO) " CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

clean:
	rm -f $(OBJS) $(deps) *~
	rm -rf *.dSYM *.out $(TARGET)

watch:
	watchmedo shell-command --command "make test" --pattern="*.c;*.h" --recursive --drop

-include $(deps)
