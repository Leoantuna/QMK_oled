OLED_ENABLE = yes
WPM_ENABLE  = yes        # Ocean usa WPM, lo dejamos por ahora

# Solo esta animación
SRC += ocean_dream.c
# SRC += luna.c
# SRC += bongocat.c

# Optimizaciones de tamaño
 LTO_ENABLE        = yes
CONSOLE_ENABLE    = no
COMMAND_ENABLE    = no
MOUSEKEY_ENABLE   = no
BOOTMAGIC_ENABLE  = no
MIDI_ENABLE       = no
AUDIO_ENABLE      = no
STENO_ENABLE      = no
SPACE_CADET_ENABLE = no
MAGIC_ENABLE      = no
