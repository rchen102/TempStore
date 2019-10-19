M=pro1
P1=AlTaken
P2=AlNonTaken
P3=Bimodal
P5=Gshare
P6=Tournament
CFLAGS=-g -Wall -std=c++14

all: $(M)

$(M) : $(M).o $(P1).o $(P2).o $(P3).o $(P5).o $(P6).o
	g++ $(CFLAGS) $(M).o $(P1).o $(P2).o $(P3).o $(P5).o $(P6).o -o $(M)

$(M).o : $(M).cpp $(P1).h $(P2).h $(P3).h $(P5).h $(P6).h
	g++ $(CFLAGS) -c $(M).cpp -o $(M).o

$(P1).o : $(P1).cpp $(P1).h
	g++ $(CFLAGS) -c $(P1).cpp -o $(P1).o

$(P2).o : $(P2).cpp $(P2).h
	g++ $(CFLAGS) -c $(P2).cpp -o $(P2).o

$(P3).o : $(P3).cpp $(P3).h
	g++ $(CFLAGS) -c $(P3).cpp -o $(P3).o

$(P5).o : $(P5).cpp $(P5).h
	g++ $(CFLAGS) -c $(P5).cpp -o $(P5).o

$(P6).o : $(P6).cpp $(P6).h
	g++ $(CFLAGS) -c $(P6).cpp -o $(P6).o


run: all
	./$(M)

clean:
	rm -rf *.o $(P)

memcheck: all
	valgrind --leak-check=full ./$(M)

