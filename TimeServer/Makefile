SRCDIR=./src
INCDIR=./include
BINDIR=./bin
OBJDIR=./.obj

ifneq ($(MAKECMDGOALS), clean)
ifeq ($(LIBCERROR_PATH), )
$(error LIBCERROR_PATH not defined)
endif
ifeq ($(LIBCNET_PATH), )
$(error LIBCNET_PATH not defined)
endif
endif

LIBCERROR_INCLUDE = $(addprefix $(LIBCERROR_PATH)/, include)
LIBCERROR = $(addprefix $(LIBCERROR_PATH)/lib/, libcerror.a)

LIBCNET_INCLUDE = $(addprefix $(LIBCNET_PATH)/, include)
LIBCNET = $(addprefix $(LIBCNET_PATH)/lib/, libcnet.a)

CFLAGS = -I$(INCDIR) -I$(LIBCERROR_INCLUDE) -I$(LIBCNET_INCLUDE) -O1 -Wall -Werror


TIME_SERVER_ITERATIVE = $(addprefix $(BINDIR)/, timeserver_iterative)
TIME_SERVER_ITERATIVE_OBJ = $(addprefix $(OBJDIR)/, timeserver_iterative.o)

OBJ = $(TIME_SERVER_ITERATIVE_OBJ)


all: $(TIME_SERVER_ITERATIVE) 
.PHONY : all clean

$(OBJDIR) $(BINDIR):
	@if [ ! -d $@ ]; then echo "mkdir $@" && mkdir $@; fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ): | $(OBJDIR)

$(TIME_SERVER_ITERATIVE): $(TIME_SERVER_ITERATIVE_OBJ) | $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBCERROR) $(LIBCNET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
