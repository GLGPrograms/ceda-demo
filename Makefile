SRC = \
	  src/ceda_print.c		\
	  src/entrypoint.c		\
	  src/main.c 			\
	  \

OBJ = $(patsubst %, %.o, $(basename $(SRC)))

ECHO	:=	@echo
QUIET	:=	@
OUTDIR	:=	build

$(OUTDIR)/main.prg: $(OUTDIR)/main.rom
	dd if=$< of=$@ bs=1 seek=2

$(OUTDIR)/main.rom: $(OBJ) | $(OUTDIR)
	zcc +z80 -create-app --no-crt -m -o $@ $?

%.o: %.c
	zcc +z80 -c -o $@ $<

%.o: %.asm
	zcc +z80 -c -o $@ $<

$(OUTDIR):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) -r $(OUTDIR)

