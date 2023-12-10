# Wonderful Interactive SHell (WI$H)

## Description

The Wonderful Interactive SHell (WISH) is a custom shell that provides basic UNIX shell functionality, including support for built-in commands, background and foreground job control, and an interactive interface for users.

## Features

- **Built-in Commands**: `cd` for changing directories and `exit` to quit the shell.
- **Job Control**: Supports background and foreground job management.
- **Interactive Interface**: Optionally uses the `readline` library for an enhanced user experience.

## Installation

To install and run the WISH shell:

1. Download the source files to your preferred directory.
2. Open a terminal and navigate to the directory containing the source files.
3. Compile the program using `make`:
   ```bash
   make
   ```
4. Run the compiled shell:
   ```bash
   ./wish
   ```

## Usage

Once the shell is running, you can execute standard UNIX commands along with the built-in commands `cd` and `exit`.

## Development

### Project Structure

- `main.c`: The main entry point of the shell.
- `func.h`: Function declarations and structures used.
- `func.c`: Implementation of the functions declared in `func.h`.
- `Makefile`: Script to compile the shell.

### Signal Handling

- **SIGINT (Ctrl-C)**: Interrupts the foreground process.
- **SIGHUP**: Terminates the shell and all associated processes.
- **SIGCHLD**: Handles background processes.

### Parsing and Execution

The shell parses user input and executes it using `fork` and `exec`.

## Limitations and Future Improvements

- **Pipes and Redirection**: Not yet implemented.
- **Shell Scripts**: No support for executing scripts yet.
- **Compatibility**: Primarily tested on UNIX systems; compatibility with other systems is not guaranteed.

## Author

- **Filipe Ramos**

## References

- UNIX manuals and `readline` library documentation.
- Course materials from Professor Guillaume Chanel, Fall 2023 semester.

## Version

- WISH version 1.0

## Goals

The primary goal of this project was to create a minimalist but functional shell capable of executing built-in commands and managing jobs. It also aims to provide an interactive user experience, potentially using the `readline` library to enhance interactions.

## Design and Architecture

The shell is divided into several key components:

1. **Main (main.c)**: The entry point of the program, responsible for initializing the shell, handling user input, and invoking the appropriate functions to execute commands.

2. **Functions (func.c and func.h)**: These files define and implement the functions necessary for the shell's operations, including signal handling, command execution, and input parsing.

3. **Signal Handling**: The shell manages signals such as SIGINT to interrupt foreground processes and SIGCHLD to monitor background processes.

4. **Parsing and Execution**: The shell parses user input and executes commands using system calls like `fork` and `exec`.

## Implemented Features

- **Built-in Commands**: `cd` for changing directories and `exit` to quit the shell.
- **Job Management**: Supports one foreground and one background job.
- **Interactive User Interface**: Conditional use of the `readline` library for a better user experience.

## Challenges and Solutions

- **Signal Management**: Handling signals, especially SIGINT and SIGCHLD, required special attention to ensure that the shell behaves correctly when interrupting processes and managing background jobs.
- **Compatibility**: The shell has been primarily tested on UNIX systems. Additional testing is required to ensure compatibility across different platforms.

## Limitations and Areas for Improvement

- **Redirection and Pipes**: Support for redirection and pipes is not yet implemented. This could be a significant future improvement.

## Conclusion

The WI$H project represents an important step in understanding and implementing the basic functionality of a UNIX shell. While there are still areas to improve, the shell provides a foundation for further exploration into operating systems and command-line interfaces.

#French

## Description

Le Wonderful Interactive SHell (WISH) est un shell personnalisé qui offre des fonctionnalités de base de shell UNIX, y compris la prise en charge des commandes intégrées, la gestion des travaux en arrière-plan et en avant-plan, et une interface interactive pour les utilisateurs.

## Fonctionnalités

- **Commandes intégrées**: `cd` pour changer de répertoire et `exit` pour quitter le shell.
- **Gestion des travaux**: Supporte un travail en avant-plan et en arrière-plan.
- **Interface interactive**: Possibilité d'utiliser la bibliothèque `readline` pour une expérience utilisateur améliorée.

## Installation

Pour installer et exécuter le shell WISH :

1. Téléchargez les fichiers source dans un dossier de votre choix.
2. Ouvrez un terminal et naviguez vers le dossier contenant les fichiers source.
3. Compilez le programme en utilisant `make`:
   ```bash
   make
   ```
4. Exécutez le shell compilé :
   ```bash
   ./wish
   ```

## Utilisation

Une fois le shell lancé, vous pouvez exécuter des commandes UNIX standard ainsi que les commandes intégrées `cd` et `exit`.

## Développement

### Structure du Projet

- `main.c`: Point d'entrée principal du shell.
- `func.h`: Déclarations des fonctions et structures utilisées.
- `func.c`: Implémentation des fonctions déclarées dans `func.h`.
- `Makefile`: Script pour compiler le shell.

### Gestion des Signaux

- **SIGINT (Ctrl-C)**: Interrompt le processus en avant-plan.
- **SIGHUP**: Termine le shell et tous les processus associés.
- **SIGCHLD**: Gère les processus en arrière-plan.

### Parsing et Exécution

Le shell parse les entrées utilisateur et les exécute en utilisant `fork` et `exec`.

## Limitations et Améliorations Futures

- **Pipes et Redirection**: Ces fonctionnalités ne sont pas encore implémentées.
- **Scripts Shell**: Le support pour l'exécution de scripts n'est pas encore disponible.
- **Compatibilité**: Testé principalement sur des systèmes UNIX; la compatibilité avec d'autres systèmes n'est pas garantie.

## Auteur

- **Filipe Ramos**

## Références

- Manuels UNIX et documentation de la bibliothèque `readline`.
- Cours du professeur Guillaume Chanel, semestre d'automne 2023

## Version

- WISH version 1.0

## Objectifs

L'objectif principal de ce projet était de créer un shell minimaliste mais fonctionnel, capable d'exécuter des commandes intégrées et de gérer des travaux. Il vise également à offrir une expérience utilisateur interactive, en utilisant potentiellement la bibliothèque `readline` pour améliorer les interactions.

## Conception et Architecture

Le shell est divisé en plusieurs composants clés :

1. **Main (main.c)** : Le point d'entrée du programme qui initialise le shell, gère les entrées de l'utilisateur et appelle les fonctions appropriées pour l'exécution des commandes.

2. **Fonctions (func.c et func.h)** : Ces fichiers définissent et implémentent les fonctions nécessaires pour les opérations du shell, y compris la gestion des signaux, l'exécution de commandes, et le parsing des entrées utilisateur.

3. **Gestion des signaux** : Le shell gère les signaux tels que SIGINT pour interrompre les processus en avant-plan et SIGCHLD pour surveiller les processus en arrière-plan.

4. **Parsing et exécution** : Le shell analyse les entrées de l'utilisateur et exécute les commandes en utilisant les appels système `fork` et `exec`.

## Fonctionnalités Implémentées

- **Commandes intégrées** : `cd` pour changer de répertoire et `exit` pour quitter le shell.
- **Gestion des travaux** : Prise en charge d'un travail en avant-plan et en arrière-plan.
- **Interface utilisateur interactive** : Utilisation conditionnelle de la bibliothèque `readline` pour une meilleure expérience utilisateur.

## Défis et Solutions

- **Gestion des signaux** : La gestion des signaux, en particulier SIGINT et SIGCHLD, a nécessité une attention particulière pour s'assurer que le shell se comporte correctement lors de l'interruption des processus et de la gestion des travaux en arrière-plan.
- **Compatibilité** : Le shell a été testé principalement sur des systèmes UNIX. Des tests supplémentaires sont nécessaires pour assurer la compatibilité sur différentes plateformes.

## Limitations et Pistes d'Amélioration

- **Redirections et Pipes** : La prise en charge des redirections et des pipes n'est pas encore implémentée. Cela pourrait être une amélioration future significative.

## Conclusion

Le projet WI$H représente une étape importante dans la compréhension et l'implémentation des fonctionnalités de base d'un shell UNIX. Bien qu'il reste des domaines à améliorer, le shell offre une base pour une exploration plus approfondie des systèmes d'exploitation et de l'interface de ligne de commande.
