PROJECT := demo

SERIALPORT = /dev/ttyUSB0

SRC = \
	  assets/ctree.c        \
	  assets/fvb.c          \
      assets/glg.c          \
	  assets/hello.c        \
	  assets/rudolph.c      \
	  src/audio.c           \
	  src/cge.c             \
	  src/crt.c             \
	  src/ctc.c             \
	  src/ctc_a.asm         \
	  src/cursor.c          \
	  src/delay.asm         \
	  src/demo.c            \
	  src/flipflap.c        \
	  src/io_a.c            \
	  src/lfsr.c            \
	  src/magiccursor.c     \
	  src/main.c 			\
	  src/matrix.c          \
	  src/mmap.c            \
	  src/performance_test.asm \
	  src/printf.c          \
	  src/snow.c            \
	  src/string.c          \
	  src/video_a.asm		\
	  src/video.c			\
	  \

OBJ = $(patsubst %, %.o, $(basename $(SRC)))

ECHO	:=	@echo
QUIET	:=	@
OUTDIR	:=	build

.PHONY: all
all: $(OUTDIR)/$(PROJECT).prg $(OUTDIR)/$(PROJECT).com

$(OUTDIR)/$(PROJECT).com: $(OUTDIR)/$(PROJECT)-cpm_code_compiler.bin
	cp $< $@

$(OUTDIR)/$(PROJECT).prg: $(OUTDIR)/$(PROJECT)-bios_code_compiler.bin
	echo -n -e '\x00\x01' > $@
	cat $< >> $@

$(OUTDIR)/$(PROJECT)-cpm_code_compiler.bin: $(OBJ) crt/cpm.asm | $(OUTDIR)
	zcc +conf.cfg \
		-crt0=crt/cpm.asm \
		-m -o $(OUTDIR)/$(PROJECT)-cpm $(OBJ)

$(OUTDIR)/$(PROJECT)-bios_code_compiler.bin: $(OBJ) crt/bios.asm | $(OUTDIR)
	zcc +conf.cfg \
		-crt0=crt/bios.asm \
		-m -o $(OUTDIR)/$(PROJECT)-bios $(OBJ)

%.o: %.c
	zcc +z80 -c -o $@ $<

%.o: %.asm
	zcc +z80 -c -o $@ $<

%.pkt: %.prg
	script/makepacket.py $< > $@

$(OUTDIR):
	mkdir -p $@

.PHONY: send
send: $(OUTDIR)/$(PROJECT).pkt
	stty -F $(SERIALPORT) 9600 crtscts
	script/sendpacket.py < $<

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) -r $(OUTDIR)

