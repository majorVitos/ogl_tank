NAME=gltank
OBJ=main.o elements.o t34.o	tga.o

LIBS=-lopengl32 -lglut32win





CFLAGS=-g
CXXFLAGS=-g




all: $(NAME)


$(NAME): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS) $(LDLIBS)






clean:
	rm -f *.o



