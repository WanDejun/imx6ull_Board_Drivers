# Makefile
TARGET:=main
TARGET_bin:=$(TARGET).bin
TARGET_elf:=$(TARGET).elf
TARGET_dis:=$(TARGET).dis

CC:=arm-linux-gnueabihf-gcc
PP:=arm-linux-gnueabihf-g++ 
CFLAGS_CPP = -Wall -nostdlib -c
CFLAGS_C = -Wall -nostdlib -c

# 头文件路径
INCSDIR:=./bsp/
INCSDIR+=${shell ls -d ./bsp/*/}
INCSDIR+=./imx6ull/
INCSDIR+=./proj/

# 源文件根目录
SRCSROOT:=./

# 源文件路径
SRCSDIR:=./bsp/
SRCSDIR+=${shell ls -d ./bsp/*/}
SRCSDIR+=./imx6ull/
SRCSDIR+=./proj/

# obj文件夹
OBJSDIR:=./obj/

# 文件名列表
# include(.h)
INCS:=$(foreach dir,$(INCSDIR),-I$(dir))

# sources(.c/.cpp)
SRCS_CPP:=$(foreach dir,$(SRCSDIR),$(wildcard $(dir)*.cpp))
SRCS_C:=$(foreach dir,$(SRCSDIR),$(wildcard $(dir)*.c))
SRCS_S:=$(foreach dir,$(SRCSDIR),$(wildcard $(dir)*.s))

# objects(.o)
OBJS:=$(patsubst $(SRCSROOT)%.cpp,$(OBJSDIR)%.o,$(SRCS_CPP))
OBJS+=$(patsubst $(SRCSROOT)%.c,$(OBJSDIR)%.o,$(SRCS_C))
OBJS+=$(patsubst $(SRCSROOT)%.s,$(OBJSDIR)%.o,$(SRCS_S))

# depends(.d)
DEPS:=$(patsubst %.o,%.d,$(OBJS))

# ALL : 
# 	@echo $(TARGET_bin) $(TARGET_elf) $(TARGET_dis)
# 	@echo SRCS_CPP: $(SRCS_CPP)
# 	@echo SRCS_C: $(SRCS_C)
# 	@echo SRCS_S: $(SRCS_S)
# 	@echo OBJS: $(OBJS)
# 	@echo INCS: $(INCS)

#######################链接######################
$(TARGET_bin) : $(OBJS)
	@echo linking...
	arm-linux-gnueabihf-ld -Timx6ul.lds $^ -o $(TARGET_elf)
	arm-linux-gnueabihf-objcopy -O binary -S -g $(TARGET_elf) $@
	arm-linux-gnueabihf-objdump -D -m arm $(TARGET_elf) > $(TARGET_dis)
	@echo comlpete!

#######################编译######################

# 编译.cpp
# -MMD -MP 用于获取.d文件(头文件引用依赖文件)
$(OBJSDIR)%.o : %.cpp
	@echo compiling $<
	@mkdir -p $(dir $@)
	$(PP) -MMD -MP $(CFLAGS_CPP) -c $(INCS) $< -o $@ 

# 编译.c
$(OBJSDIR)%.o : %.c
	@echo compiling $<
	@mkdir -p $(dir $@)
	$(CC) -MMD -MP $(CFLAGS_C) -c $(INCS) $< -o $@ 

# 编译.s
$(OBJSDIR)%.o : %.s
	@echo compiling $<
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_C) -c $< -o $@ 

# 处理依赖
-include $(DEPS)


.PHONY : clean
# 清理中间文件
clean:
	@echo try to clean...
	@rm -rf $(shell ls -d ./obj/*/) 
	@rm -rf $(TARGET_bin) $(TARGET_elf) $(TARGET_dis)
	@echo complete!

.PHONY : download
# 清理中间文件
download:
	@echo download...
	./imxdownload $(TARGET_bin) /dev/sdb
	@echo complete!