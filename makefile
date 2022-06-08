define prnt
	$(SS)echo 	$(1)
endef

# first arg, library folder; second arg, object list
define clib
	$(SS)echo Compiling static library $(1)
	$(call prnt,Changing dir to $(1))
	$(SS)$(MAKE) -s -C $(1) mklib obj_folders='$(2)'
	$(call prnt,Returning to root directory)
endef

sources = $(wildcard src/*.cpp)
objects = $(patsubst %,bin/%.o,$(basename $(notdir $(sources))))

CC = clang++ -std=c++20
SS = @
obj = bin
dep_dir = $(obj)/deps
target = $(obj)/bin

ffl = $(obj) $(dep_dir)

ifeq ($(OS),Windows_NT)
	ffl := $(subst /,\,$(ffl))
endif

build: $(ffl) $(target)

run: build
	$(SS)$(target) test.ng

VPATH = src
bin/%.o: %.cpp
	$(SS)$(CC) -Wall -Werror -c $< -o $@ -MMD -MT $@ -MP -MF $(dep_dir)/$(notdir $*).d

include $(wildcard $(dep_dir)/*.d)

terwind/lib.a:
	$(call clib,terwind,terminal)

$(target): $(objects)
	$(SS)$(CC) $^ -o $@

clean:
	$(call prnt,Cleaning bin folder...)
ifeq ($(OS),Windows_NT)
	$(SS)del /S /Q bin\*
	$(SS)rmdir bin\deps bin
else
	$(SS)rm bin/*
endif

ifeq ($(OS),Windows_NT)
define make_dir
	-@if not exist $(1) mkdir $(1)
endef
else
define make_dir
	-@mkdir -p $(1)
endef
endif

$(ffl): 
	echo $@
	$(call make_dir,$@)