
# TP4 : Jeu de Devinettes en Réseau

Ce projet est une implémentation simple d'un jeu de devinettes en réseau utilisant des sockets TCP. Les joueurs (clients) se connectent à un serveur et tentent de deviner un nombre généré aléatoirement par le serveur.

## Compilation

Pour compiler le serveur et le client, suivez ces étapes :

1. Ouvrez un terminal.
2. Naviguez vers le répertoire contenant les fichiers source.
3. Tapez `make` et appuyez sur Entrée.

La commande `make` compilera les fichiers source et générera deux exécutables : `serveur` et `client`.

## Exécution

Après la compilation, vous pouvez exécuter le serveur et les clients comme suit :

### Serveur

1. Pour démarrer le serveur, exécutez :
   ```
   ./serveur <port>
   ```
   Remplacez `<port>` par le numéro de port sur lequel vous souhaitez que le serveur écoute.

### Client

1. Pour connecter un client au serveur, exécutez :
   ```
   ./client <server_ip> <port>
   ```
   Remplacez `<server_ip>` par l'adresse IP du serveur et `<port>` par le numéro de port utilisé par le serveur.

## Fonctionnalités

- Le serveur peut gérer plusieurs connexions clients simultanément.
- Chaque client joue de manière indépendante avec le serveur.
- Le jeu consiste à deviner un nombre généré aléatoirement par le serveur dans une plage définie.
- Le client reçoit des indications si sa proposition est trop haute ou trop basse.

## Configuration

- Port par défaut : À spécifier lors de l'exécution du serveur.
- Nombre maximal de tentatives : Défini dans `common.h`.

## Détails par fichiers

### Client.c

#### Fonctionnalité :
- **Établissement de la connexion :** Ce code configure et connecte un client à un serveur en utilisant des sockets TCP.
- **Jeu de devinettes :** Le client participe à un jeu de devinettes après s'être connecté au serveur.

#### Points Clés :
- **Vérification des arguments :** Le programme s'assure que l'adresse IP du serveur et le port sont correctement passés en arguments.
- **Conversion et validation du port :** Utilisation de `convertPort` pour valider le numéro de port.
- **Gestion des erreurs :** Le programme gère les erreurs potentielles lors de la création de socket, de la connexion, etc.
- **Interaction utilisateur :** Le jeu de devinettes est géré par `jouerDevinette`, où le client peut entrer ses propositions.

### Serveur.c 

#### Fonctionnalité :
- **Attente de connexions client :** Le serveur se met en écoute sur un port spécifié et accepte les connexions entrantes.
- **Gestion des connexions client :** Chaque client connecté est géré dans un processus séparé.

#### Points Clés :
- **Validation du port :** Comme dans le client, le port est validé.
- **Création de sockets :** Le serveur crée un socket et le lie à une adresse et un port spécifiques.
- **Gestion de plusieurs clients :** Utilisation de `fork` pour gérer plusieurs clients simultanément.
- **Logique du jeu :** Chaque client joue un jeu de devinettes géré par `gererConnexion`.

### Common.h

#### Fonctionnalité :
- **Définitions communes :** Ce fichier contient des déclarations et des définitions communes utilisées à la fois par le client et le serveur.

#### Points Clés :
- **Inclusions :** Bibliothèques standard pour les opérations de réseau et de système.
- **Macros :** Définitions de constantes modifiables selon l'envie de difficulté du jeu etc.

### Fonctions.h

#### Fonctionnalité :
- **Déclarations de fonctions :** Ce fichier déclare des fonctions utilisées dans le jeu, telles que la génération de nombres aléatoires, la comparaison de propositions, etc.

#### Points Clés :
- **Prototypes de fonctions :** Déclarations des fonctions et documentation.
- **Documentation :** Commentaires expliquant le rôle de chaque fonction.

### Fonctions.c

#### Fonctionnalité :
- **Implémentation de la logique du jeu :** Ce fichier implémente la logique du jeu et la communication entre le client et le serveur.

#### Points Clés :
- **Génération de nombres aléatoires :** Implémentation de `genererNombreAleatoire` pour le jeu.
- **Gestion des propositions :** `traiterProposition` compare les propositions des clients avec le nombre mystère.
- **Communication réseau :** `envoyerReponse` et `gererConnexion` gèrent les échanges de données entre le serveur et le client.