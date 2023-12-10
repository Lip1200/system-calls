### Pizzeria

#### Objectif et Structure du Programme
Le programme de gestion de pizzeria simule un environnement où des pizzas sont préparées (`cook.c`), stockées sur un rack (`P_rack`), et ensuite servies (`server.c`). La synchronisation entre les processus de cuisson et de service est gérée à travers des sémaphores et de la mémoire partagée.

#### `cook.c` - Cuisinier
- **Fonctionnalités Principales**:
  - Prépare les pizzas et les place sur un rack.
  - Utilise des sémaphores pour gérer l'espace disponible sur le rack et la disponibilité des pizzas.

- **Synchronisation et Communication Inter-processus (IPC)**:
  - Crée une mémoire partagée pour représenter le rack de pizzas.
  - Emploie des sémaphores pour coordonner la disponibilité des places sur le rack et la préparation des pizzas.

- **Gestion d'Erreurs**:
  - Vérifie les erreurs pour les opérations de mémoire partagée et de sémaphore.
  
- **Nettoyage des Ressources**:
  - Libère les sémaphores et détache la mémoire partagée après utilisation.

#### `server.c` - Serveur
- **Fonctionnalités Principales**:
  - Sert les pizzas du rack.
  - Accède au rack de pizzas via la mémoire partagée partagée avec le processus cuisinier.

- **Synchronisation et IPC**:
  - Ouvre les mêmes objets sémaphores que le cuisinier pour la coordination.
  - Mape la mémoire partagée pour suivre l'état actuel des pizzas sur le rack.

- **Gestion d'Erreurs**:
  - Contrôle les erreurs liées à l'accès à la mémoire partagée et aux opérations de sémaphore.

- **Nettoyage des Ressources**:
  - Nettoie les sémaphores et la mémoire partagée en fin d'exécution.

#### `pizza_rack.h`
- **Définitions**:
  - Déclare la structure `P_rack` pour le stockage des pizzas.
  - Inclut les bibliothèques nécessaires pour la mémoire partagée, les sémaphores, et les fonctions standard.

