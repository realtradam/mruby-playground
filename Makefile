
.PHONY: all
all: mruby/build/host/bin/mruby
	@echo " -- Done Building -- "

.PHONY: mruby
mruby: mruby/build/host/bin/mruby

mruby/build/host/bin/mruby: build_config.rb
	@echo " -- Building mruby -- "
	(cd mruby && MRUBY_CONFIG=../build_config.rb rake)

.PHONY: clean
clean:
	(cd mruby && rake clean)

.PHONY: run
run: mruby/build/host/bin/mruby
	./mruby/build/host/bin/mruby test_suite.rb
