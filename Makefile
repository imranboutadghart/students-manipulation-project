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
	$(CC) $(CFLAGS) $(OBJ) -o etudgate

# Règle de nettoyage pour supprimer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJDIR)/*.o etudgate
	
# référence des variables
# $@ : nom de fichier de la cible de la règle.
# $^ : Les noms de tous les prérequis de la règle, séparés par des espaces et les doublons supprimés.
# $< : nom du premier prérequis de la règle.
# $? : Les noms de tous les prérequis qui sont plus récents que la cible, séparés par des espaces et les doublons supprimés.
# $* : la racine du nom du fichier cible, qui est toute partie du nom de fichier qui correspond au caractère générique % dans le modèle cible.


