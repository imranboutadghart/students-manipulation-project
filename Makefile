# Définir les variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCDIR = src
INCDIR = headers
OBJDIR = build

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

# Définir la variable d'en-tête
HEADERS = $(wildcard $(INCDIR)/*.h)

# Construire une règle pour les fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction pour l'exécutable
etudgate: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJDIR)/etudgate

# Règle de nettoyage pour supprimer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/etudgate
