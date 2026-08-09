# Z80 / SDCC Makefile

TARGET = $(notdir $(CURDIR))

BUILD_DIR = build

# Cコンパイラ
SDCC = sdcc
# アセンブラ
SDASZ80 = sdasz80
# リンカ
SDLDZ80 = sdldz80
# バイナリ変換
MAKEBIN = makebin
# 逆アセンブラ
DISASM = z80dasm

CRT0_SRC = $(wildcard *.s) 
C_SRC = $(wildcard Src/*.c)

CRT0_REL = $(BUILD_DIR)/$(CRT0_SRC:.s=.rel)
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SRC:.c=.rel)))

CODE_ADDR = 0x0200
DATA_ADDR = 0x8000

.PHONY: all clean
.SECONDARY:

all: $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).dis
clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.ihx | $(BUILD_DIR)
	$(MAKEBIN) -p $< $@

$(BUILD_DIR)/$(TARGET).ihx: $(CRT0_REL) $(OBJECTS) | $(BUILD_DIR)
	$(SDCC) -mz80 --no-std-crt0 --code-loc $(CODE_ADDR) --data-loc $(DATA_ADDR) $(CRT0_REL) $(OBJECTS) -o $@

$(BUILD_DIR)/%.rel: $(BUILD_DIR)/%.asm Makefile | $(BUILD_DIR)
	$(SDASZ80) -l -o $@ $<

$(BUILD_DIR)/%.asm: Src/%.c Makefile | $(BUILD_DIR)
	$(SDCC) -mz80 -S -o $@ $<

$(CRT0_REL): $(CRT0_SRC) Makefile| $(BUILD_DIR)
	$(SDASZ80) -l -o $@ $<

$(BUILD_DIR)/%.dis: $(BUILD_DIR)/%.bin | $(BUILD_DIR)
	$(DISASM) -a -l -t -g 0x0000 -o $@ $<
