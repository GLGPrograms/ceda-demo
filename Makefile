PROJECT := demo

SRC = \
	  src/ceda_print_a.asm	\
	  src/ceda_print_c.c	\
	  src/cursor.c          \
	  src/delay.asm         \
	  src/main.c 			\
	  src/io_a.c            \
	  \

OBJ = $(patsubst %, %.o, $(basename $(SRC)))

ECHO	:=	@echo
QUIET	:=	@
OUTDIR	:=	build

$(OUTDIR)/$(PROJECT).prg: $(OUTDIR)/$(PROJECT)_code_compiler.bin
	echo -n -e '\x00\x10' > $@
	cat $< >> $@

$(OUTDIR)/$(PROJECT)_code_compiler.bin: $(OBJ) | $(OUTDIR)
	zcc +conf.cfg \
		-crt0=src/crt.asm \
		-m -o $(OUTDIR)/$(PROJECT) $(OBJ)

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

