# $Id: GNUmakefile 68058 2013-03-13 14:47:43Z gcosmo $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := gamma
G4TARGET := $(name)
G4EXLIB := true

CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS = $(shell $(ROOTSYS)/bin/root-config --glibs)
EXTRALIBS += $(ROOTLIBS)

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

