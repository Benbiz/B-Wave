CXX			=	g++

RM			=	rm -f

##CXXFLAGS	+=	-Wextra -Wall -Werror -std=c++11
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-I/opt/z-way-server/libzway/ -I/usr/local/include/ -I./
CXXFLAGS	+=	-I./socket.io/lib/websocketpp -I./socket.io/lib/rapidjson/include -I./socket.io/src -I./dist


LDFLAGS		=	-L/usr/local/lib -L/opt/z-way-server/libs/
LDLIBS		=	-lpthread -lxml2 -lz -lm -lcrypto -larchive -lboost_system
LDLIBS		+=	-lzway -lzcommons

NAME		=	B-Wave_client

SRCS		=	BWave.cpp										\
                                main.cpp                                                                        \
				Controller.cpp									\
                                Device.cpp                                                                      \
				DeviceRecord.cpp								\
				ZSwitchBinary.cpp								\
                                ZSensorMultiLevel.cpp                                                           \
                                ZSwitchMultiLevel.cpp                                                           \
				ZCallback.cpp									\
				ZSensorBinary.cpp								\
				ZSwitchColor.cpp								\
				Dispatcher.cpp									\
				ControllerEvent.cpp								\
				Connection.cpp									\
				MessageHandler.cpp								\
				CommandHandler.cpp								\
                                ControllerHandler.cpp                                                           \
                                ModuleListHandler.cpp                                                           \
				ScenarioHandler.cpp								\
				./dist/jsoncpp.cpp								\
                                ./socket.io/src/sio_client.cpp                                                  \
                                ./socket.io/src/sio_socket.cpp                                                  \
                ./socket.io/src/internal/sio_client_impl.cpp                                                    \
                ./socket.io/src/internal/sio_packet.cpp                                                         \
                                ScenarioMotor.cpp                                                               \
                                Scenario.cpp                                                                    \
                                TriggerTree.cpp

SRCSPRECOMP	=	stdafx.h

OBJS		= $(SRCS:.cpp=.o)
OBJSPRECOMP = $(SRCSPRECOMP:.h=.h.gch)

all:		$(NAME)

$(NAME):	$(OBJSPRECOMP) $(OBJS)
			$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean:
			$(RM) $(OBJSPRECOMP) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

#compiling the precompiled header
%.h.gch:%.h $(DEPSPRECOMP) $(CURRENTMAKEFILE)
	@echo "Precompiling header $@..."
	@$(CXX) $(CXXFLAGS) -o $@ -c $< || echo "error. Disabling precompiled header"
	@echo "...Done"

.PHONY: all clean fclean re
