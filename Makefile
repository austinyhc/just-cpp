# .PHONY all check clean
# all: check

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
	test_util \
	0001_two_sum \
	0020_valid_parentheses \
	0136_single_number

TESTS := $(addprefix tests/,$(TESTS))

# string substitution)
# As an example, ./tests/0001_two_sum.c turns into ./tests/0001_two_sum.o.d
deps := $(TESTS:%=%.o.d)

TESTS_OK = $(TESTS:=.ok)

check: $(TESTS_OK)

$(TESTS_OK): %.ok: %
	$(Q)$(PRINTF) "*** Validating $< ***\n"
	$(Q)./$< && $(PRINTF) "\t$(PASS_COLOR)[ Verified  ]$(NO_COLOR)\n"
	@touch $@

# standard build rules
.SUFFIXES: .o .c
.c.o:
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF $@.d $<

$(TESTS): %: %.o
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(VECHO) "  Cleaning...\n"
	$(Q)$(RM) $(TESTS) $(TESTS_OK) $(TESTS:=.o) $(deps)

-include $(deps)
