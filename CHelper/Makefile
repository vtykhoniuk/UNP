LIB_NAME    = libchelper
LIB_INC     = CHelper.h
LIB_PIECES  = CError Strtol wrapers linkedlist strsplit signal sock_ntop sock_read sock_write sock_readline
include ../Make.lib

_install:
	mkdir -p $(INSTALL_PREFIX)/include/ADS
	$(INSTALL) ADS/linkedlist.h $(INSTALL_PREFIX)/include/ADS
	$(INSTALL) ADS/linkedstack.h $(INSTALL_PREFIX)/include/ADS
