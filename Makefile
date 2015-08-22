DIRS = $(shell ls -d */)

clean: force_look
	@for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

force_look:
	@true
