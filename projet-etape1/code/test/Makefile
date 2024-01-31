CC=gcc
CFLAGS=`pkg-config --cflags glib-2.0 sqlite3 gmp`
LIBS=`pkg-config --libs glib-2.0 sqlite3 gmp` 
BUILDDIR=../build
PROJECTLIBDIR=-L../build/lib
PROJECTLIB=-lvoting


$(shell mkdir -p $(BUILDDIR))

all: $(BUILDDIR)/test_electeur $(BUILDDIR)/test_election $(BUILDDIR)/test_vote $(BUILDDIR)/test_command_electeur $(BUILDDIR)/test_crypto $(BUILDDIR)/test_future

$(BUILDDIR)/test_future: test_future.c
	$(CC) test_future.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -o $(BUILDDIR)/test_future

$(BUILDDIR)/test_electeur: test_electeur.c
	$(CC) test_electeur.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -o $(BUILDDIR)/test_electeur

$(BUILDDIR)/test_election: test_election.c
	$(CC) test_election.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -o $(BUILDDIR)/test_election

$(BUILDDIR)/test_vote: test_vote.c
	$(CC) test_vote.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -o $(BUILDDIR)/test_vote

$(BUILDDIR)/test_command_electeur: test_command_electeur.c
	$(CC) test_command_electeur.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -o $(BUILDDIR)/test_command_electeur

$(BUILDDIR)/test_crypto: test_crypto.c
	$(CC) test_crypto.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -o $(BUILDDIR)/test_crypto

clean:
	rm $(BUILDDIR)/test_vote; rm $(BUILDDIR)/test_election; rm $(BUILDDIR)/test_electeur; rm $(BUILDDIR)/test_command_electeur; rm $(BUILDDIR)/test_crypto
