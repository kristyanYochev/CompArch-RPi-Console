    .section .rodata
    .global _font_data
    .type _font_data, @object
    .align 4
_font_data:
    .incbin "../src/font.psf"
    .global _font_data_size
    .type _font_data_size, @object
    .align 4
_font_data_size:
    .int _font_data_size - _font_data
