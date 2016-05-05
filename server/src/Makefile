CC 		:=		g++
BUILD 		:= 		debug
TARGET		:=		../$(BUILD)/
SRCS 		:=	 	respondtcpsrv.cpp
OBJS 		:=		$(addprefix $(TARGET),$(SRCS:%.cpp=%.o))
BINS		:=		$(OBJS:%.o=%)
INCLUDE 	:=		../Include 
LIBS		:=		../Lib
LDS		:=		unp log
debug_FLAGS	:=		-O3 -ggdb
release_FLAGS	:=		-O2
CXXOPS		:=		-Wall -std=c++11 -DCXG $($(build)_FLAGS)
CXXFLAGS	:=		$(addprefix -I, $(INCLUDE)) $(addprefix -L, $(LIBS)) $(addprefix -l, $(LDS))
.PHNOY : all
all : $(BINS)
$(TARGET)respondtcpsrv : $(TARGET)respondtcpsrv.o
	$(CC) $(CXXOPS) $< -o $@ $(CXXFLAGS) 
$(TARGET)%.o : %.cpp
	$(CC) $(CXXOPS )-c $< -o $@ $(CXXFLAGS)
.PHNOY : clean
clean :
	rm $(OBJS)
