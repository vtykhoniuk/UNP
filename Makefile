DIRS = $(shell ls -d */)

all: libs bins

libs: CHelper CArray

bins: RotateMatrix EchoServer TimeServer

CHelper CArray: force_look
	@cd ./$@ && $(MAKE) install

RotateMatrix EchoServer TimeServer: force_look
	@cd ./$@ && $(MAKE)

clean: force_look
	@for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	@true
