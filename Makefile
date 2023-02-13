# @author Austin Chen

PRINTF = env printf
PASS_COLOR = \e[32;01m
NO_COLOR = \e[0m

ifeq ("$(VERBOSE)", "1")
	Q :=
	VECHO = @true
else
	Q := @
	VECHO = @$(PRINTF)
endif

CFLAGS = -I./include
CFLAGS += -std=c99 -pedantic -Wall -Wextra -Werror

TESTS = \
	0001_two_sum \
	0020_valid_parentheses \
	t00_xor \
	ctci_ch01

TESTS := $(addprefix tests/test_,$(TESTS))
DEPS  := $(TESTS:%=%.d)
TESTS_OK := $(TESTS:=.ok)

check: $(TESTS_OK)

$(TESTS_OK): %.ok: %
	$(Q)$(PRINTF) "*** Validating build/tests/$(<F) ***\n"
	$(Q)./build/tests/$(<F) && $(PRINTF) "\t$(PASS_COLOR)[ Verified  ]$(NO_COLOR)\n"
	@mkdir -p build/ok
	@touch build/ok/$(@F)

# standard build rules
.SUFFIXES: .o .c
.c.o:
	$(VECHO) "  CC\t$@\n"
	@mkdir -p build/objs
	$(Q)$(CC) -o build/objs/$(@F) $(CFLAGS) -c -MMD -MF build/objs/$(@F).d $<

$(TESTS): %: %.o
	$(VECHO) "  LD\t$@\n"
	@mkdir -p build/tests
	$(Q)$(CC) -o build/tests/$(@F) build/objs/$(^F) $(LDFLAGS)

clean:
	$(VECHO) "  Cleaning...\n"
	rm -rf build
	$(Q)$(RM) $(TESTS) $(TESTS_OK) $(TESTS:=.o) $(DEPS)

-include $(DEPS)

.PHONY: all check clean
