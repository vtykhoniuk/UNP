SRCDIR=./src
INCDIR=./include
OBJDIR=./.obj

ifneq ($(MAKECMDGOALS), clean)
ifeq ($(LIBCERROR_PATH), )
$(error LIBCERROR_PATH not defined)
endif
endif

LIBCERROR_INCLUDE = $(addprefix $(LIBCERROR_PATH)/, include)
LIBCERROR = $(addprefix $(LIBCERROR_PATH)/lib/, libCError.a)

CFLAGS = -I$(INCDIR) -I$(LIBCERROR_INCLUDE) -O1 -Wall -Werror

_CNET = cnet
_LIBCNET = $(addprefix lib, $(_CNET))
LIBCNET = $(addprefix $(SRCDIR)/, $(_LIBCNET).a)
LIBCNET_OBJ = $(addprefix $(OBJDIR)/, $(_LIBCNET).o)
LIBCNETDEPS = $(addprefix $(INCDIR)/, $(_CNET).h)

OBJ = $(LIBCNET_OBJ)


all: lib
.PHONY : all clean

$(OBJDIR):
	@if [ ! -d $@ ]; then echo "mkdir $@" && mkdir $@; fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ): | $(OBJDIR)

lib: $(LIBCNET)

$(LIBCNET): $(LIBCNET_OBJ)
	$(AR) cr $@ $< $(LIBCERROR)

install: all
ifndef INSTALL_PREFIX
	$(error INSTALL_PREFIX not defined)
else
	cp $(LIBCNET) $(INSTALL_PREFIX)/lib/
	cp $(LIBCNETDEPS) $(INSTALL_PREFIX)/include/
endif

clean:
	rm -rf $(OBJDIR) $(LIBCNET)
