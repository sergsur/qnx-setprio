ifndef QCONFIG
QCONFIG = qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION=Priority assignment tool
endef

NAME = setprio

EXTRA_SRCVPATH =                                                                \
    $(PROJECT_ROOT)/src/

CCFLAGS = -Werror -O2 -D_FORTIFY_SOURCE=2

include $(MKFILES_ROOT)/qtargets.mk
