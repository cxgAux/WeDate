CC 		:=		gcc
BUILD 		:= 		debug
TARGET		:=		../$(BUILD)/
SRCS 		:=	 	tcpserver.c
OBJS 		:=		$(addprefix $(TARGET),$(SRCS:%.c=%.o))
BINS		:=		$(OBJS:%.o=%)
INCLUDE 	:=		../Include 
LIBS		:=		../Lib
LDS		:=		unp log pthread
debug_FLAGS	:=		-O3 -ggdb
release_FLAGS	:=		-O2
CXXOPS		:=		-Wall -std=c++11 -D_REENTRANT $($(build)_FLAGS)
CXXFLAGS	:=		$(addprefix -I, $(INCLUDE)) $(addprefix -L, $(LIBS)) $(addprefix -l, $(LDS))
.PHONY : all
all : $(BINS)
$(TARGET)tcpserver : $(TARGET)tcpserver.o
	$(CC) $(CXXOPS) $< -o $@ $(CXXFLAGS) 
$(TARGET)%.o : %.c
	$(CC) $(CXXOPS )-c $< -o $@ $(CXXFLAGS)
.PHONY : clean
clean :
	rm $(OBJS)
