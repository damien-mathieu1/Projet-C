CC=gcc
CFLAGS=`pkg-config --cflags glib-2.0 sqlite3 gmp`
LIBS=`pkg-config --libs glib-2.0 sqlite3 gmp` 

AR=ar
ARFLAGS=rcs
BUILDDIR=../build
SRCDIR=.
LIBDIR=$(BUILDDIR)/lib
OBJDIR=$(BUILDDIR)/obj
LIBNAME=libvoting.a
DEPS= serveur_vote.c bd.c crypto.c threadpool.c

# Liste de tous les fichiers source
SRC := $(wildcard $(SRCDIR)/*.c)

# Conversion des fichiers source en .o
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Crée les répertoires de build si nécessaire
$(shell mkdir -p $(LIBDIR) $(OBJDIR))

# Cible par défaut
all: $(LIBDIR)/$(LIBNAME) $(BUILDDIR)/main $(DEPS)

$(BUILDDIR)/main: serveur_vote.c
	$(CC) serveur_vote.c $(CFLAGS) $(PROJECTLIBDIR) $(PROJECTLIB) $(LIBS) -lgmp -o $(BUILDDIR)/main 

	
# Règle pour construire la bibliothèque
$(LIBDIR)/$(LIBNAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Règle pour construire les fichiers objet
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cible pour nettoyer le projet
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
