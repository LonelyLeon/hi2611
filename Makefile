#
##  ¹¤³Ì¸ùMakefile
#

all: $(MAKE_MODULES)
	@echo $^

platform:
	$(MAKE) -C $(WORKROOT)/platform
	
project:
	$(MAKE) -C $(WORKROOT)/project/$(PROJECT)
	./release.sh
loader:
	$(MAKE) -C $(WORKROOT)/loader

clean:
	$(if $(filter project, $(MAKE_MODULES)), \
	     $(MAKE) -C $(WORKROOT)/project/$(PROJECT) clean)
	$(if $(filter platform, $(MAKE_MODULES)), \
	     $(MAKE) -C $(WORKROOT)/platform clean)
	$(if $(filter loader, $(MAKE_MODULES)), \
	     $(MAKE) -C $(WORKROOT)/loader clean)

platform_clean:
	$(MAKE) -C $(WORKROOT)/platform clean
project_clean:
	$(MAKE) -C $(WORKROOT)/project/$(PROJECT) clean
loader_clean:
	$(MAKE) -C $(WORKROOT)/loader clean

.PHONY: all clean platform project loader platform_clean project_clean loader_clean
