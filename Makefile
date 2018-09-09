dirs = $(shell find * -mindepth 1 -maxdepth 1 -name Makefile -printf '%H\n')
cleans = $(dirs:%=clean-%)

all: $(dirs)

clean: $(cleans)

$(dirs):
	$(MAKE) -C $@

$(cleans):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: all clean $(dirs) $(cleans)
