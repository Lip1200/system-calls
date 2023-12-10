# File Locking Management in C

## Description

This project implements a file locking system in C, allowing users to apply and remove locks on specific sections of a file interactively. The program uses `fcntl()` to manage locks, offering more control over file sections compared to `flock()`.

## Compilation

To compile the project, follow these steps:

1. **Open a terminal** in the project's directory.
2. **Compile the project** using the provided Makefile:
   ```bash
   make
   ```
3. **Run the program**:
   ```bash
   ./locker filename
   ```

## Cleaning Up

To remove compiled files:

```bash
make clean
```

## Usage Example

The program allows the user to interactively lock or unlock sections of a file:

```
$ ./locker file.txt
Enter '?' for help and 'q' to quit
```

## License

This project is licensed under the MIT License.

# Gestion des Verrous de Fichier en C

Ce projet implémente un système de gestion de verrous de fichier en C, permettant de poser et de retirer des verrous sur des sections spécifiques d'un fichier de manière interactive.

## Compilation du Projet

Pour compiler ce projet, utilisez le Makefile inclus. Assurez-vous d'avoir un environnement de compilation C comme GCC installé sur votre machine.

### Étapes pour Compiler :

1. **Ouvrez un terminal** :

   - Ouvrez un terminal dans le répertoire contenant les fichiers source du projet.

2. **Exécutez la commande make** :

   - Dans le terminal, tapez la commande suivante pour compiler le projet :
     ```
     make
     ```
   - Cette commande va lire le Makefile et exécuter les instructions de compilation spécifiées.

3. **Exécuter le programme** :
   - Après la compilation, un exécutable nommé `locker` sera créé.
   - Pour exécuter le programme, utilisez :
     ```
     ./locker nom_du_fichier
     ```
     Remplacez `nom_du_fichier` par le chemin d'accès au fichier que vous souhaitez verrouiller/déverrouiller.

### Nettoyage :

- Pour supprimer les fichiers objets et l'exécutable généré par le Makefile, utilisez la commande :
  ```
  make clean
  ```
