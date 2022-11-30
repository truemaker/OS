; C declaration: void flush_tss(void);
[bits 32]
[global flush_tss]
flush_tss:
	mov ax, 0x28 | 0 ; fifth 8-byte selector, symbolically OR-ed with 0 to set the RPL (requested privilege level).
	ltr ax
	ret