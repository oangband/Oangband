## Makefile.am -- Process this file with automake to process Makefile.in

AM_CFLAGS = -Wall

bin_PROGRAMS = oangband

WRES = windres

SUFFIXES = .rc
angband.res: angband.rc
	$(WRES) $< -O coff -o $@

oangband_SOURCES = \
  z-util.c z-virt.c z-form.c z-rand.c z-term.c z-file.c z-quark.c \
  z-msg.c \
  variable.c tables.c util.c cave.c \
  object1.c object2.c monster1.c monster2.c \
  xtra1.c xtra2.c spells1.c spells2.c \
  monmove.c monattk.c save.c files.c \
  cmd1.c cmd2.c cmd3.c cmd4.c cmd5.c cmd6.c \
  store.c birth.c load2.c \
  wizard1.c wizard2.c \
  main-gcu.c main-x11.c main.c \
  main-win.c \
  generate.c dungeon.c init1.c init2.c randart.c \
  squelch.c info.c attack.c \
  angband.h config.h defines.h externs.h h-basic.h \
  h-config.h init.h ui-event.h \
  types.h z-form.h z-rand.h z-term.h z-util.h z-quark.h \
  z-virt.h z-file.h z-msg.h main.h 

EXTRA_oangband_SOURCES = \
  main-sla.c \
  main-xxx.c main-crb.c \
  Makefile.bcc Makefile.cyg \
  Makefile.gtk \
  Makefile.lcc Makefile.std \
  Makefile.win Makefile.mpw Makefile.osx \
  angband.rc angband.ico readdib.c readdib.h

install-exec-hook:
if SET_GID
	chgrp "@GAMEGROUP@" "$(DESTDIR)$(bindir)/oangband"
	chmod g+s "$(DESTDIR)$(bindir)/oangband"
endif

